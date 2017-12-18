// Add Escape keys to user menu's
// Fix _LATB8 not connected to output pin

#include    "system.h"
#include    "menu.h"
#include    "coffee.h"
// *****************************************************************************
#define piezoOutput             _LATA1          //FIX        // Output to turn on Piezo, if Brew switch left on too long, or water level too low  Add option for user to disable
#define backLightOFF            _LATA9                  // Backlight is active LOW, so "0" is "ON", "1" is "OFF" Pin 35
#define airPump                 _LATA11                 // Run air pump for bubbler for Water Tank Level
#define pumpOutput              OC1R                    // OC1 will drive water pump
#define boilerOutput            OC2R                    // OC2 will drive Water Boiler
#define steamOutput             OC3R                    // OC3 will drive Steam Boiler
#define groupOutput             _LATB8                  // Coded for software PWM
#define brewSolenoid            _LATA3                  // Control the Water delivery Solenoid
#define steamSolenoid           _LATA2                  // Control the Steam delivery Solenoid

// *************** Inputs ******************************************************
//#define waterLevel              level                   // ADCRead(6) is Water Tank level signal
//#define readButtons           ADCRead(7)              // ADC Input to read Button press (User Input Keys) on _RC1 (AN7) Pin 26 

#define boilerTemperature       temp[0]                 // ADCRead(9)
#define steamTemperature        temp[1]                 // ADCRead(0)
#define GroupHeadTemp           temp[2]                 // ADCRead(4)

#define power                   bits[0]                 // _RB11 Power switch input state  
#define brewSwitch              bits[1]                 // _RB10 Brew Switch Input
#define steamSwitch             bits[2]                 // _RA7  Steam Switch Input          
#define waterSwitch             bits[3]                 // _RC9  Water Switch Input          

#define powerSwitch             bits[4]                 // Power Switch (Soft Bit)
#define lastPowerState          bits[5]                 // Last State of powerSwitch (Soft Bit)
#define blink                   bits[6]                 // blink flashes display when water level low
       
// *****************************************************************************

//**************** Timer2 set in pwm.c (Timer2 Runs the Shot Counter) **********
// All times are in 1/10th's of a second, so 10 = 1 seconds, 30 = 3 seconds, 15 = 1.5 seconds, etc 

#define max                     256                     // Maximun Pump Output (256 = 100%)
#define min                     26                      // Minimum Pump Output (0 = OFF)
#define preInfusionDutyCycle    40              //FIX   // This needs to move to EEPROM & have a User Interface set up so user can change it
#define preInfusionTime         (20)            //FIX   // length of time to run pump to preInfuse puck (also needs Interface & EEPROM location)
#define soakTime                (preInfusionTime + 20)//FIX    // Length of time for wetted puck to soak EEPROM
#define startRamp               (soakTime + 25)//FIX    // StartRamp starts pump and Ramps up to Max Pressure
#define continuePull            (800 + 1)               // Shot duration, 80 seconds from Start of Cycle(801)
#define warning                 (850 + 1)               // Turn on Warning Piezo, reminder to turn off switch (851)
#define steamPumpPower          12                      // DutyCycle to run pump during steam cycle

#define waterSetpoint           eepromGetData(setpoint[0])
#define steamSetpoint           eepromGetData(setpoint[1])
#define groupHeadSetpoint       eepromGetData(setpoint[2])

#define WaterPID                PIDValue[0]
#define SteamPID                PIDValue[1]
#define GroupHeadPID            PIDValue[2]


#define shotProgressCounter     counter[0]              // Timer for Steps in an extraction
#define shotTimer               counter[1]              // Times the duration of the extraction 
#define warningTimer            counter[2]              // Initiate Piezo Warning if Brew switch not turned OFF
#define shotDisplayTimer        counter[3]              // Determines how long the Shot Timer Value remains on the Display
#define backLightCounter        counter[4]              // Used to count time until Backlight turns Off
#define groupPeriodCounter      counter[5]              // Group PID Period Counter
#define steamPumpRunCounter     counter[6]              // Counter for how long to run pump after steam switch is turned on
#define lowWaterReminder        counter[7]              // Remind User level is Low when below 25%
#define numSamples              200                     // Number of samples to average for temp[] readings 
#define PIDDuration             200                     // Number of Program cycles (Period) for Group Head PID
    

// *************** Global Variables ********************************************
int __attribute__ ((space(eedata))) Settings[43];       // Global variable located in EEPROM (created by the space()attribute

RTCTime time;                                           // declare the type of the time object

unsigned int setpoint[] =   {0, 2,  4};                 //setpoint EEPROM Address "offset" values

int const Kp[]          =   {6, 8, 10};

int const Ki[]          =   {12,14,16};

int const Kd[]          =   {18,20,22};

char *desc[]            =   {"Water Temp:","Steam Temp:","Group Temp:"};

int powerFail           =   0;                          //Setting powerFail to 1, instructs the user to set the time

extern int run;

char tuning             =   0;

// *************** Main Routine ************************************************
int main(void)
{                       
    InitApp();
    
    InitializeTimers();
    
    InitializePWM();                                    // Init PWM for Water Pump, Water Boiler, and Steam Boiler

// *************** PWM Controller Initialization *******************************
    unsigned char initCon = 0;
    
    for(initCon=0;initCon<3;initCon++)
    {
        Init_PID(initCon,eepromGetData(Kp[initCon]),eepromGetData(Ki[initCon]),eepromGetData(Kd[initCon]));
    }
        
// *************** Local Variables *********************************************
    unsigned int powerOut   = 0;                        // Power Output Displayed to screen
    
    char errorCount         = 0;                        // errorCount disables power, if water level remains low too long
    
    char errorSustained     = 0;

    uint8_t count2          = 0;                        // count2 ramps pump pressure
    
    int samples[3][numSamples] ={[0 ... 2] = {0}};      //Used to average temp[] over "numSamples" of samples
    
    static unsigned int temp[3]    = {0,0,0};
    
    unsigned int shortTermTemp[3]= {0,0,0};                                              
    
    uint8_t sampleIndex     = 0;                        // Used to calculate average sample of temp[]
    
    float total[3]          = {0,0,0};                  // Running total of temp[] samples 
    
    unsigned char testKey   = 0;                        // Variable used for Storing Which Menu Key is Pressed
    
    int bits[9]             = {0};
 
    //    int internalBGV;
    
    int PIDValue[]          = {0,0,0};                  // PID calculated values (Water, Steam and Group)
    
    int setRangeL[]         = {1800,2650,1850};            // Set Point Low Limits      FIX Group Setpoint back to Min 180
    
    int setRangeH[]         = {2100,2850,2150};         // Set Point High Limits
    
    int previous_time       = 0;                        //Used with time.second to limit some stuff to once a second
            
    unsigned int counter[8] = {0,0,0,0,1140,0,0,0};     // Shot progress, Shot timer, Shot Warning timer, Shot display Timer, Back Light, groupPeriodCounter,
                                                        // Steam Pump run Timer, Low Water Reminder
    uint16_t level          = 0;
    
    static char ONTimer     = 0;                        // Bit to enable Auto Start of Machine
    
    
// ******************************************************************************
    LCDBitmap(&menu0[0], 5, 84);                        //Draw Menu0

    while(1)
    {
        power       =   !_RB11;                         // RB11 is pulled high normally, pulled low by turning ON Power switch, so 0 is ON, 1 is OFF
        
        brewSwitch  =   !_RB10;                         // RB10 is pulled high normally, pulled low by turning ON Brew switch, so 0 is ON, 1 is OFF
        
        steamSwitch =   !_RA7;                          // RA7 is pulled high normally, pulled low by turning ON Steam switch, so 0 is ON, 1 is OFF
        
        waterSwitch =   !_RC9;                          // RC9 is pulled high normally, pulled low by turning ON Water switch, so 0 is ON, 1 is OFF

        static int timer = 0;                           // Used to count up time in a loop, to auto exit if user in a menu too long
        
        time = getRTCTime();                            // get the time
        

// *************** Calculate Temperature Averages ******************************
        shortTermTemp[0] = tempCalc(ADCRead(9));        //Assign the ADC(9) Boiler Temp to a temporary variable
        total[0] = total[0] - samples[0][sampleIndex];  // Subtract the oldest sample data from the total
        samples[0][sampleIndex] = shortTermTemp[0];     // Assign the just read temperature to the location of the current oldest data
        total[0] = total[0] + samples[0][sampleIndex];  // Add that new sample to the total
        boilerTemperature = total[0] / numSamples;      // Assign the average value of total to the boilerTemperature variable


        shortTermTemp[1] = tempCalc(ADCRead(0));        // Assign the ADC(0) (Steam Temp) to a temporary variable
        total[1] = total[1] - samples[1][sampleIndex];  // Subtract the oldest sample data from the total
        samples[1][sampleIndex] = shortTermTemp[1];     // Assign the just read temperature to the location of the current oldest data
        total[1] = total[1] + samples[1][sampleIndex];  // Add that new sample to the total
        steamTemperature = total[1] / numSamples;       // Assign the average value of total to the GroupHeadTemp variable

 
        shortTermTemp[2] = tempCalc(ADCRead(4));        //Assign the ADC(4) Group Head Temp to a temporary variable
        total[2] = total[2] - samples[2][sampleIndex];  // Subtract the oldest sample data from the total
        samples[2][sampleIndex] = shortTermTemp[2];     // Assign the just read temperature to the location of the current oldest data
        total[2] = total[2] + samples[2][sampleIndex];  // Add that new sample to the total

        sampleIndex += 1;                               // and move to the next index location
        if(sampleIndex >= numSamples)                   //If we have reached the max number of samples
        {
            sampleIndex = 0;                            //Reset to zero
        }
        GroupHeadTemp = total[2] / numSamples;          // Assign the average value of total to the GroupHeadTemp variable

// *************** Auto Turn ON Machine at User selected Dates & Times *********
        if(previous_time != time.second)                // Only execute the following code once a second
        {
            previous_time = time.second;

            ONTimer = runTimer(time.weekday,time.hour,time.minute);
            
            if(power==1 || ONTimer==1)
            {
                powerSwitch = 1;                        // powerSwitch is the Virtual Power control Variable
                (power==1)?(run=0):(run=run);           // if power switch is on, disable AutoStart, or Kill AutoStart by cycling Power Switch (run is in RTCC.C)
            }
            else
            {
                powerSwitch = 0;                        // powerSwitch can turn OFF Machine, even if Power is ON
            }
            
// *************** Check for and re-act to Low Water Level *********************
            errorCount>9?powerSwitch=0:powerSwitch;    // If errorCount (water Level Low) > 9 seconds, turn OFF Power
            
//            level = waterTankLevel();
            level = 30;
            
            if(level < 15)
            {
                errorCount +=1;                         // Increment the Error Counter
                piezoOutput = 1-piezoOutput;            // Turn On the Piezo Alarm
                errorCount>10?(errorCount=10,piezoOutput=0):errorCount; // Limit Error Counter to 10, and turn piezo OFF
            }
            else
            {
                errorCount -= 1;
                errorCount<0?errorCount=0:errorCount;
            }
            
            if(errorCount > 1)
            {
                errorSustained>8?airPump=0:(airPump=1,errorSustained+=1);
            }
            
// *************** Increment counter to Auto turn OFF BackLight ****************
            backLightCounter +=1;                       // Increment the "Seconds" counter to turn OFF Backlight

// ******************************************************************************
            if(powerSwitch)
            {
                if(lastPowerState!=powerSwitch)
                {
                    LCDClear();
                    LCDBitmap(&menu0[0], 5, 84);        //Draw Menu0
                    OC1CON2bits.OCTRIS  = 0;
                    OC2CON2bits.OCTRIS  = 0;
                    OC3CON2bits.OCTRIS  = 0;
                    backLightCounter    = 0;
                }
                
                if(powerFail == 1)
                {
                    LCDWriteStringXY(4,0,"Press \"Time\" to Set");
                    LCDWriteStringXY(4,1,"the Current Time");
                }
                else
                {
                    if(tuning)
                    {
                        WaterPID        = PID_Calculate(0, waterSetpoint, boilerTemperature);// Calculate Water PID Value
                        goto there;
                    }
                    WaterPID        = PID_Calculate(0, waterSetpoint, boilerTemperature);// Calculate Water PID Value
                    SteamPID        = PID_Calculate(1, steamSetpoint, steamTemperature); // Calculate Steam PID Value
                    GroupHeadPID    = PID_Calculate(2, groupHeadSetpoint, GroupHeadTemp);// Calculate Group PID Value
                    
                    displayTime();

                    gotoXY(2,1);                        //LCD Line 2 Display

                    if(steamSwitch)
                    {
                        LCDWriteString(desc[1]);
                        LCDWriteIntXY(48,1,steamTemperature,4,1,0);
                        LCDWriteCharacter(123);         // generate degree symbol in font list
                        LCDWriteCharacter(70);
                    }
                    else
                    {
                        LCDWriteString(desc[0]);
                        LCDWriteIntXY(48,1,boilerTemperature,4,1,0);
                        LCDWriteCharacter(123);         // generate degree symbol in font list
                        LCDWriteCharacter(70);
                    }

                    LCDWriteStringXY(2,2,desc[2]);
                    LCDWriteIntXY(48,2,GroupHeadTemp,4,1,0);
                    LCDWriteCharacter(123);             // generate degree symbol in font list
                    LCDWriteCharacter(70);
                    LCDWriteCharacter(' ');
                    
                
                    if(shotTimer == 0)
                    {
                        LCDWriteStringXY(2,3,"Tank Level:");
                        LCDWriteIntXY(48,3,level,-1,0,0);
                        LCDWriteCharacter('%');
                        LCDWriteCharacter(' ');
                        LCDWriteCharacter(' ');
                    
                        if(level < 25)                  // Tank level < 25%
                        {
                            blink = 1 - blink;          // toggle blink variable
                            if(blink)
                            {
                                LCDWriteStringXY(48,3,"LOW");
                                LCDWriteCharacter(' ');
                                LCDWriteCharacter(' ');

                                lowWaterReminder+=1;    

                                if(lowWaterReminder>29) // blink toggles every other second, so, 1/2 the delay time - 1.
                                {
                                    piezoOutput=1;
                                    if(!brewSwitch)     // Disable delay if we are pulling a shot (will mess with pump timing)
                                    {
                                        __delay_ms(30); // Short, but, annoying piezo reminder
                                    }
                                    piezoOutput=0;      
                                    lowWaterReminder=0;
                                }
                            }
                        }
                    }
                    else
                    {
                        LCDWriteStringXY(2,3,"Shot Timer:");
                        LCDWriteIntXY(48,3,shotTimer,4,1,0);
                    }
                }
            }
            else
            {
                LCDBitmap(&coffee[0], 0,504);           //Draw Splash Screen
                gotoXY(1,4);
                LCDWriteCharacter(' ');                 // Need to Write something to the screen to get it to Draw the Splash Screen  FIX
                backLightCounter    +=1200;             // 1200 counts is the number required to turn OFF the Backlight
                
                OC1CON2bits.OCTRIS  = 1;                // Tri-State the OC1 Pin, if powerSwitch is OFF
                OC2CON2bits.OCTRIS  = 1;                // Tri-State the OC2 Pin, if powerSwitch is OFF
                OC3CON2bits.OCTRIS  = 1;                // Tri-State the OC3 Pin, if powerSwitch is OFF
                shotTimer           = 0;                // Re-Set the ShotTimer
            }
        }
        
        there:
        if(tuning)
        {
            LCDWriteStringXY(0,1,desc[0]);
            LCDWriteIntXY(48,1,boilerTemperature,4,1,0);
            LCDWriteCharacter(123);         // generate degree symbol in font list
            LCDWriteCharacter(70);
        }            
// *************** Run Air Pump once an hour for Level transmitter *************
        if(powerSwitch)
        {
            if(time.minute == 0 && time.second < 5)
            {
                airPump = 1;
            }
            else
            {
                airPump = 0;
            }

// *************** Drive PID Outputs *******************************************
            groupPeriodCounter+=1;
        
            if(groupPeriodCounter > PIDDuration)
            {
                groupPeriodCounter = 0;
            }
        
//            LCDWriteIntXY(0,4,groupPeriodCounter,4,0,0);
  //          LCDWriteIntXY(22,4,GroupHeadPID,5,0,0);
    //        LCDWriteIntXY(44,4,groupOutput,2,0,0);
            if(GroupHeadPID > groupPeriodCounter)
            {
                groupOutput = 1;
            }
            else
            {
                groupOutput = 0;
            }
 
            if(steamSwitch)                             //Steam setpoint takes priority
            { 
                steamSolenoid=1;
                
                // OC3 is Initialized as edge aligned, OC2 as center-aligned (OC3R is dutycycle for OC3, OC2R is start of cycle for OC2)
                OC3R=SteamPID;                     // Start Steam Boiler Output at beginning of cycle, can use up to 100% of cycle    
                OC2R=0X1E85-WaterPID+OC3R;
                
                (WaterPID+OC2R>0X1E84)?(OC2RS=0X1E84):(OC2RS=WaterPID+OC2R+1); // Water PID takes what it needs from whatever cycle is left
                
                LCDWriteIntXY(0,4,WaterPID,4,0,0);
                LCDWriteIntXY(22,4,SteamPID,4,0,0);
                LCDWriteIntXY(44,4,OC2R,4,0,0);
                LCDWriteIntXY(66,4,OC3RS,4,0,0);

                steamPumpRunCounter+=1;                 // Water Pump runs at Steam Power Level for 3100 Program cycles FIX (add EEPROM & HMI location to set duration)
                
                if(steamPumpRunCounter<3100)
                {
                    OC1R = steamPumpPower;
                }
                else
                {
                    OC1R = 0;
                    steamPumpRunCounter = 3100;
                }
            }
            else                                //Water setpoint takes priority
            {
                LCDWriteIntXY(0,4,WaterPID,4,0,0);
                LCDWriteIntXY(22,4,SteamPID,4,0,0);
                LCDWriteIntXY(44,4,OC3R,4,0,0);
                LCDWriteIntXY(66,4,OC2R,4,0,0);

                steamSolenoid=0;
                steamPumpRunCounter = 0;        // Reset the Steam Pump run counter, so, if Steam switch is pressed again, pump will run

                OC3R=0;
                OC2R=0x1E85-WaterPID;           // OC2R must be at least 1, so 0x1E85 instead of 0x1E84!!
            }

// *************** Brew a Shot of Espresso *************************************
            
            if(brewSwitch)
            {
                OC2R = 2;
                backLightCounter = 0;           // Turn on Backlight if you are pulling a shot.
                
                LCDWriteStringXY(2,4,"Pump Output:");
                LCDWriteInt(powerOut,3,0,0);
                LCDWriteCharacter('%');
                LCDWriteCharacter(' ');
                LCDWriteCharacter(' ');
                
                T2CONbits.TON       =   1;      // Turn Timer2 ON
                
                shotDisplayTimer    =   0;      // Timer to reset Shot Counter    
                
                if(shotProgressCounter <= preInfusionTime)
                {
                    brewSolenoid=1;
                    pumpOutput = preInfusionDutyCycle;
                }
                
                if(shotProgressCounter > preInfusionTime && shotProgressCounter <= soakTime)
                {
                    pumpOutput = 0;
                }

                if (shotProgressCounter > soakTime && shotProgressCounter <= startRamp)               
                {
                    if(pumpOutput <= max)
                    {
                        count2+=1;
                        
                        if(count2 >5)           // 13 gets us to !00% in 2.5 seconds (the current amount of StartRamp Time)
                        {
                            if(pumpOutput<max) pumpOutput +=16;
                            count2 = 0;
                        }
                    }
                }
            
                if(shotProgressCounter > startRamp && shotProgressCounter <= continuePull)
                {
                    if(pumpOutput >= min)
                    {   
                        count2 +=1;
                        
                        if(count2 > 15)
                        {
                            pumpOutput -=2;
                            count2 = 0;
                        }
                    }
                } 
                    
                if(shotProgressCounter > 300 + preInfusionTime + soakTime)//&& shotProgressCounter < warning-30)// Allow up to 30 second pull, them limit pump output to min
                {
                    pumpOutput = min;
                }
                
                if(shotProgressCounter > 600) pumpOutput  = 0;// Turn off the Pump as well
                
                
                if (shotProgressCounter >= warning)     // 90 Seconds has elapsed without Brew Switch being turned off,
                {                  
                    piezoOutput = 1;                    // Activate Piezo Buzzer for 1/2 second
//                    pumpOutput  = 0;                    // Turn off the Pump as well
                }

                if(shotProgressCounter >= warning + 5)  // Piezo has been on for 1/2 second
                { 
                    piezoOutput = 0;                    // So, Shut it off! (pulsing alarm)
                    shotProgressCounter = (warning - 25);// set time back 2.5 seconds, so it can go again.(in 2 seconds)
                    warningTimer+=1;                    // Increment warningTimer every 2.5 seconds, after 10 counts, alarm will go solid
                }

                if(warningTimer >= 10)                  // After 10 counts of pulsing alarm being ignored,
                { 
                    piezoOutput = 1;                        // turn Piezo on constantly,
                    shotProgressCounter = (warning - 250);  // and set tenCount to below the pulsing alarm time,
                    warningTimer = 10;                      // so Piezo will not start pulsing alarm again.
                }                                       
                
                
                if(IFS0bits.T2IF)
                {
                    shotProgressCounter +=1;
    
                    if(shotProgressCounter > soakTime)
                    {
                        shotTimer +=1;
                    }

                    IFS0bits.T2IF = 0;
                }
                powerOut = pumpOutput*100/256;
            }
            else
            {
                brewSolenoid        =   0;
                piezoOutput         =   0;
                warningTimer        =   0;
                T2CONbits.TON       =   0;
                shotProgressCounter =   0;
//                pumpOutput          =   0;
                shotDisplayTimer    +=  1;

                if(shotDisplayTimer >=12500)                                    // Approximately 20 seconds (about 625 counts/second)
                {
                    shotTimer =         0;
                }
            }
            
// ******************************************************************************
            if(waterSwitch)
            {
                pumpOutput = max;
                OC2R = 2;
            }
        }
        
// ******************************************************************************
        if(!brewSwitch && !steamSwitch && !waterSwitch)
        {
            pumpOutput              =   0;
        }
        
// ******************************************************************************
        testKey = readButton();


        if (testKey == Menu)
        {
            backLightCounter = 0;               // Reset BackLight counter
            
            if(timer<1)
            {
                powerSwitch = 0;
                timer+=1;
                goto done2;
            }
            
            LCDClear();
            LCDBitmap(&menu2[0], 5,84);         //Draw Menu2
            LCDWriteStringXY(4,1,"Press \"ENTER\" Key");
            LCDWriteStringXY(4,2,"to Set the Time");

            while(testKey != Enter)
            {
                testKey = readButton();
                timer +=1;
                __delay_ms(10);
                if (timer > 500)
                {
                    timer = 0;
                    LCDClear();
                    LCDBitmap(&menu2[0], 5, 84);//Draw Menu2
                    goto done2;
                }
            }
            SetTime();
            
            timer = 0;

//                LCDBitmap(&menu0[0], 5, 84);                 //Draw Menu0
            __delay_ms(500);
            
            done2:;
            LCDBitmap(&menu0[0], 5, 84);        //Draw Menu0
        }
        
// ******************************************************************************
        
        if(testKey == Enter)
        {
            backLightCounter = 0;               // Reset BackLight counter
            
            if(timer<1)
            {
                powerSwitch = 0;
                timer+=1;
                goto Exit2;
            }

//            testKey = KEY_NONE;
            
            LCDClear();
            LCDBitmap(&menu2[0], 5, 84);        //Draw Menu2
            LCDWriteStringXY(0,1,"Press \"ENTER\" to Set Start/Stop Times");

            while(testKey != Enter)
            {
                testKey = readButton();
                 timer +=1;
                 __delay_ms(10);
               
                if(timer > 500)
                {
                    timer = 0;
                    LCDClear();
                    LCDBitmap(&menu2[0], 5, 84);//Draw Menu2
                    goto Exit2;                                                 
                }
            }
            
            timer = 0;
            writeStartStopTimes();
            LCDBitmap(&menu0[0], 5, 84);        //Draw Menu0
            __delay_ms(500);
            
            Exit2:; 
        }
// ******************************************************************************

        if (testKey == Down)
        {
            backLightCounter = 0;               // Reset BackLight counter
            
            if(timer<1)
            {
                powerSwitch = 0;
                timer+=1;
                goto Exit;
            }

            if(timer < 2)
            {
                LCDClear();
                LCDBitmap(&menu2[0], 5, 84);    //Draw Menu2
                testKey = None;
                __delay_ms(750);
            }
            
            
            int8_t choice = 0;

            while(testKey != Enter)
            {
                testKey = readButton();
                __delay_ms(10);
                
                if(timer > 500)
                {
                    timer = 0;
                    goto Exit;                  
                }

                switch(testKey)
                {
                    case Down:
                    {
                        choice -=1;
                            
                        if (choice < 0)
                        {
                            choice = 0;
                        }
                    }
                    break;

                        
                    case Up:
                    {
                        choice += 1;
                            
                        if(choice > 2)
                        {
                            choice = 2;
                        }
                    }
                    break;
                    
                    case Menu:
                    {
                        goto Exit;
                    }
                    break;
                }

                LCDWriteStringXY(0,0,"PID Settings for");
                LCDWriteStringXY(0,1,desc[choice]);
                LCDWriteStringXY(0,3,"Up/Dn Keys to Change");
                LCDWriteStringXY(0,4,"  \"Enter\" to Accept ")

                timer += 1;
            }
            
            testKey = 0;
            
            LCDClear();
            LCDBitmap(&menu2[0], 5, 84);              //Draw Menu2
            LCDWriteStringXY(0,0,"SetPoint = ");
            eepromPutData(setpoint[choice], setParameter(44,0,setRangeL[choice],setRangeH[choice],eepromGetData(setpoint[choice])));
            
            LCDWriteStringXY(0,1,"Gain =");
            eepromPutData(Kp[choice], setParameter(44,1,0,200,eepromGetData(Kp[choice])));

            LCDWriteStringXY(0,2,"Integral =");
            eepromPutData(Ki[choice], setParameter(44,2,0,500,eepromGetData(Ki[choice])));

            LCDWriteStringXY(0,3,"Derivative =");
            eepromPutData(Kd[choice], setParameter(44,3,0,500,eepromGetData(Kd[choice])));
            
            
            Init_PID(choice,eepromGetData(Kp[choice]),eepromGetData(Ki[choice]),eepromGetData(Kd[choice]));                

            timer = 0;

            LCDClear();
            LCDBitmap(&menu0[0], 5, 84);        //Draw Menu0
            __delay_ms(500);

            Exit:
            LCDClear();
            LCDBitmap(&menu0[0], 5, 84);            //Draw Menu0
        }
 
                        
// ******************************************************************************
        if (testKey == Up)                      // Reset the LCD
        {
            LCDInit();
            __delay_ms(100);
            LCDClear();
            backLightCounter = 0;               // Reset BackLight counter
            LCDBitmap(&menu0[0], 5, 84);        // Draw Menu0
        }
        
        if(backLightCounter > 1199)             // No Keys Pressed for 20 Minutes
        {
            backLightOFF = 1;                   // so, we might as well shut OFF the LCD BackLight
            backLightCounter = 1200;            // and, reset the count, so it will turn on with the next Key Press
        }
        else
        {
            backLightOFF = 0;
        }
        
        lastPowerState = powerSwitch;
        
// *****************************************************************************
        ClrWdt();                               // Clear (Re-Set) the WatchDog Timer
    }
    return(1);
}
//***************************************************************************************************************************************************************

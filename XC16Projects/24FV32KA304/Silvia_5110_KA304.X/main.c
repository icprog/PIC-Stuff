#include    "system.h"
#include    "menu.h"
#include    "coffee.h"
// ***************************************************************************************************************************************************************
#define piezoOutput             _LATA1          // Output to turn on Piezo, if Brew switch left on too long
#define backLightOFF            _LATA9          // Backlight is active LOW, so "0" is "ON", "1" is "OFF" Pin 35
#define airPump                 _LATA8          // FIX

// *************** Inputs ****************************************************************************************************************************************
// ADC Input to read Button press (User Input Keys) on _RC1 (AN7) Pin 26                                               G
// ***************************************************************************************************************************************************************

//***************************Timer2 set in pwm.c
//***************************All times are in 1/100th's of a second, so 100 = 1 seconds, 300 = 3 seconds, 150 = 1.5 seconds, etc 

#define max                     2048                                // This needs to move to EEPROM
#define min                     400                                 // Also needs to move to EEPROM & have User interface coded
#define preInfusionDutyCycle    500        //FIX                         // This needs to move to EEPROM & have a User Interface set up so user can change it
#define preInfusionTime         (25)            //FIX                    // length of time to run pump to preInfuse puck
#define soakTime                (preInfusionTime + 15)   //FIX           // Length of time for wetted puck to soak
#define startRamp               (soakTime + 25)               //FIX      // StartRamp starts pump and Ramps up to Max Pressure
#define continuePull            (800 + 1)                           // Shot duration, 60 seconds from Start of Cycle(601)
#define warning                 (850 + 1)                           // Turn on Warning Piezo, reminder to turn off switch (651)


#define PIDDuration             2499
#define WaterPID                PIDValue[0]
#define SteamPID                PIDValue[1]
#define GroupHeadPID            PIDValue[2]

#define waterPIDPeriodCounter   counter[0]
#define steamPIDPeriodCounter   counter[1]
#define groupPIDPeriodCounter   counter[2]
#define shotProgressCounter     counter[3]
#define shotTimer               counter[4]
#define warningTimer            counter[5]


#define waterSetpoint           eepromGetData(setpoint[0])
#define steamSetpoint           eepromGetData(setpoint[1])
#define groupHeadSetpoint       eepromGetData(setpoint[2])

//#define waterDeadband           eepromGetData(deadband[0])                    // FIX Remove all deadband Junk, work with PID
//#define steamDeadband           eepromGetData(deadband[1])
//#define GroupHeadDeadband       eepromGetData(deadband[2])

#define boilerTemperature       temp[0]
#define steamTemperature        temp[1]
#define GroupHeadTemp           temp[2]
#define waterLevel              level                                           //ADCRead(14) is Water Tank level signal
#define numSamples              60                                              //Number of samples to average for temp[] readings (Do not set higher than 20, or keep Max temp below 325F)
                                                                                //You have 65535/(max temp * 10) samples available Changed to float, 300 no worries!! Should be able to get 
// ***************************************************************************************************************************************************************
int __attribute__ ((space(eedata))) Settings[43];                               // Global variable located in EEPROM (created by the space()attribute

RTCTime time;                                   // declare the type of the time object

unsigned int setpoint[] =   {0, 2,  4};         //setpoint EEPROM Address "offset" values

unsigned int deadband[] =   {6, 8, 10};         //dead band EEPROM Address "offset" values

int const Kp[]          =   {12, 16, 20};

int const Ki[]          =   {24, 28, 32};

int const Kd[]          =   {34, 36, 38};

int dutyCycle[]         =   { 0,  0,  0};       // Duty Cycle for PWM Outputs

char *desc[]            = {"Water Temp:","Steam Temp:","Group Temp:"};

int powerFail           = 1;                    //Setting powerFail to 1, instructs the user to set the time

extern char run;

// ******************************************************************************
int main(void)
{                       
    InitApp();
    
    InitializeTimers();

    Initialize_PWM();

// ******************************************************************************
    unsigned char initCon = 0;
    
    for(initCon=0;initCon<3;initCon++)
    {
        Init_PID(initCon,eepromGetData(Kp[initCon]),eepromGetData(Ki[initCon]),eepromGetData(Kd[initCon]));
    }
        
// ******************************************************************************
    uint8_t blink = 1;                          // blink flashes display when water level low
    
    char errorCount = 0;                     // errorCount disables power, if water level remains low too long
    
    char errorSustained = 0;

    uint16_t count = 0;                         // Used to Increment seconds count for Brew Timer
    
    uint8_t count2 = 0;                         // count2 ramps pump pressure
    
    uint16_t count3 = 1200;                        // Used to count time until Backlight turns Off
    
    int samples[3][numSamples];                 //Used to average temp[] over "numSamples" of samples
    
    unsigned int temp[3];
    
    unsigned int shortTermTemp[3];                                              
    
    uint8_t sampleIndex = 0;                    // Used to calculate average sample of temp[]
    
    float total[3] = {0,0,0};                   // Running total of temp[] samples 

    uint16_t i = 0;                             // x is used for holding shot timer value for 20 seconds before resetting to zero
    
    uint16_t a = 0;
    
    uint8_t testKey = 0;                        // Variable used for Storing Which Menu Key is Pressed
    
    uint8_t power = 1;                          // Power switch input state     G

    uint8_t brewSwitch = 1;                     // Brew Switch Input            G

    uint8_t steamSwitch = 1;                    // Steam Switch Input           G
    
    uint8_t waterSwitch = 1;                    // Water Switch Input           G

    int internalBGV;
    
    int PIDValue[] = {0,0,0};                   // PID calculated values
    
    int setRangeL[] =   {1750,2500,1800};       // Set Point Low Limits
    
    int setRangeH[] =   {2100,2850,2150};       // Set Point High Limits
    
    int previous_time = 0;                      //Used with time.second to limit some stuff to once a second
            
    int counter[6] = {0,0,0,0,0,0};                                             //PID Counter for boiler temp, steam temp, and grouphead temp, as well as shot progress counter, shot timer, and warning timer
    
    uint16_t level      = 0;
    
    static char ONTimer = 0;
    
    char powerSwitch    = 0;
    
    char lastPowerState = 0;
    
// ******************************************************************************
    LCDBitmap(&menu0[0], 5, 84);                 //Draw Menu0

    while(1)
    {
//        power = _RB11;                          // FIX
        power = !_RB11;                         // RB11 is pulled high normally, pulled low by turning ON Power switch, so 0 is ON, 1 is OFF
        
        brewSwitch = !_RB10;                    // RB10 is pulled high normally, pulled low by turning ON Brew switch, so 0 is ON, 1 is OFF
        
//        steamSwitch = _RA7;                     // RA7 is pulled high normally, pulled low by turning ON Steam switch, so 0 is ON, 1 is OFF
        steamSwitch = !_RA7;                    // RA7 is pulled high normally, pulled low by turning ON Steam switch, so 0 is ON, 1 is OFF
        
        waterSwitch = !_RC9;                    // RC9 is pulled high normally, pulled low by turning ON Water switch, so 0 is ON, 1 is OFF

        static int timer = 0;                                                   // Used to count up time in a loop, to auto exit if user in a menu too long
        
        time = getRTCTime();                                                    // get the time
        

        shortTermTemp[0] = ADCRead(4);          //Assign the ADC(4) Boiler Temp to a temporary variable
        
        total[0] = total[0] - samples[0][sampleIndex];// Subtract the oldest sample data from the total

        samples[0][sampleIndex] = shortTermTemp[0];   // Assign the just read temperature to the location of the current oldest data
        
        total[0] = total[0] + samples[0][sampleIndex];// Add that new sample to the total

        boilerTemperature = total[0] / numSamples;    // Assign the average value of total to the boilerTemperature variable
        
//        steamTemperature = boilerTemperature;                                   //This is a single boiler, so Steam & Water temps are the same measurement


        shortTermTemp[1] = ADCRead(5);          // Assign the ADC(5) (Steam Temp) to a temporary variable
        
        total[1] = total[1] - samples[1][sampleIndex];// Subtract the oldest sample data from the total

        samples[1][sampleIndex] = shortTermTemp[1];   // Assign the just read temperature to the location of the current oldest data
        
        total[1] = total[1] + samples[1][sampleIndex];// Add that new sample to the total
        
        sampleIndex += 1;                             // and move to the next index location
        
        if(sampleIndex >= numSamples)                 //If we have reached the max number of samples
        {
            sampleIndex = 0;                          //Reset to zero
        }
        steamTemperature = total[1] / numSamples;     // Assign the average value of total to the GroupHeadTemp variable

 
        shortTermTemp[2] = ADCRead(6);          //Assign the ADC(6) Group Head Temp to a temporary variable
        
        total[2] = total[2] - samples[2][sampleIndex];                          // Subtract the oldest sample data from the total

        samples[2][sampleIndex] = shortTermTemp[2];                             // Assign the just read temperature to the location of the current oldest data
        
        total[2] = total[2] + samples[2][sampleIndex];                          // Add that new sample to the total
        
        sampleIndex += 1;                                                       // and move to the next index location
        
        if(sampleIndex >= numSamples)                                           //If we have reached the max number of samples
        {
            sampleIndex = 0;                                                    //Reset to zero
        }
        GroupHeadTemp = total[2] / numSamples;                                  // Assign the average value of total to the GroupHeadTemp variable

// *****************************************************************************
                        
        if(previous_time != time.second)
        {
            ONTimer = runTimer(time.weekday,time.hour,time.minute);
            
            if(power==1 || ONTimer==1)
            {
                powerSwitch = 1;                // powerSwitch is the Virtual Power control Variable
                (power==1)?(run=0):(run=run);   // if power switch is on, disable AutoStart, or Kill AutoStart by cycling Power Switch
            }
            else
            {
                powerSwitch = 0;                // powerSwitch can turn OFF Machine, even if Power is ON
            }
            
            errorCount>19?powerSwitch=0:powerSwitch;// If errorCount (water Level Low) > 19 seconds, turn OFF Power
            
//            level = waterTankLevel();
            level = 30;
 
            level<10?powerSwitch=0:powerSwitch; // If LEVEL is less than 10%, Disable Outputs
            
            if(level < 12)
            {
                errorCount +=1;                 // Increment the ERROR COUNTER
                errorCount>20?errorCount=20:errorCount;// Limit Error Counter to 20
            }
            else
            {
                errorCount -= 1;
                errorCount<0?errorCount=0:errorCount;
            }
            
            if(errorCount > 1)
            {
                errorSustained>15?airPump=0:(airPump=1,errorSustained+=1);
            }
            
            count3 +=1;                         // Increment the "Seconds" counter to turn OFF Backlight
            
            previous_time = time.second;

// ******************************************************************************
            internalBGV = ADCRead(0x1A);
      
            for(i = 0;i<2;++i)
            {
                temp[i] = TempCalc(temp[i]);
            } 
            
// ******************************************************************************
            if(powerSwitch)
            {
                if(lastPowerState!=powerSwitch)
                {
                    LCDClear();
                    LCDBitmap(&menu0[0], 5, 84);//Draw Menu0
                }
                
                if(powerFail == 1)
                {
                    LCDWriteStringXY(4,0,"Press \"Time\" to Set");
                    LCDWriteStringXY(4,1,"the Current Time");
                }
                else
                {
                    displayTime();

                    gotoXY(2,1);                                //LCD Line 2 Display

                    if(steamSwitch)
                    {
                        LCDWriteString(desc[1]);
                        LCDWriteIntXY(48,1,steamTemperature,4,1,0);
                        LCDWriteCharacter(123);                 // generate degree symbol in font list
                        LCDWriteCharacter(70);
                    }
                    else
                    {
                        LCDWriteString(desc[0]);
                        LCDWriteIntXY(48,1,boilerTemperature,4,1,0);
                        LCDWriteCharacter(123);                 // generate degree symbol in font list
                        LCDWriteCharacter(70);
                    }

                    LCDWriteStringXY(2,2,desc[2]);
                    LCDWriteIntXY(48,2,GroupHeadTemp,4,1,0);
                    LCDWriteCharacter(123);                     // generate degree symbol in font list
                    LCDWriteCharacter(70);
                    LCDWriteCharacter(' ');
                
                    if(shotTimer == 0)
                    {
                        LCDWriteStringXY(2,3,"Tank Level:");
                        LCDWriteIntXY(48,3,level,-1,0,0);
                        LCDWriteCharacter('%');
                        LCDWriteCharacter(' ');
                        LCDWriteCharacter(' ');
                    
      //              LCDWriteIntXY(5,4,testKey,5,0,0);
//                    LCDWriteIntXY(5,4,dutyCycle,5,0);
//                    LCDWriteIntXY(5,16,count,5,0);
        //            LCDWriteIntXY(5,22,shotProgressCounter,5,0,0);
                    
                        if(level < 25)
                        {
                            blink = 1 - blink;
                            if(blink)
                            {
                                LCDWriteStringXY(48,3,"LOW");
                                LCDWriteCharacter(' ');
                                LCDWriteCharacter(' ');
                            }
                        }
                    }
                    else
                    {
                        LCDWriteStringXY(2,3,"Shot Timer:");
                        LCDWriteIntXY(48,3,shotTimer,4,1,0);
                    }
                
                    LCDWriteIntXY(0,4,GroupHeadPID,5,0,0);
                    LCDWriteIntXY(24,4,powerSwitch,1,0,0);
                }
            }
            else
            {
                LCDBitmap(&coffee[0], 0,504);   //Draw Splash Screen
                gotoXY(1,4);
                LCDWriteCharacter(' ');         // Need to Write something to the screen to get it to Draw the Splash Screen  FIX
                count3+=1200;                   // 1200 counts is the number required to turn OFF the Backlight
            }
        }

// ******************************************************************************
        if(powerSwitch == 1)
        {
/*            if(IFS0bits.T2IF)
            {
                IFS0bits.T2IF = 0;
                count+=1;
            }
*/
            if(time.minute == 0 && time.second < 5)
            {
                airPump = 1;
            }
            else
            {
                airPump = 0;
            }

// ******************************************************************************
//            GroupHeadPID = PID_Calculate(2, groupHeadSetpoint, temp);
            
//            if((groupHeadSetpoint - GroupHeadTemp) > GroupHeadDeadband)
  //          {
 //               dutyCycle[0] = 8191;            // Turn OC5 on 100%
    //        }
      //      else 
        //    {
                GroupHeadPID = PID_Calculate(2, groupHeadSetpoint, temp[2]);
                
 //               dutyCycle[0] = GroupHeadPID;    // Drive OC5 with PID PWM
          //  }
            
  /*          if(steamSetpoint - steamTemperature > steamDeadband)
            {
                dutyCycle[2] = 8191;
            }
            else
            {
                SteamPID = PID_Calculate(1, setpoint, temp);
                    
                dutyCycle[2] = SteamPID;
            }
                
            if(waterSetpoint - boilerTemperature > waterDeadband)
            {
                dutyCycle[1] = 8191;
            }
            else
            {
                WaterPID = PID_Calculate(0, setpoint, temp);
                   
                dutyCycle[1] = WaterPID;
            }
   
// ******************************************************************************
*/          
            
//            dutyCycle[2] = 0x8191;
            
 //           dutyCycle[1] = 0x8191;
            
            
              
//            (dutyCycle[0]==0)?(OC5CON2bits.OCTRIS = 1):(OC5CON2bits.OCTRIS = 0);
  //          (dutyCycle[1]==0)?(OC4CON2bits.OCTRIS = 1):(OC4CON2bits.OCTRIS = 0);
    //        (dutyCycle[2]==0)?(OC6CON2bits.OCTRIS = 1):(OC6CON2bits.OCTRIS = 0);
              


            if(steamSwitch == 1)                //Steam setpoint takes priority
            {
      //          OC6R = 0;                           
            
        //        OC6RS = dutyCycle[2];           // Steam Boiler Output

          //      OC4R = OC6RS;

            //    (OC4R+dutyCycle[1]>=0x2000)?(OC4RS = 0x2000):(OC4RS = OC4R + dutyCycle[1]); //Water Boiler Output
            }

            else                                //Water setpoint takes priority
            {            
              //  OC4R = 0;                           
            
//                OC4RS = dutyCycle[1];           // Water Boiler Output is Shut OFF

  //              OC6R = OC4RS;

    //            (OC6R+dutyCycle[2]>=0x2000)?(OC6RS = 0x2000):(OC6RS = OC6R + dutyCycle[2]); //Steam Boiler Output is Shut OFF
            }
            
      //      OC5R = dutyCycle[0];
 

            
            
            
            
            
//            if(steamSwitch == 1)
  //          {
    //            SteamPID = PID_Calculate(1, setpoint, temp);
      //      }
        //    else
          //  {
            //    WaterPID = PID_Calculate(0, setpoint, temp);
            //}

            //GroupHeadPID = PID_Calculate(2, setpoint, temp);
// ******************************************************************************
            
/*            if(steamSwitch == 1)                                                //Steam setpoint takes priority
            {
                if(steamSetpoint - boilerTemperature > steamDeadband)
                {
                    boilerOutput = 1;
                }
                else
                {
                    steamPIDPeriodCounter+=1;
        
                    if (steamPIDPeriodCounter > PIDDuration)
                    {
                        steamPIDPeriodCounter = 0;
                    }
        
                    if (SteamPID > steamPIDPeriodCounter)
                    {
                        boilerOutput = 1;
                    }
                    else
                    {
                        boilerOutput = 0;
                    }
                }
            }

            else                                                                //Water setpoint takes priority
            {            
                if(waterSetpoint - boilerTemperature > waterDeadband)
                {
                    boilerOutput = 1;
                }
                else
                {
                    waterPIDPeriodCounter+=1;
       
                    if (waterPIDPeriodCounter > PIDDuration)
                    {
                        waterPIDPeriodCounter = 0;
                    }
        
                    if (WaterPID > waterPIDPeriodCounter)
                    {
                        boilerOutput = 1;
                    }
                    else
                    {
                        boilerOutput = 0;
                    }
                }
            }
// ******************************************************************************
        
            if((groupHeadSetpoint - GroupHeadTemp) > GroupHeadDeadband)
            {
                groupheadOutput = 1;
            }

            else 
            {
                groupPIDPeriodCounter+=1;
        
                if(groupPIDPeriodCounter > PIDDuration)
                {
                    groupPIDPeriodCounter = 0;
                }
        
                if(GroupHeadPID > groupPIDPeriodCounter)
                {
                    groupheadOutput = 1;
                }
                else
                {
                    groupheadOutput = 0;
                }
            }
 */
 // ******************************************************************************
           
            if(brewSwitch == 1)
            {   
                a = 0;
                
                if(shotProgressCounter <= preInfusionTime)
                {
//                    dutyCycle = preInfusionDutyCycle;
                }
                
                if(shotProgressCounter > preInfusionTime && shotProgressCounter <= soakTime)
                {
  //                  dutyCycle = 0;
                }

                if (shotProgressCounter > soakTime && shotProgressCounter <= startRamp)               
                {
    //                if(dutyCycle <= max)
                    {
      //                  dutyCycle +=2;
                    }
                }
            
                if(shotProgressCounter > startRamp && shotProgressCounter <= continuePull)
                {
        //            if(dutyCycle >= min)
                    {   
                        count2 +=1;
                        
                        if(count2 > 9)
                        {
          //                  dutyCycle -=1;
                            count2 = 0;
                        }
                    }
                } 
                    
                    if(shotProgressCounter > (250 + preInfusionTime + soakTime))
                    {
            //            dutyCycle = 20;
                    }
                
                if (shotProgressCounter >= warning)                             // 90 Seconds has elapsed without Brew Switch being turned off,
                {                  
                    piezoOutput = 1;                                            // Activate Piezo Buzzer for 1/2 second
                }

                if(shotProgressCounter >= warning + 50)                          // Piezo has been on for 1/2 second
                { 
                    piezoOutput = 0;                                            // So, Shut it off! (pulsing alarm)
                    shotProgressCounter = (warning - 50);                       // set time back 2 seconds, so it can go again.(in 1.5 seconds)
                    warningTimer++;                                             // Increment z every 2 seconds, after 10 counts, alarm will go solid
                }

                if(warningTimer >= 10)                                          // After 10 seconds of pulsing alarm being ignored,
                { 
                    piezoOutput = 1;                                            // turn Piezo on constantly,
                    shotProgressCounter = (warning - 250);                       // and set tenCount to below the pulsing alarm time,
                    warningTimer = 10;                                          // so Piezo will not start pulsing alarm again.
                }                                       
                
                
                if(IFS0bits.T2IF)
                {
                    count+=1;

                    if(count == 10)
                    {
                        shotProgressCounter +=1;
    
                        if(shotProgressCounter > soakTime)
                        {
                            shotTimer +=1;
                        }
                        
                        count = 0;
                    }

                    IFS0bits.T2IF = 0;
                }
            }

            else
            {
                piezoOutput =           0;
                warningTimer =          0;
                T2CONbits.TON =         0;
                shotProgressCounter =   0;
//                dutyCycle =             0;
                a += 1;
                if(a >= 12500)                                                  //Approximately 20 seconds (about 625 counts/second)
                {
                    shotTimer =         0;
                }
            }
// ******************************************************************************

            if(waterSwitch)
            {
//                dutyCycle = 2048;
            }
        }
        else
        {
  //          boilerOutput        = 0;
//            groupheadOutput     = 0;
            shotTimer           = 0;
    //        dutyCycle           = 0;
            piezoOutput         = 0;
        }
// ******************************************************************************
        
        if(!brewSwitch && !steamSwitch && !waterSwitch)
        {
//            dutyCycle =     0;
        }
// ******************************************************************************

        testKey = readButton();
// ******************************************************************************
//        heartBeat();                                                            // HeartBeat displays the HeartBeat on the LCD,
// ******************************************************************************  but, also increments mainTimer every second 
        if (testKey == Menu)
        {
            count3 = 0;                         // Reset BackLight counter
            
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
            count3 = 0;                         // Reset BackLight counter
            
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
            count3 = 0;                         // Reset BackLight counter
            
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
                    goto Exit;                  //This uses less memory than TestKey = KEY_3
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
            
            LCDWriteStringXY(0,1,"DeadBand =");
            eepromPutData(deadband[choice], setParameter(44,1,5,100,eepromGetData(deadband[choice])));            

            LCDWriteStringXY(0,2,"Gain =");
            eepromPutData(Kp[choice], setParameter(44,2,0,200,eepromGetData(Kp[choice])));

            LCDWriteStringXY(0,3,"Integral =");
            eepromPutData(Ki[choice], setParameter(44,3,0,500,eepromGetData(Ki[choice])));

            LCDWriteStringXY(0,4,"Derivative =");
            eepromPutData(Kd[choice], setParameter(44,4,0,100,eepromGetData(Kd[choice])));
            
            
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
            count3 = 0;                         // Reset BackLight counter
            LCDBitmap(&menu0[0], 5, 84);        // Draw Menu0
        }
        
        if(count3 > 1199)                       // No Keys Pressed for 20 Minutes
        {
            backLightOFF = 1;                   // so, we might as well shut OFF the LCD BackLight
            count3 = 1200;                      // and, reset the count, so it will turn on with the next Key Press
        }
        else
        {
            backLightOFF = 0;
        }
        
        lastPowerState = powerSwitch;
 // ******************************************************************************
        ClrWdt();                               // Clear (Re-Set) the WatchDog Timer
    }
    return(1);
}
//***************************************************************************************************************************************************************

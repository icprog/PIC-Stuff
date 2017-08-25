
#include "xc.h"
#include "stdint.h"                                                             // Includes uint16_t definition
#include "lcd.h"
#include "system.h"                                                             // System funct/params, like osc/peripheral config
#include "user.h"                                                               // User Functions (Setting Setpoints, DeadBands, etc...)
#include "rtcc.h"                                                               // Real Time clock & Calendar Functions
#include <string.h>
#include "eeprom.h"
#include "touch.h"
#include "adc.h"
#include "PID_Lib.h"
#include "AnalogKeyInput.h"
#include "level.h"
#include "start_stop_timer.h"


#define boilerOutput            _LATC8                                          //Allways!!! Write to the latch!!
#define groupheadOutput         _LATA7
#define pumpOutput              _LATA2
#define tankSolenoidOutput      _LATA10
#define waterSolenoidOutput     _LATC9 
#define piezoOutput             _LATA3
#define backLightOn             _LATA1
#define airPump                 _LATB10

#define power                   _RB15                
#define steamSwitch             switches[0] 
#define brewSwitch              switches[1]
#define waterSwitch             switches[2]

//***************************Timer1 set in SYSTEM.C
//***************************All times are in 1/10th's of a second, so 100 = 10 seconds, 30 = 3 seconds, 15 = 1.5 seconds, etc                            
#define pressurizeTime          (100)                                           // Duration of Pressurize Cycle
#define preInfusionTime         (pressurizeTime + 10)                           // length of time to run pump at 50% output to preInfuse puck
#define soakTime                (preInfusionTime + 30)                          // Length of time for wetted puck to soak
#define startPull               (soakTime + 10)                                 // StartPull opens Water Solenoid and starts pump again
#define continuePull            (800 + 1)                                       // Shot duration, 60 seconds from Start of Cycle(601)
#define warning                 (850 + 1)                                       // Turn on Warning Piezo, reminder to turn off switch (651)

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

#define waterDeadband           eepromGetData(deadband[0])
#define steamDeadband           eepromGetData(deadband[1])
#define GroupHeadDeadband       eepromGetData(deadband[2])

#define boilerTemperature       temp[0]
#define steamTemperature        temp[1]
#define GroupHeadTemp           temp[2]
//#define waterLevel              level                                           //ADCRead(10) is Water Tank level signal
#define numSamples              60                                              //Number of samples to average for temp[] readings (Do not set higher than 20, or keep Max temp below 325F)
                                                                                //You have 65535/(max temp * 10) samples available Changed to float, 300 no worries!! Should be able to get 
                                                                                //over 600,000 samples from float!! However, we run out of data memory at just over 300. numSamples is an unsigned char


int __attribute__ ((space(eedata))) Settings[43];                               // Global variable located in EEPROM (created by the space()attribute

RTCTime time;                                                                   // declare the type of the time object

int const setpoint[]    =   {0, 2,  4};                                          //setpoint EEPROM Address "offset" values

int const deadband[]    =   {6, 8, 10};                                          //dead band EEPROM Address "offset" values

int const Kp[]          =   {12, 16, 20};

int const Ki[]          =   {24, 28, 32};

int const Kd[]          =   {34, 36, 38};

char *desc[] = {"Water Temp: ","Steam Temp: ","Group Head: "};

int call = 0;                                                                   //call is used to set HMI key delay time, based on what function you are in 

int powerFail = 1;                                                              //Setting powerFail to 1, instructs the user to set the time

//extern uint8_t toggle;

char blink = 1, errorCount = 0;

int samples[2][numSamples];                                                     //Used to average temp[] over "numSamples" of samples

 // ******************************************************************************

int main(void)
{
//    ConfigureOscillator();

    InitApp();
    
    ADCInit();

    LCD_Init(NONE);
    
    __delay_ms(100);
    
    LCD_Clear();
    
    RTCC_Initialize();
    
    InitCustomChars();
    
    unsigned char initCon = 0;
    
    for(initCon=0;initCon<3;initCon++)
    {
        Init_PID(initCon,eepromGetData(Kp[initCon]),eepromGetData(Ki[initCon]),eepromGetData(Kd[initCon]),0,(PIDDuration + 1));
    }
    
//    Init_PID0(eepromGetData(Kp[0]),eepromGetData(Ki[0]),eepromGetData(Kd[0]),0,(PIDDuration + 1));

  //  Init_PID1(eepromGetData(Kp[1]),eepromGetData(Ki[1]),eepromGetData(Kd[1]),0,(PIDDuration + 1));

    //Init_PID2(eepromGetData(Kp[2]),eepromGetData(Ki[2]),eepromGetData(Kd[2]),0,(PIDDuration + 1));
    

// ******************************************************************************
    extern char *WeekDay[7];
    
    extern char *month[13];
    
    int loopCounter = 3, previousLoopCounter = 3;
    
    int temp[3], shortTermTemp[2];
    
    unsigned char sampleIndex = 0;                                              //Used to calculate average sample of temp[]
    
    float total[2] = {0,0};                                                     //Running total of temp[] samples 

    int i = 0, x = 0;                                                           // x is used for holding shot timer value for 20 seconds before resetting to zero
    
    char TestKey, testSwitch;                                                   // Variable used for Storing Which Menu Key is Pressed, or which hardware key is on

    int internalBGV;
    
    int PIDValue[] = {0,0,0};                                                   // PID calculated values
    
    int previous_time = 0;                                                      //Used with time.second to limit some stuff to once a second
            
    int counter[6] = {0,0,0,0,0,0};                                             //PID Counter for boiler temp, steam temp, and grouphead temp, as well as shot progress counter, shot timer, and warning timer
    
    int switches[3] = {0,0,0};                                                  //powerSwitchinput, steamSwitch, brewSwitch, waterSwitch
            
//    char startTime[7][24][4];
    
    unsigned int backLightTimer = 0, level = 0;
    
    char ONTimer = 0, powerSwitch = 0;
    
    

 // ******************************************************************************

    while(1)
    {
        static int timer = 0;                                                   // Used to count up time in a loop, to auto exit if user in a menu too long
    
        time = getRTCTime();                                                    // get the time

//        _LATB11 = 1;
// ******************************************************************************
        shortTermTemp[0] = ADCRead(0);                                          //Assign the ADC(0) Temp to a temporary variable
        
        total[0] = total[0] - samples[0][sampleIndex];                          // Subtract the oldest sample data from the total

        samples[0][sampleIndex] = shortTermTemp[0];                             // Assign the just read temperature to the location of the current oldest data
        
        total[0] = total[0] + samples[0][sampleIndex];                          // Add that new sample to the total

        boilerTemperature = total[0] / numSamples;                              // Assign the average value of total to the boilerTemperature variable
        
        steamTemperature = boilerTemperature;                                   //This is a single boiler, so Steam & Water temps are the same measurement


        
        shortTermTemp[1] = ADCRead(5);                                          //Assign the ADC(5) Temp to a temporary variable
        
        total[1] = total[1] - samples[1][sampleIndex];                          // Subtract the oldest sample data from the total

        samples[1][sampleIndex] = shortTermTemp[1];                             // Assign the just read temperature to the location of the current oldest data
        
        total[1] = total[1] + samples[1][sampleIndex];                          // Add that new sample to the total
        
        sampleIndex += 1;                                                       // and move to the next index location
        
        if(sampleIndex >= numSamples)                                           //If we have reached the max number of samples
        {
            sampleIndex = 0;                                                    //Reset to zero
        }
        GroupHeadTemp = total[1] / numSamples;                                  // Assign the average value of total to the GroupHeadTemp variable

        
// ******************************************************************************
      
        if(previousLoopCounter != loopCounter)
        {
            LCD_Clear();
            previousLoopCounter = loopCounter;
        }


// ******************************************************************************
        if(previous_time != time.second)
        {
            ONTimer = runTimer(time.weekday,time.hour,time.minute);
            
            if(power==1 || ONTimer==1)
            {
                powerSwitch = 1;
            }
            else
            {
                powerSwitch = 0;
            }
            

            //            power==1?powerSwitch=1:(powerSwitch=0);
            
            errorCount>9?powerSwitch=0:powerSwitch;
            
//            (power==0)?errorCount=0:errorCount;
            
            level = waterTankLevel();
 
            level<10?powerSwitch=0:powerSwitch;
            
            if(level < 10)
            {
                errorCount +=1;
                errorCount>20?errorCount=20:errorCount;
                errorCount<20?airPump=1:(airPump=0);
            }
            
            previous_time = time.second;
        
// ******************************************************************************

            internalBGV = ADCRead(0x1A);
      
            for(i = 0;i<2;++i)
            {
                temp[i] = TempCalc(temp[i]);
            } 
        
// ******************************************************************************
            if(loopCounter < 3)
            {
                LCD_Set_Cursor(0,1);                                            //LCD Line 0 Display
                LCD_Write_String(desc[loopCounter]);
                LCDWriteDecIntXY(0,13,temp[loopCounter],4);
                LCD_Write_Char(0);
                LCD_Write_Char(70);
            
                LCDWriteStringXY(1,1,"SetPoint:");                              //LCD Line 1 SetPoint Display
                LCDWriteDecIntXY(1,13,eepromGetData(setpoint[loopCounter]),4);
                LCD_Write_Char(0);
                LCD_Write_Char(70);
                
                LCDWriteStringXY(2,1,"Num Errors:");
                LCDWriteIntXY(2,13,errorCount,2);
                LCDWriteStringXY(3,1,"SYS Voltage:");
                LCDWrite2DecIntXY(3,13,426242/internalBGV,3);
                LCD_Write_Char('V');
            }
        
            if(loopCounter == 3)
            {
                if(powerFail == 1)
                {
                    LCDWriteStringXY(1,1,"Please Set the Time");
                }
            
                else
                {
                    LCDWriteIntXY(0,1,time.year,2);
//                    LCD_Write_String("/");
                    LCD_Write_String(month[time.month]);
//                    LCD_Write_String("/");
                    LCD_Write_Int(time.day,2);
                    LCDWriteStringXY(0,9,WeekDay[time.weekday]);
                    LCDWriteIntXY(0,12,time.hour,2);
                    LCD_Write_String(":");
                    LCD_Write_Int(time.minute,2);
                    LCD_Write_String(":");
                    LCD_Write_Int(time.second,2);

                    LCD_Set_Cursor(1,1);                                        //LCD Line 1 Display


                    if(steamSwitch)
                    {
                        LCD_Write_String(desc[1]);
                    }
                    else
                    {
                        LCD_Write_String(desc[0]);
                    }

                    LCDWriteDecIntXY(1,13,boilerTemperature,4);
                    LCD_Write_Char(0);
                    LCD_Write_Char(70);

                    LCD_Set_Cursor(2,1);                                        //LCD Line 2 Display
                    LCD_Write_String(desc[2]);
                    LCDWriteDecIntXY(2,13,GroupHeadTemp,4);
                    LCD_Write_Char(0);
                    LCD_Write_Char(70);
                    
                    if(shotTimer == 0)
                    {
                        LCDWriteStringXY(3,1,"Tank Level:");
                        LCDWriteIntXY(3,13,level,3);
                        LCD_Write_Char (' ');
                        LCD_Write_Char ('%');

                        if(level < 25)
                        {
                            blink = 1 - blink;
                            if(blink)
                            {
                                LCDWriteStringXY(3,13,"LOW");
                                LCD_Write_Char (' ');
                                LCD_Write_Char ('%');
                            }
                        }
                    }
                    else
                    {
                    LCDWriteStringXY(3,1,"Shot Timer:");
                    LCDWriteDecIntXY(3,13,shotTimer,4);
                    }
                }
            }
        }
        
// ******************************************************************************
        
        if(powerSwitch == 1)
        {
            if(time.minute == 0 && time.second < 5)
            {
                airPump = 1;
            }
            else
            {
                airPump = 0;
            }

            if(steamSwitch == 1)
            {
                SteamPID = PID_Calculate(1, setpoint, temp);
            }
            else
            {
                WaterPID = PID_Calculate(0, setpoint, temp);
            }

            GroupHeadPID = PID_Calculate(2, setpoint, temp);

            
            if(steamSwitch == 1)                                                //Steam setpoint takes priority
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
// ******************************************************************************
            if(brewSwitch == 1)
            {   
                T1CONbits.TON = 1;
                
                x = 0;
                
                if(shotProgressCounter <= pressurizeTime)
                {
                    pumpOutput = 1;
                    tankSolenoidOutput = 1;
                }
                
                if(shotProgressCounter > pressurizeTime && shotProgressCounter <= preInfusionTime)
                {
                    tankSolenoidOutput = 0;
                    waterSolenoidOutput = 1;
                    if(IFS0bits.T1IF)
                    {
                        pumpOutput = 1 - pumpOutput;
                    }
                }
                
                if(shotProgressCounter > preInfusionTime && shotProgressCounter <= soakTime)
                {
                    pumpOutput = 0;
                }

                if (shotProgressCounter > soakTime && shotProgressCounter <= startPull)               
                {
                    waterSolenoidOutput = 1;                                    // Solenoid Valve Open (to deliver shot)
                    if(IFS0bits.T1IF)
                    {
                        pumpOutput = 1 - pumpOutput;                            // Pump delivering at 50% output
                    }
                }
            
                if(shotProgressCounter > startPull && shotProgressCounter <= continuePull)
                {
                    waterSolenoidOutput = 1;                                    // Water Solenoid Valve Open (to deliver pressure from pump @ 50%)
                    tankSolenoidOutput = 1;                                     //Tank solenoid opens to deliver volume from pressure tank
                    pumpOutput = 0;                                             //and Pump is shut Off
                }
                
                if (shotProgressCounter >= warning)                             // 90 Seconds has elapsed without Brew Switch being turned off,
                {                  
                    piezoOutput = 1;                                            // Activate Piezo Buzzer for 1/2 second
                }

                if(shotProgressCounter >= warning + 5)                          // Piezo has been on for 1/2 second
                { 
                    piezoOutput = 0;                                            // So, Shut it off! (pulsing alarm)
                    shotProgressCounter = (warning - 5);                        // set time back 2 seconds, so it can go again.(in 1.5 seconds)
                    warningTimer++;                                             // Increment z every 2 seconds, after 10 counts, alarm will go solid
                }

                if(warningTimer >= 10)                                          // After 10 seconds of pulsing alarm being ignored,
                { 
                    piezoOutput = 1;                                            // turn Piezo on constantly,
                    shotProgressCounter = (warning - 25);                       // and set tenCount to below the pulsing alarm time,
                    warningTimer = 10;                                          // so Piezo will not start pulsing alarm again.
                }                                       
                
            

                if(waterSolenoidOutput)                                         // If brewSwitch and water solenoid are both on, we are delivering a shot, so, 
                {
                    if(IFS0bits.T1IF)
                    {
                        shotTimer +=1;                                          // increment the shotTimer counter
                    }
                }
                
                if(IFS0bits.T1IF)
                {
                    IFS0bits.T1IF = 0;
                    shotProgressCounter +=1;
                }
            }

            else
            {
                piezoOutput = 0;
                warningTimer = 0;
                T1CONbits.TON = 0;
                shotProgressCounter = 0;
                x += 1;
                if(x >= 12500)                                                  //Approximately 20 seconds (about 625 counts/second)
                {
                    shotTimer = 0;
                }
            }
        
            if(waterSwitch)
            {
                pumpOutput = 1;
                waterSolenoidOutput = 1;
            }
        }
        else
        {
            boilerOutput        = 0;
            groupheadOutput     = 0;
            shotTimer           = 0;
            pumpOutput          = 0;
            tankSolenoidOutput  = 0;
            waterSolenoidOutput = 0;
            piezoOutput         = 0;
        }
        
//        if(brewSwitch == 0 && waterSwitch == 0)
// ******************************************************************************
        testSwitch = switchStateRead();
// ******************************************************************************
        
        if(testSwitch == SWITCH_BREW_SWITCH)
        {
            brewSwitch = 1;
        }
        
        if(testSwitch == SWITCH_STEAM_SWITCH)
        {
            steamSwitch = 1;
        }
        
        if(testSwitch == SWITCH_WATER_SWITCH)
        {
            waterSwitch = 1;
        }
        
        if(testSwitch == SWITCH_NONE)
        {
            brewSwitch = 0;
            steamSwitch = 0;
            waterSwitch = 0;
            pumpOutput = 0;
            waterSolenoidOutput = 0;
            tankSolenoidOutput = 0;
        }

// ******************************************************************************
        TestKey = menuRead();
// ******************************************************************************
        heartBeat();                                                            // HeartBeat displays the HeartBeat on the LCD,
// ******************************************************************************  but, also increments mainTimer every second 
        if(TestKey == KEY_NONE)             // If no key is pressed for 60 seconds
        {                                   // Turn OFF the LCD Backlight
            backLightTimer += 1;
        }
        
        else
        {
            backLightTimer = 0;
        }
        
        if (backLightTimer < 65534)
        {
            backLightOn = 1;
            
        }
        else
        {
            backLightTimer = 65534;
            backLightOn = 0;
        }




        if (TestKey == KEY_SET_TIME)
        {
            if(timer<1)
            {
                powerSwitch = 0;
                timer+=1;
                goto done2;
            }
//            TestKey = KEY_NONE;
//            __delay_ms(500);
            
            LCD_Clear();
            LCDWriteStringXY(0,0,"Press 'ENTER' to Set");
            LCDWriteStringXY(1,0,"Time");

            while(TestKey != KEY_ENTER)
            {
                TestKey = menuRead();
                timer +=1;
                __delay_ms(20);
                if (timer > 500)
                {
                    timer = 0;
                    LCD_Clear();
                    goto done2;
                }
            }
            SetTime();
            
            timer = 0;
            
            done2:;
        }
        
// ******************************************************************************
        
        if (TestKey == KEY_RESET)                                               //This will soft reset the processor
        {
            if(timer<1)
            {
                powerSwitch = 0;
                timer+=1;
                goto done;
            }

//            TestKey = KEY_NONE;
            
            LCD_Clear();
            LCDWriteStringXY(0,0,"  You are about to  ");
            LCDWriteStringXY(1,0,"ReSet the Processor");
            LCDWriteStringXY(2,0,"Hit 'Enter' to ReSet");

            while(TestKey != KEY_ENTER)
            {
                TestKey = menuRead();
                timer +=1;
                __delay_ms(20);
                if (timer > 500)
                {
                    timer = 0;
                    LCD_Clear();
                    goto done;
                }
            }
            asm( "reset" );
        }
        
        done:
// ******************************************************************************
        
        if(TestKey == KEY_START_STOP)
        {
            if(timer<1)
            {
                powerSwitch = 0;
                timer+=1;
                goto Exit2;
            }

//            TestKey = KEY_NONE;
            
            LCD_Clear();
            LCDWriteStringXY(0,0,"Press 'ENTER' to Set");
            LCDWriteStringXY(1,0,"Start/Stop Times");

            while(TestKey != KEY_ENTER)
            {
                TestKey = menuRead();
                 timer +=1;
                 __delay_ms(10);
               
                if(timer > 500)
                {
                    timer = 0;
                    LCD_Clear();
                    goto Exit2;                                                 
                }
            }
            
            timer = 0;
            writeStartStopTimes();
            
            Exit2:; 
        }
        
        
        
        
        
        /*        if (TestKey == KEY_RESET_LCD)
        {
            LCD_Cmd(0x08);
            LCD_Cmd(0x00);
            LCD_Cmd(0x0C|0);      //Enable Display ON with style selected (BLINK, ULINE, BLUL, or NONE))
            LCD_Cmd(0x00);
        }
*/
// ******************************************************************************
        if(TestKey == KEY_LEFT)
        {
            loopCounter -=1;
            
            if(loopCounter < 0)
            {
                loopCounter = 3;
            }
            __delay_ms(250);
        }
// ******************************************************************************
        if(TestKey == KEY_RIGHT)
        {
            loopCounter +=1;
            
            if(loopCounter > 3)
            {
                loopCounter = 0;
            }
            __delay_ms(250);
        }
// ******************************************************************************
        if (TestKey == KEY_MENU)
        {
            if(timer<1)
            {
                powerSwitch = 0;
                timer+=1;
                goto Exit;
            }

            signed char choice = 0;

            while(TestKey != KEY_ENTER)
            {
                TestKey = menuRead();
                
                if(timer > 1000)
                {
                    timer = 0;
                    goto Exit;                                                  //This uses less memory than TestKey = KEY_ENTER
                    
//                    TestKey = KEY_ENTER;                                      // This functions fine, but forces a write to EEProm
                }

                switch(TestKey)
                {
                    case KEY_DOWN:
                    {
                        choice -=1;
                            
                        if (choice < 0)
                        {
                            choice = 0;
                        }
                    }
                    break;

                    case KEY_LEFT:
                    {
                        choice -=1;
                            
                        if (choice < 0)
                        {
                            choice = 0;
                        }
                    }
                    break;
                        
                    case KEY_UP:
                    {
                        choice += 1;
                            
                        if(choice > 2)
                        {
                            choice = 2;
                        }
                    }
                    break;
                        
                    case KEY_RIGHT:
                    {
                        choice += 1;
                            
                        if(choice > 2)
                        {
                            choice = 2;
                        }
                    }
                    break;
                    
                    case KEY_RESET:
                    {
                        timer = 0;
                        LCD_Clear();
                        goto Exit;
                    }
                    break;
                        
                }

                if(timer < 2)
                {
                    LCD_Clear();
                }

                LCD_Set_Cursor(0,0);
                LCD_Write_String("Set Temperature for");
                LCD_Set_Cursor(1,0);
                LCD_Write_String(desc[choice]);
                LCDWriteStringXY(2,0,"Up/Dn Keys to change");
                LCDWriteStringXY(3,0,"Enter Key for Yes   ");
                
                heartBeat();                                                    // HeartBeat displays the HeartBeat on the LCD,
                                                                                // but, also increments mainTimer every second
                timer += 1;
            }
            
            TestKey = 9;
            
            LCD_Clear();


            LCD_Set_Cursor(0,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(0,strlen(desc[choice]),"Set Temp");
            eepromPutData(setpoint[choice], TempSetpoint(eepromGetData(setpoint[choice])));
            
            LCD_Set_Cursor(2,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(2,strlen(desc[choice]),"Set DB");
            eepromPutData(deadband[choice], SetDeadband(eepromGetData(deadband[choice])));            

            LCD_Clear();

            LCD_Set_Cursor(0,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(0,strlen(desc[choice]),"Gain");
            eepromPutData(Kp[choice], SetGain(eepromGetData(Kp[choice])));

            LCD_Set_Cursor(2,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(2,strlen(desc[choice]),"Integral");
            eepromPutData(Ki[choice], SetIntegral(eepromGetData(Ki[choice])));

            LCD_Clear();

            LCD_Set_Cursor(0,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(0,strlen(desc[choice]),"Rate");
            eepromPutData(Kd[choice], SetDerivative(eepromGetData(Kd[choice])));
            
            Init_PID(choice,eepromGetData(Kp[choice]),eepromGetData(Ki[choice]),eepromGetData(Kd[choice]),0,4095);                


/*            if(choice == 0)
            {
                Init_PID0(eepromGetData(Kp[0]),eepromGetData(Ki[0]),eepromGetData(Kd[0]),0,4095);                
            }
            
            else if (choice == 1)
            {
                Init_PID1(eepromGetData(Kp[1]),eepromGetData(Ki[1]),eepromGetData(Kd[1]),0,4095);
            }

            else
            {
                Init_PID2(eepromGetData(Kp[2]),eepromGetData(Ki[2]),eepromGetData(Kd[2]),0,4095);
            }
*/            
            timer = 0;

            LCD_Clear();
        }
 
        Exit:
                        
        
// ******************************************************************************
        ClrWdt();                                                               //Clear (Re-Set) the WatchDog Timer
    }
    return(0);
}
//***************************************************************************************************************************************************************

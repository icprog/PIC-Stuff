#include    "system.h"                                                             // System funct/params, like osc/peripheral config
#include    "menu.h"
// *************** Outputs ***************************************************************************************************************************************
//#define fanOutput               _LATD6                                          // Pit Viper Fan PWM Output
#define piezoOutput             _LATF1                                          // Piezo Alarm Output G
#define backLightOn             _LATD4                                          // Backlight On/Off G


// *************** Inputs ****************************************************************************************************************************************
#define power                   !_RG9                                           // Power Switch Input G             
// ***************************************************************************************************************************************************************

//***************************Timer2 set in pwm.c
//***************************All times are in 1/100th's of a second, so 100 = 1 seconds, 300 = 3 seconds, 150 = 1.5 seconds, etc 

#define maxOutput               1023                                // This needs to have User interface coded
#define minOutput               400                                 // Also needs to have User interface coded

#define OvenSetpoint            setpoint[0]
//#define steamSetpoint           setpoint[1]
//#define groupHeadSetpoint       setpoint[2]

#define waterDeadband           deadband[0]
//#define steamDeadband           deadband[1]
//#define GroupHeadDeadband       deadband[2]

#define ovenTemperature         temp[0]
#define Temperature1            temp[1]
#define Temperature2            temp[2]
#define Temperature3            temp[3]
#define Temperature4            temp[4]
#define Temperature5            temp[5]
#define Temperature6            temp[6]

#define numSamples              60                                              //Number of samples to average for temp[] readings (Do not set higher than 20, or keep Max temp below 325F)
                                                                                //You have 65535/(max temp * 10) samples available Changed to float, 300 no worries!! Should be able to get 
// ***************************************************************************************************************************************************************
extern struct tm currentTime;

extern float Kp[];
extern float Ki[];
extern float Kd[];

uint16_t setpoint[]    =   {1940, 2750, 1970};                                     //setpoint values

uint16_t deadband[]    =   {  50,   10,   50};                                     //dead band values

char *desc[] = {"Water Temp:","Steam Temp:","Group Temp:"};

uint8_t call = 0;

int8_t powerFail = 1;

uint16_t timeFU = 0;                                                              //Setting powerFail to 1, instructs the user to set the time

// ******************************************************************************
int main(void)
{
    SYSTEM_Initialize();
// ******************************************************************************
    
    uint8_t blink = 1, errorCount = 0, count2 = 0;                              // blink flashes display when level low, errorCount disables
                                                                                // power, if level remains low too long, count2 ramps pump pressure
    uint16_t dutyCycle = 0;                                                     // Water Pump duty cycle?? 

    int samples[3][numSamples];                                                 //Used to average temp[] over "numSamples" of samples
    
    int temp[3], shortTermTemp[3];                                              
    
    unsigned char sampleIndex = 0;                                              //Used to calculate average sample of temp[]
    
    float total[3] = {0,0,0};                                                   //Running total of temp[] samples 

    int i = 0, a = 0;                                                           // x is used for holding shot timer value for 20 seconds before resetting to zero
    
    char TestKey;                                                               // Variable used for Storing Which Menu Key is Pressed

    int internalBGV;
    
    int PIDValue[] = {0,0,0};                                                   // PID calculated values
    
    int previous_time = 0;                                                      //Used with time.second to limit some stuff to once a second
            
    int counter[6] = {0,0,0,0,0,0};                                             //PID Counter for boiler temp, steam temp, and grouphead temp, as well as shot progress counter, shot timer, and warning timer
    
    unsigned int level = 0;
    
    char ONTimer = 0, powerSwitch = 0;
    
    uint16_t count = 0;
    
// ******************************************************************************
    setDutyCycle(dutyCycle);
    
    loadimg(&menu3[0], 1024,0);                 //Draw Menu3

    while(1)
    {
        static int timer = 0;                                                   // Used to count up time in a loop, to auto exit if user in a menu too long

        RTCC_TimeGet(&currentTime); 

        shortTermTemp[0] = ADCRead(13);                                         //Assign the ADC(13) (Boiler Temp) to a temporary variable
        
        total[0] = total[0] - samples[0][sampleIndex];                          // Subtract the oldest sample data from the total

        samples[0][sampleIndex] = shortTermTemp[0];                             // Assign the just read temperature to the location of the current oldest data
        
        total[0] = total[0] + samples[0][sampleIndex];                          // Add that new sample to the total

        ovenTemperature = total[0] / numSamples;                              // Assign the average value of total to the ovenTemperature variable
        
//        steamTemperature = ovenTemperature;                                   //This is a single boiler, so Steam & Water temps are the same measurement

       shortTermTemp[1] = ADCRead(12);                                          //Assign the ADC(12) (Steam Temp) to a temporary variable
        
        total[1] = total[1] - samples[1][sampleIndex];                          // Subtract the oldest sample data from the total

        samples[1][sampleIndex] = shortTermTemp[1];                             // Assign the just read temperature to the location of the current oldest data
        
        total[1] = total[1] + samples[1][sampleIndex];                          // Add that new sample to the total
        
        sampleIndex += 1;                                                       // and move to the next index location
        
        if(sampleIndex >= numSamples)                                           //If we have reached the max number of samples
        {
            sampleIndex = 0;                                                    //Reset to zero
        }
        steamTemperature = total[1] / numSamples;                               // Assign the average value of total to the GroupHeadTemp variable


        shortTermTemp[2] = ADCRead(11);                                         //Assign the ADC(11) (GroupHead Temp) to a temporary variable
        
        total[2] = total[2] - samples[2][sampleIndex];                          // Subtract the oldest sample data from the total

        samples[2][sampleIndex] = shortTermTemp[2];                             // Assign the just read temperature to the location of the current oldest data
        
        total[2] = total[2] + samples[2][sampleIndex];                          // Add that new sample to the total
        
        sampleIndex += 1;                                                       // and move to the next index location
        
        if(sampleIndex >= numSamples)                                           //If we have reached the max number of samples
        {
            sampleIndex = 0;                                                    //Reset to zero
        }
        GroupHeadTemp = total[2] / numSamples;                                  // Assign the average value of total to the GroupHeadTemp variable

// ******************************************************************************
        if(previous_time != currentTime.tm_sec)
        {
            ONTimer = runTimer(currentTime.tm_wday, currentTime.tm_hour, currentTime.tm_min);
            
            if(power==1 || ONTimer==1)
            {
                powerSwitch = 1;
            }
            else
            {
                powerSwitch = 0;
            }
            
            errorCount>9?powerSwitch=0:powerSwitch;

            previous_time = currentTime.tm_sec;

// ******************************************************************************
            internalBGV = ADCRead(0x1A);
      
            for(i = 0;i<2;++i)
            {
                temp[i] = TempCalc(temp[i]);
            }
            
// ******************************************************************************
//            if (dutyCycle < 0x800)                  // 0x800 = 2048, 100 % output is 2047, but going to 2048 ensures the pin will stay at 100%                            
  //          {
    //            count +=1;
      //          if(count > 15)
        //        {
          //          dutyCycle+=1;
            //    }
            //}
        
            setDutyCycle(dutyCycle);

 
            if(powerFail == 1)
            {
                LCDWriteStringXY(3,6,"Please Set");
                LCDWriteStringXY(3,17,"the Time!");
            }
            else
            {
                displayTime();

                GoToXY(2,1);                                                //LCD Line 2 Display

                if(1)
                {
                    LCDWriteString(desc[1]);
                    LCDWriteString("/Set");
                    GoToXY(2,25);
                    LCDWriteChar('/');
                    LCDWriteInt(setpoint[1],4,1);
                }
                else
                {
                    LCDWriteString(desc[0]);
                    LCDWriteString("/Set");
                    GoToXY(2,25);
                    LCDWriteChar('/');
                    LCDWriteInt(setpoint[0],4,1);
                }

                LCDWriteIntXY(2,17,ovenTemperature,4,1);
                LCDWriteChar(129);                                          // generate degree symbol in font list
                LCDWriteChar(70);

                GoToXY(3,1);                                                //LCD Line 3 Display
                LCDWriteString(desc[2]);
                LCDWriteString("/Set");
                LCDWriteIntXY(3,17,GroupHeadTemp,4,1);
                LCDWriteChar(129);                                          // generate degree symbol in font list
                LCDWriteChar(70);
                LCDWriteChar(' ');
                LCDWriteChar('/');
                LCDWriteInt(setpoint[2],4,1);
                
            }
        }
        
// ******************************************************************************
        if(powerSwitch == 1)
        {
//            if(IFS0bits.T2IF)
  //          {
    //            IFS0bits.T2IF = 0;
      //          count+=1;
        //    }

        }
        else
        {
            dutyCycle           = 0;
            piezoOutput         = 0;
        }

// ******************************************************************************
        TestKey = menuRead();
// ******************************************************************************
//        heartBeat();                                                            // HeartBeat displays the HeartBeat on the LCD,
// ******************************************************************************  
        if (TestKey == KEY_1)
        {
            if(timer<1)
            {
                powerSwitch = 0;
                timer+=1;
                goto done2;
            }
            
            cls();
            loadimg(&menu2[0], 1024,0);                         //Draw Menu2
            LCDWriteStringXY(3,2,"Press 'ENTER' ");
            LCDWriteStringXY(3,16,"to Set the Time");

            while(TestKey != KEY_3)
            {
                TestKey = menuRead();
                timer +=1;
                __delay_ms(10);
                if (timer > 500)
                {
                    timer = 0;
                    cls();
                    loadimg(&menu3[0], 1024,0);                  //Draw Menu3
                    goto done2;
                }
            }

            RTCC_TimeSet(&currentTime);
            
            timer = 0;

            loadimg(&menu3[0], 1024,0);                         //Draw Menu3
            __delay_ms(500);
            
            done2:;
        }
        
// ******************************************************************************
        
        if(TestKey == KEY_2)
        {
            if(timer<1)
            {
                powerSwitch = 0;
                timer+=1;
                goto Exit2;
            }

//            TestKey = KEY_NONE;
            
            cls();
            loadimg(&menu2[0], 1024,0);                         //Draw Menu2
            LCDWriteStringXY(3,1,"ENTER to Set St");
            LCDWriteStringXY(3,16,"art/Stop Times");

            while(TestKey != KEY_3)
            {
                TestKey = menuRead();
                 timer +=1;
                 __delay_ms(10);
               
                if(timer > 500)
                {
                    timer = 0;
                    cls();
                    loadimg(&menu3[0], 1024,0);                  //Draw Menu2
                    goto Exit2;                                                 
                }
            }
            
            timer = 0;
            
            
            
            
            
            
            
            
            
            
            writeStartStopTimes();






            loadimg(&menu3[0], 1024,0);                          //Draw Menu2
            __delay_ms(500);
            
            Exit2:; 
        }
// ******************************************************************************

        if (TestKey == KEY_3)
        {
            if(timer<1)
            {
                powerSwitch = 0;
                timer+=1;
                goto Exit;
            }

            if(timer < 2)
            {
                cls();
                loadimg(&menu2[0], 1024,0);                     //Draw Menu2
                TestKey = KEY_NONE;
                __delay_ms(750);
            }
            
            
            int8_t choice = 0;

            while(TestKey != KEY_3)
            {
                TestKey = menuRead();
                __delay_ms(10);
                
                if(timer > 500)
                {
                    timer = 0;
                    cls();
                    loadimg(&menu3[0], 1024,0);                  //Draw Menu3
                    goto Exit;                                   //This uses less memory than TestKey = KEY_3
//                    TestKey = KEY_3;                           // This functions fine, but forces a write to EEProm
                }

                switch(TestKey)
                {
                    case KEY_1:
                    {
                        choice -=1;
                            
                        if (choice < 0)
                        {
                            choice = 0;
                        }
                    }
                    break;

                        
                    case KEY_2:
                    {
                        choice += 1;
                            
                        if(choice > 2)
                        {
                            choice = 2;
                        }
                    }
                    break;
                }


                GoToXY(1,2);
                LCDWriteString("PID Settings f");
                LCDWriteStringXY(1,16,"or ");
                LCDWriteString(desc[choice]);
                LCDWriteStringXY(2,6,"Up/Dn Keys");
                LCDWriteStringXY(2,17,"to change");
                LCDWriteStringXY(3,7,"\"Enter\" t")
                LCDWriteStringXY(3,16,"o Accept")

                timer += 1;
            }
            
            TestKey = 0;
            
            cls();
            loadimg(&menu2[0], 1024,0);              //Draw Menu2
            LCDWriteStringXY(1,1,"SetPoint = ");
            setpoint[choice] = setParameter(1,16,1750,2950,setpoint[choice]);
            
            LCDWriteStringXY(2,1,"DeadBand =");
            deadband[choice] = setParameter(2,16,5,100,deadband[choice]);            

            LCDWriteStringXY(3,1,"Gain =");
            Kp[choice] = setParameter(3,16,0,200,Kp[choice]);

            LCDWriteStringXY(4,1,"Integral =");
            Ki[choice] = setParameter(4,16,0,500,Ki[choice]);

            LCDWriteStringXY(5,1,"Derivative =");
            Kd[choice] = setParameter(5,16,0,100,Kd[choice]);
            
            
            Init_PID(choice,Kp[choice],Ki[choice],Kd[choice]);                

            timer = 0;

            cls();
            loadimg(&menu3[0], 1024,0);                  //Draw Menu2
            __delay_ms(500);
        }
 
        Exit:
                        
// ******************************************************************************
        if (TestKey == KEY_4)
        {
            init_lcd();
            cls();
            loadimg(&menu3[0], 1024,0);                         //Draw Menu3
        }
        
// ******************************************************************************
        ClrWdt();                                                               //Clear (Re-Set) the WatchDog Timer
    }
    return(1);
}
//***************************************************************************************************************************************************************

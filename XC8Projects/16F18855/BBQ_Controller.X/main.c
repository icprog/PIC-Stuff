// *************** Includes ****************************************************    
#include "system.h"

// *************** Defines *****************************************************    
#define pitSetpoint             750
#define ambientTemperature      analogs[0]                                      // Analog Chanell 1,  Pin 3
#define pitTemperature          analogs[1]                                      // Analog Chanell 3,  Pin 5
#define pitViperOutput          LATC2

//#define celcius                 analogs[0]                      // Touch pad to select Degrees C
#define farenheit               analogs[1]                      // Touch pad to select Degrees F
#define down                    analogs[2]                      // Touch pad to select Backlight Intencity Down
#define up                      analogs[3]                      // Touch pad to select Backlight Intencity Up
#define solarInTemp             analogs[4]
#define solarOutTemp            analogs[5]



// *************** Main Routine ************************************************    
void main(void)
{
    SYSTEM_Initialize();
    
    uint16_t analogs[2]         =   {0};                    // array of analog readings (button presses and temperatures)
    
    float displayTemp, displayTemp2;                    // Calculate R of Thermistor, and Temp using SteinHart/Hart equation
    
    char j                      =   0;                      // Variable to loop readAnalog function
    
    char x                      =   0;                      // Looping Initializer
    
    int pidPeriodCounter        =   0;
    
    extern int pidMaxOutput;
    
    unsigned char loop          =   64;                     // cycle (loop) counter
    
    char choice                 =   2;                      // Display degrees C or degrees F, or cycle through both if choice is "2".
    
    char C_or_F                 =   1;                      // Default Temperature Display is degrees F
    
    unsigned int bCount         =   0;                      // Loop counter for Backlight setting delay (to allow selection of both pads touched)
    
    unsigned char startDelay    =   0;                      // Loop counter to delay touchpad input until ADC stable
    
    unsigned char resetDelay    =   0;                      // Loop counter to delay backlight touchpad input until determined if two pads are touched for Reset
    
    unsigned char tPadCount     =   10;                     // Touch pad counter (counts up or down from 10, to determine is one or both pads touched) (for C_or_F choice))
    
    
    uint16_t dutyCycle6         =   523;                    // Pit Viper Fan Output
    
    uint16_t dutyCycle7         =   523;                    // display back light brightness

//    PWM6_LoadDutyValue(dutyCycle6);

    PWM7_LoadDutyValue(dutyCycle7);

    __delay_ms(300);

    LCD_Clear();


    while (1)
    {
        pidPeriodCounter+=1;
        
        if(pidPeriodCounter>pidMaxOutput)pidPeriodCounter=0;
        
        if(dutyCycle6>pidPeriodCounter)pitViperOutput=1;
        else pitViperOutput=0;
        
        for(j=0;j<2;j++) analogs[j]=readAnalog(j);                          // Read all 7 analog Temperatures
//        analogs[0] = ADCRead(3);
        
        ambientTemperature=tempCalc(analogs[0]);

        pitTemperature=tempCalc(analogs[1]);
        
        dutyCycle7=502;

        if(loop>253)
        {
//        PWM6_LoadDutyValue(dutyCycle6);
        
        PWM7_LoadDutyValue(dutyCycle7);
        
        LCDWriteStringXY(0,0,"Pit:");
        LCDWriteIntXY(5,0,pitTemperature,-1,1,0);
        LCD_Write_Char(0);                                              // generate degree symbol in font list
        LCD_Write_Char(70);
        LCD_Write_Char(' ');                                              // generate degree symbol in font list

        LCDWriteStringXY(0,1,"Ambient:");
        LCD_Write_Char(' ');                                              // generate degree symbol in font list
        LCD_Write_Int(dutyCycle6,5,1,0);
//        LCD_Write_Int(ambientTemperature,-1,1,0);
//        LCD_Write_Char(0);                                              // generate degree symbol in font list
  //      LCD_Write_Char(70);
        LCD_Write_Char(' ');                                              // generate degree symbol in font list

//        LCDWriteStringXY(0,1,"Duty Cycle");
  //      LCD_Write_Char(' ');                                              // generate degree symbol in font list
    //    LCD_Write_Int(dutyCycle7,4,0,0);
      //  LCD_Write_Char(' ');                                              // generate degree symbol in font list
        
 //       __delay_ms(1000);
        
        dutyCycle6 = PID_Calculate(pitSetpoint,pitTemperature);
        
//        if(dutyCycle6<50)dutyCycle6=0;
        loop=0;
        }
//                LCDWriteStringXY(17,2,"Set: ");
  //              LCDWriteInt(pitSetpoint,4,1);
    //            LCDWriteChar(129);                                              // generate degree symbol in font list
      //          LCDWriteChar(70);
        
//        LCDWriteIntXY(7,1,choice,1,0,0);
/*        for(x=0;x<6;x++) analogs[x]=readAnalog(x);
        
        if(analogs[0]<1020)tPadCount+=1;
            
            
        if(analogs[1]<900)tPadCount-=1;
            
        if(tPadCount<1)
        {
            choice=1;
            LCD_Clear();
            LCDWriteStringXY(0,0,"You Chose ");
            LCD_Write_Char(0);
            LCD_Write_Char('F');
            LCDWriteStringXY(0,1,"for User Display");
            tPadCount=10;
            __delay_ms(1000);
            LCD_Clear();
        }
        
        if(tPadCount>19)
        {
            choice=0;
            LCD_Clear();
            LCDWriteStringXY(0,0,"You Chose ");
            LCD_Write_Char(0);
            LCD_Write_Char('C');
            LCDWriteStringXY(0,1,"for User Display");
            tPadCount=10;
            __delay_ms(1000);
            LCD_Clear();
        }
        
        if(analogs[0]<1020&&analogs[1]<970)
        {
            tPadCount=10;
            choice=2;
            LCD_Set_Cursor(0,0);
            LCD_Write_Char(0);
            LCD_Write_Char('F');
            LCD_Write_Char(' ');
            LCD_Write_Char('&');
            LCD_Write_Char(' ');
            LCD_Write_Char(0);
            LCD_Write_Char('C');
            LCD_Write_String(" Chosen ");
            
            LCDWriteStringXY(0,1,"for User Display");
            __delay_ms(100);
            LCD_Clear();
        }
        
        
        
        startDelay+=1;
        
        if(startDelay>254)
        {
            startDelay=254;
            
            if(down<900&&up<900)RESET();
            
            if(down<900)
            {
                resetDelay+=1;
                
                if(resetDelay>20)
                {
                    while(down<975)
                    {
                        down=ADCRead(4);
                        
                        if(bCount<1)LCD_Clear();
                        bCount+=1;

                        if(dutyCycle>0)dutyCycle-=1;
                
                        LCDWriteStringXY(0,0,"   BackLight   ");
                        LCDWriteStringXY(0,1,"Intensity: ");
                        LCD_Write_Int(dutyCycle/10,-1,0,0);
                        LCD_Write_Char('%');
                        LCD_Write_Char(' ');
                        PWM6_LoadDutyValue(dutyCycle);
                    }
                    bCount=0;
                    __delay_ms(1000);
                    LCD_Clear();
                    resetDelay=0;
                }
            }

            if(up<900)
            {
                resetDelay+=1;
                
                if(resetDelay>20)
                {
                    while(up<975)
                    {
                        up=ADCRead(5);

                        if(bCount<1)LCD_Clear();
                        bCount+=1;

                        if(dutyCycle<1009)dutyCycle+=1;
                
                        LCDWriteStringXY(0,0,"   BackLight   ");
                        LCDWriteStringXY(0,1,"Intensity: ");
                        LCD_Write_Int(dutyCycle/10,-1,0,0);
                        LCD_Write_Char('%');
                        LCD_Write_Char(' ');
                        PWM6_LoadDutyValue(dutyCycle);
                    }
                    bCount=0;
                    __delay_ms(1000);
                    LCD_Clear();
                    resetDelay=0;
                }
            }
        }

// *************** Calculate & Display Temp ************************************   
        
        displayTemp = (tempCalc(solarInTemp))-6;
        
        displayTemp2 = tempCalc(solarOutTemp);

        if(loop>254)
        {
            tPadCount=10;
            LCDWriteStringXY(0,0,"In");
            LCD_Write_Char(1);
            LCD_Write_String("Solar");
            
            LCDWriteStringXY(0,1,"Out");
            LCD_Write_Char(1);
            LCD_Write_String("Pool");
  
            if(C_or_F==0)
            {
                LCDWriteIntXY(9,0,(int)displayTemp,-1,1,0);
                LCD_Write_Char(0);
                LCD_Write_Char('C');
                LCD_Write_Char(' ');
            
                LCDWriteIntXY(9,1,(int)displayTemp2,-1,1,0);
                LCD_Write_Char(0);
                LCD_Write_Char('C');
                LCD_Write_Char(' ');
            }
            
            if(C_or_F==1)
            {
                displayTemp = displayTemp*9/5+320;          // Display Temperature in DegF
                displayTemp2 = displayTemp2*9/5+320;        // Display Temperature in DegF

                LCDWriteIntXY(9,0,(int)displayTemp,-1,1,0);
                LCD_Write_Char(0);
                LCD_Write_Char('F');
                LCD_Write_Char(' ');
            
                LCDWriteIntXY(9,1,(int)displayTemp2,-1,1,0);
                LCD_Write_Char(0);
                LCD_Write_Char('F');
                LCD_Write_Char(' ');
            }
            
            
            if(choice==0)C_or_F=0;

            if(choice==1)C_or_F=1;

*/            
        //if(choice==2)C_or_F=1-C_or_F;
/*            LCDWriteIntXY(0,0,analogs[0],-1,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(6,0,analogs[1],-1,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(11,0,analogs[2],-1,0,0);
            LCD_Write_Char(' ');

            LCDWriteIntXY(0,1,analogs[3],-1,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(6,1,analogs[4],-1,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(11,1,analogs[5],-1,0,0);
            LCD_Write_Char(' ');
            
  */          
//            loop=0;
  //      }
        loop+=1;
    }
}
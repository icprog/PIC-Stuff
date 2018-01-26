// *************** Includes ****************************************************    
#include "system.h"
//#include <math.h>

// *************** Defines *****************************************************    
#define CorF            analogs[0]
#define solarInTemp     analogs[1]
#define solarOutTemp    analogs[2]

// *************** Main Routine ************************************************    
void main(void)
{
    SYSTEM_Initialize();
    
    uint16_t analogs[3]     =   {0};
    
    float R, steinhart, displayTemp, displayTemp2;                                    // Calculate R of Thermistor, and Temp using SteinHart/Hart equation

    char count              =   11;
    
    char x                  =   0;
    
    uint16_t dutyCycle      = 1023;
    
    PWM6_LoadDutyValue(dutyCycle);

    __delay_ms(300);
   
    LCD_Clear();
    
/*    LCDWriteStringXY(2,1,"A");
    __delay_ms(200);
    LCDWriteStringXY(3,1,"L");
    __delay_ms(200);
    LCDWriteStringXY(4,1,"O");
    __delay_ms(200);
    LCDWriteStringXY(5,1,"H");
    __delay_ms(200);
    LCDWriteStringXY(6,1,"A");
    __delay_ms(200);
    LCDWriteStringXY(7,1," ");
    __delay_ms(200);
    LCDWriteStringXY(8,1,"D");
    __delay_ms(200);
    LCDWriteStringXY(9,1,"A");
    __delay_ms(200);
    LCDWriteStringXY(10,1,"V");
    __delay_ms(200);
    LCDWriteStringXY(11,1,"I");
    __delay_ms(200);
    LCDWriteStringXY(12,1,"D");
    __delay_ms(200);
    LCDWriteStringXY(13,1,"!");
    __delay_ms(5000);
  */  
    LCD_Clear();

// *************** Read Temperature ********************************************    
    while (1)
    {
        PWM6_LoadDutyValue(dutyCycle);
        
        for(x=0;x<3;x++)
        {
            analogs[x]=readAnalog(x);
        }
        
        if(count>10)
        {
            LCDWriteStringXY(0,0,"Solar In");
            LCDWriteIntXY(9,0,(int)displayTemp,-1,1,0);
            LCD_Write_Char(0);
            LCD_Write_Char('F');
            LCD_Write_Char(' ');
            
            
            
            LCDWriteStringXY(0,1,"Return");
            LCDWriteIntXY(10,1,(int)displayTemp2,-1,1,0);
            LCD_Write_Char(0);
            LCD_Write_Char('F');
            LCD_Write_Char(' ');
            count=0;
        }

// *************** Calculate & Display Temp ************************************   
        
        displayTemp = tempCalc(solarInTemp);
        
        displayTemp2 = tempCalc(solarOutTemp);
/*        R = 10020/(1023/(float)solarInTemp - 1);                    // Resistance of Thermistor (R Reference/1023/readTemp -1)
        steinhart = R /10061;                                           // (R/Ro) R/R Standard (resistance of Thermistor at 25C)
        LCDWriteIntXY(11,1,ADCRead(9),-1,0,0);
        LCDWriteIntXY(0,1,analogs[1],-1,0,0);
        steinhart = log(steinhart);                                     // ln(R/Ro)
        steinhart /= 3995;                                              // 1/Beta * ln(R/Ro)
        steinhart += 1.0 / (25 + 273.15);                               // + (1/To, Temperature in degK @ 25C)
        steinhart = 1.0 / steinhart;                                    // Invert
        steinhart -= 273.15;                                            // convert to DegC

        displayTemp = steinhart*10;
        
        displayTemp = displayTemp*9/5+320;                          // Display Temperature in DegF
            
        R = 10020/(1023/(float)solarOutTemp - 1);                    // Resistance of Thermistor (R Reference/1023/readTemp -1)
        
        steinhart = R /10061;                                           // (R/Ro) R/R Standard (resistance of Thermistor at 25C)
        steinhart = log(steinhart);                                     // ln(R/Ro)
        steinhart /= 3995;                                              // 1/Beta * ln(R/Ro)
        steinhart += 1.0 / (25 + 273.15);                               // + (1/To, Temperature in degK @ 25C)
        steinhart = 1.0 / steinhart;                                    // Invert
        steinhart -= 273.15;                                            // convert to DegC
 

        displayTemp2 = steinhart*10;
        
            displayTemp2 = displayTemp2*9/5+320;                          // Display Temperature in DegF
  */          
        
        count+=1;
    }
}
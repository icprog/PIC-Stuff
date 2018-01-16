// *************** Includes ****************************************************    
#include "system.h"
#include <math.h>

// *************** Defines *****************************************************    
#define     numSamples  50                                              // Number of Temperature readings to Average
#define     SOLARIN     ADCRead(9)
#define     SOLAROUT    ADCRead(11)

// *************** Externally available Variables ******************************    
uint16_t samples[2][numSamples] = {0};

// *************** Main Routine ************************************************    
void main(void)
{
    SYSTEM_Initialize();
   
    uint16_t solarInTemp, solarOutTemp;
    
    float R, steinhart, displayTemp, displayTemp2;                                    // Calculate R of Thermistor, and Temp using SteinHart/Hart equation
    
    static uint16_t sampleIndex0 = 0, sampleIndex1 = 0;

    int32_t totals[2] = {0};

    char count          = 11;
    
   __delay_ms(300);
   
// *************** Read Temperature ********************************************    
    while (1)
    {
        if(count>10)
        {
            LCDWriteStringXY(0,4,"Solar In");
            LCDWriteIntXY(60,4,(int)displayTemp,-1,1,0);
            LCD_Write_Char(0);
            LCD_Write_Char('F');
            LCD_Write_Char(' ');
            
            LCDWriteStringXY(0,5,"Pool Return");
            LCDWriteIntXY(60,5,(int)displayTemp2,-1,1,0);
            LCD_Write_Char(0);
            LCD_Write_Char('F');
            LCD_Write_Char(' ');
            count=0;
        }

        solarInTemp = SOLARIN;                           // Assign the just read temperature to the location of the current oldest data
            
        totals[0] = totals[0] - samples[0][sampleIndex0];   // Subtract the oldest sample data from the total

        samples[0][sampleIndex0] = solarInTemp;             // Assign the just read temperature to the location of the current oldest data

        totals[0] = totals[0] + samples[0][sampleIndex0];   // Add that new sample to the total
            
        sampleIndex0 += 1;                                  // and move to the next index location
            
        if(sampleIndex0 >= numSamples)
        {
            sampleIndex0 = 0;
        }
            
        solarInTemp = totals[0] / numSamples;                          // assign the average value of total to the readTemperature variable
        


        solarOutTemp = SOLAROUT;                                       // Assign the just read temperature to the location of the current oldest data
            
        totals[1] = totals[1] - samples[1][sampleIndex1];                         // Subtract the oldest sample data from the total

        samples[1][sampleIndex1] = solarOutTemp;                         // Assign the just read temperature to the location of the current oldest data

        totals[1] = totals[1] + samples[1][sampleIndex1];                         // Add that new sample to the total
            
        sampleIndex1 += 1;                                               // and move to the next index location
            
        if(sampleIndex1 >= numSamples)
        {
            sampleIndex1 = 0;
        }
            
        solarOutTemp = totals[1] / numSamples;                          // assign the average value of total to the readTemperature variable
        
// *************** Calculate & Display Temp ************************************    
        R = 10010/(1023/(float)solarInTemp - 1);                    // Resistance of Thermistor (R Reference/1023/readTemp -1)
        
        steinhart = R /10061;                                           // (R/Ro) R/R Standard (resistance of Thermistor at 25C)
        steinhart = log(steinhart);                                     // ln(R/Ro)
        steinhart /= 3995;                                              // 1/Beta * ln(R/Ro)
        steinhart += 1.0 / (25 + 273.15);                               // + (1/To, Temperature in degK @ 25C)
        steinhart = 1.0 / steinhart;                                    // Invert
        steinhart -= 273.15;                                            // convert to DegC

        displayTemp = steinhart*10;
        
            displayTemp = displayTemp*9/5+320;                          // Display Temperature in DegF
            

            
        R = 9975/(1023/(float)solarOutTemp - 1);                    // Resistance of Thermistor (R Reference/1023/readTemp -1)
        
        steinhart = R /10061;                                           // (R/Ro) R/R Standard (resistance of Thermistor at 25C)
        steinhart = log(steinhart);                                     // ln(R/Ro)
        steinhart /= 3995;                                              // 1/Beta * ln(R/Ro)
        steinhart += 1.0 / (25 + 273.15);                               // + (1/To, Temperature in degK @ 25C)
        steinhart = 1.0 / steinhart;                                    // Invert
        steinhart -= 273.15;                                            // convert to DegC
 

        displayTemp2 = steinhart*10;
        
            displayTemp2 = displayTemp2*9/5+320;                          // Display Temperature in DegF
            
        
        count+=1;
       }
  //  }
}
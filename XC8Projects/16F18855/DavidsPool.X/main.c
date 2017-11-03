// *************** Includes ****************************************************    
#include "system.h"
#include <math.h>

// *************** Defines *****************************************************    
#define     numSamples  50                                              // Number of Temperature readings to Average

// *************** Externally available Variables ******************************    
uint16_t samples[numSamples] = {0};

// *************** Main Routine ************************************************    
void main(void)
{
    SYSTEM_Initialize();
   
    uint16_t readTemperature, readTemperatureOld, seconds = 0, counter = 0, minutes = 0;
    
    uint8_t  toggle = 0;
    
    float R, steinhart, displayTemp;                                                 // Calculate R of Thermistor, and Temp using SteinHart/Hart equation
    
    static uint16_t sampleIndex = 0;

    int32_t totals = 0;

// *************** Read Temperature ********************************************    
    while (1)
    {
        readTemperature = ADCC_GetSingleConversion(2);                  // Assign the just read temperature to the location of the current oldest data
            
        totals = totals - samples[sampleIndex];                         // Subtract the oldest sample data from the total

        samples[sampleIndex] = readTemperature;                         // Assign the just read temperature to the location of the current oldest data

        totals = totals + samples[sampleIndex];                         // Add that new sample to the total
            
        sampleIndex += 1;                                               // and move to the next index location
            
        if(sampleIndex >= numSamples)
        {
            sampleIndex = 0;
        }
            
        readTemperature = totals / numSamples;                          // assign the average value of total to the readTemperature variable
        
// *************** Calculate & Display Temp ************************************    
        R = 10200/(1023/(float)readTemperature - 1);                    // Resistance of Thermistor (R Reference/1023/readTemp -1)
        
        steinhart = R /10061;                                           // (R/Ro) R/R Standard (resistance of Thermistor at 25C)
        steinhart = log(steinhart);                                     // ln(R/Ro)
        steinhart /= 3995;                                              // 1/Beta * ln(R/Ro)
        steinhart += 1.0 / (25 + 273.15);                               // + (1/To, Temperature in degK @ 25C)
        steinhart = 1.0 / steinhart;                                    // Invert
        steinhart -= 273.15;                                            // convert to DegC
 

        displayTemp = steinhart*10;
        
        if(toggle == 1)
        {
            displayTemp = displayTemp*9/5+320;                          // Display Temperature in DegF
            
            LCDWriteIntXY(0,0,(int)displayTemp,-1,1,0);
            LCDWriteCharacter(0);
            LCDWriteCharacter('F');
            LCDWriteCharacter(' ');
        }
        else
        {
            LCDWriteIntXY(0,0,(int)displayTemp,-1,1,0);                      //Display Temperature in DegC
            LCDWriteCharacter(0);
            LCDWriteCharacter('C');
            LCDWriteCharacter(' ');
        }
        
// *************** Timer for Display Update ************************************    
        counter +=1;                                                    // toggle counter
        
        if(counter>12)
        {
            toggle = 1-toggle;                                          // toggle C or F on Display
            counter = 0;
        }

// *************** Test if a Button or Buttons are being pressed ***************  (user.h)   
        readButtons();                                                  // check if a button is pressed         
    }
}
#include "system.h"
#include "lcd.h"
#include <math.h>
#include <stdio.h>

#define     numSamples  50                                                      // Number of Temperature readings to Average


uint16_t samples[numSamples];


void main(void)
{
    SYSTEM_Initialize();
   
    uint16_t readTemperature, setpoint = 24, outCurrent = PWM6_INITIALIZE_DUTY_VALUE, readTemperatureOld, timer = 0, counter = 0, minute = 0;
    
    unsigned char startupTimer = 0, firstTimeThrough = 0;
    
    float R, steinhart;
    
    char s[8];
    
    static uint16_t sampleIndex = 0;

    int32_t totals = 0;
    

    
    while (1)
    {
        readTemperature = ADCC_GetSingleConversion(2);                          // Assign the just read temperature to the location of the current oldest data
            
        totals = totals - samples[sampleIndex];                                 // Subtract the oldest sample data from the total

        samples[sampleIndex] = readTemperature;                                 // Assign the just read temperature to the location of the current oldest data

        totals = totals + samples[sampleIndex];                                 // Add that new sample to the total
            
        sampleIndex += 1;                                                       // and move to the next index location
            
        if(sampleIndex >= numSamples)
        {
            sampleIndex = 0;
        }
            
        readTemperature = totals / numSamples;                                  // assign the average value of total to the readTemperature variable
        
        if(startupTimer >= 250)
        {
            if(firstTimeThrough == 0)
            {
                readTemperatureOld = readTemperature;
                firstTimeThrough +=1;
            }
            
            if(readTemperature > readTemperatureOld)
            {
                readTemperatureOld += 1;
            }
        
            if(readTemperature < readTemperatureOld)
            {
                readTemperatureOld -= 1;
            }
        
            readTemperature = readTemperatureOld;
            
            startupTimer = 249;
        }


        
        if(setpoint > steinhart)
        {
            if(outCurrent < 1022)
            {
                    outCurrent++;
            }
            else
            {
                outCurrent = 1023;
            }
        }
        
        if(setpoint < steinhart)
        {
            if(outCurrent > 1)
            {
                outCurrent-=1;
            }
            else
            {
                outCurrent = 0;
            }
        }

        PWM6_LoadDutyValue(outCurrent);
        
        R = 10200/(1023/(float)readTemperature - 1);                            // Resistance of Thermistor (R Reference/1023/readTemp -1)
        
        steinhart = R /10061;                                                   // (R/Ro) R/R Standard (resistance of Thermistor at 25C)
        steinhart = log(steinhart);                                             // ln(R/Ro)
        steinhart /= 3995;                                                      // 1/Beta * ln(R/Ro)
        steinhart += 1.0 / (25 + 273.15);                                       // + (1/To, Temperature in degK @ 25C)
        steinhart = 1.0 / steinhart;                                            // Invert
        steinhart -= 273.15;                                                    // convert to DegC
 
//        percentOutput = (uint16_t)(outCurrent*.09765625);
        
//        measuredCurrent = (uint16_t)(readCurrent * 1.5454545454);
        
        
//        LCDWriteIntXY(0,0,measuredCurrent,-1,0,0);
  //      LCD_Write_Char('m');
    ///    LCD_Write_Char('a');
       // LCD_Write_Char(' ');
//        LCD_Write_Char(' ');

  //      LCDWriteIntXY(0,8,percentOutput,2,0,0);
    //    LCD_Write_Char('%');
      //  LCD_Write_Char(' ');
        //LCD_Write_Char(' ');



        sprintf(s,"%3.1f", steinhart );
        LCD_Set_Cursor(0,0);
        LCD_Write_String(s);
        LCD_Write_Char(0);
        LCD_Write_Char('C');
        LCD_Write_Char(' ');
        LCD_Write_Char(' ');

        sprintf(s,"%d  ", minute);
        LCD_Set_Cursor(1,0);
        LCD_Write_String(s);

        startupTimer +=1;
        counter+=1;
        
        if(setpoint - steinhart < 2)
        {
            if(counter>=314)
            {
                minute+=1;
                counter = 0;
            }
        }
        CLRWDT();
    }
}
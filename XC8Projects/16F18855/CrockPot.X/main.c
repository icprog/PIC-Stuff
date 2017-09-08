#include "system.h"
#include "lcd.h"
#include <math.h>
#include "user.h"

#define     numSamples  50                                                      // Number of Temperature readings to Average


uint16_t samples[numSamples];

uint8_t setpoint = 70, presets[5]={0,70,95,105,120};


void main(void)
{
    SYSTEM_Initialize();
   
    uint16_t readTemperature, outCurrent = PWM6_INITIALIZE_DUTY_VALUE, readTemperatureOld, displayTemp = 70, counter = 0, counter2 = 0, minute = 0;
    
    uint8_t startupTimer = 0, firstTimeThrough = 0, toggle = 0;
    
    float R, steinhart;
    
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
        
        if(startupTimer >= 70)
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

            if(setpoint > steinhart)
            {
                if(outCurrent < 1023)
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
                if(outCurrent > 0)
                {
                    outCurrent-=1;
                }
                else
                {
                    outCurrent = 0;
                }
            }

            PWM6_LoadDutyValue(outCurrent);                                         // Load DutyCycle to control output at desired temperature
            
            startupTimer = 69;
        }


        
        
        R = 10200/(1023/(float)readTemperature - 1);                            // Resistance of Thermistor (R Reference/1023/readTemp -1)
        
        steinhart = R /10061;                                                   // (R/Ro) R/R Standard (resistance of Thermistor at 25C)
        steinhart = log(steinhart);                                             // ln(R/Ro)
        steinhart /= 3995;                                                      // 1/Beta * ln(R/Ro)
        steinhart += 1.0 / (25 + 273.15);                                       // + (1/To, Temperature in degK @ 25C)
        steinhart = 1.0 / steinhart;                                            // Invert
        steinhart -= 273.15;                                                    // convert to DegC
 

        displayTemp = (uint16_t)steinhart * 10;
        
        if(toggle == 1)
        {
            displayTemp = displayTemp*9/5+320;                                  // Display Temperature in DegF
            LCDWriteIntXY(0,1,displayTemp,-1,1,0);
            LCD_Write_Char(0);
            LCD_Write_Char('F');
            LCD_Write_Char(' ');
        }
        else
        {
            LCDWriteIntXY(0,1,displayTemp,-1,1,0);                              //Display Temperature in DegC
            LCD_Write_Char(0);
            LCD_Write_Char('C');
            LCD_Write_Char(' ');
        }
        
//        LCDWriteStringXY(1,0,"Time:")
  //      LCDWriteIntXY(1,5,minute,-1,0,0);                                       // Display Number of minutes spent within 2 DegC of Setpoint (or hotter))

        LCDWriteIntXY(1,0,counter,-1,0,0);
        LCD_Write_Char(' ');
        startupTimer +=1;                                                       // Hold PWM at 100% while temperature reading stabilizes
//        counter+=1;                                                             // Minute counter
        counter2 +=1;                                                           // toggle counter
        
        if(TMR0IF)
        {
            TMR0H   =   0x24;               // Load Preset to Timer0 of 63750 (at 255KHz, this should produce 1 rollover/second)
            TMR0L   =   0xB8;
            TMR0IF = 0;
            counter+=1;
        }
        
        if(counter2>12)
        {
            toggle = 1-toggle;
            counter2 = 0;
        }
        
        if(setpoint - steinhart < 2)
        {
            if(counter>=314)
            {
                minute+=1;
//                counter = 0;
            }
        }
        readButtons();                                                          // check if a button is pressed
        tempSetpoint();
//        CLRWDT();
    }
}
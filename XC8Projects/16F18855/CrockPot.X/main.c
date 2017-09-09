#include "system.h"
#include "lcd.h"
#include <math.h>
#include "user.h"
#include "PID_Lib.h"
#include <stdio.h>
// *****************************************************************************    

#define     numSamples  50                                              // Number of Temperature readings to Average

uint16_t samples[numSamples];

uint8_t setpoint = 70, presets[5]={0,70,95,105,120};                    // PreSet Temps Selected by pressing both buttons at same time

// *****************************************************************************    
void main(void)
{
    SYSTEM_Initialize();
   
    uint16_t readTemperature, PWM_Output = PWM6_INITIALIZE_DUTY_VALUE, readTemperatureOld, displayTemp = 70, seconds = 0, counter = 0, minutes = 0;
    
    uint8_t startupTimer = 0, firstTimeThrough = 0, toggle = 0;
    
    float R, steinhart;                                                 // Calculate R of Thermistor, and Temp using SteinHart/Hart equation
    
    static uint16_t sampleIndex = 0;

    int32_t totals = 0;
    

// *****************************************************************************    
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
        
// *****************************************************************************    
        if(startupTimer >= 70)                                          // has been running at least 10 seconds
        {
            if(firstTimeThrough == 0)
            {
                readTemperatureOld = readTemperature;
                counter = 0;
                firstTimeThrough +=1;                                   // firstTimeThrough has been incremented once, will not come here
            }                                                           // till reset, so, no need to limit count of firstTimeThrough
            
            if(readTemperature > readTemperatureOld)
            {
                readTemperatureOld += 1;
            }
        
            if(readTemperature < readTemperatureOld)
            {
                readTemperatureOld -= 1;
            }
        
            readTemperature = readTemperatureOld;

            PWM_Output = (int)PID_Calculate(setpoint, steinhart);       // Calculate DutyCycle (PWM_Output)  
            
            if((setpoint-steinhart)>4)                                  // Turn on output @100% until within 4 DegC of setpoint
            {
                PWM_Output = 1023;
            }
            
            PWM6_LoadDutyValue(PWM_Output);                             // Load DutyCycle to control output at desired temperature
            
            startupTimer = 69;
        }

        startupTimer +=1;                                               // Hold PWM at 100% while temperature reading stabilizes

// *****************************************************************************    
        R = 10200/(1023/(float)readTemperature - 1);                    // Resistance of Thermistor (R Reference/1023/readTemp -1)
        
        steinhart = R /10061;                                           // (R/Ro) R/R Standard (resistance of Thermistor at 25C)
        steinhart = log(steinhart);                                     // ln(R/Ro)
        steinhart /= 3995;                                              // 1/Beta * ln(R/Ro)
        steinhart += 1.0 / (25 + 273.15);                               // + (1/To, Temperature in degK @ 25C)
        steinhart = 1.0 / steinhart;                                    // Invert
        steinhart -= 273.15;                                            // convert to DegC
 

        displayTemp = (uint16_t)(steinhart * 10);
        
        if(toggle == 1)
        {
            displayTemp = displayTemp*9/5+320;                          // Display Temperature in DegF
            LCDWriteIntXY(0,1,displayTemp,-1,1,0);
            LCD_Write_Char(0);
            LCD_Write_Char('F');
            LCD_Write_Char(' ');
        }
        else
        {
            LCDWriteIntXY(0,1,displayTemp,-1,1,0);                      //Display Temperature in DegC
            LCD_Write_Char(0);
            LCD_Write_Char('C');
            LCD_Write_Char(' ');
        }
// *****************************************************************************  (lcd.h)  
//        LCDWriteStringXY(1,0,"Time:")
        LCDWriteIntXY(1,4,PWM_Output,4,0,0);                              // Display Number of minutes spent within 2 DegC of Setpoint (or hotter))
        LCD_Write_Char(' ');

// *****************************************************************************    
        counter +=1;                                                    // toggle counter
        
        if(counter>12)
        {
            toggle = 1-toggle;                                          // toggle C or F on Display
            counter = 0;
        }

// *****************************************************************************  (timers.h)   
        if(TMR0IF)
        {
            TMR0H   =   0x24;                                           // Load Preset to Timer0 of 9375 (at current processor speed,
            TMR0L   =   0x9F;                                           // this should produce 1 rollover/second)
            TMR0IF = 0;                                                 // Reset Interrupt Flag
            seconds+=1;                                                         // And increment seconds counter
        }
        
        if(setpoint - steinhart < 2)                                    //If at, near, or over setpoint, start counting time in minutes
        {
            if(seconds>63)                                              // Was counting fast, so, make it count extra seconds
            {
                minutes+=1;                                                          
                seconds = 0;
            }
        }
        
// *****************************************************************************  (user.h)   
        readButtons();                                                  // check if a button is pressed         
        tempSetpoint();                                                 // Set Temperature if user is asking    
    }
}
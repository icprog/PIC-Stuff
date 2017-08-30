#include <xc.h>
#include "system.h"
#include "user.h"
#include "interupts.h"
#include "lcd.h"

#define numSamples          20                                                  //Number of samples to average for current reading


unsigned char output = 255;

void main()
{
    Init();                                                                     // Init Ports & PWM Setup

    __delay_ms(250);                                                            // Power Up delay for LCD
    
    LCD_Init(0);                                                                // Init LCD
    
    LCD_Clear();                                                                // Clear Screen

    PORTCbits.RC0 = 1;

    
//    extern unsigned char output;
    unsigned char setpoint, readTemperature, tempReadTemperature;
    unsigned char x;
    unsigned int total;
    int samples[numSamples];                                                    //Samples to average current over x number of samples
    unsigned char sampleIndex = 0;                                              //Used to calculate average current measurement
    

    while(1)                                                                    // Infinite loop
    {
        tempReadTemperature = ADCRead(3);                                       // Read current & assign it to a temporary variable 
            
        total = total - samples[sampleIndex];                                   // Subtract the oldest sample data from the total

        samples[sampleIndex] = tempReadTemperature;                             // Assign the just read current measurement to the location of the currently oldest data

        total = total + samples[sampleIndex];                                   // Add that new sample to the total
           
        sampleIndex += 1;                                                       // and move to the next index location
            
        if(sampleIndex >= numSamples)
        {
            sampleIndex = 0;
        }
            
        readTemperature = total / numSamples;                                   // assign the average current value of total to the readCurrent variable
        



                 
        for(x = 0 ; x < 255 ; x++)
        {
            setpoint = (setpoint + ADCRead(2))/2;
        }
        
        __delay_ms(1000);
        

        if(setpoint >= readTemperature + 2)
        {
            if(output < 255)
            {
                output+=1;
            }
            else
            {
                output = 255;
            }
        }
        

        if(setpoint <= readTemperature - 2)
        {
            
            
            if(output > 0)
            {
                output-=1;
            }
            else
            {
                output = 0;
            }
        }
        

        LCD_Clear();
    
        
        LCDWriteStringXY(0,0,"PWM=");
        LCDWriteIntXY(0,4,CCPR1L,3,0,0);

        LCDWriteStringXY(0,8,"OP=");
        LCDWriteIntXY(0,11,output,3,0,0);

        LCDWriteStringXY(1,0,"MV=");
        LCDWriteIntXY(1,3,readTemperature,3,0,0);
    }
}

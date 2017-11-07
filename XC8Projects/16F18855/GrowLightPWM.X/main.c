#include "system.h"


void main(void)
{
    SYSTEM_Initialize();                        // Initialize the Device
    
    extern unsigned int I;                      // Average value of Vsense
    
    unsigned int currentFlow    = 0;            // Calculated Current Flow (based on Vsense)
    
    unsigned int setPoint       = 700;          // Current Flow Set Point
    
    unsigned int dutyCycle      = 0;            // Output Duty Cycle required to drive LED's
    
    signed char count           = 0;
    
    unsigned int count3 = 0;
    
    drawBox();                                  // Draw an Outline around the display

    while (1)
    {
        currentFlow = I;                        // Do some math to make Voltage = Current in circuit  FIX
        
        if(currentFlow>setPoint)                // currentFlow is too high
        {
            count-=1;
            
            if(count<-2)
            {
                dutyCycle>0?dutyCycle-=1:dutyCycle; // if currentFlow is >0, decrement Output
                count = 0;
            }
        }
        else if(currentFlow<setPoint)           // currentFlow is below setPoint, so,           
        {
            count+=1;
            if(count>2)
            {
                dutyCycle<1023?dutyCycle+=1:dutyCycle;// if currentFlow is less than Maximum, increment Output
                count = 0;
            }
        }
        else

            
        PWM6_LoadDutyValue(dutyCycle);          // Load the just calculated dutyCycle
        
        LCDWriteStringXY(4,1,"Set Point:");
        LCD_Write_Int(setPoint,-1,0,0);
        LCD_Write_String("mA ");

        LCDWriteStringXY(8,2,"Amperage:");
        LCD_Write_Int(currentFlow,-1,0,0);
        LCD_Write_String("mA ");
        
        LCDWriteStringXY(4,3,"DutyCycle:");
        LCD_Write_Int(dutyCycle,5,0,0);
        
        LCDWriteStringXY(20,4,"Count:");
        LCD_Write_Int(count,-1,0,1);
        LCD_Write_Character(' ');
        LCD_Write_Character(' ');
        
        LCDWriteIntXY(4,5,count3,5,0,0)
        
        if(PIR4bits.TMR2IF)
        {
            count3+=1;
        }
        
        CLRWDT();                               // Clear the WatchDog Timer
    }
}
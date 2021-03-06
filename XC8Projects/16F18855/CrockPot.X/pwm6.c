#include <xc.h>
#include "pwm6.h"

void PWM6_Initialize(void)
{
    PWM6CON = 0x80;                     // Pg 287, PWM6POL active_hi; PWM6EN enabled;
     
    PWM6DCH = 0xFF;                     //0xFF;                     // Pg 288, Duty Cycle High ; FFC0 = 1023
     
    PWM6DCL = 0xC0;                     //0xC0;                     // Pg 288, Duty Cycle Low ;
     
    CCPTMRS1bits.P6TSEL = 0x1;          //Pg 456, PWM6 Timer Selection 0X1 = TMR2
}

void PWM6_LoadDutyValue(uint16_t dutyValue)
{
    PWM6DCH = (dutyValue & 0x03FC)>>2;  // Writing to 8 MSBs of PWM duty cycle in PWMDCH register (Duty Cycle High))
    
    PWM6DCL = (dutyValue & 0x0003)<<6;  // Writing to 2 LSBs of PWM duty cycle in PWMDCL register (Duty Cycle Low))
}
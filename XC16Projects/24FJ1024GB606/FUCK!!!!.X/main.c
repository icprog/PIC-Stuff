#include    "system.h"                                                          // System funct/params, like osc/peripheral config
//#include    "menu.h"

int main(void)
{
    
    int dutyCycle = 1000;
    
    void InitializeTimers(void)
    {
        T1CONbits.TON =     0;                          // Timer1 is used for generating PWM frequency
        T1CONbits.TCS =     1;                          // Timer Clock source selected by T1ECS
        T1CONbits.T1ECS =   0x0;                        // Timer 1 Extended Clock Selection bits (00 = Secondary Oscillator)
        T1CONbits.TCKPS =   0x1;                        // Timer 1 input clock pre-scale bits 01 = 1:8 
        TMR1 =              0x0000;                     // Timer 1 preset value??
        PR1 =               0x03FF;                     // Timer 1 Period value of .25 Seconds for a Frequency of 4Hz
        T1CONbits.TON =     1;                          // TIMER 1 ON
        T2CONbits.TON =     0;                          // Turn Timer OFF
        PR2 =               0x2000;                     // Period value set in Timer 2, to make it so Timer 2 rolls over every 1/100th seconds
        T2CONbits.TON =     1;                          // Turn Timer 2 ON
    }
// *****************************************************************************

void Initialize_PWM(void)
{
    OC5CON2bits.OCTRIS  =   0;
    OC5R =                  0x0000;                 // Set On time (Duty Clcle))
    OC5RS =                 0x2000;                 // Set Period for Edge aligned PWM
    OC5CON2bits.SYNCSEL =   0X1F;                   // Set Timer 1 as Sync source
    OC5CON2bits.OCTRIG =    0;                      // Set OC3 as Sync source
    OC5CON1bits.OCTSEL =    0;                    // Set Timer 2 as clock source
//    OC5TMR =                0x0000;                 // Set OC3 timer to zero
    OC5CON1bits.OCM =       0x6;                    // Set OC3 Mode to Edge aligned PWM (Center aligned works as well, except it is on until OCxR, turns off until OCxRS, so, 
}                                                   // dutyCycle of zero turns ON OC, until it hits OCxRS (works fine down to dC of 1, then goes to pulsing mode)
// *****************************************************************************
void setDutyCycle(unsigned int dutyCycle)
{
    OC5R = dutyCycle;                              
}
    SYSTEM_Initialize();

    uint16_t count, count3;
    
    Initialize_PWM();
    
    setDutyCycle(8192);
    
    while(1)
    {
        
        T1CONbits.TON = 1;
        T2CONbits.TON = 1;
//        xxx +=1;
        if(IFS0bits.T2IF)
        {
            IFS0bits.T2IF = 0;
            count+=1;
        }
        if(IFS0bits.T1IF)
        {
            IFS0bits.T1IF = 0;
            count3+=1;
        }
        
        LCDWriteIntXY(0,0,count,5,0,0);
        LCDWriteIntXY(42,0,count3,5,0,0);
        
        

        
// ******************************************************************************
        ClrWdt();                                                               //Clear (Re-Set) the WatchDog Timer
    }
    return(1);
}
//***************************************************************************************************************************************************************

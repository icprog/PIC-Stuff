#include "pwm.h"


// PWM Setup    Timer 1 is set to use Secondary Oscillator (32768 Hz), with the Pre-Scaler set at 1:8, giving us 4096 Hz (32768/8)
// We then set PR1 to 0x3FF (1023, which gives us 1024 counts, 0 - 1023), so the timer will roll over 4 times in one second.
// We then can set our dutyCycle anywhere between 0 (OFF) and 2047 (ON 100%)



    void InitializeTimers(void)
    {
        T1CONbits.TON =     0;                          // Timer1 is used for generating PWM frequency
        T1CONbits.TCS =     1;                          // Timer Clock source selected by T1ECS
        T1CONbits.T1ECS =   0x0;                        // Timer 1 Extended Clock Selection bits (00 = Secondary Oscillator)
        T1CONbits.TCKPS =   0x1;                        // Timer 1 input clock pre-scale bits 01 = 1:8 
        TMR1 =              0x0000;                     // Timer 1 preset value??
        PR1 =               0x03FF;                     // Timer 1 Period value of .25 Seconds for a Frequency of 4Hz
        T1CONbits.TON =     1;                          // TIMER 1 ON

        T2CONbits.TON   =   0;                          // Turn Timer OFF
        T2CONbits.TCS   =   1;                          // Timer Clock source selected by T1ECS
        T2CONbits.TECS  =   0x0;                        // Timer 2 Extended Clock Selection bits (00 = Secondary Oscillator)
        T2CONbits.TCKPS =   0x0;                        // Timer 2 input clock pre-scale bits 01 = 1:8 
//        TMR2 =              0x0000;                     // Timer 1 preset value??
        PR2 =               0x2000;                     // Period value set in Timer 2, to make it so Timer 2 rolls over every 1/100th seconds
        T2CONbits.TON =     1;                          // Turn Timer 2 ON
    }
// *****************************************************************************

void Initialize_PWM(void)
{
//    OC5CON2bits.OCTRIS  =   0;
    OC4R =                  0x0000;                 // Set On time (Duty Cycle) OCx Pin will output high, until timer resource reaches OCxR, then pin is set low, so if OCxR is 0, no output
    OC4RS =                 0x2000;                 // Set Period for Edge aligned PWM, OCx resets, and resets timer, when timer reaches OCxRS
    OC4CON2bits.SYNCSEL =   0X1F;                   // Set OCxRS as Sync source, so, the OCx is technically it's own sync source
    OC4CON2bits.OCTRIG =    0;                      // Set Synchronous operation
    OC4CON1bits.OCTSEL =    0;                      // Set Timer 2 as clock source (Timer2 is the default))
//    OC5TMR =                0x0000;                 // Set OC3 timer to zero
    OC4CON1bits.OCM =       0x6;                    // Set OC3 Mode to Edge aligned PWM (Center aligned works as well, except it is on until OCxR, turns off until OCxRS, so, 

    OC5R =                  0x0000;                 // Set On time (Duty Cycle))
    OC5RS =                 0x2000;                 // Set Period for Edge aligned PWM
    OC5CON2bits.SYNCSEL =   0X1F;                   // Set Set OCxRS as Sync source
    OC5CON2bits.OCTRIG =    0;                      // Set OC3 as Sync source
    OC5CON1bits.OCTSEL =    0;                      // Set Timer 2 as clock source
//    OC5TMR =                0x0000;                 // Set OC3 timer to zero
    OC5CON1bits.OCM =       0x6;                    // Set OC3 Mode to Edge aligned PWM (Center aligned works as well, except it is on until OCxR, turns off until OCxRS, so, 

    OC6R =                  0x0000;                 // Set On time (Duty Cycle))
    OC6RS =                 0x2000;                 // Set Period for Edge aligned PWM
    OC6CON2bits.SYNCSEL =   0X03;                   // Set Set OC5RS as Sync source??
    OC6CON2bits.OCTRIG =    0;                      // Set OC3 as Sync source
    OC6CON1bits.OCTSEL =    0;                      // Set Timer 2 as clock source
//    OC6TMR =                0x0000;                 // Set OC3 timer to zero
    OC6CON1bits.OCM =       0x7;                    // Set OC3 Mode to Edge aligned PWM (Center aligned works as well, except it is on until OCxR, turns off until OCxRS, so, 
}                                                   // dutyCycle of zero turns ON OC, until it hits OCxRS (works fine down to dC of 1, then goes to pulsing mode)
// *****************************************************************************
void setDutyCycle(unsigned int dutyCycle)
{
    OC4R = dutyCycle;                              
    OC5R = dutyCycle -1000;                              
    OC6R = dutyCycle; 
    
    if(_OC6IF)
    {
        ;
    }
}

/*void InitializeTimers(void)
{
    T1CONbits.TON   =   0;                          // Timer1 is used for generating PWM frequency
    T1CONbits.TCS   =   1;                          // Timer Clock source selected by T1ECS
    T1CONbits.T1ECS =   0x0;                        // Timer 1 Extended Clock Selection bits (00 = Secondary Oscillator)
    T1CONbits.TCKPS =   0x1;                        // Timer 1 input clock pre-scale bits 01 = 1:8 
    TMR1            =   0x0000;                     // Timer 1 preset value??
    PR1             =   0x03FF;                     // Timer 1 Period value of .25 Seconds for a Frequency of 4Hz
    T1CONbits.TON   =   1;                          // TIMER 1 ON
    
    T2CONbits.TON   =   0;                          // Turn Timer OFF
    T2CONbits.TCS   =   1;                          // Timer 2 Clock source selected by T2ECS
    T2CONbits.TECS  =   0x0;                        // Run Timer 2 from Secondary Oscillator
    TMR2            =   0x0000;
    PR2             =   0x2000;                     // Period value set in Timer 2, to make it so Timer 2 rolls over every .25 seconds
    T2CONbits.TON   =   1;                          // Turn Timer 2 ON
}
// *****************************************************************************

void Initialize_PWM(void)
{
    OC6CON2bits.OCTRIS  =   0;
    OC6R =                  0x0000;                 // Set On time (Duty Clcle))
    OC6RS =                 0x2000;                 // Set Period for Edge aligned PWM
    OC6CON2bits.SYNCSEL =   0X1F;                   // Set Timer 1 as Sync source
    OC6CON2bits.OCTRIG =    0;                      // Set OC3 as Sync source
    OC6CON1bits.OCTSEL =    0;                    // Set Timer 2 as clock source
//    OC5TMR =                0x0000;                 // Set OC3 timer to zero
    OC6CON1bits.OCM =       0x6;                    // Set OC3 Mode to Edge aligned PWM (Center aligned works as well, except it is on until OCxR, turns off until OCxRS, so, 

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
// *****************************************************************************
void setDutyCycle(unsigned int dutyCycle)
{
    OC6R = dutyCycle;                              
    OC5R = dutyCycle;                              
}
// *****************************************************************************
*/
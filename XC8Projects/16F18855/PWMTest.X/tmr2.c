#include <xc.h>
#include "tmr2.h"

void TMR2_Initialize(void)
{
    T2CON = 0x02;                   // T2CKPS 1:4 Clock PreScaler; T2OUTPS 1:1 Out PostScaler; TMR2ON off;
    
    T2CLKCON = 0x01;                // Pg 440, T2CS(T2 Clock Source) FOSC/4; 
    
    T2HLT = 0x00;                   // Pg 442, Hardware Limit Cntrl, T2PSYNC Not Synchronized; T2MODE Software control; T2CKPOL Ris ing Edge; T2CKSYNC Not Synchronized;
                                    // Setup as freerunning software gated
    T2RST = 0x00;                   // Pg 443, External Reset Source, T2RSEL T2CKIPPS pin;

    T2PR = 0xFF;                    // Period register, PR2 120; 

    T2TMR = 0x00;                   // TMR2 0;
    
    PIR4bits.TMR2IF = 0;            // Clearing IF flag.

    T2CONbits.TMR2ON = 1;           // Start the Timer by writing to TMRxON bit
}
/*
void TMR2_ModeSet(TMR2_HLT_MODE mode)
{
   // Configure different types HLT mode
    T2HLTbits.MODE = mode;
}

void TMR2_ExtResetSourceSet(TMR2_HLT_EXT_RESET_SOURCE reset)
{
    //Configure different types of HLT external reset source
    T2RSTbits.RSEL = reset;
}

void TMR2_Start(void)
{
    T2CONbits.TMR2ON = 1;           // Start the Timer by writing to TMRxON bit
}

void TMR2_StartTimer(void)
{
    TMR2_Start();
}

void TMR2_Stop(void)
{
    // Stop the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 0;
}

void TMR2_StopTimer(void)
{
    TMR2_Stop();
}

uint8_t TMR2_Counter8BitGet(void)
{
    uint8_t readVal;

    readVal = TMR2;

    return readVal;
}

uint8_t TMR2_ReadTimer(void)
{
    return TMR2_Counter8BitGet();
}

void TMR2_Counter8BitSet(uint8_t timerVal)
{
    // Write to the Timer2 register
    TMR2 = timerVal;
}

void TMR2_WriteTimer(uint8_t timerVal)
{
    TMR2_Counter8BitSet(timerVal);
}

void TMR2_Period8BitSet(uint8_t periodVal)
{
   PR2 = periodVal;
}

void TMR2_LoadPeriodRegister(uint8_t periodVal)
{
   TMR2_Period8BitSet(periodVal);
} */
/*
bool TMR2_HasOverflowOccured(void)
{
    // check if  overflow has occurred by checking the TMRIF bit
    bool status = PIR4bits.TMR2IF;
    if(status)
    {
        // Clearing IF flag.
        PIR4bits.TMR2IF = 0;
    }
    return status;
} */
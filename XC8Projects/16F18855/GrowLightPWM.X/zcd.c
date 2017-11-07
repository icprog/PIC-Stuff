#include "zcd.h"

#define     numSamples  50                      // Number of Temperature readings to Average

unsigned int samples[numSamples]        = {0};

unsigned int Vsense                     = 0;    // Voltage across Rsense

unsigned int I                          = 0;    // Current Calculatedd from Vsense

unsigned int sampleIndex                = 0;

int32_t totals                          = 0;


void ZCD_Initialize (void)
{
    ZCD1CON = 0x82;                             // ZCD1POL not inverted; ZCD1EN enabled; ZCD1INTP enabled; ZCD1INTN disabled; 

    PIR2bits.ZCDIF = 0;                         // Clear IF flag before enabling the interrupt.

    PIE2bits.ZCDIE = 1;                         // Enabling ZCD interrupt.
}

void ZCD_ISR(void)
{
    PIR2bits.ZCDIF = 0;                         // Clear the ZCD interrupt flag
    
    Vsense = ADCRead(7);                        // Measure the Voltage across the sense resistor

    totals = totals - samples[sampleIndex];     // Subtract the oldest sample data from the total

    samples[sampleIndex] = Vsense;              // Assign the just read temperature to the location of the current oldest data

    totals = totals + samples[sampleIndex];     // Add that new sample to the total
            
    sampleIndex += 1;                           // and move to the next index location
            
    if(sampleIndex >= numSamples)
    {
        sampleIndex = 0;
    }
            
    I = totals / numSamples;                    // assign the average value of total to the readTemperature variable
}

/*bool ZCD_IsLogicLevel(void)
{
    // Return ZCD logic level depending on the output polarity selected.
#if (__XC8_VERSION < 1360)
    return (ZCDCONbits.ZCDOUT);
#else // __XC8_VERSION
    return (ZCD1CONbits.ZCD1OUT);
#endif // __XC8_VERSION
}
*/



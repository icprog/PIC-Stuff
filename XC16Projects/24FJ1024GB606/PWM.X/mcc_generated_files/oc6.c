#include <xc.h>
#include "oc6.h"

static uint16_t         gOC6Mode;

void OC6_Initialize (void)
{
    // ENFLT0 disabled; ENFLT1 disabled; OCFLT2 disabled; ENFLT2 disabled; OCSIDL disabled; OCM Edge-Aligned PWM mode; OCFLT1 disabled; OCFLT0 disabled; OCTSEL TMR2; TRIGMODE Only Software; 
    OC6CON1 = 0x0006;
    // SYNCSEL TMR2; TRIGSTAT disabled; DCB Start of instruction cycle; OCINV disabled; OCTRIG Sync; OC32 disabled; FLTOUT disabled; OCTRIS disabled; FLTMD Cycle; FLTTRIEN disabled; 
    OC6CON2 = 0x000C;
    // OC6RS 255; 
    OC6RS = 0x00FF;
    // OC6R 255; 
    OC6R = 0x00FF;
	
    gOC6Mode = OC6CON1bits.OCM;
    
    IFS2bits.OC6IF = false;
    IEC2bits.OC6IE = true;
}



void __attribute__ ( ( interrupt, no_auto_psv ) ) _ISR _OC6Interrupt( void )
{
    if(IFS2bits.OC6IF)
    {
        IFS2bits.OC6IF = 0;
    }
}


void OC6_Start( void )
{
    OC6CON1bits.OCM = gOC6Mode;
}


void OC6_Stop( void )
{
    OC6CON1bits.OCM = 0;
}


void OC6_SingleCompareValueSet( uint16_t value )
{
    OC6R = value;
}


void OC6_DualCompareValueSet( uint16_t priVal, uint16_t secVal )
{
    OC6R = priVal;
	
    OC6RS = secVal;
}


void OC6_CentreAlignedPWMConfig( uint16_t priVal, uint16_t secVal )
{
    OC6R = priVal;
	
    OC6RS = secVal;
}

void OC6_EdgeAlignedPWMConfig( uint16_t priVal, uint16_t secVal )
{
    OC6R = priVal;
	
    OC6RS = secVal;
}

void OC6_SecondaryValueSet( uint16_t secVal )
{
   
    OC6RS = secVal;
}


void OC6_PrimaryValueSet( uint16_t priVal )
{
   
    OC6R = priVal;
}

bool OC6_IsCompareCycleComplete( void )
{
    return(IFS2bits.OC6IF);
}


bool OC6_FaultStatusGet( OC6_FAULTS faultNum )
{
    bool status;
    /* Return the status of the fault condition */
   
    switch(faultNum)
    { 
        case OC6_FAULT0:status = OC6CON1bits.OCFLT0;
            break;
        case OC6_FAULT1:status = OC6CON1bits.OCFLT1;
            break;
        case OC6_FAULT2:status = OC6CON1bits.OCFLT2;
            break;
        default :
            break;

    }
    return(status);
}


void OC6_FaultStatusClear( OC6_FAULTS faultNum )
{
    
    switch(faultNum)
    { 
        case OC6_FAULT0:OC6CON1bits.OCFLT0 = 0;
                break;
        case OC6_FAULT1:OC6CON1bits.OCFLT1 = 0;
                break;
        case OC6_FAULT2:OC6CON1bits.OCFLT2 = 0;
                break;
        default :
                break;
    }    
}


void OC6_ManualTriggerSet( void )
{
    OC6CON2bits.TRIGSTAT= true; 
}

bool OC6_TriggerStatusGet( void )
{
    return( OC6CON2bits.TRIGSTAT );
}


void OC6_TriggerStatusClear( void )
{
    /* Clears the trigger status */
    OC6CON2bits.TRIGSTAT = 0;
}

/**
 End of File
*/

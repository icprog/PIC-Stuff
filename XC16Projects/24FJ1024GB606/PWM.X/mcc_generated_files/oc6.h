#ifndef _OC6_H
#define _OC6_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
typedef enum
{   
    /* Fault 0 */
    OC6_FAULT0        /*DOM-IGNORE-BEGIN*/  = 0,/*DOM-IGNORE-END*/
    /* Fault 1 */
    OC6_FAULT1        /*DOM-IGNORE-BEGIN*/  = 1,/*DOM-IGNORE-END*/
    /* Fault 2 */
    OC6_FAULT2        /*DOM-IGNORE-BEGIN*/  = 2/*DOM-IGNORE-END*/
} OC6_FAULTS;

/**
  Section: Interface Routines
*/


/**
  @Summary
    This function initializes OC instance : 6

  @Description
    This routine initializes the OC6 driver instance for : 6
    index, making it ready for clients to open and use it.
    This routine must be called before any other OC6 routine is called.
	
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
    uint16_t priVal,secVal;
    bool completeCycle = false;
    priVal = 0x1000;
    secVal = 0x2000;
    OC6_FAULTS faultNum = OC6_FAULT0;

    OC6_Initialize();
    
    OC6_CentreAlignedPWMConfig( priVal, secVal );
  
    OC6_Start();

    while(1)
    {
        faultStat =  OC6_FaultStatusGet( faultNum );

        if(faultStat)
        {
            OC6_FaultStatusClear( faultNum );
        }

        completeCycle = OC6_IsCompareCycleComplete( void );
        if(completeCycle)
        {
            OC6_Stop();
        }
    }
    </code>

*/

void OC6_Initialize (void);


/**
  @Summary
    Enables the OC module with the corresponding operation mode.

  @Description
    This routine enables the OC module with the corresponding operation mode.

  @Preconditions
    OC6_Initialize function should have been called 

  @Param
    None.

  @Returns
    None.

  @Example 
    Refer to OC6_Initialize() for an example	
 
*/
void OC6_Start( void );

/**
  @Summary
    Disables the OC module.

  @Description
    This routine disables the OC module.

  @Preconditions
    OC6_Initialize function should have been called 

  @Param
    None.

  @Returns
    None.

*/
void OC6_Stop( void );

/**
  @Summary
    Sets the primary compare value.

  @Description
    This routine sets the primary compare value.

  @Preconditions
    OC6_Initialize function should have been called 

  @Param
    None.

  @Returns
    None.

  @Example 
    <code>
        uint16_t value = 0x1000;
        OC6_SingleCompareValueSet( value );
    <code>
*/

void OC6_SingleCompareValueSet( uint16_t value ) __attribute__((deprecated ("\nThis will be removed in future MCC releases. \nUse OC6_PrimaryValueSet instead. ")));

/**
  @Summary
    Sets the primary and secondary compare value.

  @Description
    This routine sets the primary and secondary compare value.

  @Preconditions
    OC6_Initialize function should have been called 

  @Param
    priVal - 16 bit primary compare value.
    secVal - 16 bit primary compare value.	

  @Returns
    None.

  @Example 
    <code>
        uint16_t priVal = 0x1000;
        uint16_t secVal = 0x2000;
        OC6_DualCompareValueSet( priVal,secVal );
    <code>
  	
*/

void OC6_DualCompareValueSet( uint16_t priVal, uint16_t secVal ) __attribute__((deprecated ("\nThis will be removed in future MCC releases. \nUse OC6_PrimaryValueSet and OC6_SecondaryValueSet instead. ")));

/**
  @Summary
    Sets the primary and secondary compare value for Center Aligned PWM

  @Description
    This routine sets the primary and secondary compare value for Center Aligned PWM.

  @Preconditions
    OC6_Initialize function should have been called 

  @Param
    priVal - 16 bit primary compare value.
    secVal - 16 bit primary compare value.	
	
  @Returns
    None.

  @Example 
    Refer to OC6_Initialize() for an example

*/
void OC6_CentreAlignedPWMConfig( uint16_t priVal, uint16_t secVal ) __attribute__((deprecated ("\nThis will be removed in future MCC releases. \nUse OC6_PrimaryValueSet and OC6_SecondaryValueSet instead. ")));

/**
  @Summary
    Sets the primary and secondary compare value for Edge Aligned PWM.

  @Description
    This routine sets the primary and secondary compare value for Edge Aligned PWM.

  @Preconditions
    OC6_Initialize function should have been called 

  @Param
    priVal - 16 bit primary compare value.
    secVal - 16 bit primary compare value.	

  @Returns
    None.

  @Example 
    <code>
        uint16_t priVal = 0x1000;
        uint16_t secVal = 0x2000;
        OC6_EdgeAlignedPWMConfig( priVal,secVal );
    <code> 
 	
*/
void OC6_EdgeAlignedPWMConfig( uint16_t priVal, uint16_t secVal ) __attribute__((deprecated ("\nThis will be removed in future MCC releases. \nUse OC6_PrimaryValueSet and OC6_SecondaryValueSet instead. ")));

/**
  @Summary
    Sets the primary compare value of respective OC.
	
  @Description
    This routine sets the primary compare value for respective OC.

  @Preconditions
    OC6_Initialize function should have been called 

  @Param
    priVal - 16 bit primary compare value.
    

  @Returns
    None.

  @Example 
    <code>
        uint16_t priVal = 0x1000;
        OC6_PrimaryValueSet( uint16_t priVal);
    <code> 
 	
*/
void OC6_PrimaryValueSet( uint16_t priVal);

/**
  @Summary
    Sets the secondary compare value of respective OC.
	
  @Description
    This routine sets the Secondary compare value for respective OC.

  @Preconditions
    OC6_Initialize function should have been called 

  @Param
    secVal - 16 bit secondary compare value.
    

  @Returns
    None.

  @Example 
    <code>
        uint16_t secVal = 0x1000;
        OC6_SecondaryValueSet( uint16_t secVal);
    <code> 
 	
*/
void OC6_SecondaryValueSet( uint16_t secVal);


/**
  @Summary
    Gets the status of the compare cycle completion.

  @Description
    This routine gets the status of the compare cycle completion.

  @Preconditions
    OC6_Initialize function should have been called 

  @Param
    None.

  @Returns
    Boolean value describing the current status of the cycle completion. Returns
    true  : When the compare cycle has completed. 
    false : When the compare cycle has not completed. 

  @Example 
    Refer to OC6_Initialize() for an example
	

*/
bool OC6_IsCompareCycleComplete( void );

/**
  @Summary
    Gets the status of the PWM fault condition occurrence.

  @Description
    This routine gets the status of the PWM fault condition occurrence.
  
  @Preconditions
    OC6_Initialize function should have been called 

  @Param
    faultNum - The fault number

  @Returns
    boolean value describing the occurrence of the fault condition.
    true  : When the specified fault has occurred.
    false : When the specified fault has not occurred.
	
  @Example 
    Refer to OC6_Initialize() for an example 
 

*/
bool OC6_FaultStatusGet( OC6_FAULTS faultNum );

/**
  @Summary
    Clears the status of the PWM fault condition occurrence.

  @Description
    This routine clears the status of the PWM fault condition occurrence.
	
  @Preconditions
    None.	

  @Param
    faultNum - The fault number
  
  @Returns
    None.

  @Example 
    Refer to OC6_Initialize() for an example 
  	
*/
void OC6_FaultStatusClear( OC6_FAULTS faultNum );


/**
  @Summary
    Sets the manual trigger

  @Description
    This routine sets the manual trigger
	
  @Preconditions
    OC6_Initialize function should have been called 

  @Param
    None
 
  @Returns
    None.
	
  @Example 
    Refer to OC6_TriggerStatusGet() for an example	
 
*/
void OC6_ManualTriggerSet( void );

/**
  @Summary
    Gets the status of the timer trigger.

  @Description
    This routine gets the status of the timer trigger source if it has been triggered.
	
  @Preconditions
    OC6_Initialize function should have been called 
	
  @Param
    None
	
  @Returns
    Boolean value describing the timer trigger status.
    true  : When the timer source has triggered and is running 
    false : When the timer has not triggered and being held clear 

  @Example 
    <\code>	
    if(OC6_TriggerStatusGet())
    {
        OC6_TriggerStatusClear();
    }
    <\code>	
*/
bool OC6_TriggerStatusGet( void );

/**
  @Summary
    Clears the status of the timer trigger.

  @Description
    This routine clears the status of the timer trigger.
	
  @Preconditions
    OC6_Initialize function should have been called

  @Param
    None
	
  @Returns
    None.
	
  @Example 
    Refer to OC6_TriggerStatusGet() for an example	

*/
void OC6_TriggerStatusClear( void );
#endif
#include    "system.h"
#include    "buttons.h"

uint16_t    readButtons =   0;
int8_t      button      =   0;

char readButton(void)
{
    readButtons = ADCRead(6);                           // Read AN6 (_RB6) Value to determine which button is pushed
    
    if(readButtons > 1900 && readButtons < 2050)
    {
        button = 1;                                     // Menu Button has been pressed
    }
    
    else if(readButtons > 2250 && readButtons < 2460)
    {
        button = 2;                                     // Enter Button has been pressed
    }
    
    else if(readButtons > 2900 && readButtons < 3100)
    {
        button = 3;                                     // Down Button has been pressed
    }
    
    else if(readButtons > 3900)
    {
        button = 4;                                     // Up Button has been pressed
    }
    
    else
    {
        button = 0;                                     // No Button has been pressed
    }
    return (button);
}
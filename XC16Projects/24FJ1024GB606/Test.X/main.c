#include "system.h"

int main(void)
{
    SYSTEM_Initialize();                        // initialize the device

    while (1)
    {
        __delay_ms(1000);
    }

    return -1;
}
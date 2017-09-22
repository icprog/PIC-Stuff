
#include    "system.h"

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    bcdTime_t now;                                                                   // declare the type of the time object
 
    char month, second;
    struct tm currentTime;

    RTCC_Initialize();

    while(1)
    {
        RTCC_TimeGet(&currentTime); 
       _RF3 = 1;
       __delay_ms(1000);
       _RF3 = 0;
       __delay_ms(1000);
        
       month = now.tm_mon; 
       second = now.tm_sec;
       
       LCDWriteIntXY(0,0,month,-1,0);
       LCDWriteIntXY(1,0,second,-1,0);
    }


    return -1;
}
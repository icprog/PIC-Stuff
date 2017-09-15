#include "system.h"
#include "menu.h"

int main(void)
{
    SYSTEM_Initialize();                        // initialize the device
    
    char loopCount = 0;
    
    extern uint16_t x,y;                                               


    while (1)
    {
  //      if(loopCount<10)
    //    {
//        loadimg(&menu2[0], 1024,0);                     //Draw Menu2
      //  }
//        loadimg(&menu2[0], 1024,0);                     //Draw Menu2
      //  __delay_ms(3750);
 //       LCDWriteStringXY(3,6,"Please Set");
   //     LCDWriteStringXY(3,17,"the Time!");
        _RF3 = 1;
        __delay_ms(1000);
        
        menuRead();
       // LCDWriteIntXY(4,0,x,5,0);
//        LCDWriteIntXY(5,0,y,5,0);
  //      LCDWriteIntXY(1,1,loopCount,5,0);
    //    LCDWriteIntXY(2,1,ADCRead(ADC_CHANNEL_CTMU_TEMPERATURE_SENSOR_INPUT),5,0);
        _RF3 = 0;
        __delay_ms(1000);
        
//        _RB15 = 1;
  //      __delay_ms(500);
    //    _RB15 = 0;
//        __delay_ms(5000);
/*        
        if(loopCount >253)
        {
            displayOn(0);
            loopCount = 0;
            __delay_ms(10);
            displayOn(1);
        }
        
*/
//        if(loopCount<10)
  //      {
            loopCount+=1;
      //  }
    }
    return -1;
}
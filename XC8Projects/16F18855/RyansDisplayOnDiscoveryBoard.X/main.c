// *************** Includes ****************************************************    
#include "system.h"
#include <math.h>
#include "coffee.h"

// *************** Main Routine ************************************************    
void main(void)
{
    int count               =   0;
    
    SYSTEM_Initialize();
   
    LCDBitmap(&coffee[0], 0,504);           //Draw Splash Screen
    gotoXY(1,4);
    LCDWriteCharacter(' ');                 // Need to Write something to the screen to get it to Draw the Splash Screen  FIX
   
   __delay_ms(2500);

   while (1)
    {
        if(count<1)LCDClear();
        
        if(count==1)LCDWriteStringXY(0,0," Nokia 5110 Display  ");
       
        if(count==35)LCDWriteStringXY(0,1,"Some Minor Bug Fixes and all will be Good!");

        if(count==70)LCDWriteStringXY(35,4,"5... ");

        if(count==95)LCDWriteStringXY(35,4,"4... ");

        if(count==120)LCDWriteStringXY(35,4,"3... ");

        if(count==145)LCDWriteStringXY(35,4,"2... ");
        
        if(count==170)LCDWriteStringXY(35,4,"1... ");

        if(count==195)LCDClear();
        
        if(count==196)
        {
            LCDDrawBox();
        }
        
        if(count>196&&count<227)
        {
//            LCDDrawBox();
            LCDWriteStringXY(8,1,"LAYNE SUCKS COCK!!");
            LCDWriteStringXY(8,2,"A LOT!! of COCK");
            
            LCDWriteStringXY(4,4,"Number Sucked:");

            LCDWriteIntXY(64,4,count-196,-1,0,0);
    
            __delay_ms(500);
        }
        
        __delay_ms(50);
        
        if(count>=227)
        {
            count=0;
            LCDClear();
        }
        
        count+=1;
    }
}
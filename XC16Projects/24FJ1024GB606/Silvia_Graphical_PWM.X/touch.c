#include "touch.h"
#include "system.h"
//#include "adc.h"                                    // Included to use ADC functionality

#define cycleDelay          50

#define xPos_In             TRISBbits.TRISB15       // pin 1 on connector Note, Either xPos or xNeg must be an Analog in as well
#define xNeg_In             TRISFbits.TRISF4        // pin 3 on connector
#define yPos_In             TRISBbits.TRISB14       // pin 4 on connector Note, Either yPos or yNeg must be an Analog in as well
#define yNeg_In             TRISFbits.TRISF4        // pin 4 on connector
#define xPos_Out            LATBbits.LATB15
#define xNeg_Out            LATFbits.LATF4
#define yPos_Out            LATBbits.LATB14
#define yNeg_Out            LATFbits.LATF4

uint16_t x,y;                                               



//#define xPos_In             TRISAbits.TRISA2        // pin 1 on connector Note, Either xPos or xNeg must be an Analog in as well
//#define xNeg_In             TRISAbits.TRISA9        // pin 2 on connector
//#define yPos_In             TRISAbits.TRISA3        // pin 3 on connector Note, Either yPos or yNeg must be an Analog in as well
//#define yNeg_In             TRISAbits.TRISA11       // pin 4 on connector
//#define xPos_Out            LATAbits.LATA2
//#define xNeg_Out            LATAbits.LATA9
//#define yPos_Out            LATAbits.LATA3
//#define yNeg_Out            LATAbits.LATA11
#define colume1             1250
#define colume2             2100


// ***************************************************************************************************************************************************************

char menuRead()
{
    static uint8_t lastKeyState = KEY_NONE, key = KEY_NONE, j, k, L;
    uint8_t col = 0, row = 0;                            
//    uint16_t x,y;                                               

//    xPos_In             = 1;    //Set x+ to an Input
  //  IOCPDBbits.IOCPDB15 = 1;    //Enable Weak-Pull-Downs on Analog port pin, as Pull downs can't be enabled when pin is switched to a OP
    //xNeg_In             = 1;    //Set x- to an Input
    yPos_In             = 0;    //Set y+ to an Output
    yPos_Out = 1;
    __delay_ms(4500);
    yPos_Out = 0;
    __delay_ms(1000);
    _LATB15 = 1;
    __delay_ms(1500);
    _LATB15 = 0;
//    yNeg_In             = 0;    //Set y- to an output
  //  yPos_Out            = 1;    //Set y+ to +5V
    //yNeg_Out            = 0;    //Set y- to 0V
//    x = ADCRead(15);            //Read ADC value of x+
  //  yPos_Out = 0;               //Set y+ to 0V
    //IOCPDBbits.IOCPDB15 = 1;    //Disable Weak-Pull-Downs on Analog port pin

//    yPos_In             = 1;    //Set y+ to an Input
  //  IOCPDBbits.IOCPDB14 = 1;    //Enable Weak-Pull-Downs on Analog port pin
    //yNeg_In             = 1;    //Set y- to an Input
//    xPos_In             = 0;    //Set x+ to an Output
  //  xNeg_In             = 0;    //Set x- to an Output
    //xPos_Out            = 1;    //Set x+ to +5V
//    xNeg_Out            = 0;    //Set x- to 0V
  //  y = ADCRead(14);            //Read ADC value of y+
    //xPos_Out            = 0;    //Set x+ to 0V
//    IOCPDBbits.IOCPDB14 = 0;    //Disable Weak-Pull-Downs on Analog port pin, as Pull downs can't be enabled when pin is switched to a OP

    // ***************************************************************************************************************************************************************
       
    if(x < 220 || y < 220)
    {
        key = KEY_NONE;
        j = 0;
    }
    
    if(x >= 220 && x <1075)
    {
        col = 1;
    }
    else if(x >= 1075 && x < 1990)
    {
        col = 2;
    }
    else if(x >= 1990)
    {
        col = 3;
    }
    else
    {
        col = 0;
    }
    
    if(y >= 220 && y <1000)
    {
        row = 1;
    }
    else if(y >= 1000 && y < 2000)
    {
        row = 2;
    }
    else if(y >= 2000)
    {
        row = 3;
    }
    else
    {
        row = 0;
    }
// ***************************************************************************************************************************************************************
    
    if(col == 1)
    {
        if(row == 1)
        {
            key = KEY_START_STOP;
        }
        else if(row == 2)
        {
            key = KEY_LEFT;
        }
        else if(row == 3)
        {
            key = KEY_RESET;
        }
        else 
        {
            key = KEY_NONE;
            j = 0;
        }
    }
    
    else if(col == 2)
    {
        if(row == 1)
        {
            key = KEY_DOWN;
        }
        else if(row == 2)
        {
            key = KEY_ENTER;
        }
        else if(row == 3)
        {
            key = KEY_UP;
        }
        else 
        {
            key = KEY_NONE;
        }
    }

    else if(col == 3)
    {
        if(row == 1)
        {
            key = KEY_MENU;
        }
        else if(row == 2)
        {
            key = KEY_RIGHT;
        }
        else if(row == 3)
        {
            key = KEY_SET_TIME;
        }
        else 
        {
            key = KEY_NONE;
        }
    }
    
    else
    {
        key = KEY_NONE;
    }
// ***************************************************************************************************************************************************************
    if (key != KEY_NONE)
    {
        k = 15;
        L = 25;
        
        
        if (lastKeyState != key)
        {
            lastKeyState = key;
        }
        else                                        //Button (key) has been in the pressed state for 2 program cycles, so,
        {
            j += 1;                                 //increment the "button pressed" counter,
            
            if(j == 1)
            {
                return (lastKeyState);              //and return the value of that button
            }
            
            else if(j >1 && j <= k)
            {
                return (KEY_NONE);
            }
                
            else if(j > k)                                   //If button has been pressed for an additional 30 program cycles,
            {
                __delay_ms(L);                     //return the key every program cycle, with a delay between Key presses if Key is held down
                return (lastKeyState);
            }
            
            else
            {
                return(KEY_NONE);
            }
        }
    }
    j = 0;
    return (KEY_NONE);                                  // If all else fails ...
}
#include "lcd.h"
#include <stdint.h>

// ***********************************************
// LCD Type Selection
// Uncomment Just one of them
// ************************************************
//#define LCD_TYPE_2_LINE	//For 16 or 20 Chars by 2 lines
#define LCD_TYPE_4_LINE     //For 16 or 20 Chars by 4 lines
// ************************************************


#define RS _RC4             // Define REGISTER SELECT Bit
#define EN _RC6             // Define ENABLE Bit
#define D4 _RC0             // Define LCD Data Port D4
#define D5 _RC1             // Define LCD Data Port D5
#define D6 _RC2             // Define LCD Data Port D6
#define D7 _RC3             // Define LCD Data Port D7



uint8_t __cgram[] =                                     // YOU CAN USE LCD_Write_Char(48 + Ascii code) for any char in the Display Rom!!!
{
    0x0C, 0x12, 0x12, 0x0C, 0x00, 0x00, 0x00, 0x00,     // Char0 Degree symbol, Use LCD_Write_Char(0); to display this char
	0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00, 0x00,     // Char2 Open Heart
	0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00, 0x00,     // Char3 Solid Heart

/*  	
    0x0C, 0x12, 0x12, 0x0C, 0x00, 0x00, 0x00, 0x00,     // Degree symbol, char num #0 Use LCD_Write_Char(0); to display this char
    0x0E, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x00,     // Battery Empty, char num #1 Use LCD_Write_Char(1); to display this char      
    0x0E, 0x1B, 0x11, 0x11, 0x11, 0x1F, 0x1F, 0x00,     // Battery 1/4,   char num #2 Use LCD_Write_Char(2); to display this char      
    0x0E, 0x1B, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x00,     // Battery 1/2,   char num #3 Use LCD_Write_Char(3); to display this char
    0x0E, 0x1B, 0x11, 0x1F, 0x1F, 0x1F, 0x1F, 0x00,     // Battery 3/4,   char num #4 Use LCD_Write_Char(4); to display this char
    0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00,     // Battery Full,  char num #5 Use LCD_Write_Char(5); to display this char
    0x00, 0x04, 0x02, 0x1F, 0x02, 0x04, 0x00, 0x00,     // Arrow Right    char num #6 Use LCD_Write_Char(6); to display this char
    0x00, 0x00, 0x0E, 0x11, 0x11, 0x0A, 0x1B, 0x00      // Ohm symbol,    char num #7 Use LCD_Write_Char(7); to display this char 
	0x0E, 0x11, 0x1B, 0x15, 0x11, 0x1F, 0x11, 0x0E,     //
	0x04, 0x04, 0x04, 0x04, 0x1F, 0x0E, 0x04, 0x00,     //
	0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00, 0x00,     // Open Heart
	0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00, 0x00,     // Solid Heart
	0x0E, 0x11, 0x0A, 0x00, 0x04, 0x11, 0x0E, 0x00,     // Face
	0x0E, 0x11, 0x1B, 0x15, 0x11, 0x1F, 0x11, 0x0E,     //Char6
	0x00, 0x04, 0x0E, 0x1F, 0x0E, 0x04, 0x00, 0x00,     //Char7   */
};


// ***************************************************************************************************************************************************************
void InitCustomChars()
{
  uint8_t i;
  LCD_Cmd(0x04);                        // Set CGRAM Address (in LCD))
  LCD_Cmd(0x00);                        // Set Starting Point in CGRAM Address (I think?))
  for (i = 0; i < sizeof(__cgram) ; i++)
    LCD_Write_Char(__cgram[i]);
  LCD_Cmd(0);                           // Return to Home
  LCD_Cmd(2);                           // .. return to Home
}

// ***************************************************************************************************************************************************************
void LCD_Port(char a)
{
	if(a & 1)
		D4 = 1;
	else
		D4 = 0;

	if(a & 2)
		D5 = 1;
	else
		D5 = 0;

	if(a & 4)
		D6 = 1;
	else
		D6 = 0;

	if(a & 8)
		D7 = 1;
	else
		D7 = 0;
}

// ***************************************************************************************************************************************************************
void LCD_Cmd(char a)
{
	RS = 0;             // => RS = 0
	LCD_Port(a);
	EN  = 1;             // => E = 1
        __delay_ms(4);
        EN  = 0;             // => E = 0
}

// ***************************************************************************************************************************************************************
void LCD_Clear()
{
	LCD_Cmd(0);
	LCD_Cmd(1);
}

// ***************************************************************************************************************************************************************
void LCD_Set_Cursor(char x, char y)
{
#ifdef LCD_TYPE_2_LINE

    char temp,z,w;
    
	if(x == 0)
	{                
        temp = 0x80 + y;
		z = temp>>4;
		w = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(w);
	}

	else if(x == 1)
	{
		temp = 0xC0 + y;
		z = temp>>4;
		w = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(w);
	}

#endif
        
#ifdef LCD_TYPE_4_LINE	
        
    char temp,z,w;
    
	if(x == 0)
	{                
        temp = 0x80 + y;
		z = temp>>4;
		w = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(w);
	}

	else if(x == 1)
	{
		temp = 0xC0 + y;
		z = temp>>4;
		w = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(w);
	}


	else if(x == 2)
	{
        temp = 0x94 + y;
		z = temp>>4;
		w = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(w);
	}

    else if(x == 3)
	{
	    temp = 0xD4 + y;
		z = temp>>4;
		w = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(w);
	}
#endif
}

// ***************************************************************************************************************************************************************
void LCD_Init(char style)
{
  LCD_Port(0x00);
   __delay_ms(20);
  LCD_Cmd(0x03);
	__delay_ms(5);
  LCD_Cmd(0x03);
	__delay_ms(11);
  LCD_Cmd(0x03);
  /////////////////////////////////////////////////////
  LCD_Cmd(0x02);
  LCD_Cmd(0x02);
  LCD_Cmd(0x08);
  LCD_Cmd(0x00);
  LCD_Cmd(0x0C|style);      //Enable Display ON with style selected (BLINK, ULINE, BLUL, or NONE))
  LCD_Cmd(0x00);
  LCD_Cmd(0x06);
}

// ***************************************************************************************************************************************************************
void LCD_Write_Char(char a)
{
   char temp,y;
   temp = a&0x0F;
   y = a&0xF0;
   RS = 1;             // => RS = 1
   LCD_Port(y>>4);             //Data transfer
   EN = 1;
   __delay_us(40);
   EN = 0;
   LCD_Port(temp);
   EN = 1;
   __delay_us(40);
   EN = 0;
}

// ***************************************************************************************************************************************************************
void LCD_Write_String(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   LCD_Write_Char(a[i]);
}

// ***************************************************************************************************************************************************************
void LCD_Write_Int(int val, char field_length)
{
	/***************************************************************
	This function writes a integer type value to LCD module

	Arguments:
	1)int val	: Value to print

	2)unsigned int field_length :total length of field in which the value is printed
	must be between 1-5 if it is -1 the field length is no of digits in the val

	****************************************************************/

	char str[5]={0,0,0,0,0};
	int i=4,j=0;

        //Handle negative integers
        if(val<0)
        {
            LCD_Write_Char('-');   //Write Negative sign
            val=val*-1;     //convert to positive
        }

	while(val)
	{
            str[i]=val%10;
            val=val/10;
            i--;
	}
	if(field_length==-1)
		while(str[j]==0) j++;
	else
		j=5-field_length;

	
	for(i=j;i<5;i++)
	{
	LCD_Write_Char(48+str[i]);
	}
}

// ***************************************************************************************************************************************************************
void LCD_Write_Signed_Dec_Int(int val, char field_length)
{
	/***************************************************************
	This function writes a integer type value to LCD module, while 
    taking that value, dividing by ten, and inserting a decimal point!

	Arguments:
	1)int val	: Value to print

	2)char field_length :total length of field in which the value is printed
	must be between 1-5 if it is "-1" the field length is no of digits in the val

	****************************************************************/

	char str[5]={0,0,0,0,0};
	int i=4,j=0;
    
    if(val<0)                   //Handle negative integers
    {
        LCD_Write_Char('-');    //Write Negative sign
        val=val*-1;             //convert to positive
    }

    else
    {
        LCD_Write_Char('+');     //Int was already positive, so put a positive sign.
    }

	while(val)
	{
            str[i]=val%10;
            val=val/10;
            i--;
	}
    
	if(field_length == -1)
		while(str[j] == 0) j++;
	else
		j=5-field_length;

	
	for(i=j;i<4;i++)
	{
	LCD_Write_Char(48+str[i]);
	}
    
    LCD_Write_Char(46);         //A decimal period!
    LCD_Write_Char(48+str[4]);
}

// ***************************************************************************************************************************************************************
void LCD_Write_Dec_Int(int val, char field_length)
{
	/***************************************************************
	This function writes a integer type value to LCD module, while 
    taking that value, dividing by ten, and inserting a decimal point!

	Arguments:
	1)int val	: Value to print

	2)char field_length :total length of field in which the value is printed
	must be between 1-5 if it is "-1" the field length is no of digits in the val

	****************************************************************/

	char str[5]={0,0,0,0,0};
	int i=4,j=0;

	while(val)
	{
            str[i]=val%10;
            val=val/10;
            i--;
	}
    
	if(field_length == -1)
		while(str[j] == 0) j++;
	else
		j=5-field_length;

	
	for(i=j;i<4;i++)
	{
	LCD_Write_Char(48+str[i]);
	}
    
    LCD_Write_Char(46);         //A decimal period!
    LCD_Write_Char(48+str[4]);
}

// ***************************************************************************************************************************************************************
void LCD_Shift_Right()
{
	LCD_Cmd(0x01);
	LCD_Cmd(0x0C);
}

// ***************************************************************************************************************************************************************
void LCD_Shift_Left()
{
	LCD_Cmd(0x01);
	LCD_Cmd(0x08);
}

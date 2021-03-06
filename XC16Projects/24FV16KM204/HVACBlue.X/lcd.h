#ifndef LCD_H
#define LCD_H

#include "system.h"

// ***********************************************
// LCD Type Selection
// Uncomment Just one of them
// ************************************************
//#define LCD_TYPE_2_LINE	//For 16 or 20 Chars by 2 lines
#define LCD_TYPE_4_LINE     //For 16 or 20 Chars by 4 lines
// ************************************************
#define RS _RC6             // Define REGISTER SELECT Bit
#define EN _RC7             // Define ENABLE Bit
#define D4 _RA9             // Define LCD Data Port D4
#define D5 _RC3             // Define LCD Data Port D5
#define D6 _RC4             // Define LCD Data Port D6
#define D7 _RC5             // Define LCD Data Port D7
// ***************************************************************************************************************************************************************
#define NONE     0X00
#define BLINK    0X01
#define ULINE    0X02
#define BLUL     0X03 
// ****MACROS*****************************************************************************************************************************************************
#define LCDWriteStringXY(x,y,a) {\
 LCD_Set_Cursor(x,y);\
 LCD_Write_String(a);\
}
// ***************************************************************************************************************************************************************
#define LCDWriteIntXY(x,y,val,field_length, numPlaces, sign) {\
 LCD_Set_Cursor(x,y);\
 LCD_Write_Int(val,field_length, numPlaces, sign);\
}
/***************************************************************************************************************************************************************
 #define LCDWriteSignedDecIntXY(x,y,val,field_length) {\
 LCD_Set_Cursor(x,y);\
 LCD_Write_Signed_Dec_Int(val,field_length);\
 }
 */ 
/***************************************************************************************************************************************************************
 #define LCDWriteDecIntXY(x,y,val,field_length) {\
 LCD_Set_Cursor(x,y);\
 LCD_Write_Dec_Int(val,field_length);\
 }
 */
// ***************************************************************************************************************************************************************
void InitCustomChars();
// ***************************************************************************************************************************************************************
void LCD_Port(char a);
// ***************************************************************************************************************************************************************
void LCD_Cmd(char a);
// ***************************************************************************************************************************************************************
void LCD_Clear();
// ***************************************************************************************************************************************************************
void LCD_Set_Cursor(char x, char y);
// ***************************************************************************************************************************************************************
void LCD_Init(char style);
// ***************************************************************************************************************************************************************
void LCD_Write_Char(char a);
// ***************************************************************************************************************************************************************
void LCD_Write_String(char *a);
// ***************************************************************************************************************************************************************
void LCD_Write_Int(int value,signed char fieldLength, signed char numPlaces, signed char sign);
// ***************************************************************************************************************************************************************
//void LCD_Write_Int(int val, char field_length);
// ***************************************************************************************************************************************************************
//void LCD_Write_Signed_Dec_Int(int val, char field_length);
// ***************************************************************************************************************************************************************
//void LCD_Write_Dec_Int(int val, char field_length);
// ***************************************************************************************************************************************************************
//void LCD_Write_2Dec_Int(int val, char field_length);
// ***************************************************************************************************************************************************************
//void LCD_Shift_Right();
// ***************************************************************************************************************************************************************
//void LCD_Shift_Left();
#endif

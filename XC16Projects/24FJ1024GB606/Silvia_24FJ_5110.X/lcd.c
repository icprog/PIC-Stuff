#include "lcd.h"


#define LCD_CLK     LATGbits.LATG8
#define LCD_DIN     LATGbits.LATG7
#define LCD_DC      LATGbits.LATG6
#define LCD_CE      LATEbits.LATE7
#define LCD_RST     LATEbits.LATE6

#define LCD_COMMAND 0
#define LCD_DATA    1

#define LCD_X       84                                      // LCD Width  29mm
#define LCD_Y       48                                      // LCD Height 19 mm


const char fonts [][3] = {
    0x00, 0x00, 0x00,  // sp
    0x00, 0x4E, 0x00,  // ! *
    0x06, 0x00, 0x06,  // " *
    0xff, 0xff, 0xff,  // #
    0x48, 0xd6, 0x24,  // $ *
    0x13, 0x6B, 0x64,  // % *
    0xff, 0xff, 0xff,  // &
    0x00, 0x06, 0x00,  // ' *
    0x38, 0x44, 0x82,  // ( *
    0x82, 0x44, 0x38,  // ) *
    0x14, 0x08, 0x3E,  // *
    0x10, 0x38, 0x10,  // + *
    0xa0, 0x60, 0x00,  // , *
    0x10, 0x10, 0x10,  // - *
    0x60, 0x60, 0x00,  // . *
    0x60, 0x18, 0x06,  // / *
    0x7c, 0x42, 0x7c,  // 0 *
    0x44, 0x7e, 0x40,  // 1 *
    0x64, 0x52, 0x4c,  // 2 *
    0x4a, 0x4a, 0x34,  // 3 *
    0x38, 0x24, 0x7e,  // 4 *
    0x4e, 0x4a, 0x32,  // 5 *
    0x3c, 0x4a, 0x32,  // 6 *
    0x62, 0x1a, 0x06,  // 7 *
    0x76, 0x4a, 0x76,  // 8 *
    0x4c, 0x52, 0x3c,  // 9 *
    0x6c, 0x6c, 0x00,  // : *
    0xac, 0x6c, 0x00,  // ; *
    0x10, 0x28, 0x44,  // < * 60
    0x28, 0x28, 0x28,  // = *
    0x44, 0x28, 0x10,  // > *
    0x02, 0x59, 0x06,  // ?
    0xFF, 0xFF, 0xFF,  // @
    0x7c, 0x12, 0x7c,  // A * 65
    0x7E, 0x5A, 0x34,  // B *
    0x3c, 0x42, 0x42,  // C *
    0x7e, 0x42, 0x3c,  // D *
    0x7e, 0x4a, 0x42,  // E *
    0x7e, 0x0a, 0x0a,  // F * 70
    0x3c, 0x52, 0x34,  // G *
    0x7e, 0x08, 0x7e,  // H *
    0x42, 0x7e, 0x42,  // I *
    0x30, 0x40, 0x3e,  // J *
    0x7e, 0x18, 0x66,  // K * 75
    0x7e, 0x40, 0x40,  // L *
    0x7e, 0x1c, 0x7e,  // M *
    0x7e, 0x02, 0x7e,  // N *
    0x3c, 0x42, 0x3c,  // O *
    0x7e, 0x12, 0x0c,  // P * 80
    0x7e, 0x62, 0xfe,  // Q *
    0x7e, 0x32, 0x4e,  // R *
    0x44, 0x4a, 0x32,  // S *
    0x02, 0x7e, 0x02,  // T *
    0x7e, 0x40, 0x7e,  // U * 85
    0x3e, 0x40, 0x3e,  // V *
    0x7E, 0x38, 0x7E,  // W *
    0x66, 0x18, 0x66,  // X *
    0x0e, 0x70, 0x0e,  // Y *
    0x62, 0x5a, 0x46,  // Z * 90
    0x00, 0x7e, 0x42,  // [ *
    0x06, 0x18, 0x60,  // backslash *
    0x42, 0x7e, 0x00,  // ] *
    0x04, 0x02, 0x04,  // ^ *
    0x40, 0x40, 0x40,  // _ * 95
    0x00, 0x02, 0x04,  // ` *
    0x74, 0x54, 0x78,  // a *
    0x7e, 0x48, 0x30,  // b *
    0x30, 0x48, 0x48,  // c *
    0x30, 0x48, 0x7e,  // d * 100
    0x38, 0x54, 0x58,  // e *
    0x7c, 0x0a, 0x02,  // f *
    0x98, 0xa4, 0x7c,  // g *
    0x7e, 0x08, 0x70,  // h *
    0x48, 0x7a, 0x40,  // i * 105
    0x88, 0xfa, 0x00,  // j *
    0x7e, 0x18, 0x64,  // k *
    0x42, 0x7E, 0x40,  // l *
    0x7c, 0x38, 0x7c,  // m *
    0x7C, 0x04, 0x78,  // n * 110
    0x38, 0x44, 0x38,  // o *
    0xFc, 0x24, 0x18,  // p *
    0x18, 0x24, 0xfc,  // q *
    0x78, 0x04, 0x04,  // r *
    0x48, 0x54, 0x24,  // s * 115
    0x04, 0x3e, 0x44,  // t *
    0x7C, 0x40, 0x7C,  // u *
    0x3c, 0x40, 0x3c,  // v *
    0x7c, 0x30, 0x7c,  // w *
    0x6c, 0x10, 0x6c,  // x * 120
    0x9c, 0xa0, 0x7c,  // y *
    0x64, 0x54, 0x4c,  // z *
    0xFF, 0xFF, 0xFF,  // 
    0xFF, 0xFF, 0xFF,  // O
    0xFF, 0xFF, 0xFF,  // U   125
    0xFF, 0xFF, 0xFF,  // a
    0xFF, 0xFF, 0xFF,  // o
    0xFF, 0xFF, 0xFF,  // u
    0x0C, 0x12, 0x0c,  // degree symbol
    0xfc, 0x40, 0x7c,  // µ * 130
    0xFF, 0xFF, 0xFF,  // <
    0xFF, 0xFF, 0xFF,  // 
};

char x, y;

void gotoXY(char x, char y)
{
    LCDWrite(0, 0x80 | x);                                  // Column.
    LCDWrite(0, 0x40 | y);                                  // Row.
}


void LCDBitmap(const char my_array[])                             //This takes a large array of bits and sends them to the LCD
{
    int index;
    for (index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
    LCDWrite(LCD_DATA, my_array[index]);
}


//This function takes in a character, looks it up in the font table/array
//And writes it to the screen
//Each character is 8 bits tall and 5 bits wide. We pad one blank column of
//pixels on each side of the character for readability.

void LCD_Write_Character(const char character)
{
//    LCDWrite(LCD_DATA, 0x00); //Blank vertical line padding
    int index;
    for (index = 0 ; index < 3 ; index++)
    {
    LCDWrite(LCD_DATA, fonts[character - 0x20][index]); //0x20 is the ASCII character for Space (? ?). The font table starts with this character
    }
    
    LCDWrite(LCD_DATA, 0x00); //Blank vertical line padding
    
}

//Given a string of characters, one by one is passed to the LCD
void LCD_Write_String(const char *characters) 
{
while (*characters)
LCD_Write_Character(*characters++);
}

//Clears the LCD by writing zeros to the entire screen
void LCD_Clear(void)
{
    int index;
    for (index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
    LCDWrite(LCD_DATA, 0x00);
    gotoXY(0, 0); //After we clear the display, return to the home position
}

void LCD_Write_Int(int value,signed char fieldLength, signed char numPlaces, signed char sign)     //writes a integer type value to LCD module
{
	char str[5]={0,0,0,0,0};            // Integer can be up to 5 characters long
	int i=4,j=0;

    if(value<0)                         // Handle negative integers
    {
        LCD_Write_Character('-');              // Write Negative sign to the LCD
        value=value*-1;                 // convert negative value to a positive value
    }
    
    else
    {
        if(sign == 1)
        {
            LCD_Write_Character('+');
        }
    }

	while(value)
	{
            str[i]=value%10;
            value=value/10;
            i--;
	}
	if(fieldLength==-1)                 // if fieldLength is -1, the field length is # of digits in the value
    {
		while(str[j]==0)
        {
            j++;
        }
    }
	else
    {
		j=5-fieldLength;                // fieldLength must be between 1 and 5
    }

	for(i=j;i<(5-numPlaces);i++)
	{
        LCD_Write_Character(48+str[i]);            // Write out Integer value to the screen as characters
	}

    if(numPlaces == 1)
    {
        LCD_Write_Character(46);                   //A decimal period!
        LCD_Write_Character(48+str[4]);
    }

    if(numPlaces == 2)
    {
        LCD_Write_Character(46);                   //A decimal period!
        LCD_Write_Character(48+str[3]);
        LCD_Write_Character(48+str[4]);
    }
}

//This sends the magical commands to the PCD8544
void LCDInit(void)
{
//Configure control pins
TRISGbits.TRISG8    =   0;
TRISGbits.TRISG7    =   0;
TRISGbits.TRISG6    =   0;
TRISEbits.TRISE7    =   0;
TRISEbits.TRISE6    =   0;
LCD_DIN = 0;
LCD_CLK = 0;
LCD_DC  = 0;
LCD_RST = 0;
LCD_RST = 1;
LCDWrite(LCD_COMMAND, 0x21); //Tell LCD that extended commands follow

//The code for changing the contrast on the fly is easy. Set the SCE pin to low to enable the serial interface.
//Set the D/C pin to low (which tells the LCD you are sending commands, not pixel data), then send byte 0x21 which enables the extended instruction set,
//then send the contrast byte, then send byte 0x20 which returns to the basic instruction set. You do not need to reset the panel or anything like that.
//The acceptable range is between 0x80 (being a contrast value of 0) and 0xFF (being a contrast value of 127)
LCDWrite(LCD_COMMAND, 0xBB); //Set LCD Vop (Contrast): Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark

LCDWrite(LCD_COMMAND, 0x04); //Set Temp coefficent

LCDWrite(LCD_COMMAND, 0x14); //LCD bias mode 1:48: Try 0x13 or 0x14

LCDWrite(LCD_COMMAND, 0x20); //We must send 0x20 to tell the display to use standard commands

LCDWrite(LCD_COMMAND, 0x0C); //Set display control, normal mode. 0x0D for inverse
}


//There are two memory banks in the LCD, data/RAM and commands. This
//function sets the DC pin high or low depending, and then sends
//the data byte
void LCDWrite(uint8_t data_or_command, uint8_t data) {
uint8_t i,d;
d=data;
if(data_or_command == 0)
{
    LCD_DC=0;
}
else
{
    LCD_DC=1;
}

//data_or_command; //Tell the LCD that we are writing either to data or a command
//Send the data
LCD_CE = 0;
// digitalWrite(PIN_SCE, LOW);
for(i=0;i<8;i++)
{
LCD_DIN = 0;
if(d&0x80)LCD_DIN=1;
LCD_CLK=1;
d<<=1;
LCD_CLK=0;
}
// shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
LCD_CE=1;
// digitalWrite(PIN_SCE, HIGH);
}


void drawBox(void)
{
    int j;
    
    for(j = 0; j < 84; j++) // top
    {
        gotoXY(j, 0);
        LCDWrite(LCD_DATA,0x01);
    }

    for(j = 0; j < 84; j++) //Bottom
    {
        gotoXY(j, 5);
        LCDWrite(LCD_DATA,0x80);
    }
    
    for(j = 0; j < 6; j++) // Right
    {
        gotoXY(83, j);
        LCDWrite(LCD_DATA,0xff);
    }
    
    for(j = 0; j < 6; j++) // Left
    {
        gotoXY(0, j);
        LCDWrite(LCD_DATA,0xff);
    }
}

#ifndef USER_H
#define	USER_H
#include <xc.h>
#include "lcd.h"
#include "eeprom.h"

int TempSetpoint(int b);

char readButtons(void);

#endif
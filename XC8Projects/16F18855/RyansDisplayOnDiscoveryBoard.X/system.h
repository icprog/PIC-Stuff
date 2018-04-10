#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h>
#include <stdint.h>
#include "lcd.h"
#include "adc.h"
#include "tmr2.h"
#include "pwm.h"

#define _XTAL_FREQ  1000000         // Define clock freq for __delay_ms();


void SYSTEM_Initialize(void);

void OSCILLATOR_Initialize(void);

#endif
#ifndef SYSTEM_H
#define	SYSTEM_H

#include    <xc.h>
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/rtcc.h"

//#include    "pin_manager.h"
#include    <stdint.h>
#include    <stdbool.h>
//#include    "interrupt_manager.h"
//#include    "traps.h"
#include    "glcd.h"
//#include    "pid.h"  
//#include    "adc.h"
//#include    "touch.h"
//#include    "pwm.h"
//#include    "rtcc.h"
//#include    "traps.h"
//#include    "user.h"
//#include    "DEE Emulation 16-bit.h"
//#include    "menu.h"


#define _XTAL_FREQ  32000000UL
#define FOSC        32000000UL
#define FCY         FOSC/2

#include <libpic30.h>                   // FOSC & FCY "MUST" be defined before including libPIC30H

void SYSTEM_Initialize(void);

void OSCILLATOR_Initialize(void);

#endif

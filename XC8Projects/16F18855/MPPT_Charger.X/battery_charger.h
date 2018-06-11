#include "system.h"

#define		IOUT1				RC4 // was RA1
#define		VIN1				RC7 // was RA2
#define		IIN1        		RC6 // was RC2
#define		VOUT1				RC5 // was RC3

#define		SET_CURRENT(x)		{ Iref = x; }
#define		SET_VOLTAGE(x)		{ Vref = x; }
#define		WARMUP_TIME			64
#define		CONSTANT_VOLTAGE	(!Imode)
#define		I_BAT_DETECT		16 
#define		CO1					RA6
#define		CO2					RA7
#define		TRIS_CO1			TRISA6
#define		TRIS_CO2			TRISA7
#define		VSENSE              Vout
#define		ISENSE              Iout


#define		STOP_CONVERTER()	{ increment = 0; TRIS_CO1 = 1; TRIS_CO2 = 1; }   // NCO is Numerically controller oscillator, will now be PWM to Converter?
//#define		STOP_CONVERTER()	{ increment = 0; set_NCO(); TRIS_CO1 = 1; TRIS_CO2 = 1; }   // NCO is Numerically controller oscillator, will now be PWM to Converter?
#define  	START_CONVERTER()	{ warmup = WARMUP_TIME; TRIS_CO1 = 0; TRIS_CO2 = 0; }       // NCO is PWM to Converter?


#ifndef BATTERY_CHARGER_H
	#define BATTERY_CHARGER_H
	enum charge_states { IDLE = 0, FAULT = 1, FINISHED = 2, PRECHARGE = 3, CHARGE = 4, FLOAT = 5 };
#endif
    
    

#define		BATTERY_SLA
//#define		BATTERY_LIFEPO
//#define		BATTERY_LICO

#ifdef	BATTERY_SLA
	#include "lead_acid.h"
	#define 	ISTOP	IFLOAT
#endif

#ifdef	BATTERY_LIFEPO
	#include "LiFePo.h"
#endif

#ifdef	BATTERY_LICO
	#include "LiCo.h"
#endif

#define 	IMIN_UPDATE			5
#define		VBAT_DETECTION		1640

extern unsigned char battery_state;

void Init_Battery_State_Machine(void);
void Battery_State_Machine(void);
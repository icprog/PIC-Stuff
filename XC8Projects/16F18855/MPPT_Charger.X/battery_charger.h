#include "system.h"

#define		IOUT				RA1
#define		VIN					RA2
#define		IIN					RC2
#define		VOUT				RC3

#define		SET_CURRENT(x)		{ iref = x; }


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
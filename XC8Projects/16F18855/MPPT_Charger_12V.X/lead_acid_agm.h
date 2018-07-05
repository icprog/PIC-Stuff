//Lead-acid battery specific parameters
#ifndef     LEAD_ACID_AGM_H
#define     LEAD_ACID_AGM_H
#define     PRESET1
//define      PRESET2


//	1.75V per cell cutoff voltage
// 	2.10V per cell charged OCV voltage
//	2.25V per cell floating voltage
//	2.40V per cell charging voltage

#ifdef PRESET1

    #define CHARGING_VOLTAGE		1445	// 14.45V
//    #define CHARGING_VOLTAGE		1440	// 14.40V
	#define	FLOATING_VOLTAGE		1380	// 13.80V
	#define	CUTOFF_VOLTAGE			1075	// 10.75V

	#define	ILIM_PRECHARGE			10      // 1A, Small current set at PRECHARGE stage
	#define	ILIM					55      // 5.5A Point where we switch back to MPPT, or Current Mode
	#define IFLOAT					25      // 2.5A, minimum charging current				

#endif

#define	PRECHARGE_TIME              3

#endif

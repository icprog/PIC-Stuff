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

    #define CHARGING_VOLTAGE		1400	//14.00V
//    #define CHARGING_VOLTAGE		1350	//14.40V
	#define	FLOATING_VOLTAGE		1340	//13.40V
	#define	CUTOFF_VOLTAGE			1075	//10.75V

	#define	ILIM_PRECHARGE			10      //1A, Small current set at PRECHARGE stage
	#define	ILIM					35      //3.5A Point Where we switch back to MPPT, or Current Mode
	#define IFLOAT					15      //1.5A, minimum charging current				

#endif

#define	PRECHARGE_TIME		600

//#define FLOAT_TIME			43200

//#define	FLOAT_RELAX_TIME	(FLOAT_TIME - 10)

#define IFLAT_COUNT		600

#endif

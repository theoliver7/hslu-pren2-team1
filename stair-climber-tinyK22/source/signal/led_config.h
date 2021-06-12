//=======================================================
// PREN2 - TEAM1 - STAIRCLIMBER
//=======================================================
//	PWM_Test_TinyK22
//	19.03.2021
//	Authors: Widmer Michael, Friedli Manuel
//=======================================================
//DESCRIPTION
//=======================================================
//
//=======================================================

#ifndef UTILS_LED_CONFIG_H_
#define UTILS_LED_CONFIG_H_

//=======================================================
// DEFINES
//======================================================= 
#define MAX_DUTYCYCLE 		(float)255.0 	//

#define CH_LED_RED 		3		//
#define FTM_LED_RED 	FTM3	//
#define MOD_LED_RED		FTM3_MODULO

#define CH_LED_GREEN	4	//
#define FTM_LED_GREEN	FTM0	//
#define MOD_LED_GREEN	FTM0_MODULO

#define CH_LED_BLUE 	5	//
#define FTM_LED_BLUE 	FTM0	//
#define MOD_LED_BLUE	FTM0_MODULO

#endif

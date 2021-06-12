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

#ifndef UTILS_FTM0_CONFIG_H_
#define UTILS_FTM0_CONFIG_H_

//=======================================================
// INCLUDES
//=======================================================
#include "platform.h"

//=======================================================
// DEFINES
//======================================================= 
//-------------------------------------------------------
// FTM0 MODUL SETTINGS
//-------------------------------------------------------
#define FTM2_MODULO 			0xFFFF	// 65535
#define FTM2_CLOCK				2 		// 1: System-Clock 60MHz 2: Fixed-Freq-Clock 250kHz
#define FTM2_CLOCK_PRESCALER 	2 		// 0:1 1:2 2:4 3:8 4:16 5:32 6:64 7:128
#define FTM2_PWM_MODE 			0		// 1: Center aligned 0: Edge aligned
#define FTM2_ENABLE_INTERRUPT 	0		// 1: Enabled 0: Disabled
#define FTM2_INTERRUPT_PRIO		8		// Interrupt priority
#define FTM2_TOF_TIME			(float)(((FTM2_MODULO+1)*4)/(FIXED_SYSTEM_CLOCK))

//-------------------------------------------------------
// CHANNEL SETTINGS
// For further information see K22F Sub-Family Reference Manual
// Chapter 39.3.6 on page 906
//-------------------------------------------------------
// CHANNEL 0 #EMPTY #PTB18
//-------------------------------------------------------
#define FTM2_CH0_MSA	0 	//
#define FTM2_CH0_MSB	0 	//
#define FTM2_CH0_ELSA	0 	//
#define FTM2_CH0_ELSB	0 	//
#define FTM2_CH0_CHIE	0 	// Channel Interrupt 1: Enabled 0: Disabled
#define FTM2_CH0_PWM_SV 0	// First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

//-------------------------------------------------------
// CHANNEL 1 #FREQ_GEN_STEPPER #PTB19
//-------------------------------------------------------
#define FTM2_CH1_MSA	1 	//
#define FTM2_CH1_MSB	0 	//
#define FTM2_CH1_ELSA	0 	//
#define FTM2_CH1_ELSB	1 	//
#define FTM2_CH1_CHIE	0 	// Channel Interrupt 1: Enabled 0: Disabled
#define FTM2_CH1_PWM_SV 0 	// First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

#endif

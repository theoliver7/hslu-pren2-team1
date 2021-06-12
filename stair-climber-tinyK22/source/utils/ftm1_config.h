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

#ifndef UTILS_FTM1_CONFIG_H_
#define UTILS_FTM1_CONFIG_H_

//=======================================================
// INCLUDES
//=======================================================
#include "platform.h"

//=======================================================
// DEFINES
//======================================================= 
//-------------------------------------------------------
// FTM1 MODUL SETTINGS
//-------------------------------------------------------
#define FTM1_MODULO 			0x0257	// 65535		//0x7FFF	// 32767
#define FTM1_CLOCK				1 		// 1: System-Clock 60MHz 2: Fixed-Freq-Clock 250kHz					//10us Periode
#define FTM1_CLOCK_PRESCALER 	0 		// 0:1 1:2 2:4 3:8 4:16 5:32 6:64 7:128								//""
#define FTM1_PWM_MODE 			0		// 1: Center aligned 0: Edge aligned
#define FTM1_ENABLE_INTERRUPT 	0		// 1: Enabled 0: Disabled
#define FTM1_INTERRUPT_PRIO		8		// Interrupt priority
#define FTM1_TOF_TIME			(float)(((FTM1_MODULO+1)*1)/(FIXED_SYSTEM_CLOCK))

//-------------------------------------------------------
// CHANNEL SETTINGS
// For further information see K22F Sub-Family Reference Manual
// Chapter 39.3.6 on page 906
//-------------------------------------------------------
// CHANNEL 0 #Inputcapture Ultrasonic
//-------------------------------------------------------
#define FTM1_CH0_MSA	0 		//
#define FTM1_CH0_MSB	0 		//
#define FTM1_CH0_ELSA	1 		//
#define FTM1_CH0_ELSB	1 		//
#define FTM1_CH0_CHIE	1 		// Channel Interrupt 1: Enabled 0: Disabled
#define FTM1_CH0_PWM_SV 0	// First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

//-------------------------------------------------------
// CHANNEL 1 #EMPTY
//-------------------------------------------------------
#define FTM1_CH1_MSA	0 //
#define FTM1_CH1_MSB	0 //
#define FTM1_CH1_ELSA	0 //
#define FTM1_CH1_ELSB	0 //
#define FTM1_CH1_CHIE	0 // Channel Interrupt 1: Enabled 0: Disabled
#define FTM1_CH1_PWM_SV 0 // First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------


#endif

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
#define FTM0_MODULO 			0xFFFE	// 65534		//0x7FFF	// 32767
#define FTM0_CLOCK				1 		// 1: System-Clock 60MHz 2: Fixed-Freq-Clock 250kHz					//1.0922ms Periode
#define FTM0_CLOCK_PRESCALER 	0 		// 0:1 1:2 2:4 3:8 4:16 5:32 6:64 7:128								//""
#define FTM0_PWM_MODE 			0		// 1: Center aligned 0: Edge aligned
#define FTM0_ENABLE_INTERRUPT 	0		// 1: Enabled 0: Disabled
#define FTM0_INTERRUPT_PRIO		8		// Interrupt priority
#define FTM0_TOF_TIME			(float)(((FTM0_MODULO+1)*1)/(FIXED_SYSTEM_CLOCK))

//-------------------------------------------------------
// CHANNEL SETTINGS
// For further information see K22F Sub-Family Reference Manual
// Chapter 39.3.6 on page 906
//-------------------------------------------------------
// CHANNEL 0 #unused
//-------------------------------------------------------
#define FTM0_CH0_MSA	0 		//
#define FTM0_CH0_MSB	0 		//
#define FTM0_CH0_ELSA	0 		//
#define FTM0_CH0_ELSB	0 		//
#define FTM0_CH0_CHIE	0 		// Channel Interrupt 1: Enabled 0: Disabled
#define FTM0_CH0_PWM_SV 0	// First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

//-------------------------------------------------------
// CHANNEL 1 #LIFTMOT1_DOWN
//-------------------------------------------------------
#define FTM0_CH1_MSA	0 //
#define FTM0_CH1_MSB	1 //
#define FTM0_CH1_ELSA	1 //
#define FTM0_CH1_ELSB	0 //
#define FTM0_CH1_CHIE	0 // Channel Interrupt 1: Enabled 0: Disabled
#define FTM0_CH1_PWM_SV 0xFFFF // First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

//-------------------------------------------------------
// CHANNEL 2 #LIFTMOT1_UP
//-------------------------------------------------------
#define FTM0_CH2_MSA	0 		//
#define FTM0_CH2_MSB	1 		//
#define FTM0_CH2_ELSA	1 		//
#define FTM0_CH2_ELSB	0 		//
#define FTM0_CH2_CHIE	0 		// Channel Interrupt 1: Enabled 0: Disabled
#define FTM0_CH2_PWM_SV 0xFFFF 	// First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

//-------------------------------------------------------
// CHANNEL 3 #
//-------------------------------------------------------
#define FTM0_CH3_MSA	0 //
#define FTM0_CH3_MSB	0 //
#define FTM0_CH3_ELSA	0 //
#define FTM0_CH3_ELSB	0 //
#define FTM0_CH3_CHIE	0 // Channel Interrupt 1: Enabled 0: Disabled
#define FTM0_CH3_PWM_SV 0 // First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

//-------------------------------------------------------
// CHANNEL 4 #LED_GREEN #PTD4
//-------------------------------------------------------
#define FTM0_CH4_MSA	0 //
#define FTM0_CH4_MSB	1 //
#define FTM0_CH4_ELSA	1 //
#define FTM0_CH4_ELSB	0 //
#define FTM0_CH4_CHIE	0 // Channel Interrupt 1: Enabled 0: Disabled
#define FTM0_CH4_PWM_SV 0 // First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

//-------------------------------------------------------
// CHANNEL 5 #LED_BLUE #PTD5
//-------------------------------------------------------
#define FTM0_CH5_MSA	0 //
#define FTM0_CH5_MSB	1 //
#define FTM0_CH5_ELSA	1 //
#define FTM0_CH5_ELSB	0 //
#define FTM0_CH5_CHIE	0 // Channel Interrupt 1: Enabled 0: Disabled
#define FTM0_CH5_PWM_SV 0 // First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

//-------------------------------------------------------
// CHANNEL 6 #LIFTMOT2_UP
//-------------------------------------------------------
#define FTM0_CH6_MSA	0 //
#define FTM0_CH6_MSB	1 //
#define FTM0_CH6_ELSA	1 //
#define FTM0_CH6_ELSB	0 //
#define FTM0_CH6_CHIE	0 // Channel Interrupt 1: Enabled 0: Disabled
#define FTM0_CH6_PWM_SV 0xFFFF // First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

//-------------------------------------------------------
// CHANNEL 7 #LIFTMOT2_DOWN
//-------------------------------------------------------
#define FTM0_CH7_MSA	0 //
#define FTM0_CH7_MSB	1 //
#define FTM0_CH7_ELSA	1 //
#define FTM0_CH7_ELSB	0 //
#define FTM0_CH7_CHIE	0 // Channel Interrupt 1: Enabled 0: Disabled
#define FTM0_CH7_PWM_SV 0xFFFF // First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

#endif

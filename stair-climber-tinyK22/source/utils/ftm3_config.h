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

#ifndef UTILS_FTM3_CONFIG_H_
#define UTILS_FTM3_CONFIG_H_

//=======================================================
// INCLUDES
//=======================================================
#include "platform.h"

//=======================================================
// DEFINES
//======================================================= 
//-------------------------------------------------------
// FTM3 MODUL SETTINGS
//-------------------------------------------------------
#define FTM3_MODULO 			0xFFFF	// 65535		//0x7FFF	// 32767
#define FTM3_CLOCK				1 		// 1: System-Clock 60MHz 2: Fixed-Freq-Clock 250kHz
#define FTM3_CLOCK_PRESCALER 	0 		// 0:1 1:2 2:4 3:8 4:16 5:32 6:64 7:128
#define FTM3_PWM_MODE 			0		// 1: Center aligned 0: Edge aligned
#define FTM3_ENABLE_INTERRUPT 	0		// 1: Enabled 0: Disabled
#define FTM3_INTERRUPT_PRIO		8		// Interrupt priority
#define FTM3_TOF_TIME			(float)(((FTM3_MODULO+1)*1)/(FIXED_SYSTEM_CLOCK))

//-------------------------------------------------------
// CHANNEL SETTINGS
// For further information see K22F Sub-Family Reference Manual
// Chapter 39.3.6 on page 906
//-------------------------------------------------------
// CHANNEL 0 #DC_MOT2 FORWARD
//-------------------------------------------------------
#define FTM3_CH0_MSA	0 		//
#define FTM3_CH0_MSB	1 		//
#define FTM3_CH0_ELSA	1 		//
#define FTM3_CH0_ELSB	0 		//
#define FTM3_CH0_CHIE	0 		// Channel Interrupt 1: Enabled 0: Disabled
#define FTM3_CH0_PWM_SV 0xFFFF	// First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

//-------------------------------------------------------
// CHANNEL 1 #DC_MOT3 BACKWARD
//-------------------------------------------------------
#define FTM3_CH1_MSA	0 //
#define FTM3_CH1_MSB	1 //
#define FTM3_CH1_ELSA	1 //
#define FTM3_CH1_ELSB	0 //
#define FTM3_CH1_CHIE	0 // Channel Interrupt 1: Enabled 0: Disabled
#define FTM3_CH1_PWM_SV 0xFFFF // First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

//-------------------------------------------------------
// CHANNEL 2 #DC_MOT3 FORWARD
//-------------------------------------------------------
#define FTM3_CH2_MSA	0 		//
#define FTM3_CH2_MSB	1 		//
#define FTM3_CH2_ELSA	1 		//
#define FTM3_CH2_ELSB	0 		//
#define FTM3_CH2_CHIE	0 		// Channel Interrupt 1: Enabled 0: Disabled
#define FTM3_CH2_PWM_SV 0xFFFF 	// First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

//-------------------------------------------------------
// CHANNEL 3 #LED_RED #PTD3
//-------------------------------------------------------
#define FTM3_CH3_MSA	0 //
#define FTM3_CH3_MSB	1 //
#define FTM3_CH3_ELSA	1 //
#define FTM3_CH3_ELSB	0 //
#define FTM3_CH3_CHIE	0 // Channel Interrupt 1: Enabled 0: Disabled
#define FTM3_CH3_PWM_SV 0 // First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

//-------------------------------------------------------
// CHANNEL 4 #
//-------------------------------------------------------
#define FTM3_CH4_MSA	0 //
#define FTM3_CH4_MSB	0 //
#define FTM3_CH4_ELSA	0 //
#define FTM3_CH4_ELSB	0 //
#define FTM3_CH4_CHIE	0 // Channel Interrupt 1: Enabled 0: Disabled
#define FTM3_CH4_PWM_SV 0 // First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

//-------------------------------------------------------
// CHANNEL 5 #DC_MOT1 BACKWARD
//-------------------------------------------------------
#define FTM3_CH5_MSA	0 //
#define FTM3_CH5_MSB	1 //
#define FTM3_CH5_ELSA	1 //
#define FTM3_CH5_ELSB	0 //
#define FTM3_CH5_CHIE	0 // Channel Interrupt 1: Enabled 0: Disabled
#define FTM3_CH5_PWM_SV 0xFFFF // First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

//-------------------------------------------------------
// CHANNEL 6 #DC_MOT_1 FORWARD
//-------------------------------------------------------
#define FTM3_CH6_MSA	0 //
#define FTM3_CH6_MSB	1 //
#define FTM3_CH6_ELSA	1 //
#define FTM3_CH6_ELSB	0 //
#define FTM3_CH6_CHIE	0 // Channel Interrupt 1: Enabled 0: Disabled
#define FTM3_CH6_PWM_SV 0xFFFF // First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

//-------------------------------------------------------
// CHANNEL 7 #DC_MOT2 BACKWARD
//-------------------------------------------------------
#define FTM3_CH7_MSA	0 //
#define FTM3_CH7_MSB	1 //
#define FTM3_CH7_ELSA	1 //
#define FTM3_CH7_ELSB	0 //
#define FTM3_CH7_CHIE	0 // Channel Interrupt 1: Enabled 0: Disabled
#define FTM3_CH7_PWM_SV 0xFFFF // First value put in CONTROLS[CHn].CnV
//-------------------------------------------------------

#endif

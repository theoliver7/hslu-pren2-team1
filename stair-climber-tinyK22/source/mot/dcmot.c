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

//=======================================================
//INCLUDES
//=======================================================
#include "dcmot.h"
#include "dcmot_config.h"
#include "stdint.h"
#include "platform.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
//=======================================================
// DEFINES
//======================================================= 

//=======================================================
// FUNCTION DEFINITIONS
//======================================================= 

/*
 * Helpfunction: short delay helps the motor get speed smoothly
 *
 */
static void DCMOT_short_delay(void) {
	for (int i = 0; i < (DCMOT_POS_FINE * 20000); i++) {
		__asm volatile ("nop");
	}
}

/*
 * Helpfunction for aproaching backwards speed finely
 *
 */
static void DCMOT_fine_startup_backwards(int motor_ch, uint8_t speed) {
	if (speed > 0) {
		int value = FTM3->CONTROLS[motor_ch].CnV;		//get actual CnV value
		int dif = (0xFFFF / 256 * speed) - value;

		for (uint8_t x = 0; x < 100; x++) {
			FTM3->CONTROLS[motor_ch].CnV += dif / 100;
			DCMOT_short_delay();
		}
		FTM3->CONTROLS[motor_ch].CnV = (0xFFFF / 256 * speed);
	} else {
		FTM3->CONTROLS[motor_ch].CnV = 0xFFFF;
	}
}

/*
 * Helpfunction for aproaching backwards speed finely
 *
 */
static void DCMOT_fine_startup_vorward(int motor_ch, uint8_t speed) {
	if (speed > 0) {
		int value = FTM3->CONTROLS[motor_ch].CnV;		//get actual CnV value
		int dif = (0xFFFF / 256 * speed) - value;

		for (uint8_t x = 0; x < 100; x++) {
			FTM3->CONTROLS[motor_ch].CnV += dif / 100;
			DCMOT_short_delay();
		}
		FTM3->CONTROLS[motor_ch].CnV = (0xFFFF / 256 * speed);
	} else {
		FTM3->CONTROLS[motor_ch].CnV = 0xFFFF;
	}
}

/*
 * Sets the vorward speed for motor from 0 to 100%
 * valid Parameters: all: true all false: only front and back
 * 			         speed: 0 - 255 (=0-100%)
 *
 * returns 0, if there was a error
 * */
bool DCMOT_sync_vorward(bool all, uint8_t speedv) {
	uint8_t speed = 255 - speedv;
	if (speed > 0) {
		int mod_val = (0xFFFF / 256 * speed);
		if (all) {
			FTM3->CONTROLS[CHANNEL_DCMOT1_VORWARD].CnV = mod_val;
			FTM3->CONTROLS[CHANNEL_DCMOT2_VORWARD].CnV = mod_val;
			FTM3->CONTROLS[CHANNEL_DCMOT3_VORWARD].CnV = mod_val;
		} else {
			FTM3->CONTROLS[CHANNEL_DCMOT2_VORWARD].CnV = mod_val;
			FTM3->CONTROLS[CHANNEL_DCMOT3_VORWARD].CnV = mod_val;
		}
		return 1;
	} else {
		if (all) {
			FTM3->CONTROLS[CHANNEL_DCMOT1_VORWARD].CnV = 0xFFFF;
			FTM3->CONTROLS[CHANNEL_DCMOT2_VORWARD].CnV = 0xFFFF;
			FTM3->CONTROLS[CHANNEL_DCMOT3_VORWARD].CnV = 0xFFFF;
		} else {
			FTM3->CONTROLS[CHANNEL_DCMOT2_VORWARD].CnV = 0xFFFF;
			FTM3->CONTROLS[CHANNEL_DCMOT3_VORWARD].CnV = 0xFFFF;
		}
		return 1;
	}
}

/*
 * Sets the vorward speed for motor from 0 to 100%
 * valid Parameters: all: true => all false => only front and back
 * 			         speed: 0 - 255 (=0-100%)
 *
 * returns 0, if there was a error
 * */
bool DCMOT_sync_backward(bool all, uint8_t speedv) {
	uint8_t speed = 255 - speedv;
	if (speed > 0) {
		int mod_val = (0xFFFF / 256 * speed);
		if (all) {
			FTM3->CONTROLS[CHANNEL_DCMOT1_BACKWARDS].CnV = mod_val;
			FTM3->CONTROLS[CHANNEL_DCMOT2_BACKWARDS].CnV = mod_val;
			FTM3->CONTROLS[CHANNEL_DCMOT3_BACKWARDS].CnV = mod_val;
		} else {
			FTM3->CONTROLS[CHANNEL_DCMOT2_BACKWARDS].CnV = mod_val;
			FTM3->CONTROLS[CHANNEL_DCMOT3_BACKWARDS].CnV = mod_val;
		}
		return 1;
	} else {
		if (all) {
			FTM3->CONTROLS[CHANNEL_DCMOT1_BACKWARDS].CnV = 0xFFFF;
			FTM3->CONTROLS[CHANNEL_DCMOT2_BACKWARDS].CnV = 0xFFFF;
			FTM3->CONTROLS[CHANNEL_DCMOT3_BACKWARDS].CnV = 0xFFFF;
		} else {
			FTM3->CONTROLS[CHANNEL_DCMOT2_BACKWARDS].CnV = 0xFFFF;
			FTM3->CONTROLS[CHANNEL_DCMOT3_BACKWARDS].CnV = 0xFFFF;
		}
		return 1;
	}
}

/*
 * Sets the vorward speed for motor from 0 to 100%
 * valid Parameters: all: true => all false => only front and back
 * 			         speed: 0 - 255 (=0-100%)
 *
 * returns 0, if there was a error
 * */
bool DCMOT_vorward(uint8_t motor, uint8_t speedv) {
	uint8_t speed = 255 - speedv;		//0: 0% speed, 255: 100% speed
	switch (motor) {
	case 1:
		DCMOT_fine_startup_vorward(CHANNEL_DCMOT1_VORWARD, speed);
		break;
	case 2:
		DCMOT_fine_startup_vorward(CHANNEL_DCMOT2_VORWARD, speed);
		break;
	case 3:
		DCMOT_fine_startup_vorward(CHANNEL_DCMOT3_VORWARD, speed);
		break;
	default:
		return 0;		//There was a fail
		break;
	}
	return 1;
}

/*
 * Sets the backward speed for motor from 0 to 100%
 * valid Parameters: motor: 1 / 2 / 3
 * 			         speed: 0 - 256 (=0-100%)
 *
 * returns 0, if there was a error
 * */
bool DCMOT_backward(uint8_t motor, uint8_t speedv) {
	uint8_t speed = 255 - speedv;		//0: 100% speed, 255: 0% speed
	switch (motor) {
	case 1:
//			FTM3->CONTROLS[CHANNEL_DCMOT1_VORWARD].CnV = 0xFFFF;	//stop motor
		DCMOT_fine_startup_backwards(CHANNEL_DCMOT1_BACKWARDS, speed);
		break;
	case 2:
//			FTM3->CONTROLS[CHANNEL_DCMOT2_VORWARD].CnV = 0xFFFF;	//stop motor
		DCMOT_fine_startup_backwards(CHANNEL_DCMOT2_BACKWARDS, speed);
		break;
	case 3:
//			FTM3->CONTROLS[CHANNEL_DCMOT3_VORWARD].CnV = 0xFFFF;	//stop motor
		DCMOT_fine_startup_backwards(CHANNEL_DCMOT3_BACKWARDS, speed);
		break;
	default:
		return 0;		//There was a fail
		break;
	}
	return 1;
}


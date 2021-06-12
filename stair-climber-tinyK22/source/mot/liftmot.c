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

#include "liftmot.h"
#include "liftmot_config.h"
#include "stdint.h"
#include "platform.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "utils/ftm0_config.h"
#include "signal/led.h"
#include "sensors/ledbarrier.h"
#include "sensors/groundsensor.h"

//=======================================================
// DEFINES
//======================================================= 

//=======================================================
// FUNCTION DEFINITIONS
//======================================================= 

int deadtime = 3200000;

/*
 * Helpfunction: short delay helps the motor get speed smoothly
 *
 */
static void LIFTMOT_short_delay(void) {
	for (int i = 0; i < (MOT_POS_FINE * 20000); i++) {
		__asm volatile ("nop");
	}
}

static void wait(int cycles) {
	for (int i = 0; i < cycles; i++) {
		__asm volatile ("nop");
	}
}

/*
 * Helpfunction for aproaching backwards speed finely
 *
 */
static void LIFTMOT_fine_startup_down(int motor_and_direction, int speedv) {
	if (speedv > 0) {
		int speed = 256 - speedv;
		int value = FTM0->CONTROLS[motor_and_direction].CnV; //get actual CnV value
		int dif = (FTM0_MODULO / 256 * speed) - value;

		for (uint8_t x = 0; x < 100; x++) {
			FTM0->CONTROLS[motor_and_direction].CnV += dif / 100;
			LIFTMOT_short_delay();
		}
		FTM0->CONTROLS[motor_and_direction].CnV = (FTM0_MODULO / 256 * speed);
	} else {
		FTM0->CONTROLS[motor_and_direction].CnV = 0xFFFF;
	}
}

/*
 * Helpfunction for aproaching up-speed finely
 *
 */
static void LIFTMOT_fine_startup_up(int motor_and_direction, int speedv) {
	if (speedv > 0) {
		int speed = 256 - speedv;
		int value = FTM0->CONTROLS[motor_and_direction].CnV; //get actual CnV value
		int dif = (FTM0_MODULO / 256 * speed) - value;

		for (uint8_t x = 0; x < 100; x++) {
			FTM0->CONTROLS[motor_and_direction].CnV += dif / 100;
			LIFTMOT_short_delay();
		}
		FTM0->CONTROLS[motor_and_direction].CnV = (FTM0_MODULO / 256 * speed);
	} else {
		FTM0->CONTROLS[motor_and_direction].CnV = 0xFFFF;
	}
}

/*
 * Sets the upwards speed for motor from 0 to 100%
 * valid Parameters: speed: 0 - 255 (=0-100%)
 *
 * returns Parameters: 0: if there was a error, 1: everything went okey
 * */
bool LIFTMOT_sync_up(uint8_t speedv) {
	uint8_t speed = 256 - speedv;
	if (speed > 0) {
		int mod_val = (FTM0_MODULO / 256 * speed);
		FTM0->CONTROLS[CHANNEL_LIFTMOT1_UP].CnV = mod_val;
		FTM0->CONTROLS[CHANNEL_LIFTMOT2_UP].CnV = mod_val;
		return 1;
	} else {
		FTM0->CONTROLS[CHANNEL_LIFTMOT1_UP].CnV = 0xFFFF;
		FTM0->CONTROLS[CHANNEL_LIFTMOT2_UP].CnV = 0xFFFF;
		return 1;
	}
}

/*
 * Sets the upwards speed for motor from 0 to 100%
 * valid Parameter: speed: 0 - 255 (=0-100%)
 *
 * returns Parameters: 0: if there was a error, 1: everything went okey
 * */
bool LIFTMOT_sync_down(uint8_t speedv) {
	uint8_t speed = 255 - speedv;
	if (speed > 0) {
		int mod_val = (FTM0_MODULO / 255 * speed);
		FTM0->CONTROLS[CHANNEL_LIFTMOT1_DOWN].CnV = mod_val;
		FTM0->CONTROLS[CHANNEL_LIFTMOT2_DOWN].CnV = mod_val;
		return 1;
	} else {
		FTM0->CONTROLS[CHANNEL_LIFTMOT1_DOWN].CnV = 0xFFFF;
		FTM0->CONTROLS[CHANNEL_LIFTMOT2_DOWN].CnV = 0xFFFF;
		return 1;
	}
}

/*
 * Sets the upwards speed for motor from 0 to 100%
 * valid Parameters: motor: 1 / 2
 * 			         speed: 0 - 255 (=0-100%)
 *
 * returns Parameters: 0: if there was a error, 1: everything went okey
 * */

bool LIFTMOT_up(uint8_t motor, uint8_t speed) {

	switch (motor) {
	case 1:
		LIFTMOT_fine_startup_up(CHANNEL_LIFTMOT1_UP, speed);
		break;
	case 2:
		LIFTMOT_fine_startup_up(CHANNEL_LIFTMOT2_UP, speed);
		break;
	default:
		return 0;		//There was a fail
		break;
	}
	return 1;
}

/*
 * Sets the backward speed for motor from 0 to 100%
 * valid Parameters: motor: 1 / 2
 * 			         speed: 0 - 256 (=0-100%)
 *
 * returns Parameters: 0: if there was a error, 1: everything went okey
 * */
bool LIFTMOT_down(uint8_t motor, uint8_t speed) {

	switch (motor) {
	case 1:
		LIFTMOT_fine_startup_down(CHANNEL_LIFTMOT1_DOWN, speed);
		break;
	case 2:
		LIFTMOT_fine_startup_down(CHANNEL_LIFTMOT2_DOWN, speed);
		break;

	default:
		return 0;		//There was a fail
		break;
	}
	return 1;
}

typedef enum segment_state_e {
	top = 1, bottom, ground, aboveground, underground
} segment_state_t;

segment_state_t STATE_FRONT = aboveground;
segment_state_t STATE_BACK = aboveground;

// This function lifts the middle segment slightly off the ground.
// Both outer segments have to be in the same valid state. Valid
// states are: ground, aboveground.
bool LIFTMOT_DRIVE_POS_MIDDLEUP() {
	if ((STATE_FRONT == aboveground) && (STATE_BACK == aboveground)) {
		// alt war 75 50
		LIFTMOT_sync_down(150);
		wait(1000000);
		LIFTMOT_sync_down(75);
		while (!GET_GROUND_SENSOR()) {
			;
		}
		wait(16000000);
		LIFTMOT_sync_down(200);
		wait(4000000);
		LIFTMOT_sync_down(0);
		wait(10000);
		LIFTMOT_sync_down(75);
		STATE_FRONT = underground;
		STATE_BACK = underground;
		return true;
	} else if ((STATE_FRONT == ground) && (STATE_BACK == ground)) {
		LIFTMOT_sync_down(240);
		wait(4000000);
//		LIFTMOT_sync_down(0); //alt (ist nach dem hochfahren wieder heruntergefallen)
		LIFTMOT_sync_down(0);
		wait(10000);
		LIFTMOT_sync_down(75);
		STATE_FRONT = underground;
		STATE_BACK = underground;
		return true;
	} else {
		return false;
	}
}

// This function puts the middle segment back on the ground.
bool LIFTMOT_DRIVE_POS_MIDDLEDOWN() {
//	if ((STATE_FRONT == underground) && (STATE_BACK == underground)) {
//		LIFTMOT_sync_up(75);
//		wait(1000000);
//		LIFTMOT_sync_up(50);
//		while (GET_GROUND_SENSOR()) {
//			;
//		}
//		wait(4000000);
//		LIFTMOT_sync_down(0);
//		LIFTMOT_DRIVE_POS_OUTERGROUND();
//		STATE_FRONT = ground;
//		STATE_BACK = ground;
//		return true;
//	} else if ((STATE_FRONT == ground) && (STATE_BACK == ground)) {
//		return true;
//	} else {
//		return false;
//	}
//	if (STATE_FRONT == aboveground && STATE_BACK == aboveground) //if you are in synchdrivepos
//				{
//		LIFTMOT_DRIVE_POS_OUTERGROUND();
//				}
	if (STATE_FRONT == underground && STATE_BACK == underground) //if you are in synchdrivepos
			{
		LIFTMOT_sync_up(200);
		wait(4000000);
		LIFTMOT_sync_up(50);
		wait(2000000);
		LIFTMOT_sync_down(200);
		wait(2000000);
//		LIFTMOT_sync_down(0);
		LIFTMOT_sync_down(50);
		wait(2000000);
		STATE_FRONT = ground;
		STATE_BACK = ground;
		return 1;
	} else if ((STATE_FRONT == ground) && (STATE_BACK == ground)) {
		return true;
	}
	return 0;

}

// This function sets the outer segments back on the ground.
bool LIFTMOT_DRIVE_POS_OUTERGROUND() {
	LIFTMOT_sync_down(150);
	wait(1000000);
	LIFTMOT_sync_down(100);
	while (!GET_GROUND_SENSOR()) {
		;
	}
	wait(10000000);
	LIFTMOT_sync_down(0);
	STATE_FRONT = ground;
	STATE_BACK = ground;
	return true;
}

// This function sets the outer segments back on the ground.
bool LIFTMOT_FRONT_GROUND() {
	LIFTMOT_down(1, 250);
	wait(1500000);
	LIFTMOT_down(1, 100);
	while (!GET_GROUND_SENSOR()) {
		;
	}
	wait(10000000);
	LIFTMOT_down(1, 0);
	// fährt wieder kurz nach oben, dass sich das segment wieder in der gleichen
	// position wie das hintere befindet
	LIFTMOT_up(1, 230);
	wait(3700000);
	LIFTMOT_up(1, 0);
	// Status noch nicht umgestellt
	STATE_FRONT = aboveground;
	return true;
}

// This function lifts the outer segments slightly off the ground.
bool LIFTMOT_DRIVE_POS_OUTERUP() {
	if ((STATE_FRONT == ground) && (STATE_BACK == ground)) {
		LIFTMOT_sync_up(230);
		wait(4000000);
//		LIFTMOT_sync_up(0); //alt (ist nach dem hochfahren wieder heruntergefallen)
		LIFTMOT_sync_up(50);
		STATE_FRONT = aboveground;
		STATE_BACK = aboveground;
		return true;
	} else {
		return false;
	}
}

// true: front false: back
bool LIFTMOT_GOTO_TOP(bool segment) {
	if (segment) {
		if (STATE_FRONT == top) {
			return false;
		} else {
			LIFTMOT_up(1, 255);
			wait(deadtime);
			LIFTMOT_up(1, 255);
			while (!LEDBARRIER_FRONT_GET()) {
				;
			}
			LIFTMOT_up(1, 40);
			STATE_FRONT = top;
			return true;
		}
	} else {
		if (STATE_BACK == top) {
			return false;
		} else {
			LIFTMOT_up(2, 255);
			wait(deadtime);
			LIFTMOT_up(2, 255);
			while (!LEDBARRIER_BACK_GET()) {
				;
			}
			LIFTMOT_up(2, 40);
			STATE_BACK = top;
			return true;
		}
	}
}

// true: front false: back
bool LIFTMOT_GOTO_BOTTOM(bool segment) {
	if (segment) {
		if (STATE_FRONT == bottom) {
			return false;
		} else {
			LIFTMOT_down(1, 255);
			wait(20000);
			LIFTMOT_down(1, 75);
			wait(deadtime);
			while (!LEDBARRIER_FRONT_GET()) {
				;
			}
			LIFTMOT_down(1, 0);
			STATE_FRONT = bottom;
			return true;
		}
	} else {
		if (STATE_BACK == bottom) {
			return false;
		} else {
			LIFTMOT_down(2, 255);
			wait(20000);
			LIFTMOT_down(2, 75);
			wait(deadtime);
			while (!LEDBARRIER_BACK_GET()) {
				;
			}
			LIFTMOT_down(2, 0);
			STATE_BACK = bottom;
			return true;
		}
	}
}

bool LIFTMOT_MIDSEGM_TOP() {
	//21.5
	LIFTMOT_sync_down(255);
	wait(200000);
	LIFTMOT_sync_down(100);
	// muss wieder auf die untere lösung zurückgestellt werden (noch icht getestet)
	// vor 21.5
//	LIFTMOT_down(1, 100);
	while (!GET_GROUND_SENSOR()) {
		;
	}
//	wait(2000000);

	//NEU
	LIFTMOT_down(2, 255);
	LIFTMOT_down(1, 255);
	wait(2000000);
	//alt
//	while (!LEDBARRIER_FRONT_GET()) {
//		;
//	}
//
//	//hinten
//	LIFTMOT_down(2, 255);
//	//vorne
//	LIFTMOT_down(1, 250);
//	wait(1000000);

	// NEU AB 30.5
	//	//hinten
	LIFTMOT_down(2, 255);
	//	//vorne
	LIFTMOT_down(1, 220);

	// 20.5
	while (!LEDBARRIER_FRONT_GET() || !LEDBARRIER_BACK_GET()) {
		if (LEDBARRIER_FRONT_GET()) {
			LIFTMOT_down(1, 50);
		}
		if (LEDBARRIER_BACK_GET()) {
			LIFTMOT_down(2, 50);
		}
	}
	wait(2000000);
	LIFTMOT_sync_down(75);
	return 1;
}

void LIFTMOT_LETDOWN() {
//	LIFTMOT_sync_up(250);
//	wait(2000000);
//	LIFTMOT_sync_up(50);
//	wait(5000);
	LIFTMOT_sync_up(250);
	wait(2000000);
	LIFTMOT_sync_up(50);
	wait(400000);
	LIFTMOT_sync_down(0);
	STATE_FRONT = ground;
	STATE_BACK = bottom;
}


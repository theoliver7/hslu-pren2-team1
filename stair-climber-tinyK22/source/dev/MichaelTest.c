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
#include "MichaelTest.h"
#include "signal/led.h"
#include "mot/stepmot.h"
#include "mot/dcmot.h"
#include "mot/liftmot.h"
#include "sensors/ultrasonic.h"
#include "sensors/ledbarrier.h"
#include "sensors/groundsensor.h"
#include "mot/stair_ascend.h"
#include <stdbool.h>
//=======================================================
// DEFINES
//======================================================= 

//=======================================================
// FUNCTION DEFINITIONS
//======================================================= 

void MichaelTest_Run() {
//	disable_Stepper_Driver();

// Test LED on Breadboard
//	LED_RED_dim(255);
//	wait(8000000);
//	LED_GREEN_dim(255);
//	wait(8000000);
//	LED_BLUE_dim(255);
//	wait(8000000);
//	LED_RED_dim(0);
//	wait(8000000);
//	LED_GREEN_dim(0);
//	wait(8000000);
//	LED_BLUE_dim(0);
//	wait(8000000);
//	__asm("nop");

// Test Stepper Driver on Breadboard
// nur drehmodul
//	enable_Stepper_Driver();
//	reset_Driver();
//	bool direction = false;
//	stepsize_t stepsize = _1_32;
//	float slope = 0.15;
//	int steps = 50;
//	int max_frequency = 300;
//	for(int i = 0; i<2; i++){
//		turn_acc_STEPMOT(false, stepsize, slope, steps, max_frequency);
//		wait(8000000);
//		turn_acc_STEPMOT(true, stepsize, slope, steps, max_frequency);
//		wait(8000000);
//	}
//	disable_Stepper_Driver();

// Test Stepper Driver on Breadboard
// ganzer roboter
//	enable_Stepper_Driver();
//	reset_Driver();
//	bool direction = false;
//	stepsize_t stepsize = _1_64;
//	float slope = 0.50;
//	int steps = 50;
//	int max_frequency = 100;
//	for (int i = 0; i < 10; i++) {
//		turn_acc_STEPMOT(false, stepsize, slope, steps, max_frequency);
//		wait(8000000);
//		turn_acc_STEPMOT(true, stepsize, slope, steps, max_frequency);
//		wait(8000000);
//	}
//	disable_Stepper_Driver();

// Test LED_Barriers
//	while (1) {
//		if (GET_LED_BR_BACK()) {
//			LED_BLUE_dim(255);
//		} else {
//			LED_BLUE_dim(0);
//		}
//		if (GET_LED_BR_FRONT()) {
//			LED_GREEN_dim(255);
//		} else {
//			LED_GREEN_dim(0);
//		}
//		if (GET_LED_BR_STEPPER()) {
//			LED_RED_dim(255);
//		} else {
//			LED_RED_dim(0);
//		}
//	}

// Test ground Sensor
//	while(1) {
//		if (GET_GROUND_SENSOR()) {
//			LED_RED_dim(255);
//		} else {
//			LED_RED_dim(0);
//		}
//	}

// TEST LIFTMOT BACK and FRONT
//#define LIFTMOT_FRONT 1
//#define LIFTMOT_BACK 2
//
//	LED_BLUE_dim(255);
//	LIFTMOT_down(LIFTMOT_FRONT, 100);
//	while (!GET_LED_BR_FRONT()) {
//		;
//	}
//	LED_GREEN_dim(255);
//	LED_BLUE_dim(0);
//	LIFTMOT_down(LIFTMOT_FRONT, 0);
//	wait(8000000);
//	while (!GET_LED_BR_FRONT()) {
//		;
//	}
//	LED_GREEN_dim(0);
//	LIFTMOT_up(LIFTMOT_FRONT, 100);
//	wait(8000000);
//	while (!GET_LED_BR_FRONT()) {
//		;
//	}
//	LED_GREEN_dim(255);
//	LIFTMOT_up(LIFTMOT_FRONT, 0);
//	wait(8000000);
//	while (!GET_LED_BR_FRONT()) {
//		;
//	}
//	LED_GREEN_dim(0);
//	// BACK
//	LED_BLUE_dim(255);
//	LIFTMOT_down(LIFTMOT_BACK, 100);
//	while (!GET_LED_BR_FRONT()) {
//		;
//	}
//	LED_GREEN_dim(255);
//	LED_BLUE_dim(0);
//	LIFTMOT_down(LIFTMOT_BACK, 0);
//	wait(8000000);
//	while (!GET_LED_BR_FRONT()) {
//		;
//	}
//	LED_GREEN_dim(0);
//	LIFTMOT_up(LIFTMOT_BACK, 100);
//	wait(8000000);
//	while (!GET_LED_BR_FRONT()) {
//		;
//	}
//	LED_GREEN_dim(255);
//	LIFTMOT_up(LIFTMOT_BACK, 0);
//	wait(8000000);
//	while (!GET_LED_BR_FRONT()) {
//		;
//	}
//	LED_GREEN_dim(0);

// DRIVING MOTORS TEST
//#define MOT_FRONT 2
//#define MOT_BACK 3
//#define MOT_MIDDLE 1
//	// FRONT
//	LED_BLUE_dim(255);
//	DCMOT_vorward(MOT_FRONT, 250);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	wait(8000000);
//	DCMOT_vorward(MOT_FRONT, 0);
//	LED_GREEN_dim(255);
//	LED_BLUE_dim(0);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	wait(8000000);
//	LED_GREEN_dim(0);
//	LED_BLUE_dim(255);
//	DCMOT_backwards(MOT_FRONT, 250);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	wait(8000000);
//	DCMOT_backwards(MOT_FRONT, 0);
//	LED_GREEN_dim(255);
//	LED_BLUE_dim(0);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	LED_GREEN_dim(0);
//	wait(8000000);
//
//	// MIDDLE
//	LED_BLUE_dim(255);
//	DCMOT_vorward(MOT_MIDDLE, 250);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	wait(8000000);
//	DCMOT_vorward(MOT_MIDDLE, 0);
//	LED_GREEN_dim(255);
//	LED_BLUE_dim(0);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	wait(8000000);
//	LED_GREEN_dim(0);
//	LED_BLUE_dim(255);
//	DCMOT_backwards(MOT_MIDDLE, 250);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	wait(8000000);
//	DCMOT_backwards(MOT_MIDDLE, 0);
//	LED_GREEN_dim(255);
//	LED_BLUE_dim(0);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	LED_GREEN_dim(0);
//	wait(8000000);
//
//	// BACK
//	LED_BLUE_dim(255);
//	DCMOT_vorward(MOT_BACK, 250);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	wait(8000000);
//	DCMOT_vorward(MOT_BACK, 0);
//	LED_GREEN_dim(255);
//	LED_BLUE_dim(0);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	wait(8000000);
//	LED_GREEN_dim(0);
//	LED_BLUE_dim(255);
//	DCMOT_backwards(MOT_BACK, 250);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	wait(8000000);
//	DCMOT_backwards(MOT_BACK, 0);
//	LED_GREEN_dim(255);
//	LED_BLUE_dim(0);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	LED_GREEN_dim(0);
//	wait(8000000);

// sync drive all
//	LED_BLUE_dim(255);
//	DCMOT_sync_vorward(true, 120);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	wait(8000000);
//	DCMOT_sync_vorward(true, 0);
//	LED_GREEN_dim(255);
//	LED_BLUE_dim(0);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	wait(8000000);
//	LED_GREEN_dim(0);
//	LED_BLUE_dim(255);
//	DCMOT_sync_backward(true, 120);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	wait(8000000);
//	DCMOT_sync_backward(true, 0);
//	LED_GREEN_dim(255);
//	LED_BLUE_dim(0);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	LED_GREEN_dim(0);
//	wait(8000000);
//
//	// sync drive no middle
//	LED_BLUE_dim(255);
//	DCMOT_sync_vorward(false, 120);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	wait(8000000);
//	DCMOT_sync_vorward(false, 0);
//	LED_GREEN_dim(255);
//	LED_BLUE_dim(0);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	wait(8000000);
//	LED_GREEN_dim(0);
//	LED_BLUE_dim(255);
//	DCMOT_sync_backward(false, 120);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	wait(8000000);
//	DCMOT_sync_backward(false, 0);
//	LED_GREEN_dim(255);
//	LED_BLUE_dim(0);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	LED_GREEN_dim(0);
//	wait(8000000);

// sync drive up/down
//	LED_BLUE_dim(255);
//	LIFTMOT_sync_up(120);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	LED_GREEN_dim(255);
//	LED_BLUE_dim(0);
//	LIFTMOT_sync_up(0);
//	wait(8000000);
//
//
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	LED_GREEN_dim(0);
//	LED_BLUE_dim(255);
//	LIFTMOT_sync_down(120);
//	wait(8000000);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	LIFTMOT_sync_down(0);
//	LED_GREEN_dim(255);
//	LED_BLUE_dim(0);
//	wait(8000000);
//	while (!GET_LED_BR_FRONT()) {
//
//	}
//	LED_GREEN_dim(0);
//	wait(8000000);

// USONIC TEST
//	uint32_t distance1 = 0;
//	uint32_t distance2 = 0;
//
//	while (1) {
//		distance1 = ULTRASONIC_get_Distance(1);
//		distance2 = ULTRASONIC_get_Distance(2);
//		wait(10000000);
//		printf("SONIC 1: %d\tSONIC 2:%d\n", distance1,distance2);
//	}
//	bool test = false;
//	bool test = LIFTMOT_SYNC_DRIVE_POS();
//	test = LIFTMOT_GOTO_TOP(true);
//	wait(16000000);
//	test = LIFTMOT_GOTO_BOTTOM(true);
//	test = LIFTMOT_GOTO_TOP(false);
//	wait(16000000);
//	test = LIFTMOT_GOTO_BOTTOM(false);
//	while (1) {
//		;
//	}
//	LIFTMOT_MIDSEGM_TOP();

//	LIFTMOT_GOTO_TOP(false);
//	DCMOT_sync_vorward(true, 200);
//	while(1){;}
//	LIFTMOT_DRIVE_POS_MIDDLEUP();

//===============================================================================
	// Treppentest
// stair ascend
	//false cw
	//true ccw
////	turn_acc_STEPMOT(false, _1_64, 0.1, 100, 100);
//	LIFTMOT_DRIVE_POS_MIDDLEUP();
////	turn_acc_STEPMOT(false, _1_64, 0.1, 10, 100);
//	ref_STEPMOT(_1_64, 300, 2);
//	turn_acc_STEPMOT(false, _1_32, 0.1, 103, 300);
//	LIFTMOT_DRIVE_POS_MIDDLEDOWN();
//	// 1. Treppe
//	stair_ascend_ascend();
//	LIFTMOT_DRIVE_POS_MIDDLEUP();
//	STEPPER_MIDDLEUP_TURN(52);
//	LIFTMOT_DRIVE_POS_MIDDLEDOWN();
//	LIFTMOT_DRIVE_POS_OUTERUP();
//	DCMOT_vorward(1, 254);
//	wait(60000000);
//	DCMOT_vorward(1, 0);
//	LIFTMOT_DRIVE_POS_OUTERGROUND();
//	LIFTMOT_DRIVE_POS_MIDDLEUP();
//	STEPPER_MIDDLEUP_TURN(0);
//	LIFTMOT_DRIVE_POS_MIDDLEDOWN();
//	// 2. Treppe
//	stair_ascend_ascend();
//	LIFTMOT_DRIVE_POS_MIDDLEUP();
//	STEPPER_MIDDLEUP_TURN(52);
//	LIFTMOT_DRIVE_POS_MIDDLEDOWN();
//	LIFTMOT_DRIVE_POS_OUTERUP();
//	DCMOT_vorward(1, 254);
//	wait(60000000);
//	DCMOT_vorward(1, 0);
//	LIFTMOT_DRIVE_POS_OUTERGROUND();
//	LIFTMOT_DRIVE_POS_MIDDLEUP();
//	STEPPER_MIDDLEUP_TURN(0);
//	LIFTMOT_DRIVE_POS_MIDDLEDOWN();
//	// 3. Treppe
//	stair_ascend_ascend();
//	// 4. Treppe
//	stair_ascend_ascend();
//	LIFTMOT_DRIVE_POS_MIDDLEUP();
//	STEPPER_MIDDLEUP_TURN(52);
//	LIFTMOT_DRIVE_POS_MIDDLEDOWN();
//	LIFTMOT_DRIVE_POS_OUTERUP();
//	DCMOT_backward(1, 254);
//	wait(60000000);
//	DCMOT_backward(1, 0);
//	LIFTMOT_DRIVE_POS_OUTERGROUND();
//	LIFTMOT_DRIVE_POS_MIDDLEUP();
//	STEPPER_MIDDLEUP_TURN(0);
//	LIFTMOT_DRIVE_POS_MIDDLEDOWN();
//	// 5. Treppe
//	stair_ascend_ascend();
//	// 6. Treppe
//	stair_ascend_ascend();
//
//	// vorwärts fahren
//	DCMOT_sync_vorward(true, 254);
//	wait(30000000);
//	DCMOT_sync_vorward(true, 0);
//===============================================================================

//	LIFTMOT_DRIVE_POS_OUTERGROUND();
//	wait(10000000);
//	LIFTMOT_DRIVE_POS_OUTERUP();
//	wait(10000000);
//	LIFTMOT_DRIVE_POS_OUTERGROUND();
//	wait(10000000);
//	LIFTMOT_DRIVE_POS_MIDDLEUP();
//	wait(10000000);
//	LIFTMOT_DRIVE_POS_MIDDLEDOWN();

// refmot test
//	LIFTMOT_DRIVE_POS_MIDDLEUP();
//	ref_STEPMOT(_1_32, 60, 2);
//	STEPPER_MIDDLEUP_TURN(50);
//	wait(500000);
//	LIFTMOT_DRIVE_POS_MIDDLEDOWN();
//	DCMOT_vorward(1, 250);
//	wait(20000000);
//	DCMOT_backward(1, 250);
//	wait(20000000);
//	DCMOT_vorward(1, 0);
////
//	ref_STEPMOT_startfield(_1_64, 30, 2);
//
//while(1){;}

// REFTEST
//	turn_acc_STEPMOT(false, _1_64, 0.1, 50, 500);
//	ref_STEPMOT(_1_64, 200, 2);

//	turn_acc_STEPMOT(true, _1_64, 0.1, 50, 100);
//	ref_STEPMOT_startfield(_1_64, 100, 5);
//
//
//
//	while (1) {
//		if (LEDBARRIER_STEPPER_GET()) {
//			LED_BLUE_dim(255);
//		} else {
//			LED_BLUE_dim(0);
//		}
//	}

// stepmot dauertest
	/*ref_STEPMOT(_1_32, 60, 1);
	 bool direction = false;
	 stepsize_t stepsize = _1_64;
	 float slope = 0.3;
	 int steps = 50;
	 int max_frequency = 50;*/

	//ref_STEPMOT(_1_32, 60, 1);
//	bool direction = false;
//	stepsize_t stepsize = _1_32;
//	float slope = 0.3;
//	int steps = 52;
//	int max_frequency = 600;
//
//	while(1){
//		turn_acc_STEPMOT(false, stepsize, slope, steps, max_frequency);
//		wait(4000000);
//		turn_acc_STEPMOT(true, stepsize, slope, steps, max_frequency);
//		wait(4000000);
//	}
//
//STEPPER_MIDDLEDOWN_TURN(55);
//STEPPER_MIDDLEDOWN_TURN(170);
//STEPPER_MIDDLEDOWN_TURN(55);
//STEPPER_MIDDLEDOWN_TURN(34);
//STEPPER_MIDDLEDOWN_TURN(98);
//STEPPER_MIDDLEDOWN_TURN(17);
//STEPPER_MIDDLEDOWN_TURN(156);
//STEPPER_MIDDLEDOWN_TURN(183);
//	STEPPER_MIDDLEUP_TURN(55);
//	STEPPER_MIDDLEUP_TURN(60);
//	STEPPER_MIDDLEUP_TURN(25);
//	STEPPER_MIDDLEUP_TURN(15);
//	STEPPER_MIDDLEUP_TURN(76);
//	STEPPER_MIDDLEUP_TURN(110);
//	STEPPER_MIDDLEUP_TURN(105);
//	STEPPER_MIDDLEUP_TURN(183);
//	STEPPER_MIDDLEUP_TURN(145);
//	STEPPER_MIDDLEUP_TURN(160);
//	STEPPER_MIDDLEUP_TURN(50);
//	ref_STEPMOT(_1_64, 30, 2);
//	ref_STEPMOT_startfield(_1_64, 300, 2);
//	STEPPER_MIDDLEUP_TURN(147);
//	ref_STEPMOT(_1_64, 300, 2);
//		ref_STEPMOT_startfield(_1_64, 300, 2);

	// ref test 1
//	STEPPER_MIDDLEUP_TURN(50);
//	ref_STEPMOT(_1_64, 200, 2);
//
//	STEPPER_MIDDLEUP_TURN(150);
//	ref_STEPMOT(_1_64, 200, 2);
	// reftest 1
	STEPPER_MIDDLEDOWN_TURN(25);
	ref_STEPMOT_startfield(_1_64, 100, 2);
//	wait(10000000);
//	STEPPER_MIDDLEDOWN_TURN(175);
//	ref_STEPMOT_startfield(_1_64, 100, 2);

//	disable_Stepper_Driver();
}

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
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

#include "fsl_gpio.h"
#include "pin_mux.h"
#include "stepmot.h"
#include "stepmot_config.h"
#include "utils/ftm2_config.h"
#include "sensors/ledbarrier.h"
#include "signal/led.h"

//=======================================================
// DEFINES / GLOBAL VARIABLES
//======================================================= 
#define TESTMODE 1
static volatile uint16_t STEPMOT_STEPS = 0;
static uint16_t FREQ_VALUE = 0;
static uint8_t act_angle = 0;
//=======================================================
// FUNCTION DEFINITIONS
//=======================================================

//-------------------------------------------------------
//	wait
//	Fast way to extend pulses
//-------------------------------------------------------
void wait(uint32_t cycles) {
	uint32_t i = 0;
	while (i < cycles) {
		i++;
		__asm volatile ("nop");
	}
	return;
}

//-------------------------------------------------------
//	calc_MODULO
//
//-------------------------------------------------------
static uint16_t calc_MODULO(uint16_t frequency) {
	return (1.0 / (frequency * FTM2_TOF_TIME )) * (FTM2_MODULO + 1.0);
}

//-------------------------------------------------------
//	update_Driver_Revolutions
//
//-------------------------------------------------------
static void update_Driver_Revolutions(uint16_t frequency) {
	FREQ_VALUE = calc_MODULO(frequency);
}

//-------------------------------------------------------
//	init_Driver_Revolutions
//
//-------------------------------------------------------
static void init_Driver_Revolutions() {
	FTM_STEPMOT->CONTROLS[FTM_CH_STEPMOT].CnV = FREQ_VALUE;
}

//-------------------------------------------------------
//	enable_Driver_Pulse
//
//-------------------------------------------------------
static void enable_Driver_Pulse() {
	FTM_STEPMOT->CONTROLS[FTM_CH_STEPMOT].CnSC |= FTM_CnSC_ELSA(1);
	FTM_STEPMOT->CONTROLS[FTM_CH_STEPMOT].CnSC &= ~FTM_CnSC_ELSB(1);
}

//-------------------------------------------------------
//	disable_Driver_Pulse
//
//-------------------------------------------------------
static void disable_Driver_Pulse() {
	FTM_STEPMOT->CONTROLS[FTM_CH_STEPMOT].CnSC &= ~FTM_CnSC_ELSA(1);
	FTM_STEPMOT->CONTROLS[FTM_CH_STEPMOT].CnSC |= FTM_CnSC_ELSB(1);
}

//-------------------------------------------------------
//	enable_Driver_Reset
//
//-------------------------------------------------------
static void enable_Driver_Reset() {
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_RESET_GPIO,
	BOARD_INITPINS_STEPMOT_RESET_PIN, false);
}

//-------------------------------------------------------
//	disable_Driver_Reset
//
//-------------------------------------------------------
static void disable_Driver_Reset() {
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_RESET_GPIO,
	BOARD_INITPINS_STEPMOT_RESET_PIN, true);
}

void reset_Driver() {
	enable_Driver_Reset();
	wait(1000);
	disable_Driver_Reset();
}

//-------------------------------------------------------
//	normal_Driver_Direction
//
//-------------------------------------------------------
static void normal_Driver_Direction() {
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_DIR_GPIO,
	BOARD_INITPINS_STEPMOT_DIR_PIN, false);
}

//-------------------------------------------------------
//	reversed_Driver_Direction
//
//-------------------------------------------------------
static void reversed_Driver_Direction() {
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_DIR_GPIO,
	BOARD_INITPINS_STEPMOT_DIR_PIN, true);
}

//-------------------------------------------------------
//	enable_Stepper_Driver
//
//-------------------------------------------------------
void enable_Stepper_Driver() {
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_EN_GPIO,
	BOARD_INITPINS_STEPMOT_EN_PIN, false);
}

//-------------------------------------------------------
//	disable_Stepper_Driver
//
//-------------------------------------------------------
void disable_Stepper_Driver() {
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_EN_GPIO,
	BOARD_INITPINS_STEPMOT_EN_PIN, true);
}

//-------------------------------------------------------
//	enable_Step_ISR
//
//-------------------------------------------------------
static void enable_Step_ISR() {
	FTM_STEPMOT->CONTROLS[FTM_CH_STEPMOT].CnSC &= ~FTM_CnSC_CHF_MASK;
	FTM_STEPMOT->CONTROLS[FTM_CH_STEPMOT].CnSC |= FTM_CnSC_CHIE(1);
}

//-------------------------------------------------------
//	disable_Step_ISR
//
//-------------------------------------------------------
static void disable_Step_ISR() {
	FTM_STEPMOT->CONTROLS[FTM_CH_STEPMOT].CnSC &= ~FTM_CnSC_CHIE(1);
}

//-------------------------------------------------------
//	step_Size_FULL
//
//-------------------------------------------------------
static void step_Size_FULL() {
	FTM_STEPMOT->SC = FTM_SC_CLKS(FTM2_CLOCK) | FTM_SC_PS(2);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS0_GPIO,
	BOARD_INITPINS_STEPMOT_MS0_PIN, false);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS1_GPIO,
	BOARD_INITPINS_STEPMOT_MS1_PIN, false);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS2_GPIO,
	BOARD_INITPINS_STEPMOT_MS2_PIN, false);
}

//-------------------------------------------------------
//	step_Size_HALF
//
//-------------------------------------------------------
static void step_Size_HALF() {
	FTM_STEPMOT->SC = FTM_SC_CLKS(FTM2_CLOCK) | FTM_SC_PS(1);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS0_GPIO,
	BOARD_INITPINS_STEPMOT_MS0_PIN, true);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS1_GPIO,
	BOARD_INITPINS_STEPMOT_MS1_PIN, false);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS2_GPIO,
	BOARD_INITPINS_STEPMOT_MS2_PIN, false);
}

//-------------------------------------------------------
//	step_Size_1_4
//
//-------------------------------------------------------
static void step_Size_1_4() {
	FTM_STEPMOT->SC = FTM_SC_CLKS(FTM2_CLOCK) | FTM_SC_PS(0);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS0_GPIO,
	BOARD_INITPINS_STEPMOT_MS0_PIN, false);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS1_GPIO,
	BOARD_INITPINS_STEPMOT_MS1_PIN, true);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS2_GPIO,
	BOARD_INITPINS_STEPMOT_MS2_PIN, false);
}

//-------------------------------------------------------
//	step_Size_1_8
//
//-------------------------------------------------------
static void step_Size_1_8() {
	FTM_STEPMOT->SC = FTM_SC_CLKS(1) | FTM_SC_PS(7);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS0_GPIO,
	BOARD_INITPINS_STEPMOT_MS0_PIN, true);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS1_GPIO,
	BOARD_INITPINS_STEPMOT_MS1_PIN, true);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS2_GPIO,
	BOARD_INITPINS_STEPMOT_MS2_PIN, false);
}

//-------------------------------------------------------
//	step_Size_1_16
//
//-------------------------------------------------------
static void step_Size_1_16() {
	FTM_STEPMOT->SC = FTM_SC_CLKS(1) | FTM_SC_PS(6);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS0_GPIO,
	BOARD_INITPINS_STEPMOT_MS0_PIN, false);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS1_GPIO,
	BOARD_INITPINS_STEPMOT_MS1_PIN, false);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS2_GPIO,
	BOARD_INITPINS_STEPMOT_MS2_PIN, true);
}

//-------------------------------------------------------
//	step_Size_1_32
//
//-------------------------------------------------------
static void step_Size_1_32() {
	FTM_STEPMOT->SC = FTM_SC_CLKS(1) | FTM_SC_PS(5);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS0_GPIO,
	BOARD_INITPINS_STEPMOT_MS0_PIN, true);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS1_GPIO,
	BOARD_INITPINS_STEPMOT_MS1_PIN, false);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS2_GPIO,
	BOARD_INITPINS_STEPMOT_MS2_PIN, true);
}

//-------------------------------------------------------
//	step_Size_1_64
//
//-------------------------------------------------------
static void step_Size_1_64() {
	FTM_STEPMOT->SC = FTM_SC_CLKS(1) | FTM_SC_PS(4);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS0_GPIO,
	BOARD_INITPINS_STEPMOT_MS0_PIN, false);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS1_GPIO,
	BOARD_INITPINS_STEPMOT_MS1_PIN, true);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS2_GPIO,
	BOARD_INITPINS_STEPMOT_MS2_PIN, true);
}

//-------------------------------------------------------
//	step_Size_1_128
//
//-------------------------------------------------------
static void step_Size_1_128() {
	FTM_STEPMOT->SC = FTM_SC_CLKS(1) | FTM_SC_PS(3);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS0_GPIO,
	BOARD_INITPINS_STEPMOT_MS0_PIN, true);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS1_GPIO,
	BOARD_INITPINS_STEPMOT_MS1_PIN, true);
	GPIO_PinWrite(BOARD_INITPINS_STEPMOT_MS2_GPIO,
	BOARD_INITPINS_STEPMOT_MS2_PIN, true);
}

//-------------------------------------------------------
//	step_Size_Dir_Select
//-------------------------------------------------------
static uint32_t step_Size_Dir_Select(bool direction, stepsize_t stepsize,
		uint32_t steps) {
	if (!direction) {
		normal_Driver_Direction();
	} else {
		reversed_Driver_Direction();
	}

	// multiply the number of steps by the gear ratio
	steps *= STEPMOT_GEAR_RATIO;

	switch (stepsize) {
	case full: {
		step_Size_FULL();
		return steps;
		break;
	}
	case half: {
		step_Size_HALF();
		return 2 * steps;
		break;
	}
	case _1_4: {
		step_Size_1_4();
		return 4 * steps;
		break;
	}
	case _1_8: {
		step_Size_1_8();
		return 8 * steps;
		break;
	}
	case _1_16: {
		step_Size_1_16();
		return 16 * steps;
		break;
	}
	case _1_32: {
		step_Size_1_32();
		return 32 * steps;
		break;
	}
	case _1_64: {
		step_Size_1_64();
		return 64 * steps;
		break;
	}
	case _1_128: {
		step_Size_1_128();
		return 128 * steps;
		break;
	}
	default:
		break;
	}
}

//-------------------------------------------------------
//	turn_STEPMOT (constant velocity)
// 	STEPMOT_STEPS is modiified inside the ISR for the
// 	FTM0_CH2 interrupt. Everytime the ISR is called
// 	the Output toggles. The first toggle is a raising
// 	edge and the driver allways makes a step on a rising
// 	edge. Attention this function sets the motor in motion
//  but does not halt it.
//-------------------------------------------------------
// TODO redoo
void turn_STEPMOT(uint16_t frequency) {
	step_Size_FULL();
	normal_Driver_Direction();
	enable_Stepper_Driver();
	update_Driver_Revolutions(frequency);
	enable_Step_ISR();
	enable_Driver_Pulse();
}

//-------------------------------------------------------
//	halt_STEPMOT
// 	This function disables the step signal and the Step_ISR.
//	Furthermore it puts the step motor back to the power save
//	mode.
//-------------------------------------------------------
void halt_STEPMOT() {
	disable_Step_ISR();
	disable_Driver_Pulse();
	disable_Stepper_Driver();
}

//-------------------------------------------------------
//	turn_steps_STEPMOT (constant velocity)
// 	STEPMOT_STEPS is modiified inside the ISR for the
// 	FTM0_CH2 interrupt. Everytime the ISR is called
// 	the Output toggles. The first toggle is a raising
// 	edge and the driver allways makes a step on a rising
// 	edge. Because every second ISR call generates a
// 	falling edge, steps has to be Multiplied by a factor
// 	of two.
//-------------------------------------------------------
void turn_steps_STEPMOT(bool direction, stepsize_t stepsize, uint32_t steps,
		uint16_t frequency) {
	enable_Stepper_Driver();
	update_Driver_Revolutions(frequency);
	init_Driver_Revolutions();
	steps = step_Size_Dir_Select(direction, stepsize, steps);
	enable_Step_ISR();
	enable_Driver_Pulse();
	STEPMOT_STEPS = 0;
	while (STEPMOT_STEPS < (2 * steps)) {
		;
	}
	disable_Step_ISR();
	disable_Driver_Pulse();
	disable_Stepper_Driver();
}

//-------------------------------------------------------
//	turn_acc_STEPMOT (linear acceleration)
//
//-------------------------------------------------------
void turn_acc_STEPMOT(bool direction, stepsize_t stepsize, float slope,
		uint32_t steps, uint16_t max_frequency) {
	enable_Stepper_Driver();
	if ((slope >= 0) && (slope <= 0.5) && (steps >= 0)
			&& (max_frequency <= STEPMOT_MAX_FREQ)) {
		// calculate borders and incline
		steps = 2 * steps; // has to be multiplied by two because ondly every second toggle is a rising edge

		uint32_t max_Freq_Value = calc_MODULO(max_frequency);
		steps = step_Size_Dir_Select(direction, stepsize, steps);

		uint32_t left_border = slope * steps;
		uint32_t right_border = (steps - left_border);
		float incline = (float) max_frequency / (float) left_border;
		float line_offset = incline * (float) steps;

		// driver setup
		update_Driver_Revolutions(STEPMOT_MIN_FREQ);
		init_Driver_Revolutions();

		enable_Step_ISR();
		enable_Driver_Pulse();

		STEPMOT_STEPS = 0;
		while (STEPMOT_STEPS < steps) {
			if ((STEPMOT_STEPS > 0) && (STEPMOT_STEPS <= left_border)) {
				float acc_frequency = (float) STEPMOT_STEPS * incline;
				if (acc_frequency > STEPMOT_MIN_FREQ) {
#if TESTMODE
					LED_RED_dim(0);
					LED_GREEN_dim(0);
					LED_BLUE_dim(255);
#endif
					FREQ_VALUE = (1.0 / (acc_frequency * FTM2_TOF_TIME ))
							* (FTM2_MODULO + 1.0);
				}
			} else if ((STEPMOT_STEPS > left_border)
					&& (STEPMOT_STEPS < right_border)) {
#if TESTMODE
				LED_RED_dim(0);
				LED_GREEN_dim(255);
				LED_BLUE_dim(0);
#endif
				FREQ_VALUE = max_Freq_Value;
			} else if (STEPMOT_STEPS >= right_border) {
#if TESTMODE
				LED_RED_dim(255);
				LED_GREEN_dim(0);
				LED_BLUE_dim(0);
#endif
				float acc_frequency =
						(((float) STEPMOT_STEPS * (-1.0) * incline)
								+ line_offset);
				if (acc_frequency > STEPMOT_MIN_FREQ) {
					FREQ_VALUE = (1.0 / (acc_frequency * FTM2_TOF_TIME ))
							* (FTM2_MODULO + 1.0);
				}
			}
		}

#if TESTMODE
		LED_RED_dim(0);
		LED_GREEN_dim(0);
		LED_BLUE_dim(0);
#endif

		// driver setup
		disable_Step_ISR();
		disable_Driver_Pulse();
	}
	disable_Stepper_Driver();
}
//-------------------------------------------------------
//	get_ref_dir
//	This function returns the referencing direction
//-------------------------------------------------------
bool get_ref_dir(void) {
	if (act_angle <= 100) {
		return true;
	} else if (act_angle == 0) {
		return true;
	} else {
		return false;
	}
}

//-------------------------------------------------------
//	ref_STEPMOT
//	Goto reference mark when the middle segment elevated.
//  steps_to_max_vel in 1.8 deg steps (10 = 18°)
//-------------------------------------------------------
void ref_STEPMOT(stepsize_t stepsize, uint16_t max_frequency,
		uint16_t steps_to_max_vel) {
	enable_Stepper_Driver();
	bool direction = false;
	if (!LEDBARRIER_STEPPER_GET()) {
		// dir is always true (CCW) because the set act_angle is CW of the reference mark
//		bool direction = true;
		// new 31.5
		direction = get_ref_dir();
		if (max_frequency <= STEPMOT_MAX_FREQ) {
			// calculate borders and incline
			steps_to_max_vel = 2 * steps_to_max_vel; // has to be multiplied by two because ondly every second toggle is a rising edge

			uint32_t max_Freq_Value = calc_MODULO(max_frequency);
			steps_to_max_vel = step_Size_Dir_Select(direction, stepsize,
					steps_to_max_vel);

			float incline = (float) max_frequency / (float) steps_to_max_vel;
			float acc_frequency = (float) max_frequency;
			// driver setup
			update_Driver_Revolutions(STEPMOT_MIN_FREQ);
			init_Driver_Revolutions();

			enable_Step_ISR();
			enable_Driver_Pulse();

			STEPMOT_STEPS = 0;

			// hold velocity until ref mark is reached
#if TESTMODE
			LED_RED_dim(0);
			LED_GREEN_dim(255);
			LED_BLUE_dim(0);
#endif
			FREQ_VALUE = max_Freq_Value;
			while (!LEDBARRIER_STEPPER_GET()) {
				;
			}
			STEPMOT_STEPS = 0;
			FREQ_VALUE = 0;
#if TESTMODE
			LED_RED_dim(255);
			LED_GREEN_dim(0);
			LED_BLUE_dim(0);
#endif
		}

#if TESTMODE
		LED_RED_dim(0);
		LED_GREEN_dim(0);
		LED_BLUE_dim(0);
#endif

		// turn the back to compensate the braking angle
//		turn_acc_STEPMOT(true, stepsize, 0.5, steps_to_max_vel, max_frequency);
	}
	// update the act_angle variable
	act_angle = 0;

	//go back to zero degrees
	if (direction) {
		// Korrekturwinkel wenn die Refmarke von rechts angefahren wird
		turn_acc_STEPMOT(false, _1_32, 0.1, 5, 200);
	} else {
		// Korrekturwinkel wenn die Refmarke von links angefahren wird
		turn_acc_STEPMOT(false, _1_32, 0.1, 5, 200);
	}
	// driver setup
	disable_Step_ISR();
	disable_Driver_Pulse();
	disable_Stepper_Driver();
}

//-------------------------------------------------------
//	ref_STEPMOT_startfield
//	Goto reference mark when the middle segment is on ground.
//  steps_to_max_vel in 1.8 deg steps (10 = 18°)
//-------------------------------------------------------
void ref_STEPMOT_startfield(stepsize_t stepsize, uint16_t max_frequency,
		uint16_t steps_to_max_vel) {
	enable_Stepper_Driver();
	bool direction = false;
	if (!LEDBARRIER_STEPPER_GET()) {
		//auskommentiert am 27.5, da die startfahne nicht immer über 90
//	turn_acc_STEPMOT(true, _1_32, 0.25, 100, 50);

		// dir is always true (CCW) because the set act_angle is CW of the reference mark
//	bool direction = true;
		// new 31.5
		direction = get_ref_dir();

		if (max_frequency <= STEPMOT_MAX_FREQ) {
			// calculate borders and incline
			steps_to_max_vel = 2 * steps_to_max_vel; // has to be multiplied by two because only every second toggle is a rising edge

			uint32_t max_Freq_Value = calc_MODULO(max_frequency);
			steps_to_max_vel = step_Size_Dir_Select(direction, stepsize,
					steps_to_max_vel);

			float incline = (float) max_frequency / (float) steps_to_max_vel;
			float acc_frequency = (float) max_frequency;
			// driver setup
			update_Driver_Revolutions(STEPMOT_MIN_FREQ);
			init_Driver_Revolutions();

			enable_Step_ISR();
			enable_Driver_Pulse();

			STEPMOT_STEPS = 0;

			// hold velocity until ref mark is reached
#if TESTMODE
			LED_RED_dim(0);
			LED_GREEN_dim(255);
			LED_BLUE_dim(0);
#endif
			FREQ_VALUE = max_Freq_Value;
			while (!LEDBARRIER_STEPPER_GET()) {
				;
			}
			STEPMOT_STEPS = 0;

			// decelerate
#if TESTMODE
			LED_RED_dim(255);
			LED_GREEN_dim(0);
			LED_BLUE_dim(0);
#endif
			while (STEPMOT_STEPS < steps_to_max_vel) {
//				acc_frequency -= (((float) STEPMOT_STEPS * incline));
//				if (acc_frequency > STEPMOT_MIN_FREQ) {
//					FREQ_VALUE = (1.0 / (acc_frequency * FTM2_TOF_TIME ))
//							* (FTM2_MODULO + 1.0);
//				}
			}
			FREQ_VALUE = 0;
		}

#if TESTMODE
		LED_RED_dim(0);
		LED_GREEN_dim(0);
		LED_BLUE_dim(0);
#endif

	}

//	turn_acc_STEPMOT(false, _1_32, 0.1, 5, 200);

	//go back to zero degrees
	if (direction) {
		// Korrekturwinkel wenn die Refmarke von rechts angefahren wird
		turn_acc_STEPMOT(false, _1_32, 0.2, 6, 100);
	} else {
		// Korrekturwinkel wenn die Refmarke von links angefahren wird
		turn_acc_STEPMOT(false, _1_32, 0.2, 2, 100);
	}

	// update the act_angle variable
	act_angle = 0;

	// driver setup
	disable_Step_ISR();
	disable_Driver_Pulse();
	disable_Stepper_Driver();
}

//-------------------------------------------------------
//	calc_turn_params
//  This function calculates the direction and drive angle
//-------------------------------------------------------
void calc_turn_params(uint8_t set_angle, bool *direction, uint16_t *drive_angle) {
	if (set_angle != act_angle) {
		if ((0 <= act_angle) && (act_angle <= 100)) {
			if ((100 < set_angle) && (set_angle < 200)) {
				*direction = true;
				*drive_angle = act_angle + 200 - set_angle;
			} else {
				if (set_angle < act_angle) {
					*direction = true;
					*drive_angle = act_angle - set_angle;
				} else {
					*direction = false;
					*drive_angle = set_angle - act_angle;
				}
			}
		} else {
			if ((0 < set_angle) && (set_angle <= 100)) {
				*direction = false;
				*drive_angle = set_angle + 200 - act_angle;
			} else {
				if (set_angle < act_angle) {
					*direction = true;
					*drive_angle = act_angle - set_angle;
				} else {
					*direction = false;
					*drive_angle = set_angle - act_angle;
				}
			}
		}
	} else {
		// do nothing
	}
}

//-------------------------------------------------------
//	STEPPER_MIDDLEUP_TURN
//-------------------------------------------------------
// OLD
//void STEPPER_MIDDLEUP_TURN(uint8_t set_angle) {
//	if (set_angle > act_angle) {
//		turn_acc_STEPMOT(true, _1_32, 0.1, set_angle - act_angle, 300);
//		act_angle = set_angle;
//	} else if (set_angle < act_angle) {
//		turn_acc_STEPMOT(false, _1_32, 0.1, act_angle - set_angle, 300);
//		act_angle = set_angle;
//	} else if (set_angle == act_angle) {
//		// do nothing
//		__asm("nop");
//	}
//}

//-------------------------------------------------------
//	STEPPER_MIDDLEUP_TURN
//-------------------------------------------------------
// NEW
void STEPPER_MIDDLEUP_TURN(uint8_t set_angle) {
	if (set_angle != act_angle) {
		uint16_t drive_angle = 0;
		bool direction = false;
		stepsize_t stepsize = _1_32;
		float slope = 0.1;
		uint16_t max_velocity = 300;
		calc_turn_params(set_angle, &direction, &drive_angle);
//		test
//		printf("act_angle:  %d\n", act_angle);
//		printf("set_angle:  %d\n", set_angle);
//		printf("direction:  %d\n", direction);
//		printf("drive_angle:  %d\n", drive_angle);
//		printf("===================\n");
		turn_acc_STEPMOT(direction, stepsize, slope, drive_angle, max_velocity);
		act_angle = set_angle;
	} else {
		__asm("nop");
	}
}

//-------------------------------------------------------
//	STEPPER_MIDDLEDOWN_TURN
//-------------------------------------------------------
// OLD
//void STEPPER_MIDDLEDOWN_TURN(uint8_t set_angle) {
//	if (set_angle > act_angle) {
//		turn_acc_STEPMOT(true, _1_32, 0.25, set_angle - act_angle, 200);
//		act_angle = set_angle;
//	} else if (set_angle < act_angle) {
//		turn_acc_STEPMOT(false, _1_32, 0.25, act_angle - set_angle, 200);
//		act_angle = set_angle;
//	} else if (set_angle == act_angle) {
//		// do nothing
//		__asm("nop");
//	}
//}

//NEW
void STEPPER_MIDDLEDOWN_TURN(uint8_t set_angle) {
	if (set_angle != act_angle) {
		uint16_t drive_angle = 0;
		bool direction = false;
		stepsize_t stepsize = _1_32;
		float slope = 0.15;
		uint16_t max_velocity = 150;
		calc_turn_params(set_angle, &direction, &drive_angle);
		//		test
//			printf("act_angle:  %d\n", act_angle);
//			printf("set_angle:  %d\n", set_angle);
//			printf("direction:  %d\n", direction);
//			printf("drive_angle:  %d\n", drive_angle);
//			printf("===================\n");
		turn_acc_STEPMOT(direction, stepsize, slope, drive_angle, max_velocity);
		act_angle = set_angle;
	} else {
		__asm("nop");
	}
}

//-------------------------------------------------------
//	Stepper IRQ
//
//-------------------------------------------------------
void FTM2CH1_IRQHandler() {
	FTM_STEPMOT->CONTROLS[FTM_CH_STEPMOT].CnSC &= ~FTM_CnSC_CHF_MASK;
	FTM_STEPMOT->CONTROLS[FTM_CH_STEPMOT].CnV += FREQ_VALUE;
	STEPMOT_STEPS++;
}

void stepper_ein(bool direction, stepsize_t stepsize) {
	step_Size_Dir_Select(direction, stepsize, 0);
	enable_Step_ISR();
	enable_Driver_Pulse();
}

void stepper_update(uint32_t steps, uint16_t frequency) {
	update_Driver_Revolutions(frequency);
	init_Driver_Revolutions();
	uint32_t STEPMOT_STEPS = 0;
	while (STEPMOT_STEPS < (2 * steps)) {
		;
	}
}

void stepper_aus() {
	disable_Step_ISR();
	disable_Driver_Pulse();
}

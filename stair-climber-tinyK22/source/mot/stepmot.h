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

#ifndef MOT_STEPMOT_H_
#define MOT_STEPMOT_H_

//=======================================================
//INCLUDES
//=======================================================

#include <stdint.h>
#include <stdbool.h>

//=======================================================
// DEFINES
//======================================================= 

//=======================================================
// ENUMS
//=======================================================

typedef enum stepsize_e {
	full = 0,
	half,
	_1_4,
	_1_8,
	_1_16,
	_1_32,
	_1_64,
	_1_128
} stepsize_t;

//=======================================================
// FUNCTION DECLARATIONS
//=======================================================
void turn_STEPMOT(uint16_t frequency);
void halt_STEPMOT(void);
void turn_steps_STEPMOT(bool direction, stepsize_t stepsize, uint32_t steps, uint16_t frequency);
void turn_acc_STEPMOT(bool direction, stepsize_t stepsize, float slope, uint32_t steps, uint16_t max_frequency);
void ref_STEPMOT(stepsize_t stepsize, uint16_t max_frequency, uint16_t steps_to_max_vel);
void ref_STEPMOT_startfield(stepsize_t stepsize, uint16_t max_frequency, uint16_t steps_to_max_vel);
void STEPPER_MIDDLEUP_TURN(uint8_t set_angle);
void STEPPER_MIDDLEDOWN_TURN(uint8_t set_angle);
void FTM0CH2_IRQHandler(void);
void wait(uint32_t cycles);
void enable_Stepper_Driver();
void reset_Driver(void);
void disable_Stepper_Driver();
void stepper_ein(bool direction, stepsize_t stepsize);
void stepper_update(uint32_t steps, uint16_t frequency);
void stepper_aus();

#endif /*MOT_STEPMOT_H_*/

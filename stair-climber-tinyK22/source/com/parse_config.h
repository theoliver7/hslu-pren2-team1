//=======================================================
// PREN2 - TEAM1 - STAIRCLIMBER
//=======================================================
//	PWM_Test_TinyK22
//	19.03.2021
//	Authors: Widmer Michael, Friedli Manuel
//=======================================================
//DESCRIPTION
//=======================================================
//	Define all function identifiers in this config file.
//=======================================================

#ifndef COM_PARSE_CONFIG_H_
#define COM_PARSE_CONFIG_H_

//=======================================================
// DEFINES
//======================================================= 
// LEDS
#define LED_RED_IDENTIFIER				51
#define LED_GREEN_IDENTIFIER 			54
#define LED_BLUE_IDENTIFIER 			57

// DRIVE MOTORS
#define DCMOT1_FORWARD_IDENTIFIER		3
#define DCMOT1_BACKWARD_IDENTIFIER		5
#define DCMOTORS_FORWARD_IDENTIFIER		9
#define DCMOTORS_BACKWARD_IDENTIFIER	11

// STEPPER
#define STEPPER_MIDDLEUP_TURN_IDENTIFIER	21
#define STEPPER_MIDDLEDOWN_TURN_IDENTIFIER	22
#define STEPPER_GOTO_REF_MIDDLEUP_IDENTIFIER	24
#define STEPPER_GOTO_REF_STARTFIELD_IDENTIFIER	23

// ULTRASONIC
#define ULTRASONIC_1_GET_DISTANCE		45
#define ULTRASONIC_2_GET_DISTANCE		48

// DRIVING POSITIONS
#define DRIVE_POS_MIDDLEUP 27
#define DRIVE_POS_MIDDLEDOWN 28
#define DRIVE_POS_OUTERONGROUND 29
#define DRIVE_POS_OUTERUP 30
#define DRIVE_POS_FRONTUP 31
#define DRIVE_POS_FRONTGROUND  32

// CLIMB A STAIRSTEP
#define CLIMB_ONESTEP 50

#define ERRORCODE			0xAA
#define DEFAULTIDENTIFIER	255

#endif /*COM_PARSE_CONFIG_H_*/

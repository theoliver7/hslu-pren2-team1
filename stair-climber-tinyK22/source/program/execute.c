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
#include "execute.h"
#include "execute_config.h"
#include "com/parse_config.h"
#include "com/uart.h"
#include "mot/stepmot.h"
#include "mot/liftmot.h"
#include "mot/stair_ascend.h"

//=======================================================
// FUNCTION DEFINITIONS
//======================================================= 

//=======================================================
// LED
//=======================================================
//-------------------------------------------------------
//	exec_LED_RED
//	This function just calls LED_RED_dim with the new value
// 	to update the LED. The response string is sent at the end
//	after the update.
//-------------------------------------------------------
static void exec_LED_RED(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	LED_RED_dim(command->data_bytes[1]);
	uart1WriteCommand(response_str);
}

//-------------------------------------------------------
//	exec_LED_GREEN
//	This function just calls LED_GREEN_dim with the new value
// 	to update the LED. The response string is sent at the end
//	after the update.
//-------------------------------------------------------
static void exec_LED_GREEN(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	LED_GREEN_dim(command->data_bytes[1]);
	uart1WriteCommand(response_str);
}

//-------------------------------------------------------
//	exec_LED_BLUE
//	This function just calls LED_BLUE_dim with the new value
// 	to update the LED. The response string is sent at the end
//	after the update.
//-------------------------------------------------------
static void exec_LED_BLUE(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	LED_BLUE_dim(command->data_bytes[1]);
	uart1WriteCommand(response_str);
}

//=======================================================
// DRIVE MOTORS
//=======================================================
static void exec_DCMOT1_FORWARD(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	DCMOT_vorward(1, command->data_bytes[1]);
	uart1WriteCommand(response_str);
}

static void exec_DCMOT1_BACKWARD(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	DCMOT_backward(1, command->data_bytes[1]);
	uart1WriteCommand(response_str);
}

static void exec_DCMOTORS_FORWARD(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	DCMOT_sync_vorward(false, command->data_bytes[1]);
	uart1WriteCommand(response_str);
}

static void exec_DCMOTORS_BACKWARD(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	DCMOT_sync_backward(false, command->data_bytes[1]);
	uart1WriteCommand(response_str);
}

//=======================================================
// STEPPER
//=======================================================
static void exec_STEPPER_MIDDLEUP_TURN(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	STEPPER_MIDDLEUP_TURN(command->data_bytes[1]);
	uart1WriteCommand(response_str);
}

static void exec_STEPPER_MIDDLEDOWN_TURN(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	STEPPER_MIDDLEDOWN_TURN(command->data_bytes[1]);
	uart1WriteCommand(response_str);
}

static void exec_STEPPER_GOTO_REF_MIDDLEUP(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	ref_STEPMOT(_1_32, 200, 1);
	uart1WriteCommand(response_str);
}

static void exec_STEPPER_GOTO_REF_STARTFIELD(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	ref_STEPMOT_startfield(_1_64, 100, 1);
	uart1WriteCommand(response_str);
}

//=======================================================
// ULTRASONIC
//=======================================================
static void exec_USONIC_GET(uint8_t sensor, command_t *command) {
	char response_str[] = { command->cmd, '\0', '\0', command->cmd, '\0', '\0',
			'\n' };
	uint32_t distance = 0;
	if (sensor == 1) {
		distance = ULTRASONIC_get_Distance(1);
	}
	if (sensor == 2) {
		distance = ULTRASONIC_get_Distance(2);
	}

	// 0 is highbyte
	command->data_bytes[0] = ((distance & (0xFF << 8)) >> 8);
	// 1 is lowbyte
	command->data_bytes[1] = (distance & 0xFF);

	response_str[1] = command->data_bytes[0];
	response_str[2] = command->data_bytes[1];
	response_str[4] = command->data_bytes[0];
	response_str[5] = command->data_bytes[1];
	uart1WriteCommand(response_str);
}

//=======================================================
// DRIVING POSITIONS
//=======================================================
static void exec_DRIVE_POS_MIDDLEUP(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	LIFTMOT_DRIVE_POS_MIDDLEUP();
	uart1WriteCommand(response_str);
}

static void exec_DRIVE_POS_MIDDLEDOWN(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	LIFTMOT_DRIVE_POS_MIDDLEDOWN();
	uart1WriteCommand(response_str);
}

static void exec_DRIVE_POS_OUTERONGROUND(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	LIFTMOT_DRIVE_POS_OUTERGROUND();
	uart1WriteCommand(response_str);
}

static void exec_DRIVE_POS_OUTERUP(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	LIFTMOT_DRIVE_POS_OUTERUP();
	uart1WriteCommand(response_str);
}

static void exec_DRIVE_POS_FRONTUP(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	LIFTMOT_GOTO_TOP(true);
	uart1WriteCommand(response_str);
}
static void exec_DRIVE_POS_FRONTGROUND(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	LIFTMOT_FRONT_GROUND();
	uart1WriteCommand(response_str);
}

//=======================================================
// STAIRCLIMBING
//=======================================================
static void exec_CLIMB_ONESTEP(command_t *command) {
	char response_str[] = { command->cmd, command->data_bytes[0],
			command->data_bytes[1], command->cmd, command->data_bytes[0],
			command->data_bytes[1], '\n' };
	stair_ascend_ascend();
	uart1WriteCommand(response_str);
}

//=======================================================
// ERROR
//=======================================================
//-------------------------------------------------------
//	exec_ERROR
//	This function sends the error code back to the Raspberry
// 	The ERRORCODE is defined in cmd_config.h
//-------------------------------------------------------
static void exec_ERROR() {
	char error_str[] = { ERRORCODE, ERRORCODE, ERRORCODE, ERRORCODE, ERRORCODE,
	ERRORCODE, '\n' };
	uart1WriteCommand(error_str);
}

//-------------------------------------------------------
// command_selector selects the possibly complex exec
// function based on the command identifier.
//-------------------------------------------------------
void command_selector(command_t *command) {
	switch (command->cmd) {
	// LED COMMANDS
	case LED_RED_IDENTIFIER: {
		exec_LED_RED(command);
		break;
	}
	case LED_GREEN_IDENTIFIER: {
		exec_LED_GREEN(command);
		break;
	}
	case LED_BLUE_IDENTIFIER: {
		exec_LED_BLUE(command);
		break;
	}
		// DRIVEMOT COMMANDS
	case DCMOT1_FORWARD_IDENTIFIER: {
		exec_DCMOT1_FORWARD(command);
		break;
	}
	case DCMOT1_BACKWARD_IDENTIFIER: {
		exec_DCMOT1_BACKWARD(command);
		break;
	}
	case DCMOTORS_FORWARD_IDENTIFIER: {
		exec_DCMOTORS_FORWARD(command);
		break;
	}
	case DCMOTORS_BACKWARD_IDENTIFIER: {
		exec_DCMOTORS_BACKWARD(command);
		break;
	}
		// STEPPER
	case STEPPER_MIDDLEUP_TURN_IDENTIFIER: {
		exec_STEPPER_MIDDLEUP_TURN(command);
		break;
	}
	case STEPPER_MIDDLEDOWN_TURN_IDENTIFIER: {
		exec_STEPPER_MIDDLEDOWN_TURN(command);
		break;
	}
	case STEPPER_GOTO_REF_MIDDLEUP_IDENTIFIER: {
		exec_STEPPER_GOTO_REF_MIDDLEUP(command);
		break;
	}
	case STEPPER_GOTO_REF_STARTFIELD_IDENTIFIER: {
		exec_STEPPER_GOTO_REF_STARTFIELD(command);
		break;
	}
		// ULTRASONIC
	case ULTRASONIC_1_GET_DISTANCE: {
		exec_USONIC_GET(1, command);
		break;
	}
	case ULTRASONIC_2_GET_DISTANCE: {
		exec_USONIC_GET(2, command);
		break;
	}
		// DRIVING POSITIONS
	case DRIVE_POS_MIDDLEUP: {
		exec_DRIVE_POS_MIDDLEUP(command);
		break;
	}
	case DRIVE_POS_MIDDLEDOWN: {
		exec_DRIVE_POS_MIDDLEDOWN(command);
		break;
	}
	case DRIVE_POS_OUTERONGROUND: {
		exec_DRIVE_POS_OUTERONGROUND(command);
		break;
	}
	case DRIVE_POS_OUTERUP: {
		exec_DRIVE_POS_OUTERUP(command);
		break;
	}
	case DRIVE_POS_FRONTUP: {
		exec_DRIVE_POS_FRONTUP(command);
		break;
	}
	case DRIVE_POS_FRONTGROUND: {
		exec_DRIVE_POS_FRONTGROUND(command);
		break;
	}

		// CLIMB A STAIRSTEP
	case CLIMB_ONESTEP: {
		exec_CLIMB_ONESTEP(command);
		break;
	}

		// ERROR
	case ERRORCODE: {
		exec_ERROR();
		break;
	}
	default: {
		exec_ERROR();
		break;
	}
	}
}

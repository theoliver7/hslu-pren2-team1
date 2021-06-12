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
#include "parse.h"
#include "parse_config.h"

//=======================================================
// FUNCTION DEFINITIONS
//======================================================= 
//	parse_cmd_line
//-------------------------------------------------------
// This function takes the incoming string, checks if the
// data is consistent and fills it into a command variable
// for further use.
//-------------------------------------------------------
void parse_cmd_line(char *cmd_line, command_t *cmd) {
	// compare the command bytes of the string
	if (*(cmd_line + 0) == *(cmd_line + 3)) {
		// compare the data bytes of the string
		if ((*(cmd_line + 1) == *(cmd_line + 4))
				&& (*(cmd_line + 2) == *(cmd_line + 5))) {
			// LED COMMANDS
			if (*(cmd_line) == LED_RED_IDENTIFIER) {
				cmd->cmd = LED_RED_IDENTIFIER;
			} else if (*(cmd_line) == LED_GREEN_IDENTIFIER) {
				cmd->cmd = LED_GREEN_IDENTIFIER;
			} else if (*(cmd_line) == LED_BLUE_IDENTIFIER) {
				cmd->cmd = LED_BLUE_IDENTIFIER;
			}
			// DRIVEMOT COMMANDS
			else if (*(cmd_line) == DCMOT1_FORWARD_IDENTIFIER) {
				cmd->cmd = DCMOT1_FORWARD_IDENTIFIER;
			} else if (*(cmd_line) == DCMOT1_BACKWARD_IDENTIFIER) {
				cmd->cmd = DCMOT1_BACKWARD_IDENTIFIER;
			} else if (*(cmd_line) == DCMOTORS_FORWARD_IDENTIFIER) {
				cmd->cmd = DCMOTORS_FORWARD_IDENTIFIER;
			} else if (*(cmd_line) == DCMOTORS_BACKWARD_IDENTIFIER) {
				cmd->cmd = DCMOTORS_BACKWARD_IDENTIFIER;
			}
			// STEPPER
			else if (*(cmd_line) == STEPPER_MIDDLEUP_TURN_IDENTIFIER) {
				cmd->cmd = STEPPER_MIDDLEUP_TURN_IDENTIFIER;
			} else if (*(cmd_line) == STEPPER_MIDDLEDOWN_TURN_IDENTIFIER) {
				cmd->cmd = STEPPER_MIDDLEDOWN_TURN_IDENTIFIER;
			} else if (*(cmd_line) == STEPPER_GOTO_REF_MIDDLEUP_IDENTIFIER) {
				cmd->cmd = STEPPER_GOTO_REF_MIDDLEUP_IDENTIFIER;
			} else if (*(cmd_line) == STEPPER_GOTO_REF_STARTFIELD_IDENTIFIER) {
				cmd->cmd = STEPPER_GOTO_REF_STARTFIELD_IDENTIFIER;
			}
			// ULTRASONIC
			else if (*(cmd_line) == ULTRASONIC_1_GET_DISTANCE) {
				cmd->cmd = ULTRASONIC_1_GET_DISTANCE;
			} else if (*(cmd_line) == ULTRASONIC_2_GET_DISTANCE) {
				cmd->cmd = ULTRASONIC_2_GET_DISTANCE;
			}
			// DRIVING POSITIONS
			else if (*(cmd_line) == DRIVE_POS_MIDDLEUP) {
				cmd->cmd = DRIVE_POS_MIDDLEUP;
			} else if (*(cmd_line) == DRIVE_POS_MIDDLEDOWN) {
				cmd->cmd = DRIVE_POS_MIDDLEDOWN;
			} else if (*(cmd_line) == DRIVE_POS_OUTERONGROUND) {
				cmd->cmd = DRIVE_POS_OUTERONGROUND;
			} else if (*(cmd_line) == DRIVE_POS_OUTERUP) {
				cmd->cmd = DRIVE_POS_OUTERUP;
			} else if (*(cmd_line) == DRIVE_POS_FRONTUP) {
				cmd->cmd = DRIVE_POS_FRONTUP;
			} else if (*(cmd_line) == DRIVE_POS_FRONTGROUND) {
				cmd->cmd = DRIVE_POS_FRONTGROUND;
			}

			// CLIMB A STAIRSTEP
			else if (*(cmd_line) == CLIMB_ONESTEP) {
				cmd->cmd = CLIMB_ONESTEP;
			}
			// DEFAULT COMMAND
			else if (*(cmd_line) == DEFAULTIDENTIFIER) {
				cmd->cmd = DEFAULTIDENTIFIER;
			} else {
				// The TinyK22 will send the error command if received identifier
				// could not be matched to a function identifier.
				cmd->cmd = ERRORCODE;
			}
			// The function will put all consistent data inside the data_bytes.
			// This is the same for every command identifier.
			cmd->data_bytes[0] = *(cmd_line + 1);
			cmd->data_bytes[1] = *(cmd_line + 2);
		} else {
			// The TinyK22 will send the error command if data is not consistent.
			cmd->cmd = ERRORCODE;
		}
	} else {
		// The TinyK22 will send the error command if the identifiers are not equal.
		cmd->cmd = ERRORCODE;
	}
}

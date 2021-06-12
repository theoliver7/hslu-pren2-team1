//=======================================================
// PREN2 - TEAM1 - STAIRCLIMBER
//=======================================================
//	PWM_Test_TinyK22
//	17.03.2021
//	Authors: Widmer Michael, Friedli Manuel
//=======================================================
//DESCRIPTION
//=======================================================
//
//=======================================================

//=======================================================
//INCLUDES
//=======================================================
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "workloop.h"
#include "com/uart.h"
#include "com/parse.h"
#include "execute.h"

//=======================================================
// DEFINES
//======================================================= 


//=======================================================
// FUNCTION DEFINITIONS
//======================================================= 

void workloop() {

	char cmd_in_str[7] = "";
	command_t cmd_in;
	bool linerec = false;

//	printf("tinyk22 waits for line feed...\n");
//	printf("sending on uart1 finished...\n");
//	uart1WriteLine("TinyK22 Ready...\n");

	while (true) {
		while (!linerec) {
			linerec = uart1HasLineReceived();
		}
		linerec = false;
//		printf("tinyk22 received line...\n");
		uart1ReadLine(cmd_in_str, 7);
		parse_cmd_line(cmd_in_str, &cmd_in);
		command_selector(&cmd_in);
	}
}


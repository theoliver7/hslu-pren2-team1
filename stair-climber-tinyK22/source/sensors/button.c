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
#include "button.h"
#include "button_config.h"

//=======================================================
// DEFINES
//======================================================= 

//=======================================================
// FUNCTION DEFINITIONS
//======================================================= 


/*
 * Checks if the button detects something
 * valid Parameters: button: 1 / 2 / ..																//toDO
 *
 * returns 1, if the button detects something
 * returns 1, if a button Parameter was set
 * */
bool BUTTON_getValue(uint8_t button)																//toDo
 {
	switch(button)
	{
		case 1:
			return !GPIO_PinRead(BUTTON1_PORT, BUTTON1_PIN);
		break;


		case 2:
			return !GPIO_PinRead(BUTTON2_PORT, BUTTON2_PIN);
		break;

		default: return 1;																//fail
		break;
	}
	return 1;
 }

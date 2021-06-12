//=======================================================
// PREN2 - TEAM1 - STAIRCLIMBER
//=======================================================
//	PWM_Test_TinyK22
//	28.04.2021
//	Authors: Widmer Michael, Friedli Manuel
//=======================================================
//DESCRIPTION
//=======================================================
//
//=======================================================

//=======================================================
//INCLUDES
//=======================================================
#include <stdbool.h>
#include "pin_mux.h"
#include "fsl_gpio.h"
//=======================================================
// FUNCTIONS
//=======================================================
bool GET_GROUND_SENSOR(){
	if (GPIO_PinRead(BOARD_INITPINS_GROUND_SENSOR_GPIO, BOARD_INITPINS_GROUND_SENSOR_PIN)){
		return false;
	} else {
		return true;
	}
//	return GPIO_PinRead(BOARD_INITPINS_GROUND_SENSOR_GPIO, BOARD_INITPINS_GROUND_SENSOR_PIN);
}

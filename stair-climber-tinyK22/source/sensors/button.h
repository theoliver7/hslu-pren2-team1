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

#ifndef SENSORS_BUTTON_H_
#define SENSORS_BUTTON_H_

//=======================================================
//INCLUDES
//=======================================================
#include "stdint.h"
#include "stdbool.h"
#include "pin_mux.h"
#include "fsl_gpio.h"

//=======================================================
// DEFINES
//======================================================= 
#define BUTTON1_PIN 								0					//toDO
#define BUTTON1_PORT 								0
#define BUTTON2_PIN 								0
#define BUTTON2_PORT 								0

//=======================================================
// FUNCTION DECLARATIONS
//======================================================= 
bool BUTTON_getValue(uint8_t button);

#endif /*SENSORS_BUTTON_H_*/

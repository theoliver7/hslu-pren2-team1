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

#ifndef UTILS_EXECUTE_H_
#define UTILS_EXECUTE_H_

//=======================================================
//INCLUDES
//=======================================================

#include "com/parse.h"
#include "com/uart.h"
#include "mot/dcmot.h"
#include "mot/liftmot.h"
#include "mot/stepmot.h"
#include "sensors/button.h"
#include "sensors/ledbarrier.h"
#include "sensors/ultrasonic.h"
#include "signal/led.h"

//=======================================================
// FUNCTION DECLARATIONS
//=======================================================

void command_selector(command_t* cmd);


#endif /*UTILS_EXECUTE_H_*/



//=======================================================
// PREN2 - TEAM1 - STAIRCLIMBER
//=======================================================
//	PWM_Test_TinyK22
//	15.03.2021
//	Authors: Widmer Michael, Friedli Manuel
//=======================================================
//DESCRIPTION
//=======================================================
//
//=======================================================

//=======================================================
//INCLUDES
//=======================================================
#include <math.h>
#include "led.h"
#include "led_config.h"
#include "utils/ftm0.h"
#include "utils/ftm3.h"
#include "utils/ftm0_config.h"
#include "utils/ftm3_config.h"

//=======================================================
// DEFINES
//======================================================= 

//=======================================================
// FUNCTION DEFINITIONS
//=======================================================
//-------------------------------------------------------
// LED_RED
//-------------------------------------------------------
void LED_RED_dim(uint8_t dutycycle) {
	if (dutycycle <= 0) {
		// catch zero division
		FTM_LED_RED->CONTROLS[CH_LED_RED].CnV = 0;
	} else {
		FTM_LED_RED->CONTROLS[CH_LED_RED].CnV = ceil((float)MOD_LED_RED/(MAX_DUTYCYCLE/(float)dutycycle));
	}
}

//-------------------------------------------------------
// LED_GREEN
//-------------------------------------------------------
void LED_GREEN_dim(uint8_t dutycycle) {
	if (dutycycle <= 0) {
		// catch zero division
		FTM_LED_GREEN->CONTROLS[CH_LED_GREEN].CnV = 0;
	} else {
		FTM_LED_GREEN->CONTROLS[CH_LED_GREEN].CnV = ceil((float)MOD_LED_GREEN/(MAX_DUTYCYCLE/(float)dutycycle));
	}
}

//-------------------------------------------------------
// LED_BLUE
//-------------------------------------------------------
void LED_BLUE_dim(uint8_t dutycycle) {
	if (dutycycle <= 0) {
		// catch zero division
		FTM_LED_BLUE->CONTROLS[CH_LED_BLUE].CnV = 0;
	} else {
		FTM_LED_BLUE->CONTROLS[CH_LED_BLUE].CnV = ceil((float)MOD_LED_BLUE/(MAX_DUTYCYCLE/(float)dutycycle));
	}
}

void LED_INIT(){
	LED_RED_dim(0);
	LED_GREEN_dim(0);
	LED_BLUE_dim(0);
}

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

#ifndef SENSORS_ULTRASONIC_H_
#define SENSORS_ULTRASONIC_H_

//=======================================================
//INCLUDES
//=======================================================
#include "stdint.h"
#include "stdbool.h"
#include "pin_mux.h"
//=======================================================
// DEFINES
//======================================================= 
#define ULTRA_SONIC1_SEND_PORT	 GPIOB
#define ULTRA_SONIC1_SEND_PIN	 0

#define ULTRA_SONIC2_SEND_PORT	 GPIOB
#define ULTRA_SONIC2_SEND_PIN	 1



//=======================================================
// FUNCTION DECLARATIONS
//======================================================= 
uint32_t ULTRASONIC_get_Distance(uint8_t);

extern void FTM0CH6_IRQHandler(void);											//To show FTM0 there is a Handler for CH6
extern void FTM0TOF_IRQHandler(void);											//To show FTM0 there is a Handler for TOF Flag

#endif /*SENSORS_ULTRASONIC_H_*/

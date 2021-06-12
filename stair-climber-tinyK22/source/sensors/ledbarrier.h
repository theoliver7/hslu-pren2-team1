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

#ifndef SENSORS_LEDBARRIER_H_
#define SENSORS_LEDBARRIER_H_

//=======================================================
//INCLUDES
//=======================================================
#include "stdint.h"
#include "stdbool.h"
#include "pin_mux.h"

//=======================================================
// DEFINES
//======================================================= 


#define LEDBARRIER1_R_ENABLE_IRQ				PORTB_IRQn
#define LEDBARRIER1_R_CLOCKPORT					kCLOCK_PortB
#define LEDBARRIER1_R_GPIO 						GPIOB
#define LEDBARRIER1_R_PORT 						PORTB
#define LEDBARRIER1_R_PIN 						16

#define LEDBARRIER1_L_GPIO 						GPIOB
#define LEDBARRIER1_L_PORT 						PORTB
#define LEDBARRIER1_L_PIN 						16



//=======================================================
// FUNCTION DECLARATIONS
//======================================================= 
#if LED_BR_WITH_ISR
extern uint16_t steps;
void LEDBARRIER_R_RESET_STEPS(void);
void LEDBARRIER_R_INIT(void);
uint16_t LEDBARRIER_R_getSTEPS(void);
#endif
bool LEDBARRIER_FRONT_GET(void);
bool LEDBARRIER_BACK_GET(void);
bool LEDBARRIER_STEPPER_GET(void);
#endif /*SENSORS_LEDBARRIER_H_*/

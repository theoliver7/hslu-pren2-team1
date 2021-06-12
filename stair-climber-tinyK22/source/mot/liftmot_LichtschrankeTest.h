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

#ifndef MOT_LIFTMOT_H_
#define MOT_LIFTMOT_H_

//=======================================================
//INCLUDES
//=======================================================
#include "stdint.h"
#include "platform.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
//=======================================================
// DEFINES
//======================================================= 
#define CHANNEL_LIFTMOT1_UP 1				//FTM0
#define CHANNEL_LIFTMOT1_DOWN 2
#define CHANNEL_LIFTMOT2_UP 6														//toDO
#define CHANNEL_LIFTMOT2_DOWN 7


#define LIFTMOT_SPEED_STOP					0			//defines the stopspeed (=0)
#define LIFTMOT_DEFAULT_SPEED						180			//defines the speed of the motor to go up / down		Value Range: 0 - 255 (100-0%)
#define MOT_POS_FINE 						1			//declairs how finde the motor should approach the speeed (1: fast ... 5: smooth ... 10: very smooth)
//=======================================================
// FUNCTION DECLARATIONS
//======================================================= 


extern uint16_t actual_position;

bool LIFTMOT_up(uint8_t motor, uint16_t position);
bool LIFTMOT_down(uint8_t motor, uint16_t position);
uint16_t LIFTMOT_getActualPosition(void);


#endif /*MOT_LIFTMOT_H_*/

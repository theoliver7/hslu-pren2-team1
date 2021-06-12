
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
#define CHANNEL_LIFTMOT2_UP 6
#define CHANNEL_LIFTMOT2_DOWN 7

#define LIFTMOT_SPEED_STOP					0xFFFF			//defines the stopspeed (=0)
#define LIFTMOT_DEFAULT_SPEED				100			//defines the speed of the motor to go up / down		Value Range: 0 - 255 (0-100%)
#define MOT_POS_FINE 						1			//declairs how fine the motor should approach the speeed (1: fast ... 5: smooth ... 10: very smooth)

#define LIFTMOT_FRONT 1
#define LIFTMOT_BACK 2

//=======================================================
// FUNCTION DECLARATIONS
//=======================================================
bool LIFTMOT_up(uint8_t motor, uint8_t speed);
bool LIFTMOT_down(uint8_t motor, uint8_t speed);

bool LIFTMOT_sync_up(uint8_t speedv);
bool LIFTMOT_sync_down(uint8_t speedv);

bool LIFTMOT_DRIVE_POS_MIDDLEUP(void);
bool LIFTMOT_DRIVE_POS_MIDDLEDOWN(void);
bool LIFTMOT_DRIVE_POS_OUTERGROUND(void);
bool LIFTMOT_DRIVE_POS_OUTERUP(void);

bool LIFTMOT_FRONT_GROUND(void);

bool LIFTMOT_GOTO_TOP(bool);
bool LIFTMOT_GOTO_BOTTOM(bool);

void LIFTMOT_LETDOWN(void);
bool LIFTMOT_MIDSEGM_TOP(void);

#endif /*MOT_LIFTMOT_H_*/

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

#ifndef MOT_DCMOT_H_
#define MOT_DCMOT_H_

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
#define MOT_FRONT 2
#define MOT_BACK 3
#define MOT_MIDDLE 1

//=======================================================
// FUNCTION DECLARATIONS
//======================================================= 
bool DCMOT_vorward(uint8_t motor, uint8_t speed);
bool DCMOT_backward(uint8_t motor, uint8_t speed);
bool DCMOT_sync_vorward(bool all, uint8_t speed);
bool DCMOT_sync_backward(bool all, uint8_t speed);
#endif /*MOT_DCMOT_H_*/

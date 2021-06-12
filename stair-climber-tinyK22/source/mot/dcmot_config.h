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

#ifndef MOT_DCMOT_CONFIG_H_
#define MOT_DCMOT_CONFIG_H_

//=======================================================
//INCLUDES
//=======================================================

//=======================================================
// DEFINES
//======================================================= 
#define CHANNEL_DCMOT1_VORWARD 		6				//FTM3
#define CHANNEL_DCMOT1_BACKWARDS 	5
#define CHANNEL_DCMOT2_VORWARD 		0
#define CHANNEL_DCMOT2_BACKWARDS 	7
#define CHANNEL_DCMOT3_VORWARD 		2
#define CHANNEL_DCMOT3_BACKWARDS 	1

#define DCMOT_SPEED_STOP					0			//defines the stopspeed (=0)
#define DCMOT_DEFAULT_SPEED				100			//defines the speed of the motor to go up / down		Value Range: 0 - 255 (0-100%)
#define DCMOT_POS_FINE 1									//declares how finde the motor should approach the speed (1: fast ... 5: smooth ... 10: very smooth)


#endif /*MOT_DCMOT_CONFIG_H_*/

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

//=======================================================
//INCLUDES
//=======================================================
#include "liftmot_LichtschrankeTest.h"
#include "liftmot_config_LichtschrankeTest.h"
#include "stdint.h"
#include "platform.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "sensors/ledbarrier.h"
//=======================================================
// DEFINES
//======================================================= 


//=======================================================
// FUNCTION DEFINITIONS
//======================================================= 
//uint16_t actual_position = 50;
//
//
//uint16_t LIFTMOT_getActualPosition(void){
//	return actual_position;
//}
//
///*
// * Helpfunction: short delay helps the motor get speed smoothly
// *
// */
//static void LIFTMOT_short_delay(void){
//	for(int i=0;i<(MOT_POS_FINE*20000);i++)
//	{
//		__asm volatile ("nop");
//	}
//}
//
//
//static void LIFTMOT_delay(void){
//
//	for(int i=0;i<5;i++){
//	for(int i=0;i<(5000000);i++)
//	{
//		__asm volatile ("nop");
//	}
//	}
//	printf("done\n");
//}
//
///*
// * Helpfunction for aproaching backwards speed finely
// *
// */
//static void LIFTMOT_fine_startup_down(int motor_and_direction, int speed){
//	int value = FTM0->CONTROLS[motor_and_direction].CnV;								//get actual CnV value
//	int dif = (0xFFFF/256*speed) - value;
//
//	for(uint8_t x=0; x<100; x++)
//	{
//	FTM0->CONTROLS[motor_and_direction].CnV +=  dif/100;
//	LIFTMOT_short_delay();
//	}
//	FTM0->CONTROLS[motor_and_direction].CnV = (0xFFFF/256*speed);
//}
//
///*
// * Helpfunction for aproaching up-speed finely
// *
// */
//static void LIFTMOT_fine_startup_up(int motor_and_direction, int speed){
//	int value = FTM0->CONTROLS[motor_and_direction].CnV;								//get actual CnV value
//	int dif = (0xFFFF/256*speed) - value;
//
//	for(uint8_t x=0; x<100; x++)
//	{
//	FTM0->CONTROLS[motor_and_direction].CnV +=  dif/100;
//	LIFTMOT_short_delay();
//	}
//	FTM0->CONTROLS[motor_and_direction].CnV = (0xFFFF/256*speed);
//}
//
///*
// * Sets the upwards speed for motor from 0 to 100%
// * valid Parameters: motor: 1 / 2
// * 			         speed: 0 - 255 (=0-100%)
// *
// * returns Parameters: 0: if there was a error, 1: everything went okey
// * */
//bool LIFTMOT_up(uint8_t motor, uint16_t position)
//{
//	switch(motor)
//	{
//	case 1:
//			//actual_position = actual_position + LEDBARRIER_R_getSTEPS();
//			LEDBARRIER_R_RESET_STEPS();
//			LIFTMOT_fine_startup_up(CHANNEL_LIFTMOT1_UP, LIFTMOT_DEFAULT_SPEED);
//			//while(LEDBARRIER_R_getSTEPS()<position)							//wait till led barrier detects something
////			while(actual_position + LEDBARRIER_R_getSTEPS()<position)
////			{;}
//
//			FTM0->CONTROLS[CHANNEL_LIFTMOT1_UP].CnV = 0xFFFF;
//			LIFTMOT_delay();
//			actual_position = actual_position + LEDBARRIER_R_getSTEPS();
//			break;
//	case 2:
//	//		LIFTMOT_fine_startup_up(CHANNEL_LIFTMOT2_UP,LIFTMOT_SPEED);
//
//	//		while(LEDBARRIER_L_getSTEPS()!=30)							//wait till led barrier detects something
//	//		{;}
//	//		LIFTMOT_fine_startup_up(CHANNEL_LIFTMOT2_UP, LIFTMOT_SPEED_STOP);
//	//		break;
//
//	default: return 0;		//There was a fail
//	break;
//	}
//	return 1;
//}
//
///*
// * Sets the backward speed for motor from 0 to 100%
// * valid Parameters: motor: 1 / 2
// * 			         speed: 0 - 256 (=0-100%)
// *
// * returns Parameters: 0: if there was a error, 1: everything went okey
// * */
//bool LIFTMOT_down(uint8_t motor, uint16_t position)
//{
//	switch(motor)
//	{
//	case 1:
//
//		//	actual_position = actual_position - LEDBARRIER_R_getSTEPS();
//			LEDBARRIER_R_RESET_STEPS();
//			LIFTMOT_fine_startup_down(CHANNEL_LIFTMOT1_DOWN, LIFTMOT_DEFAULT_SPEED);
//			//while(LEDBARRIER_R_getSTEPS()<position)							//wait till led barrier detects something
//			while(actual_position - LEDBARRIER_R_getSTEPS()>position)
//			{;}
//			FTM0->CONTROLS[CHANNEL_LIFTMOT1_DOWN].CnV = 0xFFFF;
//			LIFTMOT_delay();
//			actual_position = actual_position - LEDBARRIER_R_getSTEPS();
//			break;
//	case 2:
//	//		LIFTMOT_fine_startup_up(CHANNEL_LIFTMOT2_DOWN,LIFTMOT_SPEED_STOP);
//	//		LIFTMOT_fine_startup_down(CHANNEL_LIFTMOT2_DOWN, LIFTMOT_SPEED);
//
//	//		LEDBARRIER_R_START();
//		//	while(LEDBARRIER_L_getSTEPS()!=30)							//wait till led barrier detects something
//		//	{;}
//	//		LIFTMOT_fine_startup_up(CHANNEL_LIFTMOT2_DOWN, LIFTMOT_SPEED_STOP);
//	//		break;
//
//	default: return 0;		//There was a fail
//	break;
//	}
//	return 1;
//}



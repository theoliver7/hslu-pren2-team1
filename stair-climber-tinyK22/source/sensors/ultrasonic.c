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
#include "ultrasonic.h"
#include "ultrasonic_config.h"
#include "stdlib.h"
#include "stdio.h"
#include "MK22F51212.h"
#include "stdint.h"
#include "pin_mux.h"
#include "fsl_gpio.h"


//=======================================================
// DEFINES
//======================================================= 

//=======================================================
// FUNCTION DEFINITIONS
//======================================================= 
static uint32_t timebase = 0;
static uint32_t starttime = 0;
static uint32_t time_measured = 0;
static bool first_flank = false;					//indicates, if the first flank of the signal was detected
static bool meas_done = false;
static bool meas_fail = false;

static void ULTRASONIC_Disable_TOF()
{
	FTM1->SC &= ~FTM_SC_TOIE_MASK;
}

static void ULTRASONIC_Enable_TOF()
{
	FTM1->SC |= FTM_SC_TOIE_MASK;
}


/*
 * Returns the Distance to the next Object
 * If there was a fail, it returns 0
 * If the ultrasonic is to close to an obstacle, it returns 1
 *
 * valid Parameters: Ultrasonic: 1 / 2
 *
 * */
uint32_t ULTRASONIC_get_Distance(uint8_t Ultrasonic)
{
	meas_fail = false;
	first_flank = false;
	meas_done = false;
	timebase = 0;
	ULTRASONIC_Enable_TOF();															//Enable Timer Interrupt
	switch(Ultrasonic)
	{
		case 1:
			GPIO_PinWrite(ULTRA_SONIC1_SEND_PORT, ULTRA_SONIC1_SEND_PIN, true);					//Send Start Signal to Sensor
		break;

		case 2:
			GPIO_PinWrite(ULTRA_SONIC2_SEND_PORT, ULTRA_SONIC2_SEND_PIN, true);
		break;

		default:
		break;
	}
	while(!meas_done){;}																//Wait till measurement is done
	if(meas_fail)							//ultrasonic had to long to respond
	{
		return 0;
	}
	//TODO Die Auflösung des U-Sonics könnte noch verfeinert werden, da der Rückgabewert
	// uint16_t gemacht werden.
	uint32_t distance = time_measured * 340/2;
	return distance/100;
}



extern void FTM1CH0_IRQHandler(void)														//Inputcompare-Handler
{
	if(!first_flank)										//First Flank of the Signal
	{
		starttime = timebase;
		first_flank = true;
	}
	else if (first_flank)												//Second Flank
	{
		time_measured = timebase - starttime;
		ULTRASONIC_Disable_TOF();							//Stop of the measurment
		meas_done = true;
	}
	FTM1->CONTROLS[0].CnSC &= ~FTM_CnSC_CHF_MASK;			//Interrupt reset
}


extern void FTM1TOF_IRQHandler(void)						//ULTRA_SONIC_TIMEBASE Handler	(Timer-Handler)
{
	if(timebase==2)														//Startsignal was over 10us
	{
		GPIO_PinWrite(ULTRA_SONIC1_SEND_PORT, ULTRA_SONIC1_SEND_PIN, false);
		GPIO_PinWrite(ULTRA_SONIC2_SEND_PORT, ULTRA_SONIC2_SEND_PIN, false);
	}
	timebase = timebase + 1;

	if(timebase >= 30000)								//Ultra_Sonic has to long to responde
	{
		meas_fail = true;
		meas_done = true;
	}

	FTM1->SC &= ~FTM_SC_TOF_MASK;							//Interrupt reset
}

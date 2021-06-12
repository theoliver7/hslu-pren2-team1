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
#include "utils/FTM1.h"
#include "utils/FTM1_config.h"
#include "sensors/ultrasonic.h"								//Show FTM1 that ultrasonic has some ISR-Handler

//=======================================================
// DEFINES
//======================================================= 

//=======================================================
// FUNCTION DEFINITIONS
//======================================================= 

//-------------------------------------------------------
// Default_Handler_FTM1()
// Default handler is called if a handler without an
// implementation is called.
//-------------------------------------------------------
void Default_Handler_FTM1() {
	__asm("bkpt");
	// Breakpoint
}

void FTM1CH0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM1")));
void FTM1CH1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM1")));
void FTM1TOF_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM1")));

//-------------------------------------------------------
// FTM1_IRQHandler()
// This function checks which interrupt flag is set and
// calls the corresponding ISR
//-------------------------------------------------------
void FTM1_IRQHandler(void) {
	if ((FTM1->CONTROLS[0].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM1CH0_IRQHandler();
	if ((FTM1->CONTROLS[1].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM1CH1_IRQHandler();
	if ((FTM1->SC & TOF_TOIE_MASK) == TOF_TOIE_MASK)
		FTM1TOF_IRQHandler();
}

//-------------------------------------------------------
// FTM1_INIT()
// This function initialises the FTM1 timer module. Changes
// should be made inside FTM1_config.h
//-------------------------------------------------------
void FTM1_INIT() {
	// CLOCKGATING
	SIM->SCGC6 |= SIM_SCGC6_FTM1(1);

	// MODULO VALUE
	FTM1->MOD = FTM1_MODULO;

	// TIMER CONTROLLREGISTER
	FTM1->SC = 	FTM_SC_CLKS(FTM1_CLOCK) |
				FTM_SC_PS(FTM1_CLOCK_PRESCALER) |
				FTM_SC_TOIE(FTM1_ENABLE_INTERRUPT) |
				FTM_SC_CPWMS(FTM1_PWM_MODE);

	//-------------------------------------------------------
	// CHANNEL 0 SETUP
	FTM1->CONTROLS[0].CnSC = 	FTM_CnSC_MSA(FTM1_CH0_MSA) |
								FTM_CnSC_MSB(FTM1_CH0_MSB) |
								FTM_CnSC_ELSA(FTM1_CH0_ELSA) |
								FTM_CnSC_ELSB(FTM1_CH0_ELSB) |
								FTM_CnSC_CHIE(FTM1_CH0_CHIE);
	FTM1->CONTROLS[0].CnV = FTM1_CH0_PWM_SV;

	//-------------------------------------------------------
	// CHANNEL 1 SETUP
	FTM1->CONTROLS[1].CnSC = 	FTM_CnSC_MSA(FTM1_CH1_MSA) |
								FTM_CnSC_MSB(FTM1_CH1_MSB) |
								FTM_CnSC_ELSA(FTM1_CH1_ELSA) |
								FTM_CnSC_ELSB(FTM1_CH1_ELSB) |
								FTM_CnSC_CHIE(FTM1_CH1_CHIE);
	FTM1->CONTROLS[1].CnV = FTM1_CH1_PWM_SV;

	//-------------------------------------------------------


	NVIC_SetPriority(FTM1_IRQn, FTM1_INTERRUPT_PRIO);   // set interrupt priority
	NVIC_EnableIRQ(FTM1_IRQn);                    		// enable interrupt
}

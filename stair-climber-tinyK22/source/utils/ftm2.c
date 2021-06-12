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
#include "utils/ftm2.h"
#include "utils/ftm2_config.h"


//=======================================================
// DEFINES
//======================================================= 

//=======================================================
// FUNCTION DEFINITIONS
//======================================================= 

//-------------------------------------------------------
// Default_Handler_FTM2()
// Default handler is called if a handler without an
// implementation is called.
//-------------------------------------------------------
void Default_Handler_FTM2() {
	__asm("bkpt");
	// Breakpoint
}

void FTM2CH0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM2")));
void FTM2CH1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM2")));
void FTM2TOF_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM2")));

//-------------------------------------------------------
// FTM2_IRQHandler()
// This function checks which interrupt flag is set and
// calls the corresponding ISR
//-------------------------------------------------------
void FTM2_IRQHandler(void) {
	if ((FTM2->CONTROLS[0].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM2CH0_IRQHandler();
	if ((FTM2->CONTROLS[1].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM2CH1_IRQHandler();
	if ((FTM2->SC & TOF_TOIE_MASK) == TOF_TOIE_MASK)
		FTM2TOF_IRQHandler();
}

//-------------------------------------------------------
// FTM2_INIT()
// This function initializes the FTM2 timer module. Changes
// should be made inside FTM2_config.h
//-------------------------------------------------------
void FTM2_INIT() {
	// CLOCKGATING
	SIM->SCGC6 |= SIM_SCGC6_FTM2(1);

	// MODULO VALUE
	FTM2->MOD = FTM2_MODULO;

	// TIMER CONTROLLREGISTER
	FTM2->SC = 	FTM_SC_CLKS(FTM2_CLOCK) |
				FTM_SC_PS(FTM2_CLOCK_PRESCALER) |
				FTM_SC_TOIE(FTM2_ENABLE_INTERRUPT) |
				FTM_SC_CPWMS(FTM2_PWM_MODE);

	//-------------------------------------------------------
	// CHANNEL 0 SETUP
	FTM2->CONTROLS[0].CnSC = 	FTM_CnSC_MSA(FTM2_CH0_MSA) |
								FTM_CnSC_MSB(FTM2_CH0_MSB) |
								FTM_CnSC_ELSA(FTM2_CH0_ELSA) |
								FTM_CnSC_ELSB(FTM2_CH0_ELSB) |
								FTM_CnSC_CHIE(FTM2_CH0_CHIE);
	FTM2->CONTROLS[0].CnV = FTM2_CH0_PWM_SV;

	//-------------------------------------------------------
	// CHANNEL 1 SETUP
	FTM2->CONTROLS[1].CnSC = 	FTM_CnSC_MSA(FTM2_CH1_MSA) |
								FTM_CnSC_MSB(FTM2_CH1_MSB) |
								FTM_CnSC_ELSA(FTM2_CH1_ELSA) |
								FTM_CnSC_ELSB(FTM2_CH1_ELSB) |
								FTM_CnSC_CHIE(FTM2_CH1_CHIE);
	FTM2->CONTROLS[1].CnV = FTM2_CH1_PWM_SV;

	NVIC_SetPriority(FTM2_IRQn, FTM2_INTERRUPT_PRIO);   // set interrupt priority
	NVIC_EnableIRQ(FTM2_IRQn);                    		// enable interrupt
}




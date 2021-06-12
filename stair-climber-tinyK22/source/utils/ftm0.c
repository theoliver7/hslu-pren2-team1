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
#include "utils/ftm0.h"
#include "utils/ftm0_config.h"

//=======================================================
// DEFINES
//======================================================= 

//=======================================================
// FUNCTION DEFINITIONS
//======================================================= 

//-------------------------------------------------------
// Default_Handler_FTM0()
// Default handler is called if a handler without an
// implementation is called.
//-------------------------------------------------------
void Default_Handler_FTM0() {
	__asm("bkpt");
	// Breakpoint
}

void FTM0CH0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM0")));
void FTM0CH1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM0")));
void FTM0CH2_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM0")));
void FTM0CH3_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM0")));
void FTM0CH4_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM0")));
void FTM0CH5_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM0")));
void FTM0CH6_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM0")));
void FTM0CH7_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM0")));
void FTM0TOF_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM0")));

//-------------------------------------------------------
// FTM0_IRQHandler()
// This function checks which interrupt flag is set and
// calls the corresponding ISR
//-------------------------------------------------------
void FTM0_IRQHandler(void) {
	if ((FTM0->CONTROLS[0].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM0CH0_IRQHandler();
	if ((FTM0->CONTROLS[1].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM0CH1_IRQHandler();
	if ((FTM0->CONTROLS[2].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM0CH2_IRQHandler();
	if ((FTM0->CONTROLS[3].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM0CH3_IRQHandler();
	if ((FTM0->CONTROLS[4].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM0CH4_IRQHandler();
	if ((FTM0->CONTROLS[5].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM0CH5_IRQHandler();
	if ((FTM0->CONTROLS[6].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM0CH6_IRQHandler();
	if ((FTM0->CONTROLS[7].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM0CH7_IRQHandler();
	if ((FTM0->SC & TOF_TOIE_MASK) == TOF_TOIE_MASK)
		FTM0TOF_IRQHandler();
}

//-------------------------------------------------------
// FTM0_INIT()
// This function initialises the ftm0 timer module. Changes
// should be made inside ftm0_config.h
//-------------------------------------------------------
void FTM0_INIT() {
	// CLOCKGATING
	SIM->SCGC6 |= SIM_SCGC6_FTM0(1);

	// MODULO VALUE
	FTM0->MOD = FTM0_MODULO;

	// TIMER CONTROLLREGISTER
	FTM0->SC = 	FTM_SC_CLKS(FTM0_CLOCK) |
				FTM_SC_PS(FTM0_CLOCK_PRESCALER) |
				FTM_SC_TOIE(FTM0_ENABLE_INTERRUPT) |
				FTM_SC_CPWMS(FTM0_PWM_MODE);

	//-------------------------------------------------------
	// CHANNEL 0 SETUP
	FTM0->CONTROLS[0].CnSC = 	FTM_CnSC_MSA(FTM0_CH0_MSA) |
								FTM_CnSC_MSB(FTM0_CH0_MSB) |
								FTM_CnSC_ELSA(FTM0_CH0_ELSA) |
								FTM_CnSC_ELSB(FTM0_CH0_ELSB) |
								FTM_CnSC_CHIE(FTM0_CH0_CHIE);
	FTM0->CONTROLS[0].CnV = FTM0_CH0_PWM_SV;

	//-------------------------------------------------------
	// CHANNEL 1 SETUP
	FTM0->CONTROLS[1].CnSC = 	FTM_CnSC_MSA(FTM0_CH1_MSA) |
								FTM_CnSC_MSB(FTM0_CH1_MSB) |
								FTM_CnSC_ELSA(FTM0_CH1_ELSA) |
								FTM_CnSC_ELSB(FTM0_CH1_ELSB) |
								FTM_CnSC_CHIE(FTM0_CH1_CHIE);
	FTM0->CONTROLS[1].CnV = FTM0_CH1_PWM_SV;

	//-------------------------------------------------------
	// CHANNEL 2 SETUP
	FTM0->CONTROLS[2].CnSC = 	FTM_CnSC_MSA(FTM0_CH2_MSA) |
								FTM_CnSC_MSB(FTM0_CH2_MSB) |
								FTM_CnSC_ELSA(FTM0_CH2_ELSA) |
								FTM_CnSC_ELSB(FTM0_CH2_ELSB) |
								FTM_CnSC_CHIE(FTM0_CH2_CHIE);
	FTM0->CONTROLS[2].CnV = FTM0_CH2_PWM_SV;

	//-------------------------------------------------------
	// CHANNEL 3 SETUP
	FTM0->CONTROLS[3].CnSC = 	FTM_CnSC_MSA(FTM0_CH3_MSA) |
								FTM_CnSC_MSB(FTM0_CH3_MSB) |
								FTM_CnSC_ELSA(FTM0_CH3_ELSA) |
								FTM_CnSC_ELSB(FTM0_CH3_ELSB) |
								FTM_CnSC_CHIE(FTM0_CH3_CHIE);
	FTM0->CONTROLS[3].CnV = FTM0_CH3_PWM_SV;

	//-------------------------------------------------------
	// CHANNEL 4 SETUP
	FTM0->CONTROLS[4].CnSC = 	FTM_CnSC_MSA(FTM0_CH4_MSA) |
								FTM_CnSC_MSB(FTM0_CH4_MSB) |
								FTM_CnSC_ELSA(FTM0_CH4_ELSA) |
								FTM_CnSC_ELSB(FTM0_CH4_ELSB) |
								FTM_CnSC_CHIE(FTM0_CH4_CHIE);
	FTM0->CONTROLS[4].CnV = FTM0_CH4_PWM_SV;

	//-------------------------------------------------------
	// CHANNEL 5 SETUP
	FTM0->CONTROLS[5].CnSC = 	FTM_CnSC_MSA(FTM0_CH5_MSA) |
								FTM_CnSC_MSB(FTM0_CH5_MSB) |
								FTM_CnSC_ELSA(FTM0_CH5_ELSA) |
								FTM_CnSC_ELSB(FTM0_CH5_ELSB) |
								FTM_CnSC_CHIE(FTM0_CH5_CHIE);
	FTM0->CONTROLS[5].CnV = FTM0_CH5_PWM_SV;

	//-------------------------------------------------------
	// CHANNEL 6 SETUP
	FTM0->CONTROLS[6].CnSC = 	FTM_CnSC_MSA(FTM0_CH6_MSA) |
								FTM_CnSC_MSB(FTM0_CH6_MSB) |
								FTM_CnSC_ELSA(FTM0_CH6_ELSA) |
								FTM_CnSC_ELSB(FTM0_CH6_ELSB) |
								FTM_CnSC_CHIE(FTM0_CH6_CHIE);
	FTM0->CONTROLS[6].CnV = FTM0_CH6_PWM_SV;

	//-------------------------------------------------------
	// CHANNEL 7 SETUP
	FTM0->CONTROLS[7].CnSC = 	FTM_CnSC_MSA(FTM0_CH7_MSA) |
								FTM_CnSC_MSB(FTM0_CH7_MSB) |
								FTM_CnSC_ELSA(FTM0_CH7_ELSA) |
								FTM_CnSC_ELSB(FTM0_CH7_ELSB) |
								FTM_CnSC_CHIE(FTM0_CH7_CHIE);
	FTM0->CONTROLS[7].CnV = FTM0_CH7_PWM_SV;

	NVIC_SetPriority(FTM0_IRQn, FTM0_INTERRUPT_PRIO);   // set interrupt priority
	NVIC_EnableIRQ(FTM0_IRQn);                    		// enable interrupt
}

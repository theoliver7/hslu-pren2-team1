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
#include "utils/ftm3.h"
#include "utils/ftm3_config.h"

//=======================================================
// DEFINES
//======================================================= 

//=======================================================
// FUNCTION DEFINITIONS
//======================================================= 

//-------------------------------------------------------
// Default_Handler_FTM3()
// Default handler is called if a handler without an
// implementation is called.
//-------------------------------------------------------
void Default_Handler_FTM3() {
	__asm("bkpt");
	// Breakpoint
}

void FTM3CH0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));
void FTM3CH1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));
void FTM3CH2_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));
void FTM3CH3_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));
void FTM3CH4_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));
void FTM3CH5_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));
void FTM3CH6_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));
void FTM3CH7_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));
void FTM3TOF_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_FTM3")));

//-------------------------------------------------------
// FTM3_IRQHandler()
// This function checks which interrupt flag is set and
// calls the corresponding ISR
//-------------------------------------------------------
void FTM3_IRQHandler(void) {
	if ((FTM3->CONTROLS[0].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM3CH0_IRQHandler();
	if ((FTM3->CONTROLS[1].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM3CH1_IRQHandler();
	if ((FTM3->CONTROLS[2].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM3CH2_IRQHandler();
	if ((FTM3->CONTROLS[3].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM3CH3_IRQHandler();
	if ((FTM3->CONTROLS[4].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM3CH4_IRQHandler();
	if ((FTM3->CONTROLS[5].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM3CH5_IRQHandler();
	if ((FTM3->CONTROLS[6].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM3CH6_IRQHandler();
	if ((FTM3->CONTROLS[7].CnSC & CHF_CHIE_MASK) == CHF_CHIE_MASK)
		FTM3CH7_IRQHandler();
	if ((FTM3->SC & TOF_TOIE_MASK) == TOF_TOIE_MASK)
		FTM3TOF_IRQHandler();
}

//-------------------------------------------------------
// FTM3_INIT()
// This function initialises the FTM3 timer module. Changes
// should be made inside FTM3_config.h
//-------------------------------------------------------
void FTM3_INIT() {
	// CLOCKGATING
	SIM->SCGC6 |= SIM_SCGC6_FTM3(1);

	// MODULO VALUE
	FTM3->MOD = FTM3_MODULO;

	// TIMER CONTROLLREGISTER
	FTM3->SC = 	FTM_SC_CLKS(FTM3_CLOCK) |
				FTM_SC_PS(FTM3_CLOCK_PRESCALER) |
				FTM_SC_TOIE(FTM3_ENABLE_INTERRUPT) |
				FTM_SC_CPWMS(FTM3_PWM_MODE);

	//-------------------------------------------------------
	// CHANNEL 3 SETUP
	FTM3->CONTROLS[0].CnSC = 	FTM_CnSC_MSA(FTM3_CH0_MSA) |
								FTM_CnSC_MSB(FTM3_CH0_MSB) |
								FTM_CnSC_ELSA(FTM3_CH0_ELSA) |
								FTM_CnSC_ELSB(FTM3_CH0_ELSB) |
								FTM_CnSC_CHIE(FTM3_CH0_CHIE);
	FTM3->CONTROLS[0].CnV = FTM3_CH0_PWM_SV;

	//-------------------------------------------------------
	// CHANNEL 1 SETUP
	FTM3->CONTROLS[1].CnSC = 	FTM_CnSC_MSA(FTM3_CH1_MSA) |
								FTM_CnSC_MSB(FTM3_CH1_MSB) |
								FTM_CnSC_ELSA(FTM3_CH1_ELSA) |
								FTM_CnSC_ELSB(FTM3_CH1_ELSB) |
								FTM_CnSC_CHIE(FTM3_CH1_CHIE);
	FTM3->CONTROLS[1].CnV = FTM3_CH1_PWM_SV;

	//-------------------------------------------------------
	// CHANNEL 2 SETUP
	FTM3->CONTROLS[2].CnSC = 	FTM_CnSC_MSA(FTM3_CH2_MSA) |
								FTM_CnSC_MSB(FTM3_CH2_MSB) |
								FTM_CnSC_ELSA(FTM3_CH2_ELSA) |
								FTM_CnSC_ELSB(FTM3_CH2_ELSB) |
								FTM_CnSC_CHIE(FTM3_CH2_CHIE);
	FTM3->CONTROLS[2].CnV = FTM3_CH2_PWM_SV;

	//-------------------------------------------------------
	// CHANNEL 3 SETUP
	FTM3->CONTROLS[3].CnSC = 	FTM_CnSC_MSA(FTM3_CH3_MSA) |
								FTM_CnSC_MSB(FTM3_CH3_MSB) |
								FTM_CnSC_ELSA(FTM3_CH3_ELSA) |
								FTM_CnSC_ELSB(FTM3_CH3_ELSB) |
								FTM_CnSC_CHIE(FTM3_CH3_CHIE);
	FTM3->CONTROLS[3].CnV = FTM3_CH3_PWM_SV;

	//-------------------------------------------------------
	// CHANNEL 4 SETUP
	FTM3->CONTROLS[4].CnSC = 	FTM_CnSC_MSA(FTM3_CH4_MSA) |
								FTM_CnSC_MSB(FTM3_CH4_MSB) |
								FTM_CnSC_ELSA(FTM3_CH4_ELSA) |
								FTM_CnSC_ELSB(FTM3_CH4_ELSB) |
								FTM_CnSC_CHIE(FTM3_CH4_CHIE);
	FTM3->CONTROLS[4].CnV = FTM3_CH4_PWM_SV;

	//-------------------------------------------------------
	// CHANNEL 5 SETUP
	FTM3->CONTROLS[5].CnSC = 	FTM_CnSC_MSA(FTM3_CH5_MSA) |
								FTM_CnSC_MSB(FTM3_CH5_MSB) |
								FTM_CnSC_ELSA(FTM3_CH5_ELSA) |
								FTM_CnSC_ELSB(FTM3_CH5_ELSB) |
								FTM_CnSC_CHIE(FTM3_CH5_CHIE);
	FTM3->CONTROLS[5].CnV = FTM3_CH5_PWM_SV;

	//-------------------------------------------------------
	// CHANNEL 6 SETUP
	FTM3->CONTROLS[6].CnSC = 	FTM_CnSC_MSA(FTM3_CH6_MSA) |
								FTM_CnSC_MSB(FTM3_CH6_MSB) |
								FTM_CnSC_ELSA(FTM3_CH6_ELSA) |
								FTM_CnSC_ELSB(FTM3_CH6_ELSB) |
								FTM_CnSC_CHIE(FTM3_CH6_CHIE);
	FTM3->CONTROLS[6].CnV = FTM3_CH6_PWM_SV;

	//-------------------------------------------------------
	// CHANNEL 7 SETUP
	FTM3->CONTROLS[7].CnSC = 	FTM_CnSC_MSA(FTM3_CH7_MSA) |
								FTM_CnSC_MSB(FTM3_CH7_MSB) |
								FTM_CnSC_ELSA(FTM3_CH7_ELSA) |
								FTM_CnSC_ELSB(FTM3_CH7_ELSB) |
								FTM_CnSC_CHIE(FTM3_CH7_CHIE);
	FTM3->CONTROLS[7].CnV = FTM3_CH7_PWM_SV;

	NVIC_SetPriority(FTM3_IRQn, FTM3_INTERRUPT_PRIO);   // set interrupt priority
	NVIC_EnableIRQ(FTM3_IRQn);                    		// enable interrupt
}




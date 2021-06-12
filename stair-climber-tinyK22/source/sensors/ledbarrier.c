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
#include "ledbarrier.h"
#include "ledbarrier_config.h"
#include "stdbool.h"
#include "ledbarrier.h"
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

//=======================================================
// DEFINES
//=======================================================
#if LED_BR_WITH_ISR
uint16_t steps = 0;
//=======================================================
// FUNCTION DEFINITIONS
//======================================================= 

uint16_t LEDBARRIER_R_getSTEPS(void)
{
	return steps;
}

void LEDBARRIER_R_RESET_STEPS(void)
{
	steps = 0;
}


/*
 * Use this function to start the count of the flags
 *
 * */
void LEDBARRIER_R_INIT(){																					//Definiert Interrupt auf GPIO
	//ClockGating
	CLOCK_EnableClock(LEDBARRIER1_R_CLOCKPORT);
	//Muxing
	PORT_SetPinMux(LEDBARRIER1_R_PORT,LEDBARRIER1_R_PIN,kPORT_MuxAsGpio);
	//Pin Konfiguration
	gpio_pin_config_t sw_config = {kGPIO_DigitalInput,0,};
	GPIO_PinInit(LEDBARRIER1_R_GPIO,LEDBARRIER1_R_PIN,&sw_config);

	//Interrupt Konfiguration
	PORT_SetPinInterruptConfig(LEDBARRIER1_R_PORT,LEDBARRIER1_R_PIN,kPORT_InterruptRisingEdge);
	//Freigabe des Interrupts
	EnableIRQ(LEDBARRIER1_R_ENABLE_IRQ);
	steps = 0;
}

//--------------------------------------------------------IRQ-Handler----------------------------------------------------------
void PORTB_IRQHandler(void) {
/* Clear external interrupt flag . */

	//Verrifiziere welcher Interrupt ausgelöst hat und Flag wieder löschen
	if (1U<<LEDBARRIER1_R_PIN) {

		uint32_t i, x;
		for(x=0;x<2;x++)
		{
			for(i=0;i<250000;i++)
			{
				__asm volatile ("nop");
			}
		}


	GPIO_PortClearInterruptFlags(LEDBARRIER1_R_GPIO,1U<<LEDBARRIER1_R_PIN);
	steps++;
	}



__DSB();
}
#else

// returns true if the barrier sees something
bool LEDBARRIER_FRONT_GET(){
	return GPIO_PinRead(BOARD_INITPINS_LEDBARRIER_RIGHT_GPIO, BOARD_INITPINS_LEDBARRIER_RIGHT_PIN);
}

// returns true if the barrier sees something
bool LEDBARRIER_BACK_GET(){
	return GPIO_PinRead(BOARD_INITPINS_LEDBARRIER_LEFT_GPIO, BOARD_INITPINS_LEDBARRIER_LEFT_PIN);
}

// returns true if the barrier sees something
bool LEDBARRIER_STEPPER_GET(){
	return GPIO_PinRead(BOARD_INITPINS_LEDBARRIER_STEPPER_GPIO, BOARD_INITPINS_LEDBARRIER_STEPPER_PIN);
}

#endif

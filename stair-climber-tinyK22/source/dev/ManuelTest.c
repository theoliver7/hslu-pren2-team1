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
#include "ManuelTest.h"
#include "stdint.h"
#include "platform.h"
#include "stdlib.h"
#include "stdio.h"
#include "mot/dcmot.h"
#include "mot/liftmot_LichtschrankeTest.h"
#include "sensors/ledbarrier.h"
#include "sensors/ultrasonic.h"
#include "sensors/button.h"

//=======================================================
// DEFINES
//======================================================= 

//=======================================================
// FUNCTION DEFINITIONS
//======================================================= 
bool check = 0;

void liftmot_test(void);
void ledbarrier_test(void);
void dcmot_test(void);
void delay_sek(uint32_t);

void ManuelTest_Run() {
//	dcmot_test();
//	liftmot_test();
//	LIFTMOT_down(1,0);
	LEDBARRIER_R_RESET_STEPS();
	FTM0->CONTROLS[1].CnV = 0xFFFF;
	FTM0->CONTROLS[2].CnV = 0xFFFF;
	LEDBARRIER_R_INIT();
	//actual_position = 50;
//	steps = 0;
	printf("jetzt einsetzen!");
	delay_sek(100);

	while (1) {
		LIFTMOT_up(1, 51);
		printf("Acutal Position up: %d \n", LIFTMOT_getActualPosition());
		delay_sek(30);

		LIFTMOT_up(1, 52);
		printf("Acutal Position down: %d \n", LIFTMOT_getActualPosition());
		delay_sek(30);

		LIFTMOT_down(1, 51);
		printf("Acutal Position down: %d \n", LIFTMOT_getActualPosition());
		delay_sek(30);

		LIFTMOT_down(1, 50);
		printf("Acutal Position down: %d \n", LIFTMOT_getActualPosition());
		delay_sek(30);

		//	printf("steps: %d \n",LEDBARRIER_R_getSTEPS());
	}
}

void liftmot_test(void) {
//	LIFTMOT_up(1);
	delay_sek(40);
//	LIFTMOT_down(1);
	delay_sek(40);
}

void dcmot_test(void) {
	check = DCMOT_vorward(1, 255);
	delay_sek(40);
	delay_sek(40);
	printf("%d", check);
	check = DCMOT_vorward(1, 120);
	delay_sek(40);
	delay_sek(40);
	printf("%d", check);
	check = DCMOT_vorward(1, 65);
	delay_sek(40);
	delay_sek(40);
	printf("%d", check);
	check = DCMOT_backward(1, 255);
	printf("%d", check);
	delay_sek(40);
	delay_sek(40);
	check = DCMOT_backward(1, 210);
	delay_sek(40);
	printf("%d", check);
	check = DCMOT_backward(1, 100);
	delay_sek(40);
	printf("%d", check);
	delay_sek(40);
	delay_sek(40);
	delay_sek(40);
	printf("%d", check);
	check = DCMOT_vorward(1, 100);
	delay_sek(40);
	printf("%d", check);
	check = DCMOT_backward(1, 163);
	delay_sek(40);
	delay_sek(40);
	delay_sek(40);
	printf("%d", check);
	check = DCMOT_backward(1, 0);
	check = DCMOT_vorward(1, 0);
}

void delay_sek(uint32_t time) {
	uint32_t i, x;
	for (x = 0; x < time; x++) {
		for (i = 0; i < 250000; i++) {
			__asm volatile ("nop");
		}
	}
}

void ledbarrier_test() {

	printf("DOWN: %d \n", LEDBARRIER_GetValue(1, false));
	delay_sek(40);
	printf("UP: %d \n", LEDBARRIER_GetValue(1, true));
	delay_sek(40);
}

void button_test() {

	printf("Button 1 pushed: %d \n", BUTTON_getValue(1));
	delay_sek(40);
	printf("Button 2 pushed: %d \n", BUTTON_getValue(2));
	delay_sek(40);
}


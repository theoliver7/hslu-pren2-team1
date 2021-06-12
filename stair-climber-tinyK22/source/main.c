//=======================================================
// PREN2 - TEAM1 - STAIRCLIMBER
//=======================================================
//	PWM_Test_TinyK22
//	19.03.2021
//	Authors: Widmer Michael, Friedli Manuel
//=======================================================
/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


//=======================================================
//INCLUDES
//=======================================================
#include <stdio.h>

#include "utils/ftm0.h"
#include "utils/ftm1.h"
#include "utils/ftm2.h"
#include "utils/ftm3.h"
#include "program/workloop.h"
#include "board.h"
#include "peripherals.h"
#include "clock_config.h"
#include "pin_mux.h"
#include "MK22F51212.h"
#include "com/uart.h"
#include "com/uart_config.h"
#include "mot/stepmot.h"
#include "program/workloop.h"
#include "dev/ManuelTest.h"
#include "dev/MichaelTest.h"
#include "signal/led.h"
#include "developmentmode.h"


//=======================================================
// PROGRAM STARTING POINT
//=======================================================
int main(void) {
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	FTM0_INIT();
	FTM1_INIT();
	FTM2_INIT();
	FTM3_INIT();
	LED_INIT();
//	enable_Stepper_Driver();
	disable_Stepper_Driver();
#if MANUEL_IS_DEVELOPING
	// test module functions of Manuel
	ManuelTest_Run();
#elif MICHAEL_IS_DEVELOPING
	// test module functions of Michael
	MichaelTest_Run();
#elif STAIRCLIMBER_SOLUTION
	// run the stairclimber solution
	uart1Init(TERMINAL_BAUDRATE);
	workloop();
#endif

	return 0;
}

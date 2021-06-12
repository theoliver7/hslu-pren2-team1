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

#ifndef PLATFORM_H_
#define PLATFORM_H_

//=======================================================
//INCLUDES
//=======================================================
#include "MK22F51212.h"

//=======================================================
// DEFINES
//=======================================================
#define CORECLOCK                  120000000  // 120 MHZ (CPU, UART0, UART1)
#define BUSCLOCK                    60000000  // 60 MHz
#define FIXED_SYSTEM_CLOCK            250000  // 250 kHz

//=======================================================
// FUNCTION DECLARATIONS
//=======================================================
// This function disables interrupts and prevents them from
// being fired right after they have been disabled. This is
// done with with the dsb and isb assembler instructions.
//-------------------------------------------------------
__STATIC_INLINE void NVIC_DisableIRQEx(IRQn_Type IRQn)
{
  NVIC_DisableIRQ(IRQn);
  __asm volatile("dsb");   // data synchronization barrier
  __asm volatile("isb");   // instruction synchronization barrier
}
//-------------------------------------------------------

#endif /*PLATFORM_H_*/

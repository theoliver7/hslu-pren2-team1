/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         driver for the serial communication (uart1 tinyk22)
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          10.03.2020
 *
 *--------------------------------------------------------------------
 */
#include <stdbool.h>
#include "com/uart.h"
#include "platform.h"

/**
 * the receive queue of this driver, implemented as ring buffer
 */
static char rxBuf[UART1_RX_BUF_SIZE];
static volatile uint16_t rxBufCount;
static uint16_t rxBufWritePos;
static uint16_t rxBufReadPos;

/**
 * the transmit queue of this driver, implemented as ring buffer
 */
static char txBuf[UART1_TX_BUF_SIZE];
static volatile uint16_t txBufCount;
static uint16_t txBufWritePos;
static uint16_t txBufReadPos;

/**
 * @brief UART Interrupt Service Routine
 * - Received bytes are stored in the queue rxBuf
 * - Bytes in the queue txBuf are sent
 */
void UART1_RX_TX_IRQHandler(void) {
	uint8_t status = UART1->S1;
	uint8_t data_in = UART1->D;
	if (status & UART_S1_RDRF_MASK) {
		// store the received byte into receiver Queue (rxBuf)
		// but only if the queue isn't full!
		if (rxBufCount < UART1_RX_BUF_SIZE) {
			rxBuf[rxBufWritePos++] = data_in;
			rxBufCount++;
			if (rxBufWritePos == UART1_RX_BUF_SIZE)
				rxBufWritePos = 0;
		}
	}

	if (status & UART_S1_TDRE_MASK) {
		if (txBufCount > 0) {
			UART1->D = txBuf[txBufReadPos++];
			txBufCount--;
			if (txBufReadPos == UART1_TX_BUF_SIZE)
				txBufReadPos = 0;
		} else {
			UART1->C2 &= ~UART_C2_TIE_MASK;
		}
	}
}

/**
 * Error Interrupt Service Routine
 * Clears the error flags.
 */
void UART1_ERR_IRQHandler(void) {
	(void) UART1->S1;
	(void) UART1->D;
}

/**
 * Writes one Byte in the transmit buffer.
 *
 * @details
 *   Switching on the TIE interrupt causes an interrupt to be
 *   triggered immediately. The function blocks until there is
 *   space in the txBuf queue.
 *
 * @param[in] ch
 *   the byte to send
 */
void uart1WriteChar(char ch) {
	while (txBufCount >= UART1_TX_BUF_SIZE)
		;
	txBuf[txBufWritePos++] = ch;
	if (txBufWritePos == UART1_TX_BUF_SIZE)
		txBufWritePos = 0;
	NVIC_DisableIRQEx(UART1_RX_TX_IRQn);
	txBufCount++;
	NVIC_EnableIRQ(UART1_RX_TX_IRQn);
	UART1->C2 |= UART_C2_TIE_MASK;
}


void uart1WriteCommand(const char *str) {
	if (str == NULL)
		return;
	for (int i = 0; i < 6; i++) {
		uart1WriteChar(*str++);
	}
	uart1WriteChar(NEW_LINE);
}

/**
 * Writes a null terminated string in the send buffer. If the
 * string is null, the function returns immediately.
 *
 * @param[in] str
 *   the null terminated string to send
 */
void uart1Write(const char *str) {
	if (str == NULL)
		return;
	while (*str != '\0')
		uart1WriteChar(*str++);
}

/**
 * Writes a null terminated string in the send buffer. If the
 * string is null, only a new new line character is sent.
 *
 * @param[in] str
 *   the null terminated string to send
 */
void uart1WriteLine(const char *str) {
	uart1Write(str);
	uart1WriteChar(NEW_LINE);
}

/**
 * Reads one char out of the rxBuf queue. The function blocks
 * until there is at least one byte in the queue.
 *
 * @return
 *   the received byte
 */
char uart1ReadChar(void) {
	char ch;
	while (rxBufCount == 0)
		;
	// Angepasst von MWI
	ch = rxBuf[rxBufReadPos];
	rxBuf[rxBufReadPos] = 0;
	rxBufReadPos++;
	//
	if (rxBufReadPos == UART1_RX_BUF_SIZE)
		rxBufReadPos = 0;
	NVIC_DisableIRQEx(UART1_RX_TX_IRQn);
	rxBufCount--;
	NVIC_EnableIRQ(UART1_RX_TX_IRQn);
	return ch;
}

/**
 * Reads a null terminated string out of the rxBuf queue. The
 * function blocks until a new Line character has been received
 * or the length has been exceeded.
 *
 * @details
 *   the new line character will be replaced with a '\0' to
 *   terminate the string.
 *
 * @param[out] *str
 *   pointer to a char array to store the received string
 * @param[in] length
 *   the length of the str char array.
 * @returns
 *   the length of the received string.
 */
uint16_t uart1ReadLine(char *str, uint16_t length) {
	uint16_t i;
	// in der for-Schlaufe i=1 auf i=0 angepasst
	for (i = 0; i < length; i++) {
		*str = uart1ReadChar();
		if (*str == NEW_LINE) {
			*str = '\0';
			break;
		}
		str++;
	}
	return i;
}

/**
 * This functions checks, if there is a new line character
 * in the rxBuf queue.
 *
 * @returns
 *   true, if there is a new line character, otherweise false.
 */
bool uart1HasLineReceived(void) {
	uint16_t i;
	uint16_t index = rxBufReadPos;

	for (i = 0; i < rxBufCount; i++) {
		if (rxBuf[index++] == NEW_LINE)
			return true;
		if (index == UART1_RX_BUF_SIZE)
			index = 0;
	}
	return false;
}

/**
 * \fn uint16_t uart1RxBufCount(void)
 * Returns the number of bytes in the receiver queue.
 *
 * @returns
 *   the number of bytes in the receiver queue.
 */
uint16_t uart1RxBufCount(void) {
	return rxBufCount;
}

/**
 *   tinyK22:
 *   - PTC3 Mux3:UART1_RX
 *   - PTC4 Mux3:UART1_TX
 */

void uart1Init(uint32_t baudrate) {
	txBufReadPos = txBufWritePos = txBufCount = 0;
	rxBufReadPos = rxBufWritePos = rxBufCount = 0;

	//configure clock
	//gating (Kinetis Reference Manual p277) KRM277
	SIM->SCGC5 |= SIM_SCGC5_PORTC(1);
	SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;

	// configure port multiplexing, enable Pull-Ups and enable OpenDrain (ODE)!
	// OpenDrain is needed to ensure that no current flows from Target-uC to the Debugger-uC

	PORTC->PCR[3] = PORT_PCR_MUX(
			3) | PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_ODE_MASK;
	PORTC->PCR[4] = PORT_PCR_MUX(
			3) | PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_ODE_MASK;

	// set the baudrate into the BDH (first) and BDL (second) register. KRM1215ff
	uint32_t bd = (CORECLOCK / (16 * baudrate));
	UART1->BDH = (bd >> 8) & 0x1F;
	UART1->BDL = bd & 0xFF;

	// enable uart receiver, receiver interrupt and transmitter as well as
	// enable and set the rx/tx interrupt in the nested vector interrupt controller (NVIC)
	UART1->C2 = UART_C2_RIE_MASK | UART_C2_RE_MASK | UART_C2_TE_MASK;
	NVIC_SetPriority(UART1_RX_TX_IRQn, PRIO_UART1);
	NVIC_EnableIRQ(UART1_RX_TX_IRQn);

	// enable the error interrupts of the uart and configure the NVIC
	UART1->C3 = UART_C3_ORIE_MASK | UART_C3_NEIE_MASK | UART_C3_FEIE_MASK;
	NVIC_SetPriority(UART1_ERR_IRQn, PRIO_UART1);
	NVIC_EnableIRQ(UART1_ERR_IRQn);
}


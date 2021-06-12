/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         driver for the serial communication (uart)
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          10.03.2020
 *
 *--------------------------------------------------------------------
 */
// TODO seperate into uart.h and uart_config.h

#include <stdint.h>
#include <stdbool.h>

#define NEW_LINE                '\n'
#define NULL                     ((void *)0)

//#define UART1_EN                  1     // [0|1] 1=>enable, 0=>disable
#define UART1_BAUDRATE          57600
#define PRIO_UART1     			8	  	// [0..15] set interrupt priority: 0=max Prio
#define UART1_RX_BUF_SIZE       512     // size of the receive buffer in bytes
#define UART1_TX_BUF_SIZE       512     // size of the transmit buffer in bytes

void uart1WriteChar(char ch);
void uart1Write(const char *str);
void uart1WriteLine(const char *str);
void uart1WriteCommand(const char *str);
char uart1ReadChar(void);
uint16_t uart1ReadLine(char *str, uint16_t length);
bool uart1HasLineReceived(void);
uint16_t uart1RxBufCount(void);
void uart1Init(uint32_t baudrate);


/*
#define UART0_EN                  1     // [0|1] 1=>enable, 0=>disable
#define UART0_PRINTF_EN           0     // [0|1] redirect printf to uart 0
#define UART0_SCANF_EN            0     // [0|1] redirect scanf to uart 0
#define UART0_RX_BUF_SIZE       512     // size of the receive buffer in bytes
#define UART0_TX_BUF_SIZE       512     // size of the transmit buffer in bytes



#define LPUART0_EN                0     // [0|1] 1=>enable, 0=>disable
#define LPUART0_PRINTF_EN         0     // [0|1] redirect printf to uart 0
#define LPUART0_SCANF_EN          0     // [0|1] redirect scanf to uart 0
#define LPUART0_RX_BUF_SIZE     512     // size of the receive buffer in bytes
#define LPUART0_TX_BUF_SIZE     512     // size of the transmit buffer in bytes


#if ((PLATFORM & TINYK22) == 0)
#undef UART1_EN
#endif

#if ((PLATFORM & MC_CAR) == 0)
#undef UART0_EN
#undef LPUART0_EN
#endif


void uart0WriteChar(char ch);
void uart0Write(const char *str);
void uart0WriteLine(const char *str);
char uart0ReadChar(void);
uint16_t uart0ReadLine(char *str, uint16_t length);
bool uart0HasLineReceived(void);
uint16_t uart0RxBufCount(void);
void uart0Init(uint16_t baudrate);


void lpuart0WriteChar(char ch);
void lpuart0Write(const char *str);
void lpuart0WriteLine(const char *str);
char lpuart0ReadChar(void);
uint16_t lpuart0ReadLine(char *str, uint16_t length);
bool lpuart0HasLineReceived(void);
uint16_t lpuart0RxBufCount(void);
void lpuart0Init(uint16_t baudrate);

*/






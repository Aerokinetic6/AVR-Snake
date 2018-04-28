#ifndef __UART_H_
#define __UART_H_

#include <avr/io.h>

#define UART0_DDR	DDRE
#define UART0_PORT	PORTE
#define UART0_TX	PE1
#define UART0_RX	PE0

#define UART1_DDR	DDRD
#define UART1_PORT	PORTD
#define UART1_TX	PD3
#define UART1_RX	PD2

void Uartinit();
unsigned char UartReadByte();

#endif

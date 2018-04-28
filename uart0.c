#define F_CPU (16000000UL)
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD-1)



void Uartinit(){

UART0_DDR |= (1<<UART0_TX);
UART0_DDR &= ~(1<<UART0_RX);

UBRR0H= (unsigned char) (MYUBRR>>8);
UBRR0L= (unsigned char) (MYUBRR);

UCSR0A=0;

UCSR0B|= ((1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0)); //!!!! RXCIE !!!!!
UCSR0C=((1<<USBS0)|(3<<UCSZ00));

}


void UartSendByte (unsigned char byte)

{

while(!(UCSR0A&(1<<UDRE0)));
UDR0=byte;

}


unsigned char UartReadByte()
{

while(!(UCSR0A&(1<<RXC0)));
return UDR0;
}

void UartSendString(unsigned char *p)
{

	while(*p){UartSendByte(*p); p++;}


}



void UartSendInt(unsigned int i)
{

	UartSendByte('0'+i/100000%10);
	UartSendByte('0'+i/10000%10);
	UartSendByte('0'+i/1000%10);
	UartSendByte('0'+i/100%10);
	UartSendByte('0'+i/10%10);
	UartSendByte('0'+i%10);




}

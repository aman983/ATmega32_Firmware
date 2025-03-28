#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "UART.h"

void UART_INIT(UART_CONFIG C){
	DDRD |= (1 << 2);
	PORTD &= ~(1 << 2);
	
	UCSRA = 0x00;
	UCSRB |= (1 << 3) | (1 << 4);
	UCSRC |= (1 << 2) | (1 << 3);
	
	UBRRH = 0x00;
	UBRRL = C; // baud 9600
}

void UART_SEND(char *STR){
	while(*STR){
		UDR = *STR;
		while((UCSRA & 0x40) == 0);
		_delay_ms(1);
		STR++;
	}
}

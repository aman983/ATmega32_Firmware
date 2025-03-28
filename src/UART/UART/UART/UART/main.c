#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "UART.h"

int main(void)
{
	char buffer[20];
	int val = 10;
    UART_INIT(SET_BAUD_9600);
	sprintf(buffer, "HELLO WORLD %d\n", val);
    while (1) 
    {
		UART_SEND(buffer);
		_delay_ms(100);
    }
}


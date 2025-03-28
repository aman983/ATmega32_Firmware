#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "UART.h"
#include "HCSR04.h"

int main(void)
{
	char buffer[20];
	UART_INIT(SET_BAUD_9600);
    HC_SR04_INIT();
	
	while (1) 
    {
		sprintf(buffer, "D = %d\n", GET_DISTANCE());
		UART_SEND(buffer);
		_delay_ms(100);
    }
}


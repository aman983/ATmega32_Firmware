#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"

int main(void)
{
	uint8_t number = 255;
	char s[10];
	char *text = "Hello World";
	LCD_INIT();
	DISPLAY(CLEAR);
	DISPLAY(SET_CURSOR_POS_10);
	WR_INT(number,s);
	DISPLAY(SET_CURSOR_POS_00);
    while (1) 
    {	
		SCROLL_TEXT(text);
		_delay_ms(500);
    }
	return 0;
}



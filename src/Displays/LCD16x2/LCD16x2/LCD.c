#define  F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"

#define EN (1 << 5)
#define RW (1 << 6)
#define RS (1 << 7)

void send_cmd(char command){
	PORTD &= ~(RS | RW);
	PORTC = command;
	PORTD |= EN;
	
	_delay_ms(10);
	PORTD &= ~EN;
}

void send_data(char data){
	PORTD |= RS;
	PORTD &= ~RW;
	
	PORTC = data;
	
	PORTD |= EN;
	_delay_ms(10);
	PORTD &= ~EN;
}

void int_to_str(uint8_t num, char *STR){
	if(num == 0){
		STR[0] = '0';
		STR[1] = '\0';
		return;
	}
	int i=0;
	while(num>0){
		STR[i++] = num%10 + '0';
		num /= 10;
	}
	STR[i] = '\0';
	
	int j=0;
	i--;
	while(j < i){
		char temp = STR[j];
		STR[j] = STR[i];
		STR[i] = temp;
		j++;
		i--;
	}
}

void WR_STR(char *STR){
	while(*STR){
		send_data(*STR);
		STR++;
	}
}

void WR_CHR(char C){
	send_data(C);
}

void WR_INT(uint8_t num, char *STR){
	int_to_str(num, STR);
	WR_STR(STR);
}

void DISPLAY(DISPLAY_SETTINGS settings){
	send_cmd(settings);
	_delay_ms(2);
}

void LCD_INIT(void){
	// Setup Data Port for LCD
	DDRC = 0xFF;
	PORTD = 0x00;
	
	// Setup control BUS for LCD
	DDRD = EN | RS | RW;
	PORTD &= ~(EN | RS | RW);
	send_cmd(0x38);
	send_cmd(0x0C);
	DISPLAY(CLEAR);
	send_cmd(0x06);
}

void SCROLL_TEXT(char *STR){
	char *str_cpy = STR;
	uint8_t str_len = 0;
	while(*str_cpy != '\0'){
		str_cpy++;
		str_len++;
	}
	
	DISPLAY(SET_CURSOR_POS_00);
	for(int i=0; i<str_len; i++){
		WR_CHR(STR[i]);
	}
	
	for(uint8_t i=0; i<str_len + 16; i++){
		_delay_ms(200);
		DISPLAY(DISPLAY_SHIFT_LEFT);
	}
	DISPLAY(SET_CURSOR_POS_00);
}
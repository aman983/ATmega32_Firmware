
#ifndef LCD_H_
#define LCD_H_

typedef enum {
	CLEAR					= 0x01,
	CURSOR_RET				= 0x02,
	CURSOR_SHIFT_LEFT		= 0x04,
	CURSOR_SHIFT_RIGHT		= 0x06,
	CUR_OFF_BLINK_OFF		= 0x0C,
	CUR_ON_BLINK_OFF		= 0x0E,
	CUR_ON_BLINK_ON			= 0x0F,
	DISPLAY_SHIFT_RIGHT		= 0x1C,
	DISPLAY_SHIFT_LEFT		= 0x18,
	SET_CURSOR_POS_00		= 0x80,
	SET_CURSOR_POS_16		= 0x8F,
	SET_CURSOR_POS_10		= 0xC0,
	}DISPLAY_SETTINGS;


void LCD_INIT(void);

void send_cmd(char command);
void send_data(char data);
void int_to_str(uint8_t num, char *STR);

void WR_INT(uint8_t num, char *STR);
void CLR_SCR(void);
void WR_STR(char *STR);
void WR_CHR(char C);
void DISPLAY(DISPLAY_SETTINGS settings);
void SCROLL_TEXT(char *STR);
#endif /* 16X2_H_ */
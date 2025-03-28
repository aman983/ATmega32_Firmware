#ifndef UART_H_
#define UART_H_

typedef enum {
	SET_BAUD_2400	= 0xCF,
	SET_BAUD_4800	= 0x67,
	SET_BAUD_9600	= 0x33,
	SET_BAUD_19200	= 0x19,
	SET_BAUD_38400	= 0x0C,
	}UART_CONFIG;

void UART_INIT(UART_CONFIG C);
void UART_SEND(char *STR);


#endif /* UART_H_ */
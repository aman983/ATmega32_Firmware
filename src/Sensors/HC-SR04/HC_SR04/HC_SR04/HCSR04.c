#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "HCSR04.h"

void HC_SR04_INIT(){
	// Set trigger pin as output
	DDRA |= (1 << 1);
	// Set echo pin as input
	DDRA &= ~(1 << 0);
	
	// Ensure trigger pin is low initially
	PORTA &= ~(1 << 1);
}

uint8_t GET_DISTANCE(){
	_delay_ms(60);  // Wait for sensor to stabilize
	uint8_t signal_time = 0;
	
	// Sending pulse to the trigger pin
	PORTA |= (1 << 1);  // Set trigger pin high
	_delay_us(10);       // Wait for 10 microseconds
	PORTA &= ~(1 << 1);  // Set trigger pin low
	
	// Wait for echo pin to go high (indicating pulse start)
	while (!(PINA & (1 << 0)));
	
	// Measure pulse width using Timer1 (16-bit timer for higher precision)
	TCNT1 = 0;  // Reset timer count
	TCCR1B |= (1 << CS11);  // Set prescaler to 8 (for microsecond resolution)
	
	// Wait for the echo pin to go low (indicating pulse end)
	while (PINA & (1 << 0));
	
	// Stop the timer
	TCCR1B &= ~(1 << CS11);
	
	// The timer count now holds the pulse width in timer ticks
	signal_time = TCNT1;
	
	// Convert the time to distance (in cm) if necessary
	// signal_time is in microseconds, and you can use the formula:
	// distance = (signal_time * speed_of_sound) / 2
	// Where speed_of_sound = 343 m/s = 0.0343 cm/us
	
	return (signal_time * 0.0343) / 2;  // Return pulse duration (in timer ticks)
}

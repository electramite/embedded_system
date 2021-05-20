/*
 * led_blink_with_interrupts.c
 *
 * Created: 20-05-2021 21:34:36
 * Author : electramite
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void in_init(){
	cli();
	DDRB = 0x01;
	PORTB = 0x00;
	TCCR0A |= (1 << WGM01);
	TCCR0B |= ((1 << CS02) | (1 << CS00)); // 
	OCR0A = 255;
	TIMSK0 |= (1 << OCIE0A);
	sei();
}

int main(void)
{	in_init();
	while(1);
}

ISR(TIMER0_COMPA_vect){
	PORTB |= 0x01;
	_delay_ms(1000);
	PORTB = 0x00;
	_delay_ms(1000);
}


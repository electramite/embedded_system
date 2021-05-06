/*
 * firebird_simulation.h
 *
 * Created: 2/15/2020 17:14:54
 * Author: e-Yantra Team
 */ 


#ifndef FIREBIRD_SIMULATION_H_
#define FIREBIRD_SIMULATION_H_


#include <avr/io.h>									// Standard AVR IO Library


// Definitions for ATmega2560 micro-controller on Firebird V robot
#if defined(__AVR_ATmega2560__)

	#define F_CPU						14745600

	#define buzzer_ddr_reg				DDRC
	#define buzzer_port_reg				PORTC
	#define buzzer_pin					3			// PC3

	#define interrupt_sw_ddr_reg		DDRE
	#define interrupt_sw_port_reg		PORTE
	#define interrupt_sw_pin_reg		PINE
	#define interrupt_sw_pin			7			// PE7
	
	#define bar_graph_led_ddr_reg		DDRJ
	#define bar_graph_led_port_reg		PORTJ
	#define bar_graph_led_2_pin			1			// PJ1
	#define bar_graph_led_8_pin			7			// PJ7
	#define bar_graph_led_6_pin			5			// PJ5

	#define lcd_data_ddr_reg			DDRC
	#define lcd_control_ddr_reg			DDRC

	#define lcd_data_port_reg			PORTC
	#define lcd_control_port_reg		PORTC

	#define RS_pin						0			// PC0
	#define RW_pin						1			// PC1
	#define EN_pin						2			// PC2

	#define DB7_pin						7			// PC7
	#define DB6_pin						6			// PC6
	#define DB5_pin						5			// PC5
	#define DB4_pin						4			// PC4

#endif


// Definitions for ATmega328P micro-controller for sample projects in Proteus Demonstration
#if defined(__AVR_ATmega328P__)
	
	#define F_CPU						16000000

	#define buzzer_ddr_reg				DDRD
	#define buzzer_port_reg				PORTD
	#define buzzer_pin					6			// PD6	( IO6 )

	#define interrupt_sw_ddr_reg		DDRD
	#define interrupt_sw_port_reg		PORTD
	#define interrupt_sw_pin_reg		PIND
	#define interrupt_sw_pin			2			// PD2	( IO2 )
	
	#define bar_graph_led_ddr_reg		DDRB
	#define bar_graph_led_port_reg		PORTB
	#define bar_graph_led_2_pin			1			// PB1	( IO9 )
	#define bar_graph_led_8_pin			0			// PB0	( IO8 )
	#define bar_graph_led_6_pin			5			// PB5	( IO13 )

	#define lcd_data_ddr_reg			DDRD
	#define lcd_control_ddr_reg			DDRB

	#define lcd_data_port_reg			PORTD
	#define lcd_control_port_reg		PORTB

	#define RS_pin						0			// PB0	( IO8 )
	#define RW_pin						2			// PB2	( IO10 )
	#define EN_pin						1			// PB1	( IO9 )

	#define DB7_pin						7			// PD7	( IO7 )
	#define DB6_pin						6			// PD6	( IO6 )
	#define DB5_pin						5			// PD5	( IO5 )
	#define DB4_pin						4			// PD4	( IO4 )

#endif


#endif /* FIREBIRD_SIMULATION_H_ */
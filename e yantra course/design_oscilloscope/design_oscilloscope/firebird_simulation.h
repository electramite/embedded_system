/*
 * firebird_simulation.h
 *
 * Created: 2/15/2020 17:14:54
 * Author: e-Yantra Team
 */ 


#ifndef FIREBIRD_SIMULATION_H_
#define FIREBIRD_SIMULATION_H_


#include <avr/io.h>									// Standard AVR IO Library
#include <avr/interrupt.h>                          // Standard AVR Interrupt Library


// Definitions for ATmega2560 micro-controller on Arduino Mega
#define F_CPU 						    16000000

#define div_hold_switch_ddr_reg       	DDRD		// DIV+, DIV- and HOLD switch data dir register
#define div_hold_switch_port_reg		PORTD		// DIV+, DIV- and HOLD switch port register
#define div_hold_switch_pin_reg			PIND		// DIV+, DIV- and HOLD switch pin register

#define div_add_sw_pin  				PD1
#define div_add_sw_pin_int       		INT1
#define div_add_sw_pin_int_vect 		INT1_vect

#define div_sub_sw_pin  				PD2
#define div_sub_sw_pin_int 				INT2
#define div_sub_sw_pin_int_vect			INT2_vect

#define hold_sw_pin 					PD3
#define hold_sw_pin_int 				INT3
#define hold_sw_pin_int_vect 			INT3_vect

#define up_down_switch_ddr_reg			DDRE		// UP and DOWN switch data dir register
#define up_down_switch_port_reg 		PORTE		// UP and DOWN switch port register
#define up_down_switch_pin_reg 		    PINE		// UP and DOWN switch pin register

#define up_sw_pin                       PE4
#define up_sw_pin_int    				INT4
#define up_sw_pin_int_vect              INT4_vect

#define down_sw_pin                     PE5
#define down_sw_pin_int 				INT5
#define down_sw_pin_int_vect            INT5_vect

#define EIMSK_reg						EIMSK
#define EICRA_reg                       EICRA
#define EICRB_reg						EICRB

#define div_add_sw_ISC_bit1     		ISC11
#define div_add_sw_ISC_bit0	        	ISC10

#define div_sub_sw_ISC_bit1     		ISC21
#define div_sub_sw_ISC_bit0	        	ISC20

#define hold_sw_ISC_bit1         		ISC31
#define hold_sw_ISC_bit0	        	ISC30

#define up_sw_ISC_bit1           		ISC41
#define up_sw_ISC_bit0	        	    ISC40

#define down_sw_ISC_bit1         		ISC51
#define down_sw_ISC_bit0	        	ISC50

#define dso_input_channel_ddr_reg       DDRK
#define dso_input_channel_port_reg      PORTK
#define dso_input_channel_pin           PK0         // DSO Input ADC channel (Arduino Mega : A0 pin)

// Bits of ADCSRA register
#define		ADCSRA_reg					ADCSRA 		// ADCSRA register
#define		ADEN_bit					ADEN		// 7	( ADC Enable bit )
#define		ADSC_bit					ADSC		// 6	( ADC Start Conversion bit )
#define		ADATE_bit					ADATE		// 5	( ADC Auto Trigger Enable bit )
#define		ADIF_bit					ADIF		// 4	( ADC Interrupt Flag bit )
#define		ADIE_bit					ADIE		// 3	( ADC Interrupt Enable bit )
#define		ADPS2_bit					ADPS2		// 2	( ADC Pre-scalar bit 2 )
#define		ADPS1_bit					ADPS1		// 1	( ADC Pre-scalar bit 1 )
#define		ADPS0_bit					ADPS0		// 0	( ADC Pre-scalar bit 0 )

// Bits of ADCSRB register
#define		ADCSRB_reg					ADCSRB 		// ADCSRB register
#define		ACME_bit					ACME		// 6	( Analog Comparator Multiplexer Enable bit )
#define		MUX5_bit					MUX5		// 3	( ADC Channel Selection bit 5 )
#define		ADTS2_bit					ADTS2		// 2	( ADC Auto Trigger Source bit 2 )
#define		ADTS1_bit					ADTS1		// 1	( ADC Auto Trigger Source bit 1 )
#define		ADTS0_bit					ADTS0		// 0	( ADC Auto Trigger Source bit 0 )

// Bits of ADMUX register
#define		ADMUX_reg					ADMUX		// ADMUX register
#define		REFS1_bit					REFS1		// 7	( Reference Selection bit 1 )
#define		REFS0_bit					REFS0		// 6	( Reference Selection bit 0 )
#define		ADLAR_bit					ADLAR		// 5	( ADC Left Result bit )
#define		MUX4_bit					MUX4		// 4	( ADC Channel Selection bit 4 )
#define		MUX3_bit					MUX3		// 3	( ADC Channel Selection bit 3 )
#define		MUX2_bit					MUX2		// 2	( ADC Channel Selection bit 2 )
#define		MUX1_bit					MUX1		// 1	( ADC Channel Selection bit 1 )
#define		MUX0_bit					MUX0		// 0	( ADC Channel Selection bit 0 )

// Bits of ACSR register
#define		ACSR_reg					ACSR		// ACSR register
#define		ACD_bit						ACD			// 7	( Analog Comparator Disable bit )

// ADC Data registersff
#define		ADCH_reg					ADCH		// ADC High Byte Data register
#define		ADCL_reg					ADCL		// ADC Low Byte Data register

#endif /* FIREBIRD_SIMULATION_H_ */
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

	#define		F_CPU							14745600
	
	// Buzzer definitions
	#define		buzzer_ddr_reg					DDRC
	#define		buzzer_port_reg					PORTC
	#define		buzzer_pin						3			// PC3
	
	// Interrupt Switch definitions
	#define		interrupt_sw_ddr_reg			DDRE
	#define		interrupt_sw_port_reg			PORTE
	#define		interrupt_sw_pin_reg			PINE
	#define		interrupt_sw_pin				7			// PE7
	
	// Bar-graph LED definitions	
	#define		bar_graph_led_ddr_reg			DDRJ
	#define		bar_graph_led_port_reg			PORTJ
	#define		bar_graph_led_2_pin				1			// PJ1
	#define		bar_graph_led_8_pin				7			// PJ7
	#define		bar_graph_led_6_pin				5			// PJ5
	
	// LCD definitions
	#define		lcd_data_ddr_reg				DDRC
	#define		lcd_control_ddr_reg				DDRC

	#define		lcd_data_port_reg				PORTC
	#define		lcd_control_port_reg			PORTC

	#define		RS_pin							0			// PC0
	#define		RW_pin							1			// PC1
	#define		EN_pin							2			// PC2

	#define		DB7_pin							7			// PC7
	#define		DB6_pin							6			// PC6
	#define		DB5_pin							5			// PC5
	#define		DB4_pin							4			// PC4
	
	// 3 White-Line sensors definitions
	#define		wl_sensors_ddr_reg				DDRF
	#define		wl_sensors_port_reg				PORTF
	#define		left_wl_sensor_pin				3			// PF3
	#define		left_wl_sensor_channel			3			// ADC3 - ADC Channel 3
	#define		center_wl_sensor_pin			2			// PF2
	#define		center_wl_sensor_channel		2			// ADC2 - ADC Channel 2
	#define		right_wl_sensor_pin				1			// PF1
	#define		right_wl_sensor_channel			1			// ADC1 - ADC Channel 1
	
	// 3rd and 4th IR proximity sensor definitions
	#define		ir_prox_3_4_sensors_ddr_reg		DDRF
	#define		ir_prox_3_4_sensors_port_reg	PORTF
	#define		ir_prox_3_sensor_pin			6			// PF6
	#define		ir_prox_3_sensor_channel		6			// ADC6 - ADC Channel 6
	#define		ir_prox_4_sensor_pin			7			// PF7
	#define		ir_prox_4_sensor_channel		7			// ADC7 - ADC Channel 7
	
	// 5th IR proximity sensor definitions
	#define		ir_prox_5_sensor_ddr_reg		DDRK
	#define		ir_prox_5_sensor_port_reg		PORTK
	#define		ir_prox_5_sensor_pin			0			// PK0
	#define		ir_prox_5_sensor_channel		8			// ADC8 - ADC Channel 8
	
	// 2nd Sharp sensor definitions
	#define		sharp_sensor_ddr_reg			DDRK
	#define		sharp_sensor_port_reg			PORTK
	#define		sharp_sensor_pin				2			// PK2
	#define		sharp_sensor_channel			10			// ADC10 - ADC Channel 10
	
	// Bits of ADCSRA register
	#define		ADCSRA_reg						ADCSRA 		// ADCSRA register
	#define		ADEN_bit						ADEN		// 7	( ADC Enable bit )
	#define		ADSC_bit						ADSC		// 6	( ADC Start Conversion bit )
	#define		ADATE_bit						ADATE		// 5	( ADC Auto Trigger Enable bit )
	#define		ADIF_bit						ADIF		// 4	( ADC Interrupt Flag bit )
	#define		ADIE_bit						ADIE		// 3	( ADC Interrupt Enable bit )
	#define		ADPS2_bit						ADPS2		// 2	( ADC Pre-scalar bit 2 )
	#define		ADPS1_bit						ADPS1		// 1	( ADC Pre-scalar bit 1 )
	#define		ADPS0_bit						ADPS0		// 0	( ADC Pre-scalar bit 0 )
	
	// Bits of ADCSRB register
	#define		ADCSRB_reg						ADCSRB 		// ADCSRB register
	#define		ACME_bit						ACME		// 6	( Analog Comparator Multiplexer Enable bit )
	#define		MUX5_bit						MUX5		// 3	( ADC Channel Selection bit 5 )
	#define		ADTS2_bit						ADTS2		// 2	( ADC Auto Trigger Source bit 2 )
	#define		ADTS1_bit						ADTS1		// 1	( ADC Auto Trigger Source bit 1 )
	#define		ADTS0_bit						ADTS0		// 0	( ADC Auto Trigger Source bit 0 )
	
	// Bits of ADMUX register
	#define		ADMUX_reg						ADMUX		// ADMUX register
	#define		REFS1_bit						REFS1		// 7	( Reference Selection bit 1 )
	#define		REFS0_bit						REFS0		// 6	( Reference Selection bit 0 )
	#define		ADLAR_bit						ADLAR		// 5	( ADC Left Result bit )
	#define		MUX4_bit						MUX4		// 4	( ADC Channel Selection bit 4 )
	#define		MUX3_bit						MUX3		// 3	( ADC Channel Selection bit 3 )
	#define		MUX2_bit						MUX2		// 2	( ADC Channel Selection bit 2 )
	#define		MUX1_bit						MUX1		// 1	( ADC Channel Selection bit 1 )
	#define		MUX0_bit						MUX0		// 0	( ADC Channel Selection bit 0 )
	
	// Bits of ACSR register
	#define		ACSR_reg						ACSR		// ACSR register
	#define		ACD_bit							ACD			// 7	( Analog Comparator Disable bit )
	
	// ADC Data registers
	#define		ADCH_reg						ADCH		// ADC High Byte Data register
	#define		ADCL_reg						ADCL		// ADC Low Byte Data register
	
	#define		BAUD_RATE						9600		// Baud rate setting
	
	// Calculate UBRR value for Baud Rate setting according to the F_CPU value
	#define		UBRR_VALUE						( ( ( F_CPU / 16 ) / BAUD_RATE ) - 1 )
	
	// USART2 Data register
	#define		UDR_reg							UDR2		// USART2 Data register
	
	// Bits of UCSR1A register
	#define		UCSRA_reg						UCSR2A		// UCSR2A register
	#define		TXC_bit							TXC2		// 6	( Transmit Complete Flag bit for UART2 )
	#define		UDRE_bit						UDRE2		// 5	( Data Register Empty Flag bit for UART2 )
	#define		U2X_bit							U2X2		// 1	( Double USART Transmission Speed bit for UART2 )
	
	// Bits of UCSR2B register
	#define		UCSRB_reg						UCSR2B		// UCSR2B register
	#define		RXCIE_bit						RXCIE2		// 7	( RX Complete Interrupt Enable bit for UART2 )
	#define		TXCIE_bit						TXCIE2		// 6	( TX Complete Interrupt Enable bit for UART2 )
	#define		UDRIE_bit						UDRIE2		// 5	( USART Data Register Empty Interrupt Enable bit for UART2 )
	#define		RXEN_bit						RXEN2		// 4	( Receiver Enable bit for UART2 )
	#define		TXEN_bit						TXEN2		// 3	( Transmitter Enable bit for UART2 )
	#define		UCSZ2_bit						UCSZ22		// 2	( Character Size selection bit 2 for UART2 )
	
	// Bits of UCSR2C register
	#define		UCSRC_reg						UCSR2C		// UCSR2C register
	#define		UMSEL1_bit						UMSEL21		// 7	( USART Mode Select bit 1 for UART2 )
	#define		UMSEL0_bit						UMSEL20		// 6	( USART Mode Select bit 0 for UART2 )
	#define		UPM1_bit						UPM21		// 5	( Parity Mode Select bit 1 for UART2 )
	#define		UPM0_bit						UPM20		// 4	( Parity Mode Select bit 0 for UART2 )
	#define		USBS_bit						USBS2		// 3	( Stop Bits Select bit for UART2 )
	#define		UCSZ1_bit						UCSZ21		// 2	( Character Size selection bit 1 for UART2 )
	#define		UCSZ0_bit						UCSZ20		// 1	( Character Size selection bit 0 for UART2 )
	#define		UCPOL_bit						UCPOL2		// 0	( Clock Polarity Select bit for UART2 )
	
	// USART2 Baud Rate registers
	#define		UBRRH_reg						UBRR2H		// USART2 High Byte Baud Rate register
	#define		UBRRL_reg						UBRR2L		// USART2 Low Byte Baud Rate register

#endif


// Definitions for ATmega328P micro-controller for sample projects in Proteus Demonstration
#if defined(__AVR_ATmega328P__)
	
	#define		F_CPU							16000000

	#define		buzzer_ddr_reg					DDRD
	#define		buzzer_port_reg					PORTD
	#define		buzzer_pin						6			// PD6	( IO6 )

	#define		interrupt_sw_ddr_reg			DDRD
	#define		interrupt_sw_port_reg			PORTD
	#define		interrupt_sw_pin_reg			PIND
	#define		interrupt_sw_pin				2			// PD2	( IO2 )
	
	#define		bar_graph_led_ddr_reg			DDRB
	#define		bar_graph_led_port_reg			PORTB
	#define		bar_graph_led_2_pin				1			// PB1	( IO9 )
	#define		bar_graph_led_8_pin				0			// PB0	( IO8 )
	#define		bar_graph_led_6_pin				5			// PB5	( IO13 )

	#define		lcd_data_ddr_reg				DDRD
	#define		lcd_control_ddr_reg				DDRB

	#define		lcd_data_port_reg				PORTD
	#define		lcd_control_port_reg			PORTB

	#define		RS_pin							0			// PB0	( IO8 )
	#define		RW_pin							2			// PB2	( IO10 )
	#define		EN_pin							1			// PB1	( IO9 )

	#define		DB7_pin							7			// PD7	( IO7 )
	#define		DB6_pin							6			// PD6	( IO6 )
	#define		DB5_pin							5			// PD5	( IO5 )
	#define		DB4_pin							4			// PD4	( IO4 )
	
	// 3 White-Line sensors definitions
	#define		wl_sensors_ddr_reg				DDRC
	#define		wl_sensors_port_reg				PORTC
	#define		left_wl_sensor_pin				1			// PC1	( AD1 / IO15 )
	#define		left_wl_sensor_channel			1			// ADC1 - ADC Channel 1
	#define		center_wl_sensor_pin			0			// PC0	( AD0 / IO14 )
	#define		center_wl_sensor_channel		0			// ADC0 - ADC Channel 0
	#define		right_wl_sensor_pin				2			// PC2	( AD2 / IO16 )
	#define		right_wl_sensor_channel			2			// ADC2 - ADC Channel 2
	
	// 3rd and 4th IR proximity sensor definitions
	#define		ir_prox_3_4_sensors_ddr_reg		DDRC
	#define		ir_prox_3_4_sensors_port_reg	PORTC
	#define		ir_prox_3_sensor_pin			3			// PC3	( AD3 / IO17 )
	#define		ir_prox_3_sensor_channel		3			// ADC3 - ADC Channel 3
	#define		ir_prox_4_sensor_pin			4			// PC4	( AD4 / IO18 )
	#define		ir_prox_4_sensor_channel		4			// ADC4 - ADC Channel 4
	
	// 5th IR proximity sensor definitions
	#define		ir_prox_5_sensor_ddr_reg		DDRC
	#define		ir_prox_5_sensor_port_reg		PORTC
	#define		ir_prox_5_sensor_pin			5			// PC5	( AD5 / IO19 )
	#define		ir_prox_5_sensor_channel		5			// ADC5 - ADC Channel 5
	
	// 3rd Sharp sensor definitions
	#define		sharp_sensor_ddr_reg			DDRC
	#define		sharp_sensor_port_reg			PORTC
	#define		sharp_sensor_pin				0			// PC0	( AD0 / IO14 )
	#define		sharp_sensor_channel			0			// ADC0 - ADC Channel 0
	
	// Bits of ADSCRA register
	#define		ADCSRA_reg						ADCSRA 		// ADCSRA register
	#define		ADEN_bit						ADEN		// 7	( ADC Enable bit )
	#define		ADSC_bit						ADSC		// 6	( ADC Start Conversion bit )
	#define		ADATE_bit						ADATE		// 5	( ADC Auto Trigger Enable bit )
	#define		ADIF_bit						ADIF		// 4	( ADC Interrupt Flag bit )
	#define		ADIE_bit						ADIE		// 3	( ADC Interrupt Enable bit )
	#define		ADPS2_bit						ADPS2		// 2	( ADC Pre-scalar bit 2 )
	#define		ADPS1_bit						ADPS1		// 1	( ADC Pre-scalar bit 1 )
	#define		ADPS0_bit						ADPS0		// 0	( ADC Pre-scalar bit 0 )
	
	// Bits of ADSCRB register
	#define		ADCSRB_reg						ADCSRB 		// ADCSRB register
	#define		ACME_bit						ACME		// 6	( Analog Comparator Multiplexer Enable bit )
	#define		MUX5_bit						3			// 3	( since MUX5 bit is not defined in ATmega328P )
	#define		ADTS2_bit						ADTS2		// 2	( ADC Auto Trigger Source bit 2 )
	#define		ADTS1_bit						ADTS1		// 1	( ADC Auto Trigger Source bit 1 )
	#define		ADTS0_bit						ADTS0		// 0	( ADC Auto Trigger Source bit 0 )
	
	// Bits of ADMUX register
	#define		ADMUX_reg						ADMUX		// ADMUX register
	#define		REFS1_bit						REFS1		// 7	( Reference Selection bit 1 )
	#define		REFS0_bit						REFS0		// 6	( Reference Selection bit 0 )
	#define		ADLAR_bit						ADLAR		// 5	( ADC Left Result bit )
	#define		MUX4_bit						4			// 4	( since MUX4 bit is not defined in ATmega328P )
	#define		MUX3_bit						MUX3		// 3	( ADC Channel Selection bit 3 )
	#define		MUX2_bit						MUX2		// 2	( ADC Channel Selection bit 2 )
	#define		MUX1_bit						MUX1		// 1	( ADC Channel Selection bit 1 )
	#define		MUX0_bit						MUX0		// 0	( ADC Channel Selection bit 0 )
	
	// Bits of ACSR register
	#define		ACSR_reg						ACSR		// ACSR register
	#define		ACD_bit							ACD			// 7	( Analog Comparator Disable bit )
	
	// ADC Data registers
	#define		ADCH_reg						ADCH		// ADC High Byte Data register
	#define		ADCL_reg						ADCL		// ADC Low Byte Data register
	
	#define		BAUD_RATE						9600		// Baud rate setting
	
	// Calculate UBRR value for Baud Rate setting according to the F_CPU value
	#define		UBRR_VALUE						( ( ( F_CPU / 16 ) / BAUD_RATE ) - 1 )
	
	// USART0 Data register ( since ATmega328P has only UART0 )
	#define		UDR_reg							UDR0		// USART0 Data register
	
	// Bits of UCSR0A register
	#define		UCSRA_reg						UCSR0A		// UCSR0A register ( since ATmega328P has only UART0 )
	#define		TXC_bit							TXC0		// 6	( Transmit Complete Flag bit for UART0 )
	#define		UDRE_bit						UDRE0		// 5	( Data Register Empty Flag bit for UART0 )
	#define		U2X_bit							U2X0		// 1	( Double USART Transmission Speed bit for UART0 )
	
	// Bits of UCSR0B register
	#define		UCSRB_reg						UCSR0B		// UCSR0B register ( since ATmega328P has only UART0 )
	#define		RXCIE_bit						RXCIE0		// 7	( RX Complete Interrupt Enable 0 bit )
	#define		TXCIE_bit						TXCIE0		// 6	( TX Complete Interrupt Enable 0 bit )
	#define		UDRIE_bit						UDRIE0		// 5	( USART Data Register Empty Interrupt Enable 1 bit )
	#define		RXEN_bit						RXEN0		// 4	( Receiver Enable 1 bit )
	#define		TXEN_bit						TXEN0		// 3	( Transmitter Enable 1 bit )
	#define		UCSZ2_bit						UCSZ02		// 2	( Character Size selection bit 2 for UART0 )
	
	// Bits of UCSR0C register
	#define		UCSRC_reg						UCSR0C		// UCSR0C register ( since ATmega328P has only UART0 )
	#define		UMSEL1_bit						UMSEL01		// 7	( USART Mode Select bit 1 for UART0 )
	#define		UMSEL0_bit						UMSEL00		// 6	( USART Mode Select bit 0 for UART0 )
	#define		UPM1_bit						UPM01		// 5	( Parity Mode Select bit 1 for UART0 )
	#define		UPM0_bit						UPM00		// 4	( Parity Mode Select bit 0 for UART0 )
	#define		USBS_bit						USBS0		// 3	( Stop Bits Select bit for UART0 )
	#define		UCSZ1_bit						UCSZ01		// 2	( Character Size selection bit 1 for UART0 )
	#define		UCSZ0_bit						UCSZ00		// 1	( Character Size selection bit 0 for UART0 )
	#define		UCPOL_bit						UCPOL0		// 0	( Clock Polarity Select bit for UART0 )
	
	// USART0 Baud Rate registers ( since ATmega328P has only UART0 )
	#define		UBRRH_reg						UBRR0H		// USART0 High Byte Baud Rate register
	#define		UBRRL_reg						UBRR0L		// USART0 Low Byte Baud Rate register

#endif


#endif /* FIREBIRD_SIMULATION_H_ */
/*
 * uart.c
 *
 * Created: 10/07/2018 10:47:03
 * Author: e-Yantra Team
 */ 

#include "firebird_simulation.h"						// Header file included that contains macro definitions essential for Firebird V robot
#include <avr/interrupt.h>								// Standard AVR Interrupt Library
#include "uart.h"										// UART Header file included that contains function definitions essential to deal with UART

#define sbit( reg, bit )	reg |= ( 1 << bit )			// Macro defined for Setting a bit of any register
#define cbit( reg, bit )	reg &= ~( 1 << bit )		// Macro defined for Clearing a bit of any register


/* 
 * Function Name: uart_init
 * Input: ubbr_value (calculate UBRR value according to the BAUD_RATE and F_CPU)
 * Output: None
 * Logic: This function initializes the UART
 * Example Call: uart_init();
 */
void uart_init (unsigned int ubbr_value)
{
	// In UCSRB_reg, disable all bits setting the Baud Rate
	UCSRB_reg	= 0x00;
	
	// In UBRRH_reg and UBRRL_reg, set the baud rate
	UBRRH_reg	= (unsigned char) ( ubbr_value >> 8 );
	UBRRL_reg	= (unsigned char) ( ubbr_value );
	
	// In UCSRC_reg, select the Asynchronous USART mode and the character size to 8 bits
	UCSRC_reg	&= ~( ( 1 << UMSEL1_bit ) | ( 1 << UMSEL0_bit ) );
	UCSRC_reg	|= ( ( 1 << UCSZ1_bit ) | ( 1 << UCSZ0_bit ) );
	
	// In UCSRB_reg, enable the receiver and transmitter
	UCSRB_reg	|= ( ( 1 << TXEN_bit ) | ( 1 << RXEN_bit ) );
	UCSRB_reg	&= ~( 1 << UCSZ2_bit );
}


/* 
 * Function Name: uart_tx
 * Input: data (a character to send)
 * Output: None
 * Logic: This function sends a character over the UART
 * Example Call: uart_tx();
 */
void uart_tx(char data)
{
	//while( ( UCSRA_reg & ( 1 << UDRE_bit ) ) == 0x00 );				// waiting to transmit	
	UDR_reg	= data;
}


/* 
 * Function Name: uart_tx_string
 * Input: *data (address of the string)
 * Output: None
 * Logic: This function sends a string over the UART
 * Example Call: uart_tx_string();
 */
void uart_tx_string(char *data)
{
	while(*data != '\0')
	{
		uart_tx(*data);
		data++;
	}
}



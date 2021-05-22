/*
 * uart.h
 *
 * Created: 10/07/2018 10:47:03
 * Author: e-Yantra Team
 */ 

#ifndef UART_H_
#define UART_H_


// This function initializes the UART
void uart_init (unsigned int ubbr_value);

// This function sends a character over the UART
void uart_tx(char data);

// This function sends a string over the UART
void uart_tx_string(char *data);


#endif /* UART_H_ */
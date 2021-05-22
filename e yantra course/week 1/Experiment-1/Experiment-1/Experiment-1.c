/*! \mainpage Week-1 Experiment-1: Getting started with Embedded C Programming
 *
 * @author     e-Yantra Team
 * @date       2020/02/12
 *
 * \subsection Aim
 * To get started with the Embedded C Programming and rectify the errors in the skeleton code
 * such that the Buzzer already present and interfaced on Firebird V robot turns ON and OFF at an interval of a second.
 *
 * \subsection Connections
 * Buzzer 				:  PC3 				<br>
 *
 */


//---------------------------------- HEADER FILES -----------------------------------------------------
#include "firebird_simulation.h"		// Header file included that contains macro definitions essential for Firebird V robot
#include <util/delay.h>					// Standard AVR Delay Library

//---------------------------------- FUNCTIONS ----------------------------------------------------------
// << TODO >> : Complete all the functions and their input arguments correctly as they might have errors


/**
 * @brief      Makes **ONLY** 'buzzer_pin' as output and initially sets it to low
 */
void buzzer_pin_config(void) { 
	// << NOTE >> : Use Masking and Shift Operators here
	
	// Make 'buzzer_pin' as output
	buzzer_ddr_reg |=  ( 1 << buzzer_pin);

	
	// Set 'buzzer_pin' to low initially
	buzzer_port_reg &= ~( 1 << buzzer_pin);

}


/**
 * @brief      Sets **ONLY** 'buzzer_pin' to high, hence turns ON the Buzzer
 */
void buzzer_on(void) {
	// << NOTE >> : Use Masking and Shift Operators here
	
	// Set 'buzzer_pin' to high
	buzzer_port_reg |= ( 1 << buzzer_pin);

}


/**
 * @brief      Sets **ONLY** 'buzzer_pin' to low, hence turns OFF the Buzzer
 */
void buzzer_off(void) {
	// << NOTE >> : Use Masking and Shift Operators here
	
	// Set 'buzzer_pin' to low
	buzzer_port_reg &= ~( 1 << buzzer_pin);

}


//---------------------------------- MAIN ----------------------------------------------------------------
/**
 * @brief      Main Function
 *
 * @details    First Initializes the Buzzer present on Firebird-V by calling buzzer_pin_config() function,
 * 			   then calls the buzzer_on() and buzzer_off() functions to turn the Buzzer ON and OFF at an interval of a second.
 */

int main(void) {
	
	// << NOTE >> : You are not allowed to modify or change anything inside this function
	
	buzzer_pin_config();				// Initialize the Buzzer
	
	while (1)
	{
		buzzer_on();					// Turn ON the Buzzer
		_delay_ms(1000);				// Delay of 1 second
		
		buzzer_off();					// Turn OFF the Buzzer
		_delay_ms(1000);				// Delay of 1 second
	}
}
//---------------------------------- END ------------------------------------------------------------------
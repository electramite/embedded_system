/*! \mainpage Week-1 Experiment-2: Bar-graph LEDs and Interrupt Switch Interfacing
 *
 * @author     e-Yantra Team
 * @date       2020/02/12
 *
 * \subsection Aim
 * To toggle the status of 2 Bar-graph LEDs depending on whether the Interrupt Switch is pressed or released.
 *
 * \subsection Connections
 * Interrupt Switch				:  PE7 				<br>
 * Bar-graph LED 2				:  PJ1 				<br>
 * Bar-graph LED 6				:  PJ5 				<br>
 * Bar-graph LED 8				:  PJ7 				<br>
 *
 */


//---------------------------------- HEADER FILES -----------------------------------------------------
#include "firebird_simulation.h"			// Header file included that contains macro definitions essential for Firebird V robot
#include <util/delay.h>						// Standard AVR Delay Library
#include <stdbool.h>						// Standard C Library for Boolean Type

//---------------------------------- FUNCTIONS ----------------------------------------------------------
// << TODO >> : Complete all the functions and their input arguments correctly as they might have errors


/**
 * @brief      Makes **ONLY** 2nd, 6th and 8th Bar-graph LED pins as output and initially sets **ONLY** 2nd Bar-graph LED as high (ON)
 */
void bar_graph_led_pins_config(void) {
	// << NOTE >> : Use Masking and Shift Operators here
	
	// Make **ONLY** 2nd, 6th and 8th Bar-graph LED pins as output
	bar_graph_led_ddr_reg	|= (1 << bar_graph_led_2_pin) | (1 << bar_graph_led_6_pin) | (1 << bar_graph_led_8_pin);


	
	// Set **ONLY** 2nd Bar-graph LED as high (ON)
	bar_graph_led_port_reg	|=(1 << bar_graph_led_2_pin) ;
}


/**
 * @brief      Makes **ONLY** Interrupt Switch pin as input and pulls it up internally
 */
void interrupt_sw_pin_config(void) {
	// << NOTE >> : Use Masking and Shift Operators here
	
	// Makes **ONLY** Interrupt Switch pin as input
	interrupt_sw_ddr_reg	&= ~(1 << interrupt_sw_pin);

	
	// Makes **ONLY** Interrupt Switch pin internally pull-up
	interrupt_sw_port_reg	|= (1 << interrupt_sw_pin);
	
}


/**
 * @brief      Checks if Interrupt Switch is pressed or not
 *
 * @return     boolean true if Interrupt Switch is pressed, else false.
 */
bool interrupt_switch_pressed(void)
{
	/*
	<< TODO >> :
		1. Write an if-else statement with a condition which checks whether the Interrupt Switch is pressed or not.
		2. If the Interrupt Switch is pressed return true, else return false
	*/
	bool status = interrupt_sw_pin_reg & (1 << interrupt_sw_pin);
	if (status == false) 
	{	
		return true;
	}
	else{

		return false;
	}
}


/**
 * @brief      Sets **ONLY** a particular Bar-graph LED pin as high (ON)
 *
 * @param[in]  led_pin   Pin number of Bar-graph LED
 */
void turn_on_bar_graph_led(unsigned char led_pin) {
	// << NOTE >> : Use Masking and Shift Operators here
	
	// Set **ONLY** a particular Bar-graph LED pin as high (ON)
	bar_graph_led_port_reg |= (1 << led_pin);
}


/**
 * @brief      Sets **ONLY** a particular Bar-graph LED pin as low (OFF)
 *
 * @param[in]  led_pin   Pin number of Bar-graph LED
 */
void turn_off_bar_graph_led(unsigned char led_pin) {
	// << NOTE >> : Use Masking and Shift Operators here
	
	// Set **ONLY** a particular Bar-graph LED pin as low (OFF)
	bar_graph_led_port_reg &= ~(1 << led_pin);
}


//---------------------------------- MAIN ----------------------------------------------------------------
/**
 * @brief      Main Function
 *
 * @details    First Initializes 3 Bar-graph LEDs and Interrupt Switch, sets **ONLY** 2nd Bar-graph LED as high (ON)
 *			   by calling bar_graph_led_pins_config() and interrupt_sw_pin_config() functions.
 *			   The 6th Bar-graph LED is turned ON by turn_on_bar_graph_led(6) function.
 *			   It then checks whether the Interrupt Switch is pressed or not.
 *			   If Switch is pressed, it turns ON the 8th Bar-graph LED and turns OFF the 2nd Bar-graph LED, vice-versa if released.
 */
int main(void) {
	
	// << NOTE >> : You are not allowed to modify or change anything inside this function
	
	bar_graph_led_pins_config();									// Initialize the 2nd, 6th and 8th Bar-graph LEDs
	interrupt_sw_pin_config();										// Initialize the Interrupt Switch
	turn_on_bar_graph_led(bar_graph_led_6_pin);
	
	while (1)
	{
		if ( interrupt_switch_pressed() )
		{
			turn_off_bar_graph_led(bar_graph_led_2_pin);			// Turn OFF 2nd Bar-graph LED
			turn_on_bar_graph_led(bar_graph_led_8_pin);				// Turn ON 8th Bar-graph LED
			
			_delay_ms(50);											// Waiting for a while for the Interrupt Switch to settle
			
			/*
				Why did we include this delay?
				
				The reason is that mechanical switches like the Interrupt Switch have a limitation called switch bounce.
				You can read more about it here: http://www.labbookpages.co.uk/electronics/debounce.html , https://electrosome.com/switch-debouncing/
				The bar_graph_led_2_on and bar_graph_led_2_off functions execute in a few microseconds, but the switch itself needs time to settle after a press.
				Typically this time is in the order of a few milliseconds.
				Introducing a delay is the simplest way of mitigating for switch bounce and this process is called de-bouncing.
			*/
		}
		else
		{
			turn_on_bar_graph_led(bar_graph_led_2_pin);				// Turn ON 2nd Bar-graph LED
			turn_off_bar_graph_led(bar_graph_led_8_pin);			// Turn OFF 8th Bar-graph LED
		}
	}
}
//---------------------------------- END ------------------------------------------------------------------
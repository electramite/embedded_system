/*! \mainpage Week-3 Experiment-2: Speed Control using 8 bit Phase Correct PWM Mode
 *
 * @author     e-Yantra Team
 * @date       2020/02/27
 *
 * \subsection Aim
 * To increase and decrease the speed of motors using Phase Correct PWM Mode.
 *
 * \subsection Connections
 * 
 * Motors Connections: 
 * Motors are connected to the Microcontroller through L293D Motor Driver IC. <br>
 *		 Motors Pin	  	Microcontroller Pin      	<br>
 *			  RB  	--> 	PA3						<br>
 *			  RF  	--> 	PA2						<br>
 *			  LF  	--> 	PA1						<br>
 *			  LB 	--> 	PA0						<br>
 * 
 * PWM Pins of the Microcontroller are connected to the L293D Motor Driver IC.
 *		   PWM Pin	  		Microcontroller Pin      	<br>
 *		  Left Motor  	--> 	PL4						<br>
 *		  Right Motor  	--> 	PL3						<br>
 *
 */

//---------------------------------- HEADER FILES --------------------------------------------------
#include "firebird_simulation.h"				// Header file that contains macro definitions essential for Firebird V robot
#include <util/delay.h>							// Standard AVR Delay Library
//---------------------------------- << TODO: DEFINE REQUIRED FUNCIONS HERE >> ---------------------

/**
 * @brief      Function to configure pins of ATmega2560 to which pins of L293D Motor Driver IC is connected
 */
void motors_pin_config(void) {
	// << NOTE >> : Use Masking and Shift Operators here

	motors_dir_ddr_reg |= ((1 << motors_RB_pin) | (1 << motors_RF_pin) | (1 << motors_LB_pin) | (1 << motors_LF_pin));			// set **ONLY** motor pins as output
	motors_dir_port_reg &= ~((1 << motors_RB_pin) | (1 << motors_RF_pin) | (1 << motors_LB_pin) | (1 << motors_LF_pin));			// stop motors initially
}

/**
 * @brief      Function to configure left and right channel pins of the L293D Motor Driver IC for PWM
 */
void pwm_pin_config(void){
	// << NOTE >> : Use Masking and Shift Operators here

	motors_pwm_ddr_reg |= ((1 << motors_pwm_L_pin) | (1 << motors_pwm_R_pin));		// set **ONLY** left and right channel pin as output
	motors_pwm_port_reg |= ((1 << motors_pwm_L_pin) | (1 << motors_pwm_R_pin));		// enable left and right channel
}


/**
 * @brief      Function to make Firebird-V move forward.
 */
void motors_move_forward(void) {
	// << NOTE >> : Use Masking and Shift Operators here

	// Set RF and LF, reset RB and LB
	motors_dir_port_reg |= ((1 << motors_RF_pin) | (1 << motors_LF_pin));
	motors_dir_port_reg &= ~((1 << motors_RB_pin) | (1 << motors_LB_pin));	
}

//-------------------
/**
 * @brief      Function to initialize Timer 5 in Phase Correct PWM mode for speed control of motors of Firebird-V
 *
 */
void timer_pwm_init(void) {
	
	// Set Non Inverting Output Compare Mode using COMn1 and COMn0 as 10
	// Configure for 8 bit Phase correct PWM mode
	TCCR5A_reg |= ((1 << COMA1_bit) | (1 << COMB1_bit) | (1 << WGM0_bit));
	TCCR5A_reg &= ~((1 << COMA0_bit) | (1 << COMB0_bit) | (1 << WGM1_bit));

	// Configure for Phase Correct PWM
	// Set Prescalar to 64
	TCCR5B_reg |= ((1 << CS1_bit) | (1 << CS0_bit));
	TCCR5B_reg &= ~((1 << CS2_bit) | (1 << WGM2_bit) | (1 << WGM3_bit));
	
	// Initialise Timer/counter register as 0
	TCNT5L_reg = 0x00;

	// Initialise OCR registers as 0
	OCR5AL_reg = 0x00;
	OCR5BL_reg = 0x00;

}

/**
 * @brief      Function to control the speed of both the motors of Firebird-V
 *
 * @param[in]  left_motor   Left motor speed 0 to 255
 * @param[in]  right_motor  Right motor speed 0 to 255
 */
void set_duty_cycle(unsigned char dcycle_pin_a, unsigned char dcycle_pin_b) {
	OCR5AL_reg = dcycle_pin_a;
	OCR5BL_reg = dcycle_pin_b;
}
//-------------------


/**
 * @brief      Main function
 *
 * @details    First initialized motors and PWM after that make the Firebird-V motors_move_forward using
 * 			   8 bit Phase correct PWM mode.
 *
 * @return     0
 */
int main() {

	unsigned char duty_cycle = 0;
		
	pwm_pin_config();			// Initialize pwm pins as output
	timer_pwm_init();			// Initialize Timer 5
	
	motors_pin_config();		// Initialize motor pins
	motors_move_forward();		// Move the robot forward
	
	// The duty cycle for the left motor decreases from the maximum value while the duty cycle for the right motor increases from the minimum value. 
	// The resulting pattern traced by the robot is approximately an "S" shape.
	while(1){
		set_duty_cycle(255 - duty_cycle, duty_cycle);		  
		duty_cycle++;										
		_delay_ms(10);
	}

	return 0;
}
/*
 * adc.c
 *
 * Created: 4/15/2021 17:14:54
 * Author: e-Yantra Team
 */ 


//---------------------------------- HEADER FILES -------------------------------------------------------
#include "adc.h"

//------------------------------------- MACROS ----------------------------------------------------------
// If any

//---------------------------------- GLOBAL VARIABLES ---------------------------------------------------
// If any

//---------------------------------- FUNCTIONS ----------------------------------------------------------
// << TODO >> : Complete all the functions as per the instructions given in form of comments


/**
 * @brief      Initializes the Analog-to-Digital converter inside the micro-controller
 */
void adc_init(void)
{
	// << NOTE >> : Use Masking and Shift Operators here
	
	// In ADCSRA, enable ADC and pre-scalar = 64 (ADEN = 1, ADPS2 = 1, ADPS1 = 1, ADPS0 = 0)
	//				and clear ADC start conversion bit, auto trigger enable bit, interrupt flag bit and interrupt enable bit
	ADCSRA_reg	|= ( (1 << ADEN_bit) | (1 << ADPS2_bit) | (1 << ADPS1_bit) );
	ADCSRA_reg	&= ~( (1 << ADSC_bit) | (1 << ADATE_bit) | (1 << ADIF_bit) | (1 << ADIE_bit) | (1 << ADPS0_bit) );
	
	// In ADCSRB, disable Analog Comparator Multiplexer, MUX5 bit and ADC Auto Trigger Source bits
	ADCSRB_reg	&= ~( (1 << ACME_bit) | (1 << MUX5_bit) | (1 << ADTS2_bit) | (1 << ADTS1_bit) | (1 << ADTS0_bit) );
	
	// In ADMUX, set the Reference Selection bits to use the AVCC as reference, and disable the channel selection bits MUX[4:0]
	ADMUX_reg	&= ~( (1 << REFS1_bit) | (1 << MUX4_bit) | (1 << MUX3_bit) | (1 << MUX2_bit) | (1 << MUX1_bit) | (1 << MUX0_bit) );
	ADMUX_reg	|= (1 << REFS0_bit);
	
	// In ADMUX, enable the ADLAR bit for 8-bit ADC result
	ADMUX_reg	|= (1 << ADLAR_bit);
	
	// In ACSR, disable the Analog Comparator by writing 1 to ACD_bit
	ACSR_reg	|= ( 1 << ACD_bit );
}


/**
 * @brief      Sets the MUX[5:0] bits according to the sensor's channel number as input
 *
 * @param[in]  channel_num   ADC channel number of sensor
 */
void select_adc_channel( unsigned char channel_num )
{
	// << NOTE >> : Use Masking and Shift Operators here
	
	// set the MUX[5:0] bits to select the ADC channel number
	if ( channel_num > 7 )
	{
		ADCSRB_reg |= ( 1 << MUX5_bit );					// set the MUX5 bit for selecting channel if its greater than 7
	}
	
	channel_num	= channel_num & 0x07;						// retain the last 3 bits from the variable for MUX[2:0] bits
	
	//ADMUX_reg	= ( ( ADMUX_reg & 0xF8 ) | channel_num );
	ADMUX_reg	= ( ADMUX_reg | channel_num );
}


/**
 * @brief      Starts the ADC by setting the ADSC bit in ADCSRA register
 */
void start_adc(void)
{
	// << NOTE >> : Use Masking and Shift Operators here
	
	// set the ADSC bit in ADCSRA register
	ADCSRA_reg		|= ( 1 << ADSC_bit );
}


/**
 * @brief      Checks if the ADC conversion for the selected channel is complete or not
 *
 * @return     boolean true if the ADC has completed its conversion for the selected channel, else false.
 */
bool check_adc_conversion_complete(void)
{
	/*
	<< TODO >> :
		1. Write an if-else statement with a condition which checks whether the ADC conversion for the selected channel is complete or not.
		2. If the ADC has completed its conversion for the selected channel return true, else return false
	*/
	if ( ( ADCSRA_reg & ( 1 << ADIF_bit ) ) == 0x10 )
	{
		return true;
	}
	else
	{
		return false;
	}
}


/**
 * @brief      Get the ADC converted data from ADC data registers
 *
 * @return     ADC converted data of the sensor by reading ADC data registers
 */
unsigned char read_adc_converted_data(void)
{
	// << NOTE >> : Use Masking and Shift Operators here
	
	unsigned char adc_8bit_data;
	
	// read the appropriate ADC data register/s
	
	unsigned char adc_data_high_byte;
	
	adc_data_high_byte	= ADCH_reg;
	adc_8bit_data		= adc_data_high_byte;
	
	return adc_8bit_data;
}


/**
 * @brief      Reset ADC config registers, ADCSRA and ADCSRB
 */
void reset_adc_config_registers(void)
{
	// << NOTE >> : Use Masking and Shift Operators here
	
	ADCSRA_reg		|= ( 1 << ADIF_bit );					// clear ADIF bit by writing 1 to it
	
	ADCSRB_reg		&= ~( 1 << MUX5_bit );					// clear the MUX5 bit
	
	// clear the MUX[4:0] bits
	ADMUX_reg		&= ~( (1 << MUX4_bit) | (1 << MUX3_bit) | (1 << MUX2_bit) | (1 << MUX1_bit) | (1 << MUX0_bit) );
}


/**
 * @brief      Convert the analog readings to 8-bit digital format from the sensor's ADC channel number as input
 *
 * @param[in]  sensor_channel_number   ADC channel number of sensor
 *
 * @return     8-bit digital data from the input sensor ADC channel
 */
unsigned char convert_analog_channel_data( unsigned char sensor_channel_number )
{
	
	unsigned char adc_8bit_data;
	
	select_adc_channel( sensor_channel_number );	
	start_adc();

	while( !( check_adc_conversion_complete() ) );	// wait for ADC conversion to complete by polling ADIF bit in ADCSRA register
	adc_8bit_data = read_adc_converted_data();
	reset_adc_config_registers();
	
	return adc_8bit_data;
}


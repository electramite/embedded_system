/*
 * adc.h
 *
 * Created: 4/15/2021 17:14:54
 * Author: e-Yantra Team
 */ 

#ifndef ADC_H_
#define ADC_H_

#include "firebird_simulation.h"    // Header file included that contains macro definitions essential for Firebird V robot
#include <stdbool.h>                // Standard C Library for Boolean Type

void adc_init(void);
void select_adc_channel( unsigned char channel_num);
void start_adc(void);
bool check_adc_conversion_complete(void);
unsigned char read_adc_converted_data(void);
void reset_adc_config_registers(void);
unsigned char convert_analog_channel_data( unsigned char sensor_channel_number );

#endif /* ADC_H_ */

/*
 *
 * The DSO screen has total size of 128 x 64 pixels, which is divided into two sections:
 * 
 * [ I ] DISPLAY WAVEFORM => Area where the input waveform is to be displayed (may it be Sine, Square, etc.)
 * 							 The center line is a reference line about which the waveform should be symmetric.
 * 							 The height of this area should accomodate the waveform with max. Vpp of 5V.
 * 							 The width of this area should accomodate the waveform with:
 * 								* min. frequency of 250 Hz (0.25 kHz)
 * 								* max. frequency of 2000 Hz (2 kHz)
 * 
 * [ II ] DISPLAY WAVEFORM INFO => Area where the information about the waveform is to be displayed.
 * 								   The peak-to-peak voltage (Vpp), frequency in kHz, ms/div, V/div.
 * 
 *  ____________________________________________________________
 * |(0,0)                                   |                   |
 * |                                        |                   |
 * |                                        |                   |
 * |          DISPLAY WAVEFORM              |                   |
 * |                                        |                   |
 * |                                        |     DISPLAY       |
 * |                                        |                   |
 * |________________________________________|                   |
 * |                                        |     WAVEFORM      |
 * |                                        |                   |
 * |                                        |                   |
 * |          DISPLAY WAVEFORM              |       INFO        |
 * |                                        |                   |
 * |                                        |                   |
 * |                                        |                   |
 * |_________________________________(95,63)|(96,63)____(127,63)|
 */

//---------------------------------- HEADER FILES -----------------------------------------------------
#include "firebird_simulation.h"
#include "u8glib.h"
#include "adc.h"
#include <util/delay.h>

//------------------------------------- MACROS ----------------------------------------------------------
// If any

//---------------------------------- GLOBAL VARIABLES ---------------------------------------------------
// array to store the data from the input waveform
// since the waveform display area is of 96 columns or pixels, we store double amount of data in buffer
// Note: the input waveform from the Function Generator has minimum value of 0 V
int buffer_input_data[192];

// values from buffer array for max., min. and half of the amplitude
int V_max, V_min, V_mid;

// peak-to-peak voltage of the input waveform
float V_pp;

// index values from buffer array which indicate:
// start of waveform : where the first wave in the buffer cuts half of the amplitude or where the first wave starts its cycle
// end of waveform : where the second wave in the buffer cuts half of the amplitude or where the first wave ends its cycle or the second wave starts its cycle
int start_wave_idx, end_wave_idx;

// msec per division to be considered in the "Display Waveform" Area
// this value should increment in steps of 0.5 up till 2.0 (OR)
// should decrement in steps of 0.5 up till 0.125 each time DIV+ (OR) DIV- switches are pressed
float ms_per_div = 0.5;

// volts per division to be considered in the "Display Waveform" Area
float volts_per_div = 0.625;

// frequency of input waveform in kHz unit
float freq;

// array to compute and store the pixel locations for the input waveform to be displayed in "Display Waveform" Area
int pixel_loc[96];

// flag to keep track whether the HOLD switch is pressed or not
// this flag will toggle between 1 and 0 on press and release of the switch respectively
int hold_flag = 0;

// vertical displacement to be applied on waveform on each press of UP and DOWN switches
// this value should increment in steps of 1 up till 31 (max. pixels that can accomodate above the center horizontal line) (OR)
// should decrement in steps of 1 up till -31 (max. pixels that can accomodate below the center horizontal line)
int vert_disp = 0;

// << NOTE >> : You can define any extra global variables below


//---------------------------------- FUNCTIONS ----------------------------------------------------------
void dso_switches_input_channel_config(void)
{

	
	
	div_hold_switch_ddr_reg &= ~((1 << div_add_sw_pin) | (1 << div_sub_sw_pin) | (1 << hold_sw_pin));
	div_hold_switch_port_reg |= ((1 << div_add_sw_pin) | (1 << div_sub_sw_pin) | (1 << hold_sw_pin));
	up_down_switch_ddr_reg &= ~((1 << up_sw_pin) | (1 << down_sw_pin));
	up_down_switch_port_reg |= ((1 << up_sw_pin) | (1 << down_sw_pin));
	dso_input_channel_ddr_reg &= ~(1 << dso_input_channel_pin);
	dso_input_channel_port_reg &= ~(1 << dso_input_channel_pin);
}


void dso_switches_interrupt_config(void)
{
	

	// All interrupts have to be disabled before configuring interrupts
	cli();	// Disable interrupts globally

	// Configure falling edge detection on div_add_sw_pin_int (INT1) and div_sub_sw_pin_int (INT2)
	EICRA_reg |= ((1 << div_add_sw_ISC_bit1) | (1 << div_sub_sw_ISC_bit1));
	EICRA_reg &= ~((1 << div_add_sw_ISC_bit0) | (1 << div_sub_sw_ISC_bit0));

	// Configure low level detection on hold_sw_pin_int (INT3)
	EICRA_reg &= ~((1 << hold_sw_ISC_bit1) | (1 << hold_sw_ISC_bit0));

	// Configure falling edge detection on up_sw_pin_int (INT4) and down_sw_pin_int (INT5)
	EICRB_reg |= ((1 << up_sw_ISC_bit1) | (1 << down_sw_ISC_bit1));
	EICRB_reg &= ~((1 << up_sw_ISC_bit0) | (1 << down_sw_ISC_bit0));

	// Enable INT1, INT2, INT3, INT4 and INT5 interrupts
	EIMSK_reg |= ((1 << down_sw_pin_int) | (1 << up_sw_pin_int) | (1 << hold_sw_pin_int) | (1 << div_sub_sw_pin_int) | (1 << div_add_sw_pin_int));

	sei();	// Enable interrupts gloabally
}

void dso_init(void)
{
	

	dso_switches_input_channel_config();
	dso_switches_interrupt_config();
	adc_init();
	glcd_setup();
}


ISR(div_add_sw_pin_int_vect)  
{
	ms_per_div = ms_per_div + 0.5; // increment ms_per_div by 0.5, each time DIV+ is pressed
	if(ms_per_div > 2.0) ms_per_div=0.5; // reset condition for ms_per_div > 2.0
}


ISR(div_sub_sw_pin_int_vect)
{
	ms_per_div -= 0.5; // Decrement ms_per_div by 0.5, each time DIV- is pressed
	if(ms_per_div <= 0) ms_per_div = 0.5;  // reset condition for ms_per_div < 0
}


ISR(hold_sw_pin_int_vect)
{
	hold_flag = 1; // setting the hold flag when hold switch is pressed
	while (div_hold_switch_pin_reg & (1 << hold_sw_pin) == 0); // wait till the switch being released 
	hold_flag = 0; // resetting the hold flag 
}


ISR(up_sw_pin_int_vect)
{
	vert_disp--; // decreasing vert_disp by 1 step on every press of UP switch
	if(vert_disp < -31) vert_disp =0;  // resetting the vert_disp to 0 when waveform moves out of the display 
}


ISR(down_sw_pin_int_vect)
{
	vert_disp++;// increasing vert_disp by 1 step on every press of DOWN switch
	if(vert_disp > 31) vert_disp =0;  // resetting the vert_disp to 0 when waveform moves out of the display  
}

void dso_start_screen(void)
{
	setFont(u8g_font_5x7);
	firstPage();
	do
	{	
		drawFrame(0,0,128,63);
		drawStr( 32, 32, "DSO START" );
		
		
	}
	while( nextPage() ); 

}


void sample_input_wave(void)
{
	
	for (int i = 0; i < 192; i++)
	{
		buffer_input_data[i] = convert_analog_channel_data(dso_input_channel_pin);// storing the data from input waveform into buffer
		  if(ms_per_div == 0.5) _delay_us(60);
		  else if(ms_per_div == 1.0) _delay_us(110);
		  else if(ms_per_div == 1.5) _delay_us(160);
		  else if(ms_per_div == 2) _delay_us(210);      

	}
}

void calc_vpp_vmid(void)
{
	V_max = 0, V_min=0;
	for(int x=0; x<192; x++){
		if(buffer_input_data[x] <= V_min) V_min = buffer_input_data[x];
		else if(buffer_input_data[x] >= V_max) V_max = buffer_input_data[x];
	}
	V_mid = ((V_max+V_min)/2);// calculating V_mid : value in buffer array that is half of the amplitude
	V_pp = (V_max-V_min)*5.0/255.0;	// calculating V_pp : value in Volts for the peak-to-peak amplitude of the input waveform
}


/**
 * 
 *		     _______	    ________
 *          |		|	   |		|
 *  ___start|_______|___end|________|______
 *          |		|	   |		|
 *          |		|______|		|
 */
void calc_start_end_wave_idx(void)
{
	
	  for(int i=0;i<192;i++)
	  {
		  if(buffer_input_data[i]<V_mid&&buffer_input_data[i+1]>=V_mid)
		  {
			  start_wave_idx=i+1;  // storing X coordinate of the point as start_wave_idx where waveform cuts the center horizontal line(V_mid) for the first time while moving up 
			  break;
		  }
	  }
	  for(int i=start_wave_idx+1;i<192;i++)
	  {
		  if(buffer_input_data[i]<V_mid&&buffer_input_data[i+1]>=V_mid)
		  {
			  end_wave_idx=i;// storing X coordinate of the point as end_wave_idx where waveform cuts the center horizontal line(V_mid) for the second time while moving up
			  break;
		  }
	  }
}


void calc_frequency(void)
{
	
	float t = end_wave_idx-start_wave_idx;
	if(t>0) freq=8/(t*(ms_per_div));  // as i'm not using the above mentioned optional feature so i multiplied the Time Period with 0.5 instead of ms_per_div
	else freq=0;
}


void measure_parameters(void)
{
	

	
	calc_vpp_vmid();
	calc_start_end_wave_idx();
	calc_frequency();
}


void translate_wave_to_pixels(void)
{
	
	  for(int i=0; i<96; i++){
		  pixel_loc[i] = (32+(V_mid-buffer_input_data[i])/4);// mapping the stored waveform (0, 255) in pixels (0, 63) and making it symmetrical about central horizontal line 
	  }
}

void draw_ref_frame(void)
{
	

	// drawing outer boundary or rectangle in the "Display Waveform" Area of 96 (columns) x 64 (rows)
	drawFrame(0, 0, 95, 63);

	// drawing the center horizontal and vertical line for reference and symmetricity
	drawLine(48, 0, 48, 63);
	drawLine(0, 32, 95, 32);

	// drawing short vertical lines or markings on center horizontal line with equal divisions for Time in msec
	for (int x = 0; x < 97; x += 8)
		drawLine(x, 31, x, 33);
	
	// drawing short horizontal lines or markings on center vertical line with equal divisions for Voltage level in Volts
	for (int y = 0 ; y < 64; y += 8)
		drawLine(47, y, 49, y);
	
	// plot small dots in all four quadrants for symmetricity in viewing the input waveform
	for (int x = 8; x < 96; x += 8)
	{
		for (int y=8; y < 64; y += 8)
			drawPixel(x,y);
	}
}

void draw_waveform(void)
{
	for(int x = 0;x < 96;x++) drawLine(x,(vert_disp+pixel_loc[x]),x,(vert_disp+pixel_loc[x+1]));
// pixel_loc stores the y coordinates of every point of the waveform, looping from 0 to 96(x coordinate) and joining these points with drawline function   
}

void display_wave_info_text_data(void)
{
	

	drawStr(96, 7, "ms/div");
	setPrintPos(96, 14);
	print_float(ms_per_div, 3);

	drawStr(96, 23, "V/div");
	setPrintPos(96, 30);
	print_float(volts_per_div, 3);
	
	drawStr(96, 40, "Vpp");
	setPrintPos(96, 47);
	print_float(V_pp, 3);
	drawStr(123, 47, "V");
	
	drawStr(96, 55, "f(kHz)");
	setPrintPos(96, 62);
	print_float(freq, 3);
}


void dso_display_waveform_data(void)
{
	
	
	firstPage();
	do
	{
		// display the reference frame
		draw_ref_frame();

		// display the waveform as close and identical as possible with the input waveform by Function Generator
		draw_waveform();

		// display the waveform info text and data of measured parameters
		display_wave_info_text_data();
	}
	while( nextPage() );
}


void start_dso_operation(void)
{
	
	// sample the input waveform
	sample_input_wave();

	// measure various parameters of the given waveform
	measure_parameters();

	// convert the waveform data points to pixel coordinates of the GLCD
	translate_wave_to_pixels();

	// display the waveform and data of measured parameters
	dso_display_waveform_data();

}


int main(void)
{
	dso_init();
	dso_start_screen();

	while(1)
	{
		start_dso_operation();
	}
	return 0;
}

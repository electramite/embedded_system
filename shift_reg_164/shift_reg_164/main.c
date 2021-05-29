/*
 * shift_reg_with_avr.c
 *
 * Created: 29-05-2021 14:50:34
 * Author : electramite
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define HC164_PORT   PORTB
#define HC164_DDR    DDRB

#define HC164_DS_POS PB0      //Data pin (DS) pin location
#define HC164_SH_CP_POS PB1      //Shift Clock (SH_CP) pin location 

//Initialize HC164 System

void HC164Init()
{
   //Make the Data(DS), Shift clock (SH_CP) lines output
   HC164_DDR|=((1<<HC164_SH_CP_POS)|(1<<HC164_DS_POS));
}


//Low level macros to change data (DS)lines
#define HC164DataHigh() (HC164_PORT|=(1<<HC164_DS_POS))

#define HC164DataLow() (HC164_PORT&=(~(1<<HC164_DS_POS)))

/*

Simple Delay function approx 0.5 seconds

*/

void Wait()
{
	for(uint8_t i=0;i<30;i++)
	{
		_delay_loop_2(0);
	}
}

//Sends a clock pulse on SH_CP line
void HC164Pulse()
{
   //Pulse the Shift Clock

   HC164_PORT|=(1<<HC164_SH_CP_POS);//HIGH
   HC164_PORT&=(~(1<<HC164_SH_CP_POS));//LOW

}


void HC164Write(uint8_t data)
{
   //Send each 8 bits serially

   //Order is MSB first
   for(uint8_t i=0;i<8;i++)
   {
      //Output the data on DS line according to the
      //Value of MSB
      if(data & 0b10000000)
      {
         //MSB is 1 so output high

         HC164DataHigh();
      }
      else
      {
         //MSB is 0 so output high
         HC164DataLow();
      }

      HC164Pulse();  //Pulse the Clock line
      data=data<<1;  //Now bring next bit at MSB position

   }
}



void main()
{
   uint8_t led_pattern[8]={
                        0b10000001,
                        0b11000011,
                        0b11100111,
                        0b11111111,
                        0b01111110,
                        0b00111100,
                        0b00011000,
                        0b00000000,
                     };

   //Initialize HC164 system

   HC164Init();

   while(1)
   {
      for(uint8_t i=0;i<8;i++)
      {
         HC164Write(led_pattern[i]);   //Write the data to HC164
         Wait();                 //Wait 

      }
   }


}



#include "u8glib.h"
#include <stdio.h>
#include <math.h>
#include "u8g.h"

u8g_t u8g;
u8g_uint_t tx, ty;          // current position for the Print base class procedures

void sys_init(void)
{
#if defined(__AVR__)
  /* select minimal prescaler (max system speed) */
  CLKPR = 0x80;
  CLKPR = 0x00;
#endif
}

void glcd_setup(void)
{
	sys_init();

	// the below function maps the Arduino Mega pin numbers to their respective Port and pin numbers
	// for example, PN (port_num, pin_num) where
	// 			D0 => Arudino pin 22 => Atmega2560 PA0 => PORTA, Pin 0 -> PN(0, 0)
	// 			D1 => Arudino pin 23 => Atmega2560 PA1 => PORTA, Pin 1 -> PN(0, 1)
	// 			EN => Arudino pin 35 => Atmega2560 PC2 => PORTC, Pin 2 -> PN(2, 2)
	// 			CS1 => Arudino pin 34 => Atmega2560 PC3 => PORTC, Pin 3 -> PN(2, 3)
	// 			and so on...
	// refer for more info: https://github.com/olikraus/u8glib/wiki/userreference#initspi-inithwspi-init8bit-initcomfn
	u8g_Init8Bit(
				&u8g, &u8g_dev_ks0108_128x64_fast,
				PN(0,0), PN(0,1), PN(0,2),
				PN(0,3), PN(0,4), PN(0,5),
				PN(0,6), PN(0,7), PN(2,2),
				PN(2,3), PN(2,4), PN(2,0),
				PN(2,1), PN(2,5)
			);
}

void setPrintPos(u8g_uint_t x, u8g_uint_t y) 
{
  tx = x;
  ty = y; 
}

void reverse(char* str, int len)
{
	int i = 0, j = len - 1, temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x) {
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}
  
	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
		str[i++] = '0';
  
	reverse(str, i);
	str[i] = '\0';
	return i;
}

void ftoa(float n, char* res, int afterpoint)
{
	// Extract integer part
	int ipart = (int)n;
  
	// Extract floating part
	float fpart = n - (float)ipart;
  
	// convert integer part to string
	int i = intToStr(ipart, res, 0);
  
	// check for display option after point
	if (afterpoint != 0) {
		res[i] = '.'; // add dot
  
		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter 
		// is needed to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint);
  
		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}

u8g_uint_t print_int(int num)
{
  char data[128];
  sprintf(data,"%d",num);
  return u8g_DrawStr(&u8g,tx,ty,data);
}

u8g_uint_t print_float(double num, int afterpoint)
{
  char data[128];
  ftoa(num,data,afterpoint);
  return u8g_DrawStr(&u8g,tx,ty,data);
}

void drawFrame(u8g_uint_t x, u8g_uint_t y, u8g_uint_t w, u8g_uint_t h)
{
	u8g_DrawFrame(&u8g,x,y,w,h);
}

void drawLine(u8g_uint_t x1, u8g_uint_t y1, u8g_uint_t x2, u8g_uint_t y2)
{
	u8g_DrawLine(&u8g,x1,y1,x2,y2);
}

void drawPixel(u8g_uint_t x, u8g_uint_t y)
{
	u8g_DrawPixel(&u8g,x,y);
}

u8g_uint_t drawStr(u8g_uint_t x, u8g_uint_t y, const char *s)
{
	return u8g_DrawStr(&u8g,x,y, s);
}

void setFont(const u8g_fntpgm_uint8_t  *font)
{
	u8g_SetFont(&u8g, font);
}

void firstPage(void)
{
	u8g_FirstPage(&u8g);
}

uint8_t nextPage(void)
{
	return u8g_NextPage(&u8g);
}



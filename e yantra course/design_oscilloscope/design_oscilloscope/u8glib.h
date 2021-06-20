/*
 * u8glib.h
 *
 * Created: 6/7/2021 17:14:54
 * Author: e-Yantra Team
 */ 

#ifndef U8GLIB_H_
#define U8GLIB_H_

#include "u8g.h"

void sys_init(void);
void glcd_setup(void);
void setPrintPos(u8g_uint_t x, u8g_uint_t y); 
u8g_uint_t print_int(int num);
u8g_uint_t print_float(double num, int afterpoint);
void drawFrame(u8g_uint_t x, u8g_uint_t y, u8g_uint_t w, u8g_uint_t h);
void drawLine(u8g_uint_t x1, u8g_uint_t y1, u8g_uint_t x2, u8g_uint_t y2);
void drawPixel(u8g_uint_t x, u8g_uint_t y);
u8g_uint_t drawStr(u8g_uint_t x, u8g_uint_t y, const char *s);
void setFont(const u8g_fntpgm_uint8_t  *font);
void firstPage(void);
uint8_t nextPage(void);

#endif /* U8GLIB_H_ */

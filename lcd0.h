#ifndef _LCD_H_
#define _LCD_H_

#include <avr/io.h>

#define LCD_DATA_DDR	DDRE
#define LCD_CMD_DDR	DDRF

#define LCD_DATA_PORT	PORTE
#define LCD_CMD_PORT	PORTF

#define LCD_RS		PF1
#define LCD_RW		PF2
#define LCD_EN		PF3

#endif


void lcd_init();
void lcd_data(uint8_t data);
void lcd_cmd(uint8_t cmd);
void lcdclock();
void lcd_string(uint8_t *p);
void lcd_integer(uint16_t num);
void lcd_gotoyx(uint8_t y, uint8_t x);
void CreateCGram();
void lcd_clear();

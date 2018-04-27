#include <avr/io.h>
#include "lcd0.h"
#include <util/delay.h>
#include <inttypes.h>



void lcd_init()
{
	
	LCD_DATA_DDR |= 0xF0;
	
	LCD_CMD_DDR |= ((1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN));
	
	
	LCD_CMD_PORT &= ~(1<<LCD_RW);

	lcd_cmd(0x30);
	_delay_ms(10);
	lcd_cmd(0x30);
	_delay_ms(5);
	lcd_cmd(0x30);
	_delay_ms(5);

	lcdclock();
	lcdclock();
	lcdclock();

	lcd_cmd(0x0E);
	lcd_cmd(0x02);
	lcd_cmd(0x06);
	lcd_cmd(0x01);
	lcd_cmd(0x0C);
	
}
void lcd_data(uint8_t data)
{
	//rs 1, mert adatot küldünk
	LCD_CMD_PORT |= (1<<LCD_RS);
	//rw 0, mert írni szeretnénk
	LCD_CMD_PORT &=~(1<<LCD_RW);
	LCD_CMD_PORT &=~(1<<LCD_EN);

	LCD_DATA_PORT &= 0x0F;
	LCD_DATA_PORT |= (data&0xF0);
	lcdclock();

	LCD_DATA_PORT &= 0x0F;
	LCD_DATA_PORT |= ((data<<4)&0xF0);
	lcdclock();
}
void lcd_cmd(uint8_t cmd)
{
	//rs 0, mert parancsot küldünk
	LCD_CMD_PORT &=~(1<<LCD_RS);
	//rw 0, mert írni szeretnénk
	LCD_CMD_PORT &=~(1<<LCD_RW);
	LCD_CMD_PORT &=~(1<<LCD_EN);

	LCD_DATA_PORT &= 0x0F;
	LCD_DATA_PORT |= (cmd&0xF0);
	lcdclock();

	LCD_DATA_PORT &= 0x0F;
	LCD_DATA_PORT |= ((cmd<<4)&0xF0);
	lcdclock();
}
void lcdclock()
{
	LCD_CMD_PORT |= (1<<LCD_EN);
	_delay_ms(5);
	LCD_CMD_PORT &=~(1<<LCD_EN);
	_dly_7s(1); //_delay_ms(5);
}

void lcd_string(uint8_t *p)
{
	while(*p)
	{
		lcd_data(*p++);
	}
}

void lcd_integer(uint16_t num)
{
	lcd_data('0'+num/10000%10); //10000-es helyiérték 0-9
	lcd_data('0'+num/1000%10);
	lcd_data('0'+num/100%10);
	lcd_data('0'+num/10%10);
	lcd_data('0'+num/10);
}

void lcd_gotoyx(uint8_t y, uint8_t x)
{
	switch(y)
	{
		case 0: {y = 0x00 + 0x80 + x; break;}
		case 1: {y = 0x40 + 0x80 + x; break;}
		case 2: {y = 0x10 + 0x80 + x; break;}
		case 3: {y = 0x50 + 0x80 + x; break;}
		default: break;
	}
	lcd_cmd(y);
}
void CreateCGram()
{
	lcd_cmd(0x40);
	lcd_data(0b11111111);
	lcd_data(0b11111111);
	lcd_data(0b11111111);
	lcd_data(0b11111111);
	lcd_data(0b11111111);
	lcd_data(0b11111111);
	lcd_data(0b11111111);
	lcd_data(0b11111111);
	
	lcd_cmd(0x48);
	lcd_data(0b00000000);
	lcd_data(0b00000000);
	lcd_data(0b00000000);
	lcd_data(0b00000000);
	lcd_data(0b00000000);
	lcd_data(0b00000000);
	lcd_data(0b00000000);
	lcd_data(0b00000000);
}


void lcd_clear()
{
	lcd_cmd(0x80);
	lcd_string("                                ");
	lcd_cmd(0xC0);
	lcd_string("                                ");

}

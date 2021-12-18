/*
 * lcd.h
 *
 *  Created on: 15 nov. 2021
 *      Author: evers
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

//Commando's naar display
#define LCD_display_on()     LCD_writecontrol(0x0E)
#define LCD_display_off()    LCD_writecontrol(0x08)
#define LCD_cursor_blink()   LCD_writecontrol(0x0F)
#define LCD_cursor_on()      LCD_writecontrol(0x0E)
#define LCD_cursor_off()     LCD_writecontrol(0x0C)
#define LCD_cursor_left()    LCD_writecontrol(0x10)
#define LCD_cursor_right()   LCD_writecontrol(0x14)
#define LCD_display_sleft()  LCD_writecontrol(0x18)
#define LCD_display_sright() LCD_writecontrol(0x1C)

#define eenregel										// define voor 1x16 display

#define Bit_RESET  		0
#define Bit_SET  		1



//Functie declaratie
void ClearBits(void);
void LCD_cursor_home(void);
void LCD_writecontrol(unsigned char data);
void LCD_init(void);
void LCD_clear(void);
void LCD_put(char *c);
void LCD_puts(char *c);
void LCD_putchar(char c);
void LCD_putint(unsigned int num);
void LCD_XY(unsigned int x, unsigned int y);
void busyflag(void);
void LCD_writenibble(unsigned char data);
void LCD_writebyte(unsigned char data);

#endif /* INC_LCD_H_ */
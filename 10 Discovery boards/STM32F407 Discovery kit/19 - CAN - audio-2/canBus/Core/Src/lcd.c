/*
 * lcd.c
 *
 *  Created on: 15 nov. 2021
 *      Author: evers
 */
#include "lcd.h"
#include "main.h"

extern unsigned char curpos; 									// remember cursorposition


//Functie om alle vier de Bits naar het display te resetten
void ClearBits(void)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
}


//Functie om de cursor naar de home positie te zetten
void LCD_cursor_home(void)
{
   LCD_writecontrol(0x02); 										// cursor home
   curpos=0;               										// reset position
}


// Stuurt een commando naar het display
void LCD_writecontrol(unsigned char data)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    LCD_writebyte(data);
}


//Functie clear screen
void LCD_clear(void)
{
   LCD_writecontrol(0x01); 										// clearscreen
   curpos=0;               										// reset position
   HAL_Delay(5);
   busyflag();
}


//Functie ga naar xY positie op het display
void LCD_XY(unsigned int x, unsigned int y)
{
	unsigned char data;
	switch(y)
	{
	case 0:  data = (1<<7)+0x00+x; break;
	case 1:  data = (1<<7)+0x40+x; break;
	case 2:  data = (1<<7)+0x14+x; break;
	default: data = (1<<7)+0x54+x; break;
	}
	LCD_writecontrol(data);
}


// init LCD
// Display wordt gebruikt in 4bits modus,2 regels, 5x7 dots font.
void LCD_init(void)
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);
	HAL_Delay(150);
    LCD_writebyte(0x30); 										// function-set boot  streepje
    HAL_Delay(150);
    LCD_writebyte(0x30);
    LCD_writebyte(0x30);
    LCD_writebyte(0x02);             							// blink
    HAL_Delay(5);
    LCD_writebyte(0x2C);  										// function set
    HAL_Delay(150);
    LCD_writebyte(0x0E);  										// lcd aan
    HAL_Delay(150);
    LCD_writebyte(0x01);  										// clear screen
    HAL_Delay(150);
    LCD_writebyte(0x06);  										// entry mode set
    HAL_Delay(150);
}


// Zet meegegeven karakter op het scherm
void LCD_putchar(char c)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    LCD_writebyte(c);
    if (++curpos==32) 											// remember cursorpositie
    	curpos=0;
}


// Zet meegegeven string op het scherm
void LCD_put(char *string)
{
    unsigned char k,j;											// vaag display; teken 8 tot 31 is niet uitgevoerd op het scherm
    for (k=0; string[k]; k++)
	{
	#ifdef eenregel												// vaag display; teken 8 tot 31 is niet uitgevoerd op het scherm
    	if(curpos==8) 											// at 8, goto next valid lcd-position
        for (j=0; j<32; j++) LCD_cursor_right();
	#endif
        LCD_putchar(string[k]);
    }
}

// Zet meegegeven string op het scherm na een clear screen
void LCD_puts(char *c)
{
    LCD_clear();
    LCD_put(c);
}


// Zet het meegegeven positief getal op het scherm
void LCD_putint(unsigned int num)
{
    unsigned int rest;
    static unsigned char chars[10] = "0123456789"; 				// possible chars
    char s[17]; 												// display has 16 chars [0..15] + 1 closing null
	s[16]='\0'; 												// closing null set
    int i=15;   												// startposition at last display char
    															// kinda function itoa, integer to ascii
    if(num==0)
        s[i--]='0'; 											// '0' at 14
    else
	{
        while(num>0 && i)
		{
            rest = num%10;
            num /= 10;
            s[i--]=chars[rest];
        }
    }
	LCD_put(&s[i+1]); 											// first, set i to starting pos, undo one i-- too much
}


// Stuurt een 4-bits commando naar het display
void LCD_writenibble(unsigned char data)
{
    ClearBits();

    if (data & 0x01)
    	{HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_SET);}

	if (data & 0x02)
		{HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);}

	if (data & 0x04)
		{HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);}

	if (data & 0x08)
		{HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);}

}

// Stuurt een 8-bits commando naar het display
void LCD_writebyte(unsigned char data)
{
    /* hoogste 4 bits */
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET);  //EN
    LCD_writenibble((data>>4)&0x0F);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET);

    busyflag();

    /* laagste 4 bits */
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET);
    LCD_writenibble(data&0x0F);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET);

    busyflag();
}


void busyflag(void)
{
	uint8_t bitstatus = 0x00;
	uint8_t bitstatus1 = Bit_SET;
	while(bitstatus == bitstatus1)
	{
		  /*Configure GPIO pins : PE3 PE4 PE5 PE6 */
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);  //RS
		//GPIO_SetBits(LCD_RW);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);    //RW
		HAL_Delay(1); //DELAY_ms(1);
		//GPIO_SetBits(LCD_EN);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET);    //EN
		HAL_Delay(1); //DELAY_ms(1);
		bitstatus = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6);
		//GPIO_ResetBits(LCD_EN);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET);    //EN
		HAL_Delay(1); //DELAY_ms(1);
	}
	 /*Configure GPIO pins : PE3 PE4 PE5 PE6 */
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	HAL_Delay(1); //DELAY_ms(1);
}

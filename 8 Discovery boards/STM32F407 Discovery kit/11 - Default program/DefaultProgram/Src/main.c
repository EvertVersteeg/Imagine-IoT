/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Evert Versteeg
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 Imagine Solutions BV.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "stm32f407xx.h"


#define	HIGH			1
#define	BTN_PRESSED		HIGH

// Function declaration
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void EXTI0_IRQHandler(void);
void init(void);

// Declare registers
uint32_t volatile *pEXTI_Pending_Reg			= (uint32_t*)(0x40013C00 + 0x14);    // EXTI => Pending register => Base address from the memory map + offset
uint32_t volatile *pEXTI_Int_Mask_Reg			= (uint32_t*)(0x40013C00 + 0x00);    // EXTI => Interrupt mask register (EXTI_IMR)
uint32_t volatile *pEXTI_Rising_Trig_Sel_Reg	= (uint32_t*)(0x40013C00 + 0x08);    // EXTI => Rising trigger delection register (EXTI_RTSR)
uint32_t volatile *pNVIC_IRQ_EN_Reg				= (uint32_t*)(0xE000E100);   		 // MVIC => IRQ enable register
uint32_t volatile *pCLK_Ctrl_Reg_Abp2			= (uint32_t*)(0x40023800 + 0x44);    // RCC => ABP2 peripheral clock enable register (RCC_ABP2ENR) (bit 14 = 1 => system configuration controller clock enable

void delay(void){
	for(uint32_t i=0 ; i < 500000/2 ; i ++);
}
// MAIN FUNCTION
int main(void)
{
	printf("Hello World\n");

	GPIO_Handle_t GpioLed;
	GPIO_Handle_t GpioBtn;

	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_PeriClockControl(GPIOD, ENABLE);
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;	//LED on PD12 (Green)
	GPIO_Init(&GpioLed);
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;	//LED on PD13 (Orange)
	GPIO_Init(&GpioLed);
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;	//LED on PD14 (Red)
	GPIO_Init(&GpioLed);
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;	//LED on PD15 (Blue)
	GPIO_Init(&GpioLed);


	GpioBtn.pGPIOx = GPIOA;
	GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_PeriClockControl(GPIOA, ENABLE);
	GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;	//User button on PA0
	GPIO_Init(&GpioBtn);

	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) == BTN_PRESSED)
		{
			delay(); //Software delay => Debouncing
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_13);
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_14);
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_15);
		}

	}
}


// Implementation of fault handlers
void HardFault_Handler(void)
{
	printf("Exeption : Hardfault\n");
	while(1);
}

void MemManage_Handler(void)
{
	printf("Exeption : MemManage\n");
	while(1);
}

void BusFault_Handler(void)
{
	printf("Exeption : Busfault\n");
	while(1);
}
// Implementation of wake up button

void EXTI0_IRQHandler(void)
{
	printf("Interrupt : Active\n");
	while(1);
}



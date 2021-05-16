/**
 ******************************************************************************
 * @file           : main.c
 * @author         : E. Versteeg @ Imagine Solutions BV
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2021 Imagine Solutions BV.
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 * Select "SWD" as interface under debug configuration => debugger tab.
 * select under window (in debug mode) => Show View => SWV => SWV ITM Data Console
 * Configure trace in the data console => select port 1 => start trace
 **/

#include "main.h"


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
uint32_t volatile *pGPIOA_Mode_Reg				= (uint32_t*)(0x40020000 + 0x00);    // GPIOA => Mode register
uint32_t volatile *pGPIOD_Mode_Reg				= (uint32_t*)(0x40020C00 + 0x00);    // GPIOD => Mode register
uint32_t volatile *pNVIC_IRQ_EN_Reg				= (uint32_t*)(0xE000E100);   		 // MVIC => IRQ enable register
uint32_t volatile *pCLK_Ctrl_Reg				= (uint32_t*)(0x40023800 + 0x30);    // RCC => GPIOAEN peripheral clock register (RCC_AHB1ENR) (bit 0 = 1 => GPIOA enable
uint32_t volatile *pCLK_Ctrl_Reg_Abp2			= (uint32_t*)(0x40023800 + 0x44);    // RCC => ABP2 peripheral clock enable register (RCC_ABP2ENR) (bit 14 = 1 => system configuration controller clock enable


// MAIN FUNCTION
int main(void)
{
    init();
	printf("Hello World\n");
	/* Loop forever */
	for(;;);
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
	printf("Interrupt : Wake up button pressed\n");

	// Clearing of exti interrupt pending
	*pEXTI_Pending_Reg |= (1 << 0);
}

void init(void)
{

	// GPIO clock enable
	*pCLK_Ctrl_Reg |= (1 << 0);   // Enable clock GPIOA
	*pCLK_Ctrl_Reg |= (1 << 3);   // Enable clock GPIOD

	// GPIO Mode registers init
	*pGPIOA_Mode_Reg &= ~(1 << 0);     //PA1 = 0 => input (button B1)
	*pGPIOD_Mode_Reg |= (1 << 12);     //PD13 = 1 => output (LD3 orange)

	// syscfg clock enable
	*pCLK_Ctrl_Reg_Abp2 |= (1 << 14);


	// ENABLE IRQ User button  B1 => User and wake up on PA0, => EXTI0

	// Edge detection riding edge button setting
	*pEXTI_Rising_Trig_Sel_Reg |= ( 1 << 0);
	// EXTI interrupt enable
	*pEXTI_Int_Mask_Reg |= (1 << 0);
	// NVIC irq enable, EXTI0 enable (IRQ 6)
	*pNVIC_IRQ_EN_Reg |= (1 << 6);
}


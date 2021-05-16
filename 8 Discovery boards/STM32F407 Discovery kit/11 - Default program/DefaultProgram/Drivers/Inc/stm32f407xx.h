/*
 * stm32407xx.h
 *
 *  Created on: 16 mei 2021
 *      Author: evers
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include<stdint.h>

#define __vo volatile

// BASE ADDRESSES of Flash and SRAM Memories
#define FLASH_BASEADDR					0x08000000U   		//Base address off flash
#define SRAM1_BASEADDR					0x20000000U   		//Base address of SRAM1 with size off 112kB
#define SRAM2_BASEADDR					0x20001C00U   		//Base address of SRAM2 with size off 16kB
#define ROM								0x1FFF0000U   		//Base address of ROM
#define SRAM 							SRAM1_BASEADDR

//AHBx and APBx Bus Peripheral base addresses
#define PERIPH_BASE						0x40000000U
#define APB1PERIPH_BASE					PERIPH_BASE
#define APB2PERIPH_BASE					0x40010000U
#define AHB1PERIPH_BASE					0x40020000U			// High speed bus
#define AHB2PERIPH_BASE					0x50000000U

//AHB1 Peripheral addresses
#define GPIOA_BASEADDR					(AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASEADDR					(AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASEADDR					(AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASEADDR					(AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASEADDR					(AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASEADDR					(AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASEADDR					(AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASEADDR					(AHB1PERIPH_BASE + 0x1C00)
#define GPIOI_BASEADDR					(AHB1PERIPH_BASE + 0x2000)


//APB1 Peripheral base addresses
#define I2C1_BASEADDR					(APB1PERIPH_BASE + 0x5400)
#define I2C2_BASEADDR					(APB1PERIPH_BASE + 0x5800)
#define I2C3_BASEADDR					(APB1PERIPH_BASE + 0x5C00)

#define SPI2_BASEADDR					(APB1PERIPH_BASE + 0x3800)
#define SPI3_BASEADDR					(APB1PERIPH_BASE + 0x3C00)

#define USART2_BASEADDR					(APB1PERIPH_BASE + 0x4400)
#define USART3_BASEADDR					(APB1PERIPH_BASE + 0x4800)
#define UART4_BASEADDR					(APB1PERIPH_BASE + 0x4C00)
#define UART5_BASEADDR					(APB1PERIPH_BASE + 0x5000)

//APB2 Peripheral base addresses
#define EXTI_BASEADDR					(APB2PERIPH_BASE + 0x3C00)
#define SPI1_BASEADDR					(APB2PERIPH_BASE + 0x3000)
#define SYSCFG_BASEADDR					(APB2PERIPH_BASE + 0x3800)
#define USART1_BASEADDR					(APB2PERIPH_BASE + 0x1000)
#define USART6_BASEADDR					(APB2PERIPH_BASE + 0x1400)

/************************************peripheral register definition stuctures*************/
typedef struct
{
	__vo uint32_t MODER;			// GPIO port mode register (GPIOx_MODER) 					OFFSET: 0x00
	__vo uint32_t OTYPER;		// GPIO port output type register (GPIOx_OTYPER)  			OFFSET: 0x04
	__vo uint32_t OSPEEDR;		// GPIO port output speed register (GPIOx_OSPEEDR) 			OFFSET: 0x08
	__vo uint32_t PUPDR;			// GPIO port pull-up/pull-down register (GPIOx_PUPDR)		OFFSET: 0x0C
	__vo uint32_t IDR;			// GPIO port input data register (GPIOx_IDR)				OFFSET: 0x10
	__vo uint32_t ODR;			// GPIO port output data register (GPIOx_ODR)				OFFSET: 0x14
	__vo uint32_t BSRR;			// GPIO port bit set/reset register (GPIOx_BSRR)			OFFSET: 0x18
	__vo uint32_t LCKR;			// GPIO port configuration lock register (GPIOx_LCKR) 		OFFSET: 0x1C
	__vo uint32_t AFR[2];		// GPIO alternate function low register (AFR[0] = GPIOx_AFRL + GPIOx_AFR[1] = AFRH) OFFSET: 0x20 - 0x24
}GPIO_RegDef_t;


// peripheral definitions (Peripheral base addresses typecasted to xxx_RegDef_t)
#define GPIOA							((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB							((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC							((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD							((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE							((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF							((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG							((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH							((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI							((GPIO_RegDef_t*)GPIOI_BASEADDR)

#endif /* INC_STM32F407XX_H_ */

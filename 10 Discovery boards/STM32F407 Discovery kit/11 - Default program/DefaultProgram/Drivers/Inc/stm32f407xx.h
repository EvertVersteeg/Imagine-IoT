/**
 ******************************************************************************
 * @file      stm32f407xx.h
 * @author    Evert Versteeg
 * @brief     Hardware setup file for STM32F407 Discovery board
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

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include<stdint.h>
#include<stdio.h>

#define __vo volatile
#define __weak __attribute__((weak))

//**********************************START:Processor Specific Details **********************************
// ARM Cortex Mx Processor NVIC ISERx register Addresses
#define NVIC_ISER0          ( (__vo uint32_t*)0xE000E100 )
#define NVIC_ISER1          ( (__vo uint32_t*)0xE000E104 )
#define NVIC_ISER2          ( (__vo uint32_t*)0xE000E108 )
#define NVIC_ISER3          ( (__vo uint32_t*)0xE000E10C )


// ARM Cortex Mx Processor NVIC ICERx register Addresses
#define NVIC_ICER0 			((__vo uint32_t*)0XE000E180)
#define NVIC_ICER1			((__vo uint32_t*)0XE000E184)
#define NVIC_ICER2  		((__vo uint32_t*)0XE000E188)
#define NVIC_ICER3			((__vo uint32_t*)0XE000E18C)

// ARM Cortex Mx Processor Priority Register Address Calculation
#define NVIC_PR_BASE_ADDR 	((__vo uint32_t*)0xE000E400)

#define NO_PR_BITS_IMPLEMENTED			4

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
#define AHB1PERIPH_BASE					0x40020000U			// AHB => High speed bus
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
#define GPIOJ_BASEADDR					(AHB1PERIPH_BASE + 0x2400)
#define GPIOK_BASEADDR					(AHB1PERIPH_BASE + 0x2800)
#define CRC_BASEADDR					(AHB1PERIPH_BASE + 0x3000)
#define RCC_BASEADDR					(AHB1PERIPH_BASE + 0x3800)

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
	__vo uint32_t MODER;		// GPIO port mode register (GPIOx_MODER) 						OFFSET: 0x00
	__vo uint32_t OTYPER;		// GPIO port output type register (GPIOx_OTYPER)  				OFFSET: 0x04
	__vo uint32_t OSPEEDR;		// GPIO port output speed register (GPIOx_OSPEEDR) 				OFFSET: 0x08
	__vo uint32_t PUPDR;		// GPIO port pull-up/pull-down register (GPIOx_PUPDR)			OFFSET: 0x0C
	__vo uint32_t IDR;			// GPIO port input data register (GPIOx_IDR)					OFFSET: 0x10
	__vo uint32_t ODR;			// GPIO port output data register (GPIOx_ODR)					OFFSET: 0x14
	__vo uint32_t BSRR;			// GPIO port bit set/reset register (GPIOx_BSRR)				OFFSET: 0x18
	__vo uint32_t LCKR;			// GPIO port configuration lock register (GPIOx_LCKR) 			OFFSET: 0x1C
	__vo uint32_t AFR[2];		// GPIO alternate function low register (AFR[0] = GPIOx_AFRL + GPIOx_AFR[1] = AFRH) OFFSET: 0x20 - 0x24
}GPIO_RegDef_t;

/*
 * peripheral register definition structure for RCC
 */
typedef struct
{
	__vo uint32_t RC;			// RCC clock control register (RCC_CR)							OFFSET: 0x00
	__vo uint32_t PLLCFGR;		// RCC PLL configuration register (RCC_PLLCFGR)					OFFSET: 0x04
	__vo uint32_t CFGR;			// RCC clock configuration register (RCC_CFGR)					OFFSET: 0x08
	__vo uint32_t CIR;			// RCC clock interrupt register (RCC_CIR)						OFFSET: 0x0C
	__vo uint32_t AHB1RSTR;		// RCC AHB1 peripheral reset register (RCC_AHB1RSTR)			OFFSET: 0x10
	__vo uint32_t AHB2RSTR;		// RCC AHB2 peripheral reset register (RCC_AHB2RSTR)			OFFSET: 0x14
	__vo uint32_t AHB3RSTR;		// RCC AHB3 peripheral reset register (RCC_AHB3RSTR)			OFFSET: 0x18
	uint32_t	  RESERVED0;	// Reserved 0													OFFSET: 0x1C
	__vo uint32_t APB1RSTR;		// RCC APB1 peripheral reset register (RCC_APB1RSTR)			OFFSET: 0x20
	__vo uint32_t APB2RSTR;		// RCC APB1 peripheral reset register (RCC_APB2RSTR)			OFFSET: 0x24
	uint32_t	  RESERVED1[2];	// Reserved 1													OFFSET: 0x28 - 0x2C
	__vo uint32_t AHB1ENR;		// RCC AHB1 peripheral clock register (RCC_AHB1ENR)				OFFSET: 0x30
	__vo uint32_t AHB2ENR;		// RCC AHB1 peripheral clock register (RCC_AHB2ENR)				OFFSET: 0x34
	__vo uint32_t AHB3ENR;		// RCC AHB1 peripheral clock register (RCC_AHB3ENR)				OFFSET: 0x38
	uint32_t	  RESERVED2;	// Reserved 2													OFFSET: 0x3C
	__vo uint32_t APB1ENR;		// RCC APB1 peripheral reset register (RCC_APB1ENR)				OFFSET: 0x40
	__vo uint32_t APB2ENR;		// RCC APB1 peripheral reset register (RCC_APB2ENR)				OFFSET: 0x44
	uint32_t	  RESERVED3[2];	// Reserved 3													OFFSET: 0x48 - 0x4C
	__vo uint32_t AHB1LPENR;	// RCC AHB1 peripheral clock register (RCC_AHB1LPENR)			OFFSET: 0x50
	__vo uint32_t AHB2LPENR;	// RCC AHB1 peripheral clock register (RCC_AHB2LPENR)			OFFSET: 0x54
	__vo uint32_t AHB3LPENR;	// RCC AHB1 peripheral clock register (RCC_AHB3LPENR)			OFFSET: 0x58
	uint32_t	  RESERVED4;	// Reserved 4													OFFSET: 0x5C
	__vo uint32_t APB1RLPENR;	// RCC APB1 peripheral reset register (RCC_APB1RLPENR)			OFFSET: 0x60
	__vo uint32_t APB2RLPENR;	// RCC APB1 peripheral reset register (RCC_APB2RLPENR)			OFFSET: 0x64
	uint32_t	  RESERVED5[2];	// Reserved 5													OFFSET: 0x68 - 0x6C
	__vo uint32_t BDCR;			// RCC Backup domain control register (RCC_BDCR)				OFFSET: 0x70
	__vo uint32_t CSR;			// RCC clock control & status register (RCC_CSR)				OFFSET: 0x74
	uint32_t	  RESERVED6[2];	// Reserved 6													OFFSET: 0x78 - 0x7C
	__vo uint32_t SSCGR;		// RCC spread spectrum clock generation register (RCC_SSCGR)	OFFSET: 0x80
	__vo uint32_t PLLI2SCFGR;	// RCC PLLI2S configuration register (RCC_PLLI2SCFGR)			OFFSET: 0x84
	__vo uint32_t PLLSAICFGR;	// RCC PLL configuration register (RCC_PLLSAICFGR)				OFFSET: 0x88
	__vo uint32_t DCKCFGR;		// RCC Dedicated clock configuration register (RCC_DCKCFGR)		OFFSET: 0x8C

}RCC_RegDef_t;


/*
 * peripheral register definition structure for EXTI
 */
typedef struct
{
	__vo uint32_t IMR;    // Interrupt mask register (EXTI_IMR)          	  	    			Address offset: 0x00 */
	__vo uint32_t EMR;    // Event mask register (EXTI_EMR)               						Address offset: 0x04 */
	__vo uint32_t RTSR;   // Rising trigger selection register (EXTI_RTSR) 						Address offset: 0x08 */
	__vo uint32_t FTSR;   // Falling trigger selection register (EXTI_FTSR)						Address offset: 0x0C */
	__vo uint32_t SWIER;  // Software interrupt event register (EXTI_SWIER)						Address offset: 0x10 */
	__vo uint32_t PR;     // Pending register (EXTI_PR)                 					   	Address offset: 0x14 */

}EXTI_RegDef_t;


/*
 * peripheral register definition structure for SYSCFG
 */
typedef struct
{
	__vo uint32_t MEMRMP;       // SYSCFG memory remap register (SYSCFG_MEMRMP)                   		Address offset: 0x00
	__vo uint32_t PMC;          // SYSCFG peripheral mode configuration register (SYSCFG_PMC)			Address offset: 0x04
	__vo uint32_t EXTICR[4];    // SYSCFG external interrupt configuration register 1 (SYSCFG_EXTICR1)	Address offset: 0x08-0x14
	uint32_t      RESERVED1[2]; //   	      							  								Reserved, 0x18-0x1C
	__vo uint32_t CMPCR;        //Compensation cell control register (SYSCFG_CMPCR)        				Address offset: 0x20
	uint32_t      RESERVED2[2]; //    				                                     				Reserved, 0x24-0x28
	__vo uint32_t CFGR;         //                                        								Address offset: 0x2C
} SYSCFG_RegDef_t;


// peripheral definitions (Peripheral base addresses type casted to GPIO_RegDef_t)
#define GPIOA							((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB							((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC							((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD							((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE							((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF							((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG							((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH							((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI							((GPIO_RegDef_t*)GPIOI_BASEADDR)
#define GPIOJ							((GPIO_RegDef_t*)GPIOJ_BASEADDR)
#define GPIOK							((GPIO_RegDef_t*)GPIOK_BASEADDR)

#define RCC								((RCC_RegDef_t*)RCC_BASEADDR)
#define EXTI							((EXTI_RegDef_t*)EXTI_BASEADDR)
#define SYSCFG							((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

// Clock enable Macros for GPIOx peripherals
#define GPIOA_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 0 ) )
#define GPIOB_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 1 ) )
#define GPIOC_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 2 ) )
#define GPIOD_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 3 ) )
#define GPIOE_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 4 ) )
#define GPIOF_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 5 ) )
#define GPIOG_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 6 ) )
#define GPIOH_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 7 ) )
#define GPIOI_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 8 ) )
#define GPIOJ_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 9 ) )
#define GPIOK_PCLK_EN()		( RCC->AHB1ENR |= ( 1 << 10 ) )

// Clock enable Macros for I2Cx peripherals
#define I2C1_PCLK_EN()			( RCC->APB1ENR |= ( 1 << 21 ))
#define I2C2_PCLK_EN()			( RCC->APB1ENR |= ( 1 << 22 ))
#define I2C3_PCLK_EN()			( RCC->APB1ENR |= ( 1 << 23 ))

// Clock enable Macros for SPIx peripherals
#define SPI1_PCLK_EN()			( RCC->APB2ENR |= ( 1 << 12 ))
#define SPI2_PCLK_EN()			( RCC->APB1ENR |= ( 1 << 14 ))
#define SPI3_PCLK_EN()			( RCC->APB1ENR |= ( 1 << 15 ))
#define SPI4_PCLK_EN()			( RCC->APB2ENR |= ( 1 << 13 ))

// Clock enable Macros for USARTx peripherals
#define USART1_PCLK_EN()		( RCC->APB2ENR |= ( 1 << 4 ))
#define USART2_PCLK_EN()		( RCC->APB1ENR |= ( 1 << 17 ))
#define USART3_PCLK_EN()		( RCC->APB1ENR |= ( 1 << 18 ))
#define UART4_PCLK_EN()			( RCC->APB1ENR |= ( 1 << 19 ))
#define UART5_PCLK_EN()			( RCC->APB1ENR |= ( 1 << 20 ))
#define USART6_PCLK_EN()		( RCC->APB1ENR |= ( 1 << 5 ))

// Clock Enable Macros for SYSCFG peripheral
#define SYSCFG_PCLK_EN()		( RCC->APB2ENR |= ( 1 << 14 ))

// Clock disable Macros for GPIOx peripherals
#define GPIOA_PCLK_DI()		( RCC->AHB1ENR &= ~( 1 << 0 ) )
#define GPIOB_PCLK_DI()		( RCC->AHB1ENR &= ~( 1 << 1 ) )
#define GPIOC_PCLK_DI()		( RCC->AHB1ENR &= ~( 1 << 2 ) )
#define GPIOD_PCLK_DI()		( RCC->AHB1ENR &= ~( 1 << 3 ) )
#define GPIOE_PCLK_DI()		( RCC->AHB1ENR &= ~( 1 << 4 ) )
#define GPIOF_PCLK_DI()		( RCC->AHB1ENR &= ~( 1 << 5 ) )
#define GPIOG_PCLK_DI()		( RCC->AHB1ENR &= ~( 1 << 6 ) )
#define GPIOH_PCLK_DI()		( RCC->AHB1ENR &= ~( 1 << 7 ) )
#define GPIOI_PCLK_DI()		( RCC->AHB1ENR &= ~( 1 << 8 ) )
#define GPIOJ_PCLK_DI()		( RCC->AHB1ENR &= ~( 1 << 9 ) )
#define GPIOK_PCLK_DI()		( RCC->AHB1ENR &= ~( 1 << 10 ) )

// Clock disable Macros for I2Cx peripherals
#define I2C1_PCLK_DI()			( RCC->APB1ENR &= ~( 1 << 21 ))
#define I2C2_PCLK_DI()			( RCC->APB1ENR &= ~( 1 << 22 ))
#define I2C3_PCLK_DI()			( RCC->APB1ENR &= ~( 1 << 23 ))

// Clock disable Macros for SPIx peripherals
#define SPI1_PCLK_DI()			( RCC->APB2ENR &= ~( 1 << 12 ))
#define SPI2_PCLK_DI()			( RCC->APB1ENR &= ~( 1 << 14 ))
#define SPI3_PCLK_DI()			( RCC->APB1ENR &= ~( 1 << 15 ))
#define SPI4_PCLK_DI()			( RCC->APB2ENR &= ~( 1 << 13 ))

// Clock disable Macros for USARTx peripherals
#define USART1_PCLK_DI()		( RCC->APB2ENR &= ~( 1 << 4 ))
#define USART2_PCLK_DI()		( RCC->APB1ENR &= ~( 1 << 17 ))
#define USART3_PCLK_DI()		( RCC->APB1ENR &= ~( 1 << 18 ))
#define UART4_PCLK_DI()			( RCC->APB1ENR &= ~( 1 << 19 ))
#define UART5_PCLK_DI()			( RCC->APB1ENR &= ~( 1 << 20 ))
#define USART6_PCLK_DI()		( RCC->APB1ENR &= ~( 1 << 5 ))

// Clock disable Macros for SYSCFG peripheral
#define SYSCFG_PCLK_DI()		( RCC->APB2ENR &= ~( 1 << 14 ))

// Macros to reset GPIOx peripherals
#define GPIOA_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOF_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5)); }while(0)
#define GPIOG_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6)); }while(0)
#define GPIOH_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)
#define GPIOI_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 8)); (RCC->AHB1RSTR &= ~(1 << 8)); }while(0)

// returns port code for given GPIOx base address
// This macro returns a code( between 0 to 7) for a given GPIO base address(x)
#define GPIO_BASEADDR_TO_CODE(x)      ( (x == GPIOA)?0:\
										(x == GPIOB)?1:\
										(x == GPIOC)?2:\
										(x == GPIOD)?3:\
								        (x == GPIOE)?4:\
								        (x == GPIOF)?5:\
								        (x == GPIOG)?6:\
								        (x == GPIOH)?7: \
								        (x == GPIOI)?8:0)

// IRQ(Interrupt Request) Numbers of STM32F407x MCU
#define IRQ_NO_EXTI0 		6
#define IRQ_NO_EXTI1 		7
#define IRQ_NO_EXTI2 		8
#define IRQ_NO_EXTI3 		9
#define IRQ_NO_EXTI4 		10
#define IRQ_NO_EXTI9_5 		23
#define IRQ_NO_EXTI15_10 	40
#define IRQ_NO_SPI1			35
#define IRQ_NO_SPI2         36
#define IRQ_NO_SPI3         51
#define IRQ_NO_SPI4
#define IRQ_NO_I2C1_EV     31
#define IRQ_NO_I2C1_ER     32
#define IRQ_NO_USART1	    37
#define IRQ_NO_USART2	    38
#define IRQ_NO_USART3	    39
#define IRQ_NO_UART4	    52
#define IRQ_NO_UART5	    53
#define IRQ_NO_USART6	    71

// macros for all the possible priority levels
#define NVIC_IRQ_PRI0    0
#define NVIC_IRQ_PRI15    15

// Generic Macros
#define ENABLE 					1
#define DISABLE 				0
#define SET						ENABLE
#define RESET					DISABLE
#define GPIO_PIN_SET			SET
#define GPIO_PIN_RESET			RESET

#include "stm32f407xx_gpio_driver.h"

#endif /* INC_STM32F407XX_H_ */
/*
 * stm32f407xx_gpio_driver.h
 *
 * GPIO initialization
 * Enable/Disable GPIO port clock
 * Read From a GPIO pin
 * Write to a GPIO pin
 * Configure alternate functionality
 * Interrupt handling
 *
 *  Created on: 24 mei 2021
 *      Author: evers
 */

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h"

typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinALtFunMOde;
}GPIO_PinConfig_t;

// Handle structure for GPIO pin
typedef struct
{

	GPIO_RegDef_t * pGPIOx;					// Holds the base address of the GPIO port to witch the pin belongs
	GPIO_PinConfig_t GPIO_PinConfig;		// Holds the GPIO pin configuration settings

}GPIO_Handle_t;


// ***** APIs suported by this driver

// Peripheral clock configuration
void GPIO_PeriClockControl(void);
// GPIO Init / De Init
void GPIO_Init(void);
void GPIO_DeInit(void);
// Data read / write
void GPIO_ReadFromInputPin(void);
void GPIO_ReadFromInputPort(void);
void GPIO_WriteToOutputPin(void);
void GPIO_WriteToOutputPort(void);
void GPIO_ToggleOutputPin(void);
// IRQ Configuration and ISR handling
void GPIO_IRQConfig(void);
void GPIO_IRQHandling(void);

#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */

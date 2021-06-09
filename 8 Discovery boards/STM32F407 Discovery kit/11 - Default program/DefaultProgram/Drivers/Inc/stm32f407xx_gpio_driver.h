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


// ***** APIs supported by this driver
void GPIO_PeriClockControl(GPIO_RegDef_t *pGIOx, uint8_t EnorDi);							// Peripheral clock configuration
void GPIO_Init(GPIO_Handle_t *pGIOx);														// GPIO Init
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);													// De Init
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);					// Read from input pin
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);										// Read from input port
uint8_t GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);		// Write to output pin
void GPIO_WriteToOutputPort(void);			// Write to output port
void GPIO_ToggleOutputPin(void);			// Toggle output pin
void GPIO_IRQConfig(void);					// IRQ Configuration and ISR handling
void GPIO_IRQHandling(void);				// IRQ Handling

#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */

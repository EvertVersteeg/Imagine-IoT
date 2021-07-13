
/*************************************************************************************************************************************************************
 *                           GPIO API header file
 *************************************************************************************************************************************************************
 * GPIO initialization
 * Enable/Disable GPIO port clock
 * Read From a GPIO pin or port
 * Write to a GPIO pin or port
 * Configure alternate functionality
 * Interrupt handling
 *
 *  Created on: 24 mei 2021
 *      Author: E. Versteeg
 *      Imagine Solutions BV
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

/*
 * GPIO pin possible modes
 */
#define GPIO_MODE_IN 		0
#define GPIO_MODE_OUT 		1
#define GPIO_MODE_ALTFN 	2
#define GPIO_MODE_ANALOG 	3
#define GPIO_MODE_IT_FT		4		//interrupt input falling edge
#define GPIO_MODE_IT_RT		5		//interrupt input falling edge
#define GPIO_MODE_IT_RFT	6		//interrupt input rising edge falling edge trigger

/*
 * GPIO possible output types
 */
#define GPIO_OP_TYPE_PP		0		//Output type push pull
#define GPIO_OP_TYPE_OD		1		//Output type open drain

/*
 * GPIO possible output types
 */
#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM	1
#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3


/*************************************************************************************************************************************************************
 *                           APIs supported by this driver
 *         For more information about th APIs check the function definition
 *************************************************************************************************************************************************************
 * Peripheral Clock setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGIOx, uint8_t EnorDi);							// Peripheral clock configuration  EnorDi => Enable or Disable

/*
 * Init and de-init GPIO
 */
void GPIO_Init(GPIO_Handle_t *pGIOx);														// GPIO Init
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);													// De Init, set register to its default state using peripheral reset register (RCC_AHB1RSTR)

/*
 * Data read and write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);					// Read from input pin
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);										// Read from input port
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint16_t PinNumber, uint8_t Value);		// Write to output pin
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint8_t Value);							// Write to output port
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint16_t PinNumber);						// Toggle output pin

/*
 * IRQ Configuration and ISR handling
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);				// IRQ Configuration and ISR handling
void GPIO_IRQHandling(uint8_t PinNumber);													// IRQ Handling

#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */

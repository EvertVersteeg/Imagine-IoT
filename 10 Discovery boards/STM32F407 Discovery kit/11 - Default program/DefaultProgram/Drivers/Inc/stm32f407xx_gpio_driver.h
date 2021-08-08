
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
 *  Created on: 24 mei 2021, update 1: 13-07-2021
 *      Author: E. Versteeg
 *      Imagine Solutions BV
 */

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h"

typedef struct
{
	uint8_t GPIO_PinNumber;					/*!< possible values from @GPIO_PIN_NUMBERS >*/
	uint8_t GPIO_PinMode;					/*!< possible values from @GPIO_PIN_MODES >*/
	uint8_t GPIO_PinSpeed;					/*!< possible values from @GPIO_PIN_SPEED >*/
	uint8_t GPIO_PinPuPdControl;			/*!< possible values from @GPIO_PIN_PUPD >*/
	uint8_t GPIO_PinOPType;					/*!< possible values from @GPIO_PIN_OUTPUT_TYPE >*/
	uint8_t GPIO_PinALtFunMode;				/*!< possible values from @GPIO_PIN_ALT_FUN >*/
}GPIO_PinConfig_t;

// Handle structure for GPIO pin
typedef struct
{

	GPIO_RegDef_t * pGPIOx;					// Holds the base address of the GPIO port to witch the pin belongs
	GPIO_PinConfig_t GPIO_PinConfig;		// Holds the GPIO pin configuration settings

}GPIO_Handle_t;

/*
 * @GPIO_PIN_NUMBERS
 * GPIO pin possible numbers
 */
#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15

/*
 * @GPIO_PIN_MODES
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
 * @GPIO_PIN_OUTPUT_TYPE
 * GPIO possible output types
 */
#define GPIO_OP_TYPE_PP		0		//Output type push pull
#define GPIO_OP_TYPE_OD		1		//Output type open drain

/*
 * @GPIO_PIN_SPEED
 * GPIO possible output types
 */
#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM	1
#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3

/*
 * @GPIO_PIN_PUPD
 * GPIO pin pull up AND pull down configuration macros
 */
#define GPIO_NO_PUPD		0		//No pull up / pull down
#define GPIO_PU				1		//Pull Up
#define GPIO_PD				2		//Pull Down


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

// Data read and write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);					// Read from input pin
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);										// Read from input port
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint16_t PinNumber, uint8_t Value);		// Write to output pin
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint8_t Value);							// Write to output port
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint16_t PinNumber);						// Toggle output pin

// IRQ Configuration and ISR handling
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */
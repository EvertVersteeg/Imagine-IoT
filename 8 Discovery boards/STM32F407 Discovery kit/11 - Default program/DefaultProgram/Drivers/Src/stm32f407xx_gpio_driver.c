
/*************************************************************************************************************************************************************
 *                           GPIO API source file
 *************************************************************************************************************************************************************
 *
 *  Created on: 24 mei 2021, update 1: 13-07-2021
 *      Author: E. Versteeg
 *      Imagine Solutions BV
 */


#include "stm32f407xx_gpio_driver.h"


// ***** APIs supported by this driver


/************************************************************************************************************************************************************
 * @fn			- GPIO_PeriClockControl
 *
 * @brief		- This function enables or disables peripheral clock for given GPIO port
 *
 * @param[in]	- Base address of the gpio peripheral
 * @param[in] 	- ENABLE or DISABLE macros
 * @param[in]	-
 *
 * @return		- none
 *
 * @Note		- none
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}else if (pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}else if (pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}else if (pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}else if (pGPIOx == GPIOJ)
		{
			GPIOJ_PCLK_EN();
		}else if (pGPIOx == GPIOK)
		{
			GPIOK_PCLK_EN();
		}
	}else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}else if (pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DI();
		}else if (pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DI();
		}else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}else if (pGPIOx == GPIOI)
		{
			GPIOI_PCLK_DI();
		}else if (pGPIOx == GPIOJ)
		{
			GPIOJ_PCLK_DI();
		}else if (pGPIOx == GPIOK)
		{
			GPIOK_PCLK_DI();
		}
	}

}

/************************************************************************************************************************************************************
 * @fn			- GPIO_Init
 *
 * @brief		- This function is for the init of a specific GPIO pin, the desired configuration is stored in the GPIO Handler.
 *
 * @param[in]	- GPIO Handle structure (stucture with the desired configuration (concerning pinnumber, desired pinmode etc))
 * @param[in] 	-
 * @param[in]	-
 *
 * @return		- none
 *
 * @Note		- none
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)														// GPIO Init
{
	uint32_t temp=0;  //temp. register

	//1. Configure the mode
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		//the non interrupt mode
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);							//Clearing	(2 bits)
		pGPIOHandle->pGPIOx->MODER |= temp;																			//Setting

	}else
	{
		//this part will be code later. (interrupt mode)
	}

	temp=0;
	//2. Configure the speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);							//Clearing	(2 bits)
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;																			//Setting

	temp=0;
	//3. Configure the pupd settings
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);								//Clearing	(2 bits)
	pGPIOHandle->pGPIOx->PUPDR |= temp;																				//Setting

	temp=0;
	//4. Configure the op type
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);							//Clearing   (1 bit)
	pGPIOHandle->pGPIOx->OTYPER |= temp;																			//Setting

	temp=0;
	//5. Configure the alt functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode  == GPIO_MODE_ALTFN)
	{
		//configure the alt function registers.
		uint8_t temp1, temp2;

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));													//Clearing   (4 bit)
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinALtFunMode << (4 * temp2));			//Setting

	}


}

/************************************************************************************************************************************************************
 * @fn			- GPIO_DeInit
 *
 * @brief		- This function sets the GPIO port configuration (GPIOA, B, C etc.) to a default state.
 *
 * @param[in]	- Base address of the gpio peripheral (GPIOA, B, C etc.)
 * @param[in] 	-
 * @param[in]	-
 *
 * @return		- none
 *
 * @Note		- uses: RCC AHB1 peripheral reset register (RCC_AHB1RSTR), set bit 0 - 7 to 1 (GPIOx)
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)														// De Init
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}else if(pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}else if (pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}else if (pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}else if (pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}else if (pGPIOx == GPIOF)
	{
		GPIOF_REG_RESET();
	}else if (pGPIOx == GPIOG)
	{
		GPIOG_REG_RESET();
	}else if (pGPIOx == GPIOH)
	{
		GPIOH_REG_RESET();
	}else if (pGPIOx == GPIOI)
	{
		GPIOI_REG_RESET();
	}
}

/*****************************************************************************************************************
 * @fn			- GPIO_ReadFromInputPin
 *
 * @brief		- This function reads the status of an input pin
 *
 * @param[in]	- Base address of the gpio peripheral (GPIOA, B, C etc.)
 * @param[in] 	- Desired pin to read (PinNumber)
 * @param[in]	-
 *
 * @return		- 1 bit ( 1 or 0)
 *
 * @Note		- none
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)						// Read from input pin
{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value;
}


/************************************************************************************************************************************************************
 * @fn			- GPIO_ReadFromInputPort
 *
 * @brief		-This function reads the status of an input port of GPIO A, B, C etc.
 *
 * @param[in]	- Base address of the gpio peripheral (GPIOA, B, C etc.)
 * @param[in] 	-
 * @param[in]	-
 *
 * @return		- 16 bits input register uint16_t
 *
 * @Note		- none
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)										// Read from input port
{
	uint16_t value;
	value = (uint8_t)pGPIOx->IDR;
	return value;
}

/************************************************************************************************************************************************************
 * @fn			- GPIO_WriteToOutputPin
 *
 * @brief		- This function writes a value (0 or 1) to an output pin
 *
 * @param[in]	- Base address of the gpio peripheral (GPIOA, B, C etc.)
 * @param[in] 	- PinNumber of the desired output pin
 * @param[in]	- Value => 0 or 1
 *
 * @return		- none
 *
 * @Note		- none
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint16_t PinNumber, uint8_t Value)		// Write to output pin
{
	if(Value == GPIO_PIN_SET)
	{
		//write 1 to the output data register at the bit field corresponding to the pin number
		pGPIOx->ODR |= (1 << PinNumber);
	}else
	{
		//write 0
		pGPIOx->ODR &= ~(1 << PinNumber);
	}

}

/************************************************************************************************************************************************************
 * @fn			- GPIO_WriteToOutputPort
 *
 * @brief		- This function writes a value (0 or 1) to an output port
 *
 * @param[in]	- Base address of the gpio peripheral (GPIOA, B, C etc.)
 * @param[in] 	- Value => 0 or 1
 * @param[in]	-
 *
 * @return		- none
 *
 * @Note		- none
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint8_t Value)							// Write to output port
{
	pGPIOx->ODR = Value;
}

/************************************************************************************************************************************************************
 * @fn			- GPIO_ToggleOutputPin
 *
 * @brief		-
 *
 * @param[in]	-
 * @param[in] 	-
 * @param[in]	-
 *
 * @return		- none
 *
 * @Note		- none
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint16_t PinNumber)						// Toggle output pin
{

}

/************************************************************************************************************************************************************
 * @fn			- GPIO_IRQConfig
 *
 * @brief		-
 *
 * @param[in]	-
 * @param[in] 	-
 * @param[in]	-
 *
 * @return		- none
 *
 * @Note		- none
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi)					// IRQ Configuration and ISR handling
{

}

/************************************************************************************************************************************************************
 * @fn			- GPIO_IRQHandling
 *
 * @brief		-
 *
 * @param[in]	-
 * @param[in] 	-
 * @param[in]	-
 *
 * @return		- none
 *
 * @Note		- none
 */
void GPIO_IRQHandling(uint8_t PinNumber)													// IRQ Handling
{

}

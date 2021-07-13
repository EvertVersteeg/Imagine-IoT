
/*************************************************************************************************************************************************************
 *                           GPIO API source file
 *************************************************************************************************************************************************************
 *
 *  Created on: 24 mei 2021
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
void GPIO_Init(GPIO_Handle_t *pGIOx)														// GPIO Init
{
	//1. Configure the mode

	//2. Configure the speed
	//3. Configure the pupd settings
	//4. Configure te optype
	//5. Configure the alt functionality

}

/************************************************************************************************************************************************************
 * @fn			- GPIO_DeInit
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
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)														// De Init
{

}

/*****************************************************************************************************************
 * @fn			- GPIO_ReadFromInputPin
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
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)						// Read from input pin
{
}

/************************************************************************************************************************************************************
 * @fn			- GPIO_ReadFromInputPort
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
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)										// Read from input port
{
}

/************************************************************************************************************************************************************
 * @fn			- GPIO_WriteToOutputPin
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
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint16_t PinNumber, uint8_t Value)		// Write to output pin
{

}

/************************************************************************************************************************************************************
 * @fn			- GPIO_WriteToOutputPort
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
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint8_t Value)							// Write to output port
{

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

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "usb_host.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "audioI2S.h"
#include "MY_CS43L22.h"
#include "wav_player.h"
#include "lcd.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern ApplicationTypeDef Appli_state;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan1;

I2C_HandleTypeDef hi2c1;

I2S_HandleTypeDef hi2s3;
DMA_HandleTypeDef hdma_spi3_tx;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */
#define WAV_FILE1 "first.wav"
#define WAV_FILE2 "second.wav"
#define WAV_FILE3 "third.wav"
#define WAV_FILE4 "fourth.wav"
#define WAV_FILE5 "fifth.wav"
#define WAV_FILE10 "start.wav"
#define WAV_FILE11 "goed.wav"
#define WAV_FILE12 "fout.wav"

CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
CAN_FilterTypeDef FilterConfig;
uint32_t TxMailbox;
uint8_t TxData[8] = {0,0,0,0,0,0,0,0};
uint8_t RxData[8] = {0,0,0,0,0,0,0,0};
unsigned char curpos = 0; 								// remember cursorposition
uint8_t start = 0;
uint8_t spelen = 0;
uint8_t verzonden = 0;
uint8_t ontvangen =0;
uint8_t herstart =0;
uint32_t tellerFijn = 0;
uint32_t tellerGrof = 0;
uint32_t reactieSnelheid = 0;
uint32_t score = 25000;                     //Hoe lager hoe beter (reactiesnelheid), 25000 is meer dan de afspeeltijd van het langste audio file
uint8_t oldpart = 1;										// hulpje omdat rand vaak dezelfde uitkomst heeft, vorige uitkomst wordt onthouden.
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN1_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2S3_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM2_Init(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */




/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	// Deelnemer = 1 (maximaal drie deelnemers)
	// CAN bus deelnemer = 0x243

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN1_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_I2S3_Init();
  MX_FATFS_Init();
  MX_USB_HOST_Init();
  MX_TIM4_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  LCD_init();

  FilterConfig.FilterBank = 0;  							//MASTER
  FilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  FilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  FilterConfig.FilterIdHigh = 0x245<<5;
  FilterConfig.FilterIdLow = 0;
  FilterConfig.FilterMaskIdHigh = 0;
  FilterConfig.FilterMaskIdLow = 0;
  FilterConfig.FilterScale=CAN_FILTERSCALE_32BIT;
  FilterConfig.FilterActivation= ENABLE;
  FilterConfig.SlaveStartFilterBank = 14;

  TxHeader.DLC = 8;            								// grote van bericht 1 - 8 in bytes
  TxHeader.IDE = CAN_ID_STD;   								// standaard berichten versturen geen debug mode
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.StdId = 0x243;        							// identificatie nummer van de CAN deelnemer
  TxHeader.TransmitGlobalTime = DISABLE;

  HAL_CAN_ConfigFilter(&hcan1,&FilterConfig);
  HAL_CAN_Start(&hcan1);
  HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING);

  CS43_Init(hi2c1, MODE_I2S);
  CS43_SetVolume(180);										//volume 0-255
  CS43_Enable_RightLeft(CS43_RIGHT_LEFT);
  audioI2S_setHandle(&hi2s3);
  bool isSdCardMounted=0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    MX_USB_HOST_Process();

    /* USER CODE BEGIN 3 */
    if(verzonden == 1){										//Zet het verzonden bericht op het display (SN = Send Node, SS = Send Song)
    	LCD_cursor_home();									//Naar welke node het bericht is gezonden en welke song gespeeld moet worden
    	HAL_Delay(150);
    	LCD_clear();
    	HAL_Delay(150);
    	LCD_put("SN:");
    	HAL_Delay(150);
    	LCD_putint(TxData[0]);
    	HAL_Delay(150);
    	LCD_put("    SS:");
    	HAL_Delay(150);
    	LCD_putint(TxData[1]);
    	HAL_Delay(150);
    	verzonden = 0;
    }


	if(herstart==1){
		uint8_t song = ((rand() % 5) + 1);							// RANDOM getal modulo % 4 => 0, 1, 2, 3 of 4,  +1 => 1 t/m 5 (keuze liedje)
		uint8_t participant = ((rand() % 3) + 1);					// RANDOM getal modulo % 4 => 0, 1 of 2,  +1 => 1 t/m 3 (keuze naar welke deelnemer het bericht toe moet)
		while (oldpart == participant){								// gedwongen wisselen van deelnemer (rand functie geeft vaak dezelfde uitkomst)
			participant = ((rand() % 3) + 1);
			}
		oldpart = participant;

		if (participant == 1 ){										// Start applicatie als de song op dit bordje moet worden afgespeeld

			RxData[0]=participant;
			RxData[1]=song;
			spelen = 1;
		}else{
			TxData[0]=participant;									// Stuur bericht naar andere deelnemers met welke song er gestart moet worden
			TxData[1]=song;
			HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
			verzonden = 1;

			spelen = 0;

		}
		herstart = 0;
	}

	// Afspelen
    if(spelen == 1)
    {
        if(spelen == 1){										//Zet het ontvangen bericht op het display (ON = Send Node, OS = Send Song)
        	LCD_cursor_home();									//Naar welke node het bericht is gezonden en welke song gespeeld moet worden
        	HAL_Delay(150);
        	LCD_clear();
        	HAL_Delay(150);
        	LCD_put("ON:");
        	HAL_Delay(150);
        	LCD_putint(RxData[0]);
        	HAL_Delay(150);
        	LCD_put("    OS:");
        	HAL_Delay(150);
        	LCD_putint(RxData[1]);
        	HAL_Delay(150);
        	verzonden = 0;
        }
    	if(Appli_state == APPLICATION_START)
    	        {
    				// Do nothing
    	        }
    	        else if(Appli_state == APPLICATION_DISCONNECT)
    	        {
    	          f_mount(NULL, (TCHAR const*)"", 0);
    	          isSdCardMounted = 0;
    	        }
    	    if(Appli_state == APPLICATION_READY)
    	        {
    	          if(!isSdCardMounted)
    	          {
    	            f_mount(&USBHFatFS, (const TCHAR*)USBHPath, 0);						//mount SD-card
    	            isSdCardMounted = 1;
    	          }

    	          // Speel START geluid
    	          HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);					// groene led aan (applicatie gestart)
    	          HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
    	          HAL_Delay(100);
    	          wavPlayer_fileSelect(WAV_FILE10);
    	          HAL_Delay(100);
    	          wavPlayer_play();
    	          while(!wavPlayer_isFinished())
    	          {
    	        	  wavPlayer_process();
    	          }
    	          wavPlayer_stop();
    	          HAL_Delay((rand() % 50)*100);					// RANDOM wachttijd
    	          tellerFijn = 0;                          		//teller fijn 0 - 1000 telt tijdens proces afspelen audiodata, teller start bij afspelen
    	          tellerGrof = 0;								//teller grof x * 1000
    	          reactieSnelheid = 25000;							//Reactiesnelheid, tellerstand na start afspelen

    	          // Speel audiofile 1, 2, 3, 4 of 5 op verzoek van andere node (RxData bericht van ander node)
    	          if(RxData[1]==1)
    	           	   {
    	        	  	  wavPlayer_fileSelect(WAV_FILE1);
    	           	   }
    	          if(RxData[1]==2)
    	           	   {
    	        	  	  wavPlayer_fileSelect(WAV_FILE2);
    	           	   }
    	          if(RxData[1]==3)
    	           	   {
    	              	   wavPlayer_fileSelect(WAV_FILE3);
    	           	   }
    	          if(RxData[1]==4)
    	              {
    	              	  wavPlayer_fileSelect(WAV_FILE4);
    	              }
    	          if(RxData[1]==5)
    	              {
    	              	  wavPlayer_fileSelect(WAV_FILE5);
    	              }
    	          if(RxData[1]==0)
    	              {
    	              	  wavPlayer_fileSelect(WAV_FILE5);
    	              }
    	          wavPlayer_play();
    	          while(!wavPlayer_isFinished())						//afspelen audiofile in loop + start teller
    	            {

    	              if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15))			//drukknop geactiveerd => reactieTijd vastleggen + LED aan
    	              {
    	            	  reactieSnelheid=tellerGrof;
    	            	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);

    	              }
    	              tellerFijn++;
    	              if(tellerFijn>1000){
    	            	  tellerGrof++;
    	            	  tellerFijn=0;
    	              }
    	              wavPlayer_process();								// speel audio data
    	            }
    	          wavPlayer_stop();
    	          }

    	        	if(reactieSnelheid<score){							//speel muziekje "goed" als de score verbeterd is
    	        		score = reactieSnelheid;
    	        		LCD_cursor_home();									//Display score
    	        		HAL_Delay(10);
    	        		LCD_clear();
    	        		HAL_Delay(10);
    	        		LCD_put("Score:  ");
    	        		HAL_Delay(10);
    	        		LCD_putint(score);
    	        		wavPlayer_fileSelect(WAV_FILE11);
    	        		wavPlayer_play();
    	        		while(!wavPlayer_isFinished()){wavPlayer_process();}
    	        		wavPlayer_stop();
    	        		HAL_Delay(500);

    	        	}else{												//speel muziekje "fout" als de score niet verbeterd is
    	        		LCD_cursor_home();									//Display score
    	        		HAL_Delay(10);
    	        		LCD_clear();
    	        		HAL_Delay(10);
    	        		LCD_put("Score:  ");
    	        		HAL_Delay(10);
    	        		LCD_putint(score);
    	        		wavPlayer_fileSelect(WAV_FILE12);
    	        		wavPlayer_play();
    	        		while(!wavPlayer_isFinished()){wavPlayer_process();}
    	        		wavPlayer_stop();
    	        	}
    	        	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);		//zet leds uit
    	        	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);												//reset start applicatie flag
    	        	LCD_cursor_home();
    	        	LCD_clear();
    	        	spelen = 0;
    	        	herstart = 1;
    	        }
  }

}
  /* USER CODE END 3 */


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 14;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_12TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */


  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2S3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S3_Init(void)
{

  /* USER CODE BEGIN I2S3_Init 0 */

  /* USER CODE END I2S3_Init 0 */

  /* USER CODE BEGIN I2S3_Init 1 */

  /* USER CODE END I2S3_Init 1 */
  hi2s3.Instance = SPI3;
  hi2s3.Init.Mode = I2S_MODE_MASTER_TX;
  hi2s3.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s3.Init.DataFormat = I2S_DATAFORMAT_16B;
  hi2s3.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
  hi2s3.Init.AudioFreq = I2S_AUDIOFREQ_44K;
  hi2s3.Init.CPOL = I2S_CPOL_LOW;
  hi2s3.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s3.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
  if (HAL_I2S_Init(&hi2s3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S3_Init 2 */

  /* USER CODE END I2S3_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();


  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_0|GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_0|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE3 PE4 PE5 PE6 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PC13 PC0 PC11 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_0|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PC15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15
                           PD0 PD4 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_0|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

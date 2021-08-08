################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/9\ Nucleo\ boards/NUCLEO-H723ZG/ip_example_2/LwIP_HTTP_Server_Socket_RTOS/Drivers/BSP/STM32H7xx_Nucleo/stm32h7xx_nucleo.c 

OBJS += \
./Drivers/BSP/STM32H743ZI-Nucleo/stm32h7xx_nucleo.o 

C_DEPS += \
./Drivers/BSP/STM32H743ZI-Nucleo/stm32h7xx_nucleo.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32H743ZI-Nucleo/stm32h7xx_nucleo.o: C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/9\ Nucleo\ boards/NUCLEO-H723ZG/ip_example_2/LwIP_HTTP_Server_Socket_RTOS/Drivers/BSP/STM32H7xx_Nucleo/stm32h7xx_nucleo.c Drivers/BSP/STM32H743ZI-Nucleo/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../../Inc -I../../Src -I../../Drivers/CMSIS/Include -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32H7xx_Nucleo -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/Components -I../../Middlewares/Third_Party/LwIP/src/include -I../../Middlewares/Third_Party/LwIP/system -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Middlewares/Third_Party/FreeRTOS/Source -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Utilities -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP/STM32H743ZI-Nucleo/stm32h7xx_nucleo.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"


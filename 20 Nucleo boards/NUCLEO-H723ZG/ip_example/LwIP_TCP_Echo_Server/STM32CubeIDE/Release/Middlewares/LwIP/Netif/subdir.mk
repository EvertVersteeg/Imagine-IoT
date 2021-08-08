################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/9\ Nucleo\ boards/NUCLEO-H723ZG/ip_example/LwIP_TCP_Echo_Server/Middlewares/Third_Party/LwIP/src/netif/ethernet.c \
C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/9\ Nucleo\ boards/NUCLEO-H723ZG/ip_example/LwIP_TCP_Echo_Server/Middlewares/Third_Party/LwIP/system/OS/sys_arch.c 

OBJS += \
./Middlewares/LwIP/Netif/ethernet.o \
./Middlewares/LwIP/Netif/sys_arch.o 

C_DEPS += \
./Middlewares/LwIP/Netif/ethernet.d \
./Middlewares/LwIP/Netif/sys_arch.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/LwIP/Netif/ethernet.o: C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/9\ Nucleo\ boards/NUCLEO-H723ZG/ip_example/LwIP_TCP_Echo_Server/Middlewares/Third_Party/LwIP/src/netif/ethernet.c Middlewares/LwIP/Netif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../../Src -I../../Middlewares/Third_Party/LwIP/system -I../../Drivers/BSP/STM32H7xx_Nucleo -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/BSP/Components -I../../Inc -I../../Middlewares/Third_Party/LwIP/src/include -I../../Drivers/BSP/Components/Common -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/LwIP/Netif/ethernet.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/LwIP/Netif/sys_arch.o: C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/9\ Nucleo\ boards/NUCLEO-H723ZG/ip_example/LwIP_TCP_Echo_Server/Middlewares/Third_Party/LwIP/system/OS/sys_arch.c Middlewares/LwIP/Netif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../../Src -I../../Middlewares/Third_Party/LwIP/system -I../../Drivers/BSP/STM32H7xx_Nucleo -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/BSP/Components -I../../Inc -I../../Middlewares/Third_Party/LwIP/src/include -I../../Drivers/BSP/Components/Common -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/LwIP/Netif/sys_arch.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"


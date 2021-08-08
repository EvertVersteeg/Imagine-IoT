################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/stm32f407xx_gpio_driver.c 

OBJS += \
./Drivers/Src/stm32f407xx_gpio_driver.o 

C_DEPS += \
./Drivers/Src/stm32f407xx_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/stm32f407xx_gpio_driver.o: ../Drivers/Src/stm32f407xx_gpio_driver.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -c -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/8 Discovery boards/STM32F407 Discovery kit/11 - Default program/DefaultProgram/Drivers" -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/8 Discovery boards/STM32F407 Discovery kit/11 - Default program/DefaultProgram/Drivers/Inc" -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/8 Discovery boards/STM32F407 Discovery kit/11 - Default program/DefaultProgram/Drivers/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Src/stm32f407xx_gpio_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


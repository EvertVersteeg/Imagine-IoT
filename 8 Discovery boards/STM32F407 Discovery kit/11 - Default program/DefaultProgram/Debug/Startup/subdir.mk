################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f407vgtx.s 

OBJS += \
./Startup/startup_stm32f407vgtx.o 

S_DEPS += \
./Startup/startup_stm32f407vgtx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/startup_stm32f407vgtx.o: ../Startup/startup_stm32f407vgtx.s Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/8 Discovery boards/STM32F407 Discovery kit/11 - Default program/DefaultProgram/Drivers" -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/8 Discovery boards/STM32F407 Discovery kit/11 - Default program/DefaultProgram/Drivers/Inc" -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/8 Discovery boards/STM32F407 Discovery kit/11 - Default program/DefaultProgram/Drivers/Src" -x assembler-with-cpp -MMD -MP -MF"Startup/startup_stm32f407vgtx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"


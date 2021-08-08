################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32wl55jcix.s 

OBJS += \
./Core/Startup/startup_stm32wl55jcix.o 

S_DEPS += \
./Core/Startup/startup_stm32wl55jcix.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/startup_stm32wl55jcix.o: ../Core/Startup/startup_stm32wl55jcix.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP/IKS01A3" -x assembler-with-cpp -MMD -MP -MF"Core/Startup/startup_stm32wl55jcix.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"


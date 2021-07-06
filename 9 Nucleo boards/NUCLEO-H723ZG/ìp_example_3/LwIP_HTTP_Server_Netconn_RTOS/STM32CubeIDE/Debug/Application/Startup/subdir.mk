################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Application/Startup/startup_stm32h723zgtx.s 

OBJS += \
./Application/Startup/startup_stm32h723zgtx.o 

S_DEPS += \
./Application/Startup/startup_stm32h723zgtx.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Startup/startup_stm32h723zgtx.o: ../Application/Startup/startup_stm32h723zgtx.s Application/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -c -I../../Inc -x assembler-with-cpp -MMD -MP -MF"Application/Startup/startup_stm32h723zgtx.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"


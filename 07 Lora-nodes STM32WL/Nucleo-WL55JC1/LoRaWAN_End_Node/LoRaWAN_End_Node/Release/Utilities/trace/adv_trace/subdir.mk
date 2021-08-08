################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/trace/adv_trace/stm32_adv_trace.c 

OBJS += \
./Utilities/trace/adv_trace/stm32_adv_trace.o 

C_DEPS += \
./Utilities/trace/adv_trace/stm32_adv_trace.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/trace/adv_trace/stm32_adv_trace.o: ../Utilities/trace/adv_trace/stm32_adv_trace.c Utilities/trace/adv_trace/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../Core/Inc -I../LoRaWAN/App -I../LoRaWAN/Target -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Utilities/trace/adv_trace -I../Utilities/misc -I../Utilities/sequencer -I../Utilities/timer -I../Utilities/lpm/tiny_lpm -I../Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -I../Middlewares/Third_Party/SubGHz_Phy -I../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Middlewares/Third_Party/LoRaWAN/Crypto -I../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../Middlewares/Third_Party/LoRaWAN/Mac -I../Middlewares/Third_Party/LoRaWAN/LmHandler -I../Middlewares/Third_Party/LoRaWAN/Utilities -I../Drivers/CMSIS/Include -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP" -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP/IKS01A3" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Utilities/trace/adv_trace/stm32_adv_trace.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


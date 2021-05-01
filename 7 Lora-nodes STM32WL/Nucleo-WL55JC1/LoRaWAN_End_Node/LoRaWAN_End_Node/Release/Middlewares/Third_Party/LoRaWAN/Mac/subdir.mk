################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/LoRaWAN/Mac/LoRaMac.c \
../Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacAdr.c \
../Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacClassB.c \
../Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacCommands.c \
../Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacConfirmQueue.c \
../Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacCrypto.c \
../Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacParser.c \
../Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacSerializer.c 

OBJS += \
./Middlewares/Third_Party/LoRaWAN/Mac/LoRaMac.o \
./Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacAdr.o \
./Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacClassB.o \
./Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacCommands.o \
./Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacConfirmQueue.o \
./Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacCrypto.o \
./Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacParser.o \
./Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacSerializer.o 

C_DEPS += \
./Middlewares/Third_Party/LoRaWAN/Mac/LoRaMac.d \
./Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacAdr.d \
./Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacClassB.d \
./Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacCommands.d \
./Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacConfirmQueue.d \
./Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacCrypto.d \
./Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacParser.d \
./Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacSerializer.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/LoRaWAN/Mac/LoRaMac.o: ../Middlewares/Third_Party/LoRaWAN/Mac/LoRaMac.c Middlewares/Third_Party/LoRaWAN/Mac/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../Core/Inc -I../LoRaWAN/App -I../LoRaWAN/Target -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Utilities/trace/adv_trace -I../Utilities/misc -I../Utilities/sequencer -I../Utilities/timer -I../Utilities/lpm/tiny_lpm -I../Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -I../Middlewares/Third_Party/SubGHz_Phy -I../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Middlewares/Third_Party/LoRaWAN/Crypto -I../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../Middlewares/Third_Party/LoRaWAN/Mac -I../Middlewares/Third_Party/LoRaWAN/LmHandler -I../Middlewares/Third_Party/LoRaWAN/Utilities -I../Drivers/CMSIS/Include -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP" -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP/IKS01A3" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/LoRaWAN/Mac/LoRaMac.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacAdr.o: ../Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacAdr.c Middlewares/Third_Party/LoRaWAN/Mac/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../Core/Inc -I../LoRaWAN/App -I../LoRaWAN/Target -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Utilities/trace/adv_trace -I../Utilities/misc -I../Utilities/sequencer -I../Utilities/timer -I../Utilities/lpm/tiny_lpm -I../Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -I../Middlewares/Third_Party/SubGHz_Phy -I../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Middlewares/Third_Party/LoRaWAN/Crypto -I../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../Middlewares/Third_Party/LoRaWAN/Mac -I../Middlewares/Third_Party/LoRaWAN/LmHandler -I../Middlewares/Third_Party/LoRaWAN/Utilities -I../Drivers/CMSIS/Include -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP" -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP/IKS01A3" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacAdr.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacClassB.o: ../Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacClassB.c Middlewares/Third_Party/LoRaWAN/Mac/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../Core/Inc -I../LoRaWAN/App -I../LoRaWAN/Target -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Utilities/trace/adv_trace -I../Utilities/misc -I../Utilities/sequencer -I../Utilities/timer -I../Utilities/lpm/tiny_lpm -I../Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -I../Middlewares/Third_Party/SubGHz_Phy -I../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Middlewares/Third_Party/LoRaWAN/Crypto -I../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../Middlewares/Third_Party/LoRaWAN/Mac -I../Middlewares/Third_Party/LoRaWAN/LmHandler -I../Middlewares/Third_Party/LoRaWAN/Utilities -I../Drivers/CMSIS/Include -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP" -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP/IKS01A3" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacClassB.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacCommands.o: ../Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacCommands.c Middlewares/Third_Party/LoRaWAN/Mac/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../Core/Inc -I../LoRaWAN/App -I../LoRaWAN/Target -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Utilities/trace/adv_trace -I../Utilities/misc -I../Utilities/sequencer -I../Utilities/timer -I../Utilities/lpm/tiny_lpm -I../Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -I../Middlewares/Third_Party/SubGHz_Phy -I../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Middlewares/Third_Party/LoRaWAN/Crypto -I../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../Middlewares/Third_Party/LoRaWAN/Mac -I../Middlewares/Third_Party/LoRaWAN/LmHandler -I../Middlewares/Third_Party/LoRaWAN/Utilities -I../Drivers/CMSIS/Include -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP" -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP/IKS01A3" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacCommands.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacConfirmQueue.o: ../Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacConfirmQueue.c Middlewares/Third_Party/LoRaWAN/Mac/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../Core/Inc -I../LoRaWAN/App -I../LoRaWAN/Target -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Utilities/trace/adv_trace -I../Utilities/misc -I../Utilities/sequencer -I../Utilities/timer -I../Utilities/lpm/tiny_lpm -I../Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -I../Middlewares/Third_Party/SubGHz_Phy -I../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Middlewares/Third_Party/LoRaWAN/Crypto -I../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../Middlewares/Third_Party/LoRaWAN/Mac -I../Middlewares/Third_Party/LoRaWAN/LmHandler -I../Middlewares/Third_Party/LoRaWAN/Utilities -I../Drivers/CMSIS/Include -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP" -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP/IKS01A3" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacConfirmQueue.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacCrypto.o: ../Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacCrypto.c Middlewares/Third_Party/LoRaWAN/Mac/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../Core/Inc -I../LoRaWAN/App -I../LoRaWAN/Target -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Utilities/trace/adv_trace -I../Utilities/misc -I../Utilities/sequencer -I../Utilities/timer -I../Utilities/lpm/tiny_lpm -I../Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -I../Middlewares/Third_Party/SubGHz_Phy -I../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Middlewares/Third_Party/LoRaWAN/Crypto -I../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../Middlewares/Third_Party/LoRaWAN/Mac -I../Middlewares/Third_Party/LoRaWAN/LmHandler -I../Middlewares/Third_Party/LoRaWAN/Utilities -I../Drivers/CMSIS/Include -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP" -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP/IKS01A3" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacCrypto.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacParser.o: ../Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacParser.c Middlewares/Third_Party/LoRaWAN/Mac/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../Core/Inc -I../LoRaWAN/App -I../LoRaWAN/Target -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Utilities/trace/adv_trace -I../Utilities/misc -I../Utilities/sequencer -I../Utilities/timer -I../Utilities/lpm/tiny_lpm -I../Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -I../Middlewares/Third_Party/SubGHz_Phy -I../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Middlewares/Third_Party/LoRaWAN/Crypto -I../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../Middlewares/Third_Party/LoRaWAN/Mac -I../Middlewares/Third_Party/LoRaWAN/LmHandler -I../Middlewares/Third_Party/LoRaWAN/Utilities -I../Drivers/CMSIS/Include -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP" -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP/IKS01A3" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacParser.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacSerializer.o: ../Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacSerializer.c Middlewares/Third_Party/LoRaWAN/Mac/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../Core/Inc -I../LoRaWAN/App -I../LoRaWAN/Target -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Utilities/trace/adv_trace -I../Utilities/misc -I../Utilities/sequencer -I../Utilities/timer -I../Utilities/lpm/tiny_lpm -I../Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -I../Middlewares/Third_Party/SubGHz_Phy -I../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Middlewares/Third_Party/LoRaWAN/Crypto -I../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../Middlewares/Third_Party/LoRaWAN/Mac -I../Middlewares/Third_Party/LoRaWAN/LmHandler -I../Middlewares/Third_Party/LoRaWAN/Utilities -I../Drivers/CMSIS/Include -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP" -I"C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/7 Lora-nodes STM32WL/Nucleo-WL55JC1/LoRaWAN_End_Node/LoRaWAN_End_Node/Drivers/BSP/IKS01A3" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/LoRaWAN/Mac/LoRaMacSerializer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"


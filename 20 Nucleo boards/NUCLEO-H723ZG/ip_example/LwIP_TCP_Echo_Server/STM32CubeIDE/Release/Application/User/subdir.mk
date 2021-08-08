################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/9\ Nucleo\ boards/NUCLEO-H723ZG/ip_example/LwIP_TCP_Echo_Server/Src/app_ethernet.c \
C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/9\ Nucleo\ boards/NUCLEO-H723ZG/ip_example/LwIP_TCP_Echo_Server/Src/ethernetif.c \
C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/9\ Nucleo\ boards/NUCLEO-H723ZG/ip_example/LwIP_TCP_Echo_Server/Src/main.c \
C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/9\ Nucleo\ boards/NUCLEO-H723ZG/ip_example/LwIP_TCP_Echo_Server/Src/stm32h7xx_it.c \
../Application/User/syscalls.c \
../Application/User/sysmem.c \
C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/9\ Nucleo\ boards/NUCLEO-H723ZG/ip_example/LwIP_TCP_Echo_Server/Src/tcp_echoserver.c 

OBJS += \
./Application/User/app_ethernet.o \
./Application/User/ethernetif.o \
./Application/User/main.o \
./Application/User/stm32h7xx_it.o \
./Application/User/syscalls.o \
./Application/User/sysmem.o \
./Application/User/tcp_echoserver.o 

C_DEPS += \
./Application/User/app_ethernet.d \
./Application/User/ethernetif.d \
./Application/User/main.d \
./Application/User/stm32h7xx_it.d \
./Application/User/syscalls.d \
./Application/User/sysmem.d \
./Application/User/tcp_echoserver.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/app_ethernet.o: C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/9\ Nucleo\ boards/NUCLEO-H723ZG/ip_example/LwIP_TCP_Echo_Server/Src/app_ethernet.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../../Src -I../../Middlewares/Third_Party/LwIP/system -I../../Drivers/BSP/STM32H7xx_Nucleo -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/BSP/Components -I../../Inc -I../../Middlewares/Third_Party/LwIP/src/include -I../../Drivers/BSP/Components/Common -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/app_ethernet.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/ethernetif.o: C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/9\ Nucleo\ boards/NUCLEO-H723ZG/ip_example/LwIP_TCP_Echo_Server/Src/ethernetif.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../../Src -I../../Middlewares/Third_Party/LwIP/system -I../../Drivers/BSP/STM32H7xx_Nucleo -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/BSP/Components -I../../Inc -I../../Middlewares/Third_Party/LwIP/src/include -I../../Drivers/BSP/Components/Common -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/ethernetif.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/main.o: C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/9\ Nucleo\ boards/NUCLEO-H723ZG/ip_example/LwIP_TCP_Echo_Server/Src/main.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../../Src -I../../Middlewares/Third_Party/LwIP/system -I../../Drivers/BSP/STM32H7xx_Nucleo -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/BSP/Components -I../../Inc -I../../Middlewares/Third_Party/LwIP/src/include -I../../Drivers/BSP/Components/Common -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32h7xx_it.o: C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/9\ Nucleo\ boards/NUCLEO-H723ZG/ip_example/LwIP_TCP_Echo_Server/Src/stm32h7xx_it.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../../Src -I../../Middlewares/Third_Party/LwIP/system -I../../Drivers/BSP/STM32H7xx_Nucleo -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/BSP/Components -I../../Inc -I../../Middlewares/Third_Party/LwIP/src/include -I../../Drivers/BSP/Components/Common -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/stm32h7xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/syscalls.o: ../Application/User/syscalls.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../../Src -I../../Middlewares/Third_Party/LwIP/system -I../../Drivers/BSP/STM32H7xx_Nucleo -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/BSP/Components -I../../Inc -I../../Middlewares/Third_Party/LwIP/src/include -I../../Drivers/BSP/Components/Common -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/sysmem.o: ../Application/User/sysmem.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../../Src -I../../Middlewares/Third_Party/LwIP/system -I../../Drivers/BSP/STM32H7xx_Nucleo -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/BSP/Components -I../../Inc -I../../Middlewares/Third_Party/LwIP/src/include -I../../Drivers/BSP/Components/Common -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/tcp_echoserver.o: C:/Users/evers/Documents/IMAGINE-IOT/Imagine-IoT/Imagine-IoT/9\ Nucleo\ boards/NUCLEO-H723ZG/ip_example/LwIP_TCP_Echo_Server/Src/tcp_echoserver.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../../Src -I../../Middlewares/Third_Party/LwIP/system -I../../Drivers/BSP/STM32H7xx_Nucleo -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/BSP/Components -I../../Inc -I../../Middlewares/Third_Party/LwIP/src/include -I../../Drivers/BSP/Components/Common -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/tcp_echoserver.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"


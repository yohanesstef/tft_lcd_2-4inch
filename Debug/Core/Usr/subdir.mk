################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Usr/lora.c \
../Core/Usr/server.c 

OBJS += \
./Core/Usr/lora.o \
./Core/Usr/server.o 

C_DEPS += \
./Core/Usr/lora.d \
./Core/Usr/server.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Usr/%.o Core/Usr/%.su Core/Usr/%.cyclo: ../Core/Usr/%.c Core/Usr/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"/home/yohanes/STM32CubeIDE/tft_lcd_2-4inch/Core/Usr" -I"/home/yohanes/STM32CubeIDE/tft_lcd_2-4inch/Core/Usr/gps" -I"/home/yohanes/STM32CubeIDE/tft_lcd_2-4inch/Core/Usr/lcd" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Usr

clean-Core-2f-Usr:
	-$(RM) ./Core/Usr/lora.cyclo ./Core/Usr/lora.d ./Core/Usr/lora.o ./Core/Usr/lora.su ./Core/Usr/server.cyclo ./Core/Usr/server.d ./Core/Usr/server.o ./Core/Usr/server.su

.PHONY: clean-Core-2f-Usr


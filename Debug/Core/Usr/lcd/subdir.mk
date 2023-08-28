################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Usr/lcd/fonts.c \
../Core/Usr/lcd/lcd_module.c \
../Core/Usr/lcd/lcd_touch.c \
../Core/Usr/lcd/tft.c 

OBJS += \
./Core/Usr/lcd/fonts.o \
./Core/Usr/lcd/lcd_module.o \
./Core/Usr/lcd/lcd_touch.o \
./Core/Usr/lcd/tft.o 

C_DEPS += \
./Core/Usr/lcd/fonts.d \
./Core/Usr/lcd/lcd_module.d \
./Core/Usr/lcd/lcd_touch.d \
./Core/Usr/lcd/tft.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Usr/lcd/%.o Core/Usr/lcd/%.su Core/Usr/lcd/%.cyclo: ../Core/Usr/lcd/%.c Core/Usr/lcd/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"/home/yohanes/STM32CubeIDE/tft_lcd_2-4inch/Core/Usr" -I"/home/yohanes/STM32CubeIDE/tft_lcd_2-4inch/Core/Usr/gps" -I"/home/yohanes/STM32CubeIDE/tft_lcd_2-4inch/Core/Usr/lcd" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Usr-2f-lcd

clean-Core-2f-Usr-2f-lcd:
	-$(RM) ./Core/Usr/lcd/fonts.cyclo ./Core/Usr/lcd/fonts.d ./Core/Usr/lcd/fonts.o ./Core/Usr/lcd/fonts.su ./Core/Usr/lcd/lcd_module.cyclo ./Core/Usr/lcd/lcd_module.d ./Core/Usr/lcd/lcd_module.o ./Core/Usr/lcd/lcd_module.su ./Core/Usr/lcd/lcd_touch.cyclo ./Core/Usr/lcd/lcd_touch.d ./Core/Usr/lcd/lcd_touch.o ./Core/Usr/lcd/lcd_touch.su ./Core/Usr/lcd/tft.cyclo ./Core/Usr/lcd/tft.d ./Core/Usr/lcd/tft.o ./Core/Usr/lcd/tft.su

.PHONY: clean-Core-2f-Usr-2f-lcd


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Usr/gps/NMEA.c \
../Core/Usr/gps/UartRingbuffer.c \
../Core/Usr/gps/gps_M8N.c 

OBJS += \
./Core/Usr/gps/NMEA.o \
./Core/Usr/gps/UartRingbuffer.o \
./Core/Usr/gps/gps_M8N.o 

C_DEPS += \
./Core/Usr/gps/NMEA.d \
./Core/Usr/gps/UartRingbuffer.d \
./Core/Usr/gps/gps_M8N.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Usr/gps/%.o Core/Usr/gps/%.su Core/Usr/gps/%.cyclo: ../Core/Usr/gps/%.c Core/Usr/gps/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"/home/yohanes/STM32CubeIDE/tft_lcd_2-4inch/Core/Usr" -I"/home/yohanes/STM32CubeIDE/tft_lcd_2-4inch/Core/Usr/gps" -I"/home/yohanes/STM32CubeIDE/tft_lcd_2-4inch/Core/Usr/lcd" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Usr-2f-gps

clean-Core-2f-Usr-2f-gps:
	-$(RM) ./Core/Usr/gps/NMEA.cyclo ./Core/Usr/gps/NMEA.d ./Core/Usr/gps/NMEA.o ./Core/Usr/gps/NMEA.su ./Core/Usr/gps/UartRingbuffer.cyclo ./Core/Usr/gps/UartRingbuffer.d ./Core/Usr/gps/UartRingbuffer.o ./Core/Usr/gps/UartRingbuffer.su ./Core/Usr/gps/gps_M8N.cyclo ./Core/Usr/gps/gps_M8N.d ./Core/Usr/gps/gps_M8N.o ./Core/Usr/gps/gps_M8N.su

.PHONY: clean-Core-2f-Usr-2f-gps


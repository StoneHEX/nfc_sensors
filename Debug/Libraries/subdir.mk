################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/irqs.c \
../Libraries/nfc_sensors.c 

OBJS += \
./Libraries/irqs.o \
./Libraries/nfc_sensors.o 

C_DEPS += \
./Libraries/irqs.d \
./Libraries/nfc_sensors.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/%.o Libraries/%.su Libraries/%.cyclo: ../Libraries/%.c Libraries/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Core/Inc -I../Libraries/BSP -I../Libraries -I../Libraries/App -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries

clean-Libraries:
	-$(RM) ./Libraries/irqs.cyclo ./Libraries/irqs.d ./Libraries/irqs.o ./Libraries/irqs.su ./Libraries/nfc_sensors.cyclo ./Libraries/nfc_sensors.d ./Libraries/nfc_sensors.o ./Libraries/nfc_sensors.su

.PHONY: clean-Libraries


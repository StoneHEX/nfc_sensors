################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/App/sensors_bus.c 

OBJS += \
./Libraries/App/sensors_bus.o 

C_DEPS += \
./Libraries/App/sensors_bus.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/App/%.o Libraries/App/%.su Libraries/App/%.cyclo: ../Libraries/App/%.c Libraries/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Core/Inc -I../Libraries/BSP -I../Libraries -I../Libraries/App -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-App

clean-Libraries-2f-App:
	-$(RM) ./Libraries/App/sensors_bus.cyclo ./Libraries/App/sensors_bus.d ./Libraries/App/sensors_bus.o ./Libraries/App/sensors_bus.su

.PHONY: clean-Libraries-2f-App


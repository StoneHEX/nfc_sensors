################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/BSP/Components/lis2dw12_driver/lis2dw12.c 

OBJS += \
./Libraries/BSP/Components/lis2dw12_driver/lis2dw12.o 

C_DEPS += \
./Libraries/BSP/Components/lis2dw12_driver/lis2dw12.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/BSP/Components/lis2dw12_driver/%.o Libraries/BSP/Components/lis2dw12_driver/%.su Libraries/BSP/Components/lis2dw12_driver/%.cyclo: ../Libraries/BSP/Components/lis2dw12_driver/%.c Libraries/BSP/Components/lis2dw12_driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Core/Inc -I../Libraries/BSP -I../Libraries -I../Libraries/App -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-BSP-2f-Components-2f-lis2dw12_driver

clean-Libraries-2f-BSP-2f-Components-2f-lis2dw12_driver:
	-$(RM) ./Libraries/BSP/Components/lis2dw12_driver/lis2dw12.cyclo ./Libraries/BSP/Components/lis2dw12_driver/lis2dw12.d ./Libraries/BSP/Components/lis2dw12_driver/lis2dw12.o ./Libraries/BSP/Components/lis2dw12_driver/lis2dw12.su

.PHONY: clean-Libraries-2f-BSP-2f-Components-2f-lis2dw12_driver


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/BSP/Components/st25dvxxkc/st25dvxxkc.c \
../Libraries/BSP/Components/st25dvxxkc/st25dvxxkc_reg.c 

OBJS += \
./Libraries/BSP/Components/st25dvxxkc/st25dvxxkc.o \
./Libraries/BSP/Components/st25dvxxkc/st25dvxxkc_reg.o 

C_DEPS += \
./Libraries/BSP/Components/st25dvxxkc/st25dvxxkc.d \
./Libraries/BSP/Components/st25dvxxkc/st25dvxxkc_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/BSP/Components/st25dvxxkc/%.o Libraries/BSP/Components/st25dvxxkc/%.su Libraries/BSP/Components/st25dvxxkc/%.cyclo: ../Libraries/BSP/Components/st25dvxxkc/%.c Libraries/BSP/Components/st25dvxxkc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Core/Inc -I../Libraries/App -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-BSP-2f-Components-2f-st25dvxxkc

clean-Libraries-2f-BSP-2f-Components-2f-st25dvxxkc:
	-$(RM) ./Libraries/BSP/Components/st25dvxxkc/st25dvxxkc.cyclo ./Libraries/BSP/Components/st25dvxxkc/st25dvxxkc.d ./Libraries/BSP/Components/st25dvxxkc/st25dvxxkc.o ./Libraries/BSP/Components/st25dvxxkc/st25dvxxkc.su ./Libraries/BSP/Components/st25dvxxkc/st25dvxxkc_reg.cyclo ./Libraries/BSP/Components/st25dvxxkc/st25dvxxkc_reg.d ./Libraries/BSP/Components/st25dvxxkc/st25dvxxkc_reg.o ./Libraries/BSP/Components/st25dvxxkc/st25dvxxkc_reg.su

.PHONY: clean-Libraries-2f-BSP-2f-Components-2f-st25dvxxkc


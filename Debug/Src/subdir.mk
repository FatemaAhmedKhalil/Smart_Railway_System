################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/DHT11_Program.c \
../Src/GPIO_Program.c \
../Src/Link_Porgram.c \
../Src/NVIC_Program.c \
../Src/RCC_Program.c \
../Src/SPI_Program.c \
../Src/TIM_HAL_Program.c \
../Src/TIM_Program.c \
../Src/croutine.c \
../Src/event_groups.c \
../Src/heap_4.c \
../Src/list.c \
../Src/main.c \
../Src/port.c \
../Src/queue.c \
../Src/stream_buffer.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/tasks.c \
../Src/timers.c 

OBJS += \
./Src/DHT11_Program.o \
./Src/GPIO_Program.o \
./Src/Link_Porgram.o \
./Src/NVIC_Program.o \
./Src/RCC_Program.o \
./Src/SPI_Program.o \
./Src/TIM_HAL_Program.o \
./Src/TIM_Program.o \
./Src/croutine.o \
./Src/event_groups.o \
./Src/heap_4.o \
./Src/list.o \
./Src/main.o \
./Src/port.o \
./Src/queue.o \
./Src/stream_buffer.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/tasks.o \
./Src/timers.o 

C_DEPS += \
./Src/DHT11_Program.d \
./Src/GPIO_Program.d \
./Src/Link_Porgram.d \
./Src/NVIC_Program.d \
./Src/RCC_Program.d \
./Src/SPI_Program.d \
./Src/TIM_HAL_Program.d \
./Src/TIM_Program.d \
./Src/croutine.d \
./Src/event_groups.d \
./Src/heap_4.d \
./Src/list.d \
./Src/main.d \
./Src/port.d \
./Src/queue.d \
./Src/stream_buffer.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/tasks.d \
./Src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F401CCUx -DSTM32 -DSTM32F4 -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/DHT11_Program.d ./Src/DHT11_Program.o ./Src/DHT11_Program.su ./Src/GPIO_Program.d ./Src/GPIO_Program.o ./Src/GPIO_Program.su ./Src/Link_Porgram.d ./Src/Link_Porgram.o ./Src/Link_Porgram.su ./Src/NVIC_Program.d ./Src/NVIC_Program.o ./Src/NVIC_Program.su ./Src/RCC_Program.d ./Src/RCC_Program.o ./Src/RCC_Program.su ./Src/SPI_Program.d ./Src/SPI_Program.o ./Src/SPI_Program.su ./Src/TIM_HAL_Program.d ./Src/TIM_HAL_Program.o ./Src/TIM_HAL_Program.su ./Src/TIM_Program.d ./Src/TIM_Program.o ./Src/TIM_Program.su ./Src/croutine.d ./Src/croutine.o ./Src/croutine.su ./Src/event_groups.d ./Src/event_groups.o ./Src/event_groups.su ./Src/heap_4.d ./Src/heap_4.o ./Src/heap_4.su ./Src/list.d ./Src/list.o ./Src/list.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/port.d ./Src/port.o ./Src/port.su ./Src/queue.d ./Src/queue.o ./Src/queue.su ./Src/stream_buffer.d ./Src/stream_buffer.o ./Src/stream_buffer.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/tasks.d ./Src/tasks.o ./Src/tasks.su ./Src/timers.d ./Src/timers.o ./Src/timers.su

.PHONY: clean-Src


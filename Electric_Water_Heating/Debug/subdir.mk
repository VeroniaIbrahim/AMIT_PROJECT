################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_Program.c \
../DIO_Program.c \
../EEPROM_Program.c \
../EXTI_Program.c \
../GIE_Program.c \
../ON_OFF_Button_Program.c \
../Project.c \
../SevenSegment_Program.c \
../TIMER1_Program.c \
../TIMER_Program.c \
../TWI_Program.c \
../main.c 

OBJS += \
./ADC_Program.o \
./DIO_Program.o \
./EEPROM_Program.o \
./EXTI_Program.o \
./GIE_Program.o \
./ON_OFF_Button_Program.o \
./Project.o \
./SevenSegment_Program.o \
./TIMER1_Program.o \
./TIMER_Program.o \
./TWI_Program.o \
./main.o 

C_DEPS += \
./ADC_Program.d \
./DIO_Program.d \
./EEPROM_Program.d \
./EXTI_Program.d \
./GIE_Program.d \
./ON_OFF_Button_Program.d \
./Project.d \
./SevenSegment_Program.d \
./TIMER1_Program.d \
./TIMER_Program.d \
./TWI_Program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



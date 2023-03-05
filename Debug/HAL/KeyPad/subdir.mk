################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KeyPad/KeyPad_Prog.c 

OBJS += \
./HAL/KeyPad/KeyPad_Prog.o 

C_DEPS += \
./HAL/KeyPad/KeyPad_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/KeyPad/%.o: ../HAL/KeyPad/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\HAL\AT24C16A" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\MCAL\I2C" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\MCAL\SPI" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\MCAL\UART" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\HAL\Servo" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\HAL\DCMotor" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\MCAL\WDT" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\MCAL\Timer" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\HAL\LM35" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\MCAL\ADC" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\MCAL\GIE" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\MCAL\ExtInt" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\MCAL\ExtInt" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\HAL\KeyPad" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\HAL\LCD" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\HAL\SSD" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\HAL\PB" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\APP" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\HAL" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\MCAL" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\HAL\LED" -I"C:\Users\Ali Mohamed\Downloads\512_GROUP\MCAL\DIO" -Wall -g2 -gstabs -O1 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



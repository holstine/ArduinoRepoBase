################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/code/Arduino/arduino-1.0.1/libraries/Servo/Servo.cpp 

OBJS += \
./Servo/Servo.o 

CPP_DEPS += \
./Servo/Servo.d 


# Each subdirectory must supply rules for building sources it contributes
Servo/Servo.o: C:/code/Arduino/arduino-1.0.1/libraries/Servo/Servo.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I../CNC/SD -I"C:\code\Arduino\A2\arduino-1.0.1\libraries\SD" -D__IN_ECLIPSE__=1 -DARDUINO=10.1 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CNC.cpp \
../GCode_Interpreter.cpp \
../init.cpp \
../process_string.cpp \
../stepper_control.cpp 

OBJS += \
./CNC.o \
./GCode_Interpreter.o \
./init.o \
./process_string.o \
./stepper_control.o 

CPP_DEPS += \
./CNC.d \
./GCode_Interpreter.d \
./init.d \
./process_string.d \
./stepper_control.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I../CNC/Arduino_Uno/arduino -I../CNC/Arduino_Uno/standard -I../CNC/CNC -IC:/code/ArduinoWorkspace/CNC/CNC/SD -I../CNC/CNC/Servo -D__IN_ECLIPSE__=1 -DARDUINO=10.1 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '



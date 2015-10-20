################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CNC3.cpp \
../CNCMachine.cpp \
../FileReader.cpp \
../GcodeProcessor.cpp \
../LCDOutput.cpp \
../Point.cpp 

OBJS += \
./CNC3.o \
./CNCMachine.o \
./FileReader.o \
./GcodeProcessor.o \
./LCDOutput.o \
./Point.o 

CPP_DEPS += \
./CNC3.d \
./CNCMachine.d \
./FileReader.d \
./GcodeProcessor.d \
./LCDOutput.d \
./Point.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\cores\arduino" -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\variants\standard" -I"C:\code\ArduinoWorkspace\CNC3" -I"C:\code\Arduino\arduino-1.0.1\libraries\SD" -D__IN_ECLIPSE__=1 -DARDUINO=101 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '



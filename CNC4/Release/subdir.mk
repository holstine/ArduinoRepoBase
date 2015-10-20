################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CNC4.cpp \
../CNCMachine.cpp \
../FileReader.cpp \
../GcodeProcessor.cpp \
../LCDOutput.cpp \
../Point.cpp 

OBJS += \
./CNC4.o \
./CNCMachine.o \
./FileReader.o \
./GcodeProcessor.o \
./LCDOutput.o \
./Point.o 

CPP_DEPS += \
./CNC4.d \
./CNCMachine.d \
./FileReader.d \
./GcodeProcessor.d \
./LCDOutput.d \
./Point.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\cores\arduino" -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\variants\mega" -I"C:\code\ArduinoWorkspace\CNC4" -I"C:\code\Arduino\arduino-1.0.1\libraries\SD" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=101 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega1280 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '



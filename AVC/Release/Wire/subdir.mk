################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/code/Arduino/arduino-1.0.1/libraries/Wire/Wire.cpp 

C_SRCS += \
C:/code/Arduino/arduino-1.0.1/libraries/Wire/twi.c 

OBJS += \
./Wire/Wire.o \
./Wire/twi.o 

C_DEPS += \
./Wire/twi.d 

CPP_DEPS += \
./Wire/Wire.d 


# Each subdirectory must supply rules for building sources it contributes
Wire/Wire.o: C:/code/Arduino/arduino-1.0.1/libraries/Wire/Wire.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\cores\arduino" -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\variants\standard" -I"C:\code\ArduinoWorkspace\AVC" -I"C:\code\Arduino\arduino-1.0.1\libraries\Wire" -I"C:\code\Arduino\arduino-1.0.1\libraries\Servo" -D__IN_ECLIPSE__=1 -DARDUINO=10.1 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

Wire/twi.o: C:/code/Arduino/arduino-1.0.1/libraries/Wire/twi.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\cores\arduino" -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\variants\standard" -I"C:\code\ArduinoWorkspace\AVC" -I"C:\code\Arduino\arduino-1.0.1\libraries\Wire" -I"C:\code\Arduino\arduino-1.0.1\libraries\Servo" -D__IN_ECLIPSE__=1 -DARDUINO=10.1 -Wall -Os -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



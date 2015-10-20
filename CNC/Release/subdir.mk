################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
../CNC.ino 

OBJS += \
./CNC.o 

INO_DEPS += \
./CNC.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.ino
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\cores\arduino" -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\variants\standard" -I"C:\code\ArduinoWorkspace\CNC" -I"C:\code\Arduino\A2\arduino-1.0.1\libraries\SD" -D__IN_ECLIPSE__=1 -DARDUINO=101 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '



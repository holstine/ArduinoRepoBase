################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/code/Arduino/A2/arduino-1.0.1/libraries/SD/utility/Sd2Card.cpp \
C:/code/Arduino/A2/arduino-1.0.1/libraries/SD/utility/SdFile.cpp \
C:/code/Arduino/A2/arduino-1.0.1/libraries/SD/utility/SdVolume.cpp 

OBJS += \
./SD/utility/Sd2Card.o \
./SD/utility/SdFile.o \
./SD/utility/SdVolume.o 

CPP_DEPS += \
./SD/utility/Sd2Card.d \
./SD/utility/SdFile.d \
./SD/utility/SdVolume.d 


# Each subdirectory must supply rules for building sources it contributes
SD/utility/Sd2Card.o: C:/code/Arduino/A2/arduino-1.0.1/libraries/SD/utility/Sd2Card.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I../CNC/Arduino_Uno/arduino -I../CNC/Arduino_Uno/standard -I../CNC/CNC -IC:/code/ArduinoWorkspace/CNC/CNC/SD -I../CNC/CNC/Servo -D__IN_ECLIPSE__=1 -DARDUINO=10.1 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

SD/utility/SdFile.o: C:/code/Arduino/A2/arduino-1.0.1/libraries/SD/utility/SdFile.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I../CNC/Arduino_Uno/arduino -I../CNC/Arduino_Uno/standard -I../CNC/CNC -IC:/code/ArduinoWorkspace/CNC/CNC/SD -I../CNC/CNC/Servo -D__IN_ECLIPSE__=1 -DARDUINO=10.1 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

SD/utility/SdVolume.o: C:/code/Arduino/A2/arduino-1.0.1/libraries/SD/utility/SdVolume.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I../CNC/Arduino_Uno/arduino -I../CNC/Arduino_Uno/standard -I../CNC/CNC -IC:/code/ArduinoWorkspace/CNC/CNC/SD -I../CNC/CNC/Servo -D__IN_ECLIPSE__=1 -DARDUINO=10.1 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '



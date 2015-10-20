################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/code/Arduino/A2/arduino-1.0.1/libraries/SD/File.cpp \
C:/code/Arduino/A2/arduino-1.0.1/libraries/SD/SD.cpp \
C:/code/Arduino/A2/arduino-1.0.1/libraries/SD/Sd2Card.cpp \
C:/code/Arduino/A2/arduino-1.0.1/libraries/SD/SdFile.cpp \
C:/code/Arduino/A2/arduino-1.0.1/libraries/SD/SdVolume.cpp 

OBJS += \
./SD/File.o \
./SD/SD.o \
./SD/Sd2Card.o \
./SD/SdFile.o \
./SD/SdVolume.o 

CPP_DEPS += \
./SD/File.d \
./SD/SD.d \
./SD/Sd2Card.d \
./SD/SdFile.d \
./SD/SdVolume.d 


# Each subdirectory must supply rules for building sources it contributes
SD/File.o: C:/code/Arduino/A2/arduino-1.0.1/libraries/SD/File.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I../CNC/Arduino_Uno/arduino -I../CNC/Arduino_Uno/standard -I../CNC/CNC -IC:/code/ArduinoWorkspace/CNC/CNC/SD -I../CNC/CNC/Servo -D__IN_ECLIPSE__=1 -DARDUINO=10.1 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

SD/SD.o: C:/code/Arduino/A2/arduino-1.0.1/libraries/SD/SD.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I../CNC/Arduino_Uno/arduino -I../CNC/Arduino_Uno/standard -I../CNC/CNC -IC:/code/ArduinoWorkspace/CNC/CNC/SD -I../CNC/CNC/Servo -D__IN_ECLIPSE__=1 -DARDUINO=10.1 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

SD/Sd2Card.o: C:/code/Arduino/A2/arduino-1.0.1/libraries/SD/Sd2Card.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I../CNC/Arduino_Uno/arduino -I../CNC/Arduino_Uno/standard -I../CNC/CNC -IC:/code/ArduinoWorkspace/CNC/CNC/SD -I../CNC/CNC/Servo -D__IN_ECLIPSE__=1 -DARDUINO=10.1 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

SD/SdFile.o: C:/code/Arduino/A2/arduino-1.0.1/libraries/SD/SdFile.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I../CNC/Arduino_Uno/arduino -I../CNC/Arduino_Uno/standard -I../CNC/CNC -IC:/code/ArduinoWorkspace/CNC/CNC/SD -I../CNC/CNC/Servo -D__IN_ECLIPSE__=1 -DARDUINO=10.1 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

SD/SdVolume.o: C:/code/Arduino/A2/arduino-1.0.1/libraries/SD/SdVolume.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I../CNC/Arduino_Uno/arduino -I../CNC/Arduino_Uno/standard -I../CNC/CNC -IC:/code/ArduinoWorkspace/CNC/CNC/SD -I../CNC/CNC/Servo -D__IN_ECLIPSE__=1 -DARDUINO=10.1 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/code/Arduino/arduino-1.0.1/libraries/SD/File.cpp \
C:/code/Arduino/arduino-1.0.1/libraries/SD/SD.cpp \
C:/code/Arduino/arduino-1.0.1/libraries/SD/Sd2Card.cpp \
C:/code/Arduino/arduino-1.0.1/libraries/SD/SdFile.cpp \
C:/code/Arduino/arduino-1.0.1/libraries/SD/SdVolume.cpp 

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
SD/File.o: C:/code/Arduino/arduino-1.0.1/libraries/SD/File.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\cores\arduino" -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\variants\mega" -I"C:\code\ArduinoWorkspace\CNC4" -I"C:\code\Arduino\arduino-1.0.1\libraries\SD" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=101 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega1280 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

SD/SD.o: C:/code/Arduino/arduino-1.0.1/libraries/SD/SD.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\cores\arduino" -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\variants\mega" -I"C:\code\ArduinoWorkspace\CNC4" -I"C:\code\Arduino\arduino-1.0.1\libraries\SD" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=101 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega1280 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

SD/Sd2Card.o: C:/code/Arduino/arduino-1.0.1/libraries/SD/Sd2Card.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\cores\arduino" -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\variants\mega" -I"C:\code\ArduinoWorkspace\CNC4" -I"C:\code\Arduino\arduino-1.0.1\libraries\SD" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=101 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega1280 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

SD/SdFile.o: C:/code/Arduino/arduino-1.0.1/libraries/SD/SdFile.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\cores\arduino" -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\variants\mega" -I"C:\code\ArduinoWorkspace\CNC4" -I"C:\code\Arduino\arduino-1.0.1\libraries\SD" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=101 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega1280 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '

SD/SdVolume.o: C:/code/Arduino/arduino-1.0.1/libraries/SD/SdVolume.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\cores\arduino" -I"C:\code\Arduino\arduino-1.0.1\hardware\arduino\variants\mega" -I"C:\code\ArduinoWorkspace\CNC4" -I"C:\code\Arduino\arduino-1.0.1\libraries\SD" -D__IN_ECLIPSE__=1 -DUSB_VID= -DUSB_PID= -DARDUINO=101 -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -g -mmcu=atmega1280 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -c -o "$@" -x c++ "$<"
	@echo 'Finished building: $<'
	@echo ' '



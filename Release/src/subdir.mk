################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Date.cpp \
../src/DcfTime.cpp \
../src/Time.cpp \
../src/lcd-routines.cpp \
../src/main.cpp \
../src/system.cpp 

OBJS += \
./src/Date.o \
./src/DcfTime.o \
./src/Time.o \
./src/lcd-routines.o \
./src/main.o \
./src/system.o 

CPP_DEPS += \
./src/Date.d \
./src/DcfTime.d \
./src/Time.d \
./src/lcd-routines.d \
./src/main.d \
./src/system.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -fno-use-cxa-atexit -mmcu=atmega8 -DF_CPU=4194304UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



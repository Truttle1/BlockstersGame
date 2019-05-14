################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ui/monsterui/Behavior.cpp \
../src/ui/monsterui/ColorBox.cpp \
../src/ui/monsterui/MonsterUI.cpp \
../src/ui/monsterui/RadioButton.cpp \
../src/ui/monsterui/TextBox.cpp 

OBJS += \
./src/ui/monsterui/Behavior.o \
./src/ui/monsterui/ColorBox.o \
./src/ui/monsterui/MonsterUI.o \
./src/ui/monsterui/RadioButton.o \
./src/ui/monsterui/TextBox.o 

CPP_DEPS += \
./src/ui/monsterui/Behavior.d \
./src/ui/monsterui/ColorBox.d \
./src/ui/monsterui/MonsterUI.d \
./src/ui/monsterui/RadioButton.d \
./src/ui/monsterui/TextBox.d 


# Each subdirectory must supply rules for building sources it contributes
src/ui/monsterui/%.o: ../src/ui/monsterui/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



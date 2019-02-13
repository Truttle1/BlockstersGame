################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ui/monsterui/MonsterUI.cpp 

OBJS += \
./src/ui/monsterui/MonsterUI.o 

CPP_DEPS += \
./src/ui/monsterui/MonsterUI.d 


# Each subdirectory must supply rules for building sources it contributes
src/ui/monsterui/%.o: ../src/ui/monsterui/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ui/fileui/FileUI.cpp 

OBJS += \
./src/ui/fileui/FileUI.o 

CPP_DEPS += \
./src/ui/fileui/FileUI.d 


# Each subdirectory must supply rules for building sources it contributes
src/ui/fileui/%.o: ../src/ui/fileui/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ui/UI.cpp \
../src/ui/UIButton.cpp 

OBJS += \
./src/ui/UI.o \
./src/ui/UIButton.o 

CPP_DEPS += \
./src/ui/UI.d \
./src/ui/UIButton.d 


# Each subdirectory must supply rules for building sources it contributes
src/ui/%.o: ../src/ui/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



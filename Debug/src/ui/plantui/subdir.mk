################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ui/plantui/PlantUI.cpp 

OBJS += \
./src/ui/plantui/PlantUI.o 

CPP_DEPS += \
./src/ui/plantui/PlantUI.d 


# Each subdirectory must supply rules for building sources it contributes
src/ui/plantui/%.o: ../src/ui/plantui/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/objects/EyeCandy.cpp \
../src/objects/Fog.cpp \
../src/objects/GameObject.cpp 

OBJS += \
./src/objects/EyeCandy.o \
./src/objects/Fog.o \
./src/objects/GameObject.o 

CPP_DEPS += \
./src/objects/EyeCandy.d \
./src/objects/Fog.d \
./src/objects/GameObject.d 


# Each subdirectory must supply rules for building sources it contributes
src/objects/%.o: ../src/objects/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



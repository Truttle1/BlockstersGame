################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/img/MonsterImg.cpp \
../src/img/ObjectColors.cpp \
../src/img/PlantImg.cpp 

OBJS += \
./src/img/MonsterImg.o \
./src/img/ObjectColors.o \
./src/img/PlantImg.o 

CPP_DEPS += \
./src/img/MonsterImg.d \
./src/img/ObjectColors.d \
./src/img/PlantImg.d 


# Each subdirectory must supply rules for building sources it contributes
src/img/%.o: ../src/img/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



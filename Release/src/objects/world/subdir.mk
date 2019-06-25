################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/objects/world/Ground.cpp \
../src/objects/world/Meat.cpp \
../src/objects/world/Monster.cpp \
../src/objects/world/Object.cpp \
../src/objects/world/Plant.cpp \
../src/objects/world/Shelter.cpp 

OBJS += \
./src/objects/world/Ground.o \
./src/objects/world/Meat.o \
./src/objects/world/Monster.o \
./src/objects/world/Object.o \
./src/objects/world/Plant.o \
./src/objects/world/Shelter.o 

CPP_DEPS += \
./src/objects/world/Ground.d \
./src/objects/world/Meat.d \
./src/objects/world/Monster.d \
./src/objects/world/Object.d \
./src/objects/world/Plant.d \
./src/objects/world/Shelter.d 


# Each subdirectory must supply rules for building sources it contributes
src/objects/world/%.o: ../src/objects/world/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Caregiver.cpp \
../InputData.cpp \
../MarkovProcessAnalytic.cpp \
../RespiteService.cpp \
../Simulation.cpp \
../main.cpp 

OBJS += \
./Caregiver.o \
./InputData.o \
./MarkovProcessAnalytic.o \
./RespiteService.o \
./Simulation.o \
./main.o 

CPP_DEPS += \
./Caregiver.d \
./InputData.d \
./MarkovProcessAnalytic.d \
./RespiteService.d \
./Simulation.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



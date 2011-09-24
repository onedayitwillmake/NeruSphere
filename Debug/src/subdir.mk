################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/HelloEclipse.cpp 

OBJS += \
./src/HelloEclipse.o 

CPP_DEPS += \
./src/HelloEclipse.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Users/mariogonzalez/GIT/LIBRARY/Cinder/boost -I/Users/mariogonzalez/GIT/LIBRARY/Cinder/include -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -O0 -g -Wall -c -fmessage-length=0 -arch i386 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Board.cpp \
../src/Form1.cpp \
../src/MagicOthello.cpp \
../src/MagicOthelloEntry.cpp \
../src/Options.cpp \
../src/optionform.cpp \
../src/squarecontrol.cpp 

OBJS += \
./src/Board.o \
./src/Form1.o \
./src/MagicOthello.o \
./src/MagicOthelloEntry.o \
./src/Options.o \
./src/optionform.o \
./src/squarecontrol.o 

CPP_DEPS += \
./src/Board.d \
./src/Form1.d \
./src/MagicOthello.d \
./src/MagicOthelloEntry.d \
./src/Options.d \
./src/optionform.d \
./src/squarecontrol.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: bada C++ Compiler'
	i686-mingw32-g++ -D_DEBUG -DSHP -DBUILD_DLL -I"D:/Bada/1.0.0/include" -I"D:/Bada/1.0.0/IDE/workspace/MagicOthello/inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	i686-mingw32-g++ -D_DEBUG -DSHP -DBUILD_DLL -I"D:/Bada/1.0.0/include" -I"D:/Bada/1.0.0/IDE/workspace/MagicOthello/inc" -O0 -g3 -Wall -E -fmessage-length=0 -o"D:/Bada/1.0.0/IDE/workspace/repository/MagicOthello/Simulator-Debug/$(notdir $(basename $@).i)" "$<"
	@echo 'Finished building: $<'
	@echo ' '



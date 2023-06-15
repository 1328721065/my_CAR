################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/HALL.c \
../code/PID_control.c \
../code/adc.c \
../code/config.c \
../code/flash_save.c \
../code/key.c \
../code/motor.c \
../code/motor_filter.c \
../code/pwm_input.c \
../code/receive.c 

OBJS += \
./code/HALL.o \
./code/PID_control.o \
./code/adc.o \
./code/config.o \
./code/flash_save.o \
./code/key.o \
./code/motor.o \
./code/motor_filter.o \
./code/pwm_input.o \
./code/receive.o 

COMPILED_SRCS += \
./code/HALL.src \
./code/PID_control.src \
./code/adc.src \
./code/config.src \
./code/flash_save.src \
./code/key.src \
./code/motor.src \
./code/motor_filter.src \
./code/pwm_input.src \
./code/receive.src 

C_DEPS += \
./code/HALL.d \
./code/PID_control.d \
./code/adc.d \
./code/config.d \
./code/flash_save.d \
./code/key.d \
./code/motor.d \
./code/motor_filter.d \
./code/pwm_input.d \
./code/receive.d 


# Each subdirectory must supply rules for building sources it contributes
code/%.src: ../code/%.c code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fG:/AURIX-v1.8.0-workspace/Seekfree_TC264_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

code/%.o: ./code/%.src code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '



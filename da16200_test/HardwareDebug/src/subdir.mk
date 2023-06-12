################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/HAL.c \
../src/da16200_AT.c \
../src/da16200_test.c \
../src/dialog_wifi_demo.c \
../src/http_server.c \
../src/sensor.c 

COMPILER_OBJS += \
src/HAL.obj \
src/da16200_AT.obj \
src/da16200_test.obj \
src/dialog_wifi_demo.obj \
src/http_server.obj \
src/sensor.obj 

C_DEPS += \
src/HAL.d \
src/da16200_AT.d \
src/da16200_test.d \
src/dialog_wifi_demo.d \
src/http_server.d \
src/sensor.d 

# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\cDepSubCommand.tmp"
	ccrl -subcommand="src\cDepSubCommand.tmp" -o "$(@:%.obj=%.d)"  -MT="$(@:%.obj=%.obj)"  -MT="$(@:%.obj=%.d)" -msg_lang=english "$<"
	@echo src\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\cSubCommand.tmp"
	ccrl -subcommand="src\cSubCommand.tmp" -msg_lang=english -o "$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo ''


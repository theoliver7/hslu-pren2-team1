################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/peripherals.c \
../board/pin_mux.c 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/peripherals.o \
./board/pin_mux.o 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/peripherals.d \
./board/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK22FN512VLH12 -DCPU_MK22FN512VLH12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\drivers" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\CMSIS" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\device" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\drivers" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\CMSIS" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\device" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\board" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\source" -Os -fno-common -g -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



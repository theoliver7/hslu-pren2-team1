################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/utils/ftm0.c \
../source/utils/ftm1.c \
../source/utils/ftm2.c \
../source/utils/ftm3.c 

OBJS += \
./source/utils/ftm0.o \
./source/utils/ftm1.o \
./source/utils/ftm2.o \
./source/utils/ftm3.o 

C_DEPS += \
./source/utils/ftm0.d \
./source/utils/ftm1.d \
./source/utils/ftm2.d \
./source/utils/ftm3.d 


# Each subdirectory must supply rules for building sources it contributes
source/utils/%.o: ../source/utils/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK22FN512VLH12 -DCPU_MK22FN512VLH12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\drivers" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\CMSIS" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\device" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\drivers" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\CMSIS" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\device" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\board" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\source" -Os -fno-common -g -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



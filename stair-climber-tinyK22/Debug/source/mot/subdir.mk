################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/mot/dcmot.c \
../source/mot/liftmot.c \
../source/mot/liftmot_LichtschrankeTest.c \
../source/mot/stair_ascend.c \
../source/mot/stepmot.c 

OBJS += \
./source/mot/dcmot.o \
./source/mot/liftmot.o \
./source/mot/liftmot_LichtschrankeTest.o \
./source/mot/stair_ascend.o \
./source/mot/stepmot.o 

C_DEPS += \
./source/mot/dcmot.d \
./source/mot/liftmot.d \
./source/mot/liftmot_LichtschrankeTest.d \
./source/mot/stair_ascend.d \
./source/mot/stepmot.d 


# Each subdirectory must supply rules for building sources it contributes
source/mot/%.o: ../source/mot/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK22FN512VLH12 -DCPU_MK22FN512VLH12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\drivers" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\CMSIS" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\device" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\drivers" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\CMSIS" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\device" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\board" -I"C:\Users\mijow\Documents\HSLU\4_Semester\PREN2\StairClimber_CProjekte\Teil_Manuel\StairClimberTinyK22_1.3\Stairclimber_TinyK22\source" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



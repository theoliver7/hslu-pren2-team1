################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include source/utils/subdir.mk
-include source/signal/subdir.mk
-include source/sensors/subdir.mk
-include source/program/subdir.mk
-include source/mot/subdir.mk
-include source/dev/subdir.mk
-include source/com/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include board/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Stairclimber_TinyK22.axf

# Tool invocations
Stairclimber_TinyK22.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="Stairclimber_TinyK22.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T PWM_Test_TinyK22_Debug.ld -o "Stairclimber_TinyK22.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Stairclimber_TinyK22.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Stairclimber_TinyK22.axf"; # arm-none-eabi-objcopy -v -O binary "Stairclimber_TinyK22.axf" "Stairclimber_TinyK22.bin" ; # checksum -p MK22FN512xxx12 -d "Stairclimber_TinyK22.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets

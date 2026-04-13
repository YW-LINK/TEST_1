################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
device/%.obj: ../device/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --idiv_support=none --isr_save_vcu_regs=off --tmu_support=tmu0 --vcu_support=vcu0 -Ooff --opt_for_speed=0 --fp_mode=relaxed --include_path="/driverlib/f28004x/driverlib" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/APP/inc" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/device" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib/inc" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all --define=_DEBUG -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="device/$(basename $(<F)).d_raw" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/CUP1_RAM/syscfg" --obj_directory="device" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

device/%.obj: ../device/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --idiv_support=none --isr_save_vcu_regs=off --tmu_support=tmu0 --vcu_support=vcu0 -Ooff --opt_for_speed=0 --fp_mode=relaxed --include_path="/driverlib/f28004x/driverlib" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/APP/inc" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/device" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib/inc" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all --define=_DEBUG -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="device/$(basename $(<F)).d_raw" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/CUP1_RAM/syscfg" --obj_directory="device" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



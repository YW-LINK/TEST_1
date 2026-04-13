################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
F280049_lib/%.obj: ../F280049_lib/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --idiv_support=none --isr_save_vcu_regs=off --tmu_support=tmu0 --vcu_support=vcu0 -O0 --opt_for_speed=0 --fp_mode=relaxed --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3/APP/inc" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3" --include_path="C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3/device" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3/driverlib" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3/driverlib/inc" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3/F280049_lib" --include_path="C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --advice:performance=all --define=_DEBUG -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="F280049_lib/$(basename $(<F)).d_raw" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3/CUP1_RAM/syscfg" --obj_directory="F280049_lib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

F280049_lib/%.obj: ../F280049_lib/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --idiv_support=none --isr_save_vcu_regs=off --tmu_support=tmu0 --vcu_support=vcu0 -O0 --opt_for_speed=0 --fp_mode=relaxed --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3/APP/inc" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3" --include_path="C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3/device" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3/driverlib" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3/driverlib/inc" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3/F280049_lib" --include_path="C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --advice:performance=all --define=_DEBUG -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="F280049_lib/$(basename $(<F)).d_raw" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3/CUP1_RAM/syscfg" --obj_directory="F280049_lib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



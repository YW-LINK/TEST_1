################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Debug/syscfg/%.obj: ../Debug/syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --opt_for_speed=0 --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24" --include_path="C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/device" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/driverlib" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/driverlib/inc" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/F280049_lib" --include_path="C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/syscfile" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/APP" --advice:performance=all --define=_DEBUG -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Debug/syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/CUP1_RAM/syscfg" --obj_directory="Debug/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



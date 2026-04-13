################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
syscfile/%.obj: ../syscfile/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --opt_for_speed=0 --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24" --include_path="C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/device" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/driverlib" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/driverlib/inc" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/F280049_lib" --include_path="C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/syscfile" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/APP" --advice:performance=all --define=_DEBUG -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="syscfile/$(basename $(<F)).d_raw" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/CUP1_RAM/syscfg" --obj_directory="syscfile" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-824541985: ../syscfile/untitled.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1220/ccs/utils/sysconfig_1.15.0/sysconfig_cli.bat" -s "C:/ti/c2000/C2000Ware_4_03_00_00/.metadata/sdk.json" --script "C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/syscfile/untitled.syscfg" -o "syscfg" --package F28004x_100PZ --part F28004x_100PZ --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-824541985 ../syscfile/untitled.syscfg
syscfg/board.h: build-824541985
syscfg/board.cmd.genlibs: build-824541985
syscfg/board.opt: build-824541985
syscfg/pinmux.csv: build-824541985
syscfg/c2000ware_libraries.cmd.genlibs: build-824541985
syscfg/c2000ware_libraries.opt: build-824541985
syscfg/c2000ware_libraries.c: build-824541985
syscfg/c2000ware_libraries.h: build-824541985
syscfg/clocktree.h: build-824541985
syscfg/: build-824541985

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --opt_for_speed=0 --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24" --include_path="C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/device" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/driverlib" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/driverlib/inc" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/F280049_lib" --include_path="C:/ti/ccs1220/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/syscfile" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/APP" --advice:performance=all --define=_DEBUG -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/Zhang.Xinbo/workspace_v12/testday_3_24/CUP1_RAM/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-45120049: ../f280049c_freertos_TDDB_version.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.23.1/sysconfig_cli.bat" --script "C:/Workspace/TDDB_Controlcore49_V1.0/f280049c_freertos_TDDB_version.syscfg" -o "syscfg" -s "C:/ti/c2000/C2000Ware_5_04_00_00/.metadata/sdk.json" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-45120049 ../f280049c_freertos_TDDB_version.syscfg
syscfg/board.h: build-45120049
syscfg/board.cmd.genlibs: build-45120049
syscfg/board.opt: build-45120049
syscfg/board.json: build-45120049
syscfg/pinmux.csv: build-45120049
syscfg/adc.dot: build-45120049
syscfg/sw_prioritized_defaultisr.c: build-45120049
syscfg/sw_prioritized_isr_levels.h: build-45120049
syscfg/c2000ware_libraries.cmd.genlibs: build-45120049
syscfg/c2000ware_libraries.opt: build-45120049
syscfg/c2000ware_libraries.c: build-45120049
syscfg/c2000ware_libraries.h: build-45120049
syscfg/c2000_freertos.c: build-45120049
syscfg/c2000_freertos.h: build-45120049
syscfg/FreeRTOSConfig.h: build-45120049
syscfg/c2000_freertos.cmd.genlibs: build-45120049
syscfg/c2000_freertos.opt: build-45120049
syscfg/syscfg_c.rov.xs: build-45120049
syscfg/clocktree.h: build-45120049
syscfg: build-45120049

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --opt_for_speed=2 --include_path="C:/ti/c2000/C2000Ware_5_04_00_00" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/APP/inc" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/device" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib/inc" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all --define=DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/CUP1_FLASH/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

tasks.obj: C:/ti/c2000/C2000Ware_5_04_00_00/kernel/FreeRTOS/Source/tasks.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --opt_for_speed=2 --include_path="C:/ti/c2000/C2000Ware_5_04_00_00" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/APP/inc" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/device" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib/inc" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all --define=DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/CUP1_FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

queue.obj: C:/ti/c2000/C2000Ware_5_04_00_00/kernel/FreeRTOS/Source/queue.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --opt_for_speed=2 --include_path="C:/ti/c2000/C2000Ware_5_04_00_00" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/APP/inc" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/device" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib/inc" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all --define=DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/CUP1_FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

list.obj: C:/ti/c2000/C2000Ware_5_04_00_00/kernel/FreeRTOS/Source/list.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --opt_for_speed=2 --include_path="C:/ti/c2000/C2000Ware_5_04_00_00" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/APP/inc" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/device" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib/inc" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all --define=DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/CUP1_FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

timers.obj: C:/ti/c2000/C2000Ware_5_04_00_00/kernel/FreeRTOS/Source/timers.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --opt_for_speed=2 --include_path="C:/ti/c2000/C2000Ware_5_04_00_00" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/APP/inc" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/device" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib/inc" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all --define=DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/CUP1_FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

event_groups.obj: C:/ti/c2000/C2000Ware_5_04_00_00/kernel/FreeRTOS/Source/event_groups.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --opt_for_speed=2 --include_path="C:/ti/c2000/C2000Ware_5_04_00_00" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/APP/inc" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/device" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib/inc" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all --define=DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/CUP1_FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

stream_buffer.obj: C:/ti/c2000/C2000Ware_5_04_00_00/kernel/FreeRTOS/Source/stream_buffer.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --opt_for_speed=2 --include_path="C:/ti/c2000/C2000Ware_5_04_00_00" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/APP/inc" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/device" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib/inc" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all --define=DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/CUP1_FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

port.obj: C:/ti/c2000/C2000Ware_5_04_00_00/kernel/FreeRTOS/Source/portable/CCS/C2000_C28x/port.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --opt_for_speed=2 --include_path="C:/ti/c2000/C2000Ware_5_04_00_00" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/APP/inc" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/device" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib/inc" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all --define=DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/CUP1_FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

portasm.obj: C:/ti/c2000/C2000Ware_5_04_00_00/kernel/FreeRTOS/Source/portable/CCS/C2000_C28x/portasm.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --opt_for_speed=2 --include_path="C:/ti/c2000/C2000Ware_5_04_00_00" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/APP/inc" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/device" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib/inc" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all --define=DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/CUP1_FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

heap_4.obj: C:/ti/c2000/C2000Ware_5_04_00_00/kernel/FreeRTOS/Source/portable/MemMang/heap_4.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --opt_for_speed=2 --include_path="C:/ti/c2000/C2000Ware_5_04_00_00" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/APP/inc" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/device" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/driverlib/inc" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --advice:performance=all --define=DEBUG --define=_FLASH -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Workspace/TDDB_Controlcore49_V1.0/CUP1_FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-378828463: ../f280049c_freertos_HTRB_version.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs2011/ccs/utils/sysconfig_1.23.0/sysconfig_cli.bat" --script "C:/Workspace/TDDB_Controlcore49_V1.0/f280049c_freertos_HTRB_version.syscfg" -o "syscfg" -s "/.metadata/sdk.json" -p "F28004x_100PZ" -r "F28004x_100PZ" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/error.h: build-378828463 ../f280049c_freertos_HTRB_version.syscfg
syscfg: build-378828463



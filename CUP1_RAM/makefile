################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./APP/src/htrb_control.obj" \
"./APP/src/main.obj" \
"./APP/src/sci_cmd.obj" \
"./APP/src/sci_fifo.obj" \
"./APP/src/sys.obj" \
"./device/device.obj" \
"./device/f28004x_codestartbranch.obj" \
"./driverlib/adc.obj" \
"./driverlib/asysctl.obj" \
"./driverlib/can.obj" \
"./driverlib/cla.obj" \
"./driverlib/clapromcrc.obj" \
"./driverlib/clb.obj" \
"./driverlib/cmpss.obj" \
"./driverlib/cputimer.obj" \
"./driverlib/dac.obj" \
"./driverlib/dcc.obj" \
"./driverlib/dcsm.obj" \
"./driverlib/dma.obj" \
"./driverlib/ecap.obj" \
"./driverlib/epwm.obj" \
"./driverlib/eqep.obj" \
"./driverlib/erad.obj" \
"./driverlib/flash.obj" \
"./driverlib/fsi.obj" \
"./driverlib/gpio.obj" \
"./driverlib/hrcap.obj" \
"./driverlib/hrpwm.obj" \
"./driverlib/i2c.obj" \
"./driverlib/interrupt.obj" \
"./driverlib/lin.obj" \
"./driverlib/memcfg.obj" \
"./driverlib/pga.obj" \
"./driverlib/pmbus.obj" \
"./driverlib/sci.obj" \
"./driverlib/sdfm.obj" \
"./driverlib/spi.obj" \
"./driverlib/sysctl.obj" \
"./driverlib/version.obj" \
"./driverlib/xbar.obj" \
"../28004x_generic_ram_lnk.cmd" \
"../f28004x_headers_bios.cmd" \
"../driverlib/ccs/Debug/driverlib_eabi.lib" \
$(GEN_CMDS__FLAG) \
-lrts2800_fpu32_eabi.lib \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include APP/src/subdir_vars.mk
-include device/subdir_vars.mk
-include driverlib/subdir_vars.mk
-include driverlib/ccs/Debug/subdir_vars.mk
-include subdir_rules.mk
-include APP/src/subdir_rules.mk
-include device/subdir_rules.mk
-include driverlib/subdir_rules.mk
-include driverlib/ccs/Debug/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
TDDB_Controlcore49_V1.0.out 

EXE_OUTPUTS__QUOTED += \
"TDDB_Controlcore49_V1.0.out" 


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "TDDB_Controlcore49_V1.0.out"

# Tool invocations
TDDB_Controlcore49_V1.0.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --idiv_support=none --isr_save_vcu_regs=off --tmu_support=tmu0 --vcu_support=vcu0 -Ooff --opt_for_speed=0 --fp_mode=relaxed --advice:performance=all --define=_DEBUG -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"TDDB_Controlcore49_V1.0.map" --stack_size=0x200 --warn_sections -i"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/lib" -i"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --priority --reread_libs --diag_wrap=off --display_error_number --xml_link_info="TDDB_Controlcore49_V1.0_linkInfo.xml" --rom_model -o "TDDB_Controlcore49_V1.0.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "APP\src\htrb_control.obj" "APP\src\main.obj" "APP\src\sci_cmd.obj" "APP\src\sci_fifo.obj" "APP\src\sys.obj" "device\device.obj" "device\f28004x_codestartbranch.obj" "driverlib\adc.obj" "driverlib\asysctl.obj" "driverlib\can.obj" "driverlib\cla.obj" "driverlib\clapromcrc.obj" "driverlib\clb.obj" "driverlib\cmpss.obj" "driverlib\cputimer.obj" "driverlib\dac.obj" "driverlib\dcc.obj" "driverlib\dcsm.obj" "driverlib\dma.obj" "driverlib\ecap.obj" "driverlib\epwm.obj" "driverlib\eqep.obj" "driverlib\erad.obj" "driverlib\flash.obj" "driverlib\fsi.obj" "driverlib\gpio.obj" "driverlib\hrcap.obj" "driverlib\hrpwm.obj" "driverlib\i2c.obj" "driverlib\interrupt.obj" "driverlib\lin.obj" "driverlib\memcfg.obj" "driverlib\pga.obj" "driverlib\pmbus.obj" "driverlib\sci.obj" "driverlib\sdfm.obj" "driverlib\spi.obj" "driverlib\sysctl.obj" "driverlib\version.obj" "driverlib\xbar.obj" 
	-$(RM) "APP\src\htrb_control.d" "APP\src\main.d" "APP\src\sci_cmd.d" "APP\src\sci_fifo.d" "APP\src\sys.d" "device\device.d" "driverlib\adc.d" "driverlib\asysctl.d" "driverlib\can.d" "driverlib\cla.d" "driverlib\clapromcrc.d" "driverlib\clb.d" "driverlib\cmpss.d" "driverlib\cputimer.d" "driverlib\dac.d" "driverlib\dcc.d" "driverlib\dcsm.d" "driverlib\dma.d" "driverlib\ecap.d" "driverlib\epwm.d" "driverlib\eqep.d" "driverlib\erad.d" "driverlib\flash.d" "driverlib\fsi.d" "driverlib\gpio.d" "driverlib\hrcap.d" "driverlib\hrpwm.d" "driverlib\i2c.d" "driverlib\interrupt.d" "driverlib\lin.d" "driverlib\memcfg.d" "driverlib\pga.d" "driverlib\pmbus.d" "driverlib\sci.d" "driverlib\sdfm.d" "driverlib\spi.d" "driverlib\sysctl.d" "driverlib\version.d" "driverlib\xbar.d" 
	-$(RM) "device\f28004x_codestartbranch.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets


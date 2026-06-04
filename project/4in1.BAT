SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\
SET ARMCC5_ASMOPT=--diag_suppress=9931
SET ARMCC5_CCOPT=--diag_suppress=9931
SET ARMCC5_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=STM32F103CB
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=4in1
SET CPU_CLOCK=0x00B71B00
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\device_timer.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\scheduler.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\task_data_input.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\task_data_output.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\init.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\task_data_remap.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\time.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\task_adc_converttick.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\shm_adctopwm.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\stm32f10x_stmadc_hardwaretable.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\stm32f10x_stmadc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\stm32f10x_adctopwm_iwdg.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\stmf10x_fir_lowpass.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\stmflash.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\adcfirlpf.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\stm32f10x_rcpwm.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\stm32f10x_rcpwm_hardwaretable.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\core_cm3.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\system_stm32f10x.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via "..\out\startup_stm32f10x_md._ia"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\misc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\stm32f10x_flash.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\stm32f10x_gpio.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\stm32f10x_rcc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\stm32f10x_iwdg.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\stm32f10x_adc.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\out\stm32f10x_tim.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via "..\out\stm32f10x_ADCtoPWM.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" "..\out\stm32f10x_ADCtoPWM.axf" --i32combined --output "..\out\stm32f10x_ADCtoPWM.hex"

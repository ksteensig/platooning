LDSCRIPT   = ../libopencm3/lib/stm32/f4/stm32f405x6.ld
LIBNAME    = opencm3_stm32f4
ARCH_FLAGS = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
DEFINES    = -DSTM32F4
OBJS	     = usart.o vl53l1_api.o vl53l1_api_core.o vl53l1_api_preset_modes.o \
					 	 vl53l1_core.o vl53l1_error_strings.o vl53l1_register_funcs.o \
					   vl53l1_wait.o vl53l1_api_calibration.o vl53l1_api_debug.o \
						 vl53l1_api_strings.o vl53l1_core_support.o vl53l1_platform.o \
						 vl53l1_silicon_core.o \


all: lib main.elf

include ./make.mk

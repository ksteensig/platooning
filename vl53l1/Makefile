ARCH_FLAGS = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
DEFINES    = -DSTM32F4
OBJS	     = vl53l1_api.o vl53l1_api_core.o vl53l1_api_preset_modes.o \
					 	 vl53l1_core.o vl53l1_error_strings.o vl53l1_register_funcs.o \
					   vl53l1_wait.o vl53l1_api_calibration.o vl53l1_api_debug.o \
						 vl53l1_api_strings.o vl53l1_core_support.o vl53l1_platform.o \
						 vl53l1_silicon_core.o \


all: $(OBJS)

PREFIX	?= arm-none-eabi
CC		= $(PREFIX)-gcc
OPENCM3_DIR = ../libopencm3

CFLAGS		+= -O3 \
		   -Wall -Wextra -Wimplicit-function-declaration \
		   -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes \
		   -Wundef -Wshadow \
		   -I$(OPENCM3_DIR)/include \
		   -fno-common $(ARCH_FLAGS) -MD $(DEFINES)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	find . -name \*.o -type f -exec rm -f {} \;
	find . -name \*.d -type f -exec rm -f {} \;
	rm -f *.elf
	rm -f *.bin

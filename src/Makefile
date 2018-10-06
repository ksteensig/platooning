
LDSCRIPT   = ../libopencm3/lib/stm32/f4/stm32f405x6.ld
LIBNAME    = opencm3_stm32f4
ARCH_FLAGS = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
DEFINES    = -DSTM32F4
OBJS	   = usart.o

all: lib main.elf

include ./make.mk

asmwrapper.elf: ${OBJS} $(LDSCRIPT)
	$(LD) -o ${OBJS} $(LDFLAGS) -l$(LIBNAME)

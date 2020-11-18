# the target architecture
ARCH = i686
ARCHDIR = arch/$(ARCH)

# programs used
NASMC = nasm
CC = i686-elf-gcc

# architecture-specific configurations
include src/$(ARCHDIR)/make.conf

NASMFLAGS = $(ARCH_NASMFLAGS)
CFLAGS = -Wall -Wextra -ffreestanding -O3 $(ARCH_CFLAGS)

# lists of files
OBJS = \
 src/asd_kernel.o \
 src/$(ARCHDIR)/boot.o \
 src/$(ARCHDIR)/kernel/gdt.o \
 src/$(ARCHDIR)/kernel/load_gdt.o

INCLUDE = \
 -iquote include/ \
 -iquote include/$(ARCHDIR)/

.SUFFIXES: .o .c .asm
.PHONY: default install clean

default: asd_kernel.bin

install asd_kernel.bin:
	mkdir -p $(SYSROOT)/boot
	cp asd_kernel.bin $(SYSROOT)/boot/

asd_kernel.bin: $(OBJS) src/$(ARCHDIR)/linker.ld
	$(CC) $(CFLAGS) -T src/$(ARCHDIR)/linker.ld -nostdlib -nodefaultlibs -lgcc\
		-o asd_kernel.bin $(OBJS)

.asm.o:
	$(NASMC) $(NASMFLAGS) $<

.c.o:
	$(CC) $(CFLAGS) -c $(INCLUDE) -o $@ $<

clean:
	#$(RM) $(BIN_DIR)/*
	echo nah

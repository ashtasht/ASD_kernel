# the target platform and architecture
ARCH = i686
PLATFORM = pc99
ARCHDIR = arch/$(ARCH)
PLATFORMDIR = platform/$(PLATFORM)

# programs used
NASM = nasm
CC = i686-elf-gcc

# architecture-specific configurations
include src/$(ARCHDIR)/arch/make.conf

NASMFLAGS = $(ARCH_NASMFLAGS)
CFLAGS = -Wall -Wextra -ffreestanding -O3 $(ARCH_CFLAGS)

# lists of files
OBJS = \
 src/$(ARCHDIR)/arch/asm/isr.o \
 src/$(ARCHDIR)/arch/asm/load_gdt.o \
 src/$(ARCHDIR)/arch/asm/load_idt.o \
 src/$(ARCHDIR)/arch/asm/out_8.o \
 src/$(ARCHDIR)/arch/boot.o \
 src/$(ARCHDIR)/arch/pic.o \
 src/asd_kernel.o

INCLUDE = \
 -iquote include/ \
 -iquote include/$(ARCHDIR)/ \
 -iquote include/$(PLATFORMDIR)/

.SUFFIXES: .o .c .asm
.PHONY: default install clean

default: asd_kernel.bin

install asd_kernel.bin:
	mkdir -p $(SYSROOT)/boot
	cp asd_kernel.bin $(SYSROOT)/boot/

asd_kernel.bin: $(OBJS)
	$(CC) $(CFLAGS) -T src/$(ARCHDIR)/arch/linker.ld -nostdlib \
	 -nodefaultlibs -lgcc -o asd_kernel.bin $(OBJS)

.asm.o:
	$(NASM) $(NASMFLAGS) $<

.c.o:
	$(CC) $(CFLAGS) -c $(INCLUDE) -o $@ $<

clean:
	#$(RM) $(BIN_DIR)/*
	echo nah

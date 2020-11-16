# the target architecture
ARCH = i686
ARCHDIR = src/arch/$(ARCH)

# programs used
NASMC = nasm
CC = i686-elf-gcc

# architecture-specific configurations
include $(ARCHDIR)/make.conf

NASMFLAGS = $(ARCH_NASMFLAGS)
CFLAGS = -Wall -Wextra -ffreestanding -O3 $(ARCH_CFLAGS)

# lists of files
OBJS = \
 src/boot.o \
 src/asd_kernel.o

.SUFFIXES: .o .c .asm
.PHONY: default install clean

default: asd_kernel.bin

install asd_kernel.bin:
	mkdir -p $(SYSROOT)/boot
	cp asd_kernel.bin $(SYSROOT)/boot/

asd_kernel.bin: $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) $(CFLAGS) -T $(ARCHDIR)/linker.ld -nostdlib -nodefaultlibs -lgcc \
		-o asd_kernel.bin $(OBJS)

.asm.o:
	$(NASMC) $(NASMFLAGS) $<

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	#$(RM) $(BIN_DIR)/*
	echo nah

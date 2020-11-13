# the target architecture
ARCH = i386
ARCHDIR = src/arch/$(ARCH)

# programs used
NASMC = nasm
ZIGC = zig

# architecture-specific configurations
include $(ARCHDIR)/make.conf

NASMFLAGS = $(ARCH_NASM_FLAGS)
ZIGFLAGS = --release-small $(ARCH_ZIG_FLAGS)

# lists of files
OBJS_ASM = \
 src/boot.o
OBJS_ZIG = \
 src/asd_kernel.o

.SUFFIXES: .o .zig .asm
.PHONY: default default

default: asd_kernel

asd_kernel: $(OBJS_ZIG) $(OBJS_ASM) $(ARCHDIR)/linker.ld
	$(ZIGC) build-exe $(ZIGFLAGS) --name asd_kernel --linker-script $(ARCHDIR)/linker.ld --object $(shell echo $(OBJS_ASM) $(OBJS_ZIG) | sed 's/ / --object /g')

src/boot.o:
	$(NASMC) $(NASMFLAGS) src/boot.asm

.zig.o:
	$(ZIGC) build-obj $< --output-dir $(dir $@) $(ZIGFLAGS)

clean:
	#$(RM) $(BIN_DIR)/*
	echo nah

; TODO Use multiboot 2

; multiboot header constants
MBALIGN equ 1 << 0 ; align loaded modules on page boundaries
MEMINFO equ 1 << 1 ; provide memory map
FLAGS equ MBALIGN | MEMINFO ; multiboot flag field
MAGIC equ 0x1BAD002 ; a magic number TODO research about
CHECKSUM equ -(MAGIC + FLAGS)

; multiboot header TODO research about
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

; stack stuff TODO research about
section .bss
	align 16
	stack_bottom: resb 16384
	stack_top:

section .text
global _start:function (_start.end - _start)
_start:
	; set up a stack
	mov esp, stack_top

	extern kernel_mail
	call kernel_main

	cli

.hang:
	hlt
	jmp .hang

.end:

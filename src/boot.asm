; bootstrap

; multiboot flags
MBALIGN	equ	1 << 0
MEMINFO	equ	1 << 1
FLAGS	equ MBALIGN | MEMINFO

; multiboot magic number
MAGIC	equ	0x1BADB002

; multiboot checksum
SUM	equ	- (MAGIC + FLAGS)

; multiboot header
section .multiboot
align 4
	dd	MAGIC
	dd	FLAGS
	dd	SUM

; define a stack
section .bss
	align 16
	stack_bottom:	resb 16384
	stack_top:

section .text
global _start:function (_start.end - _start)
_start:
	; initialize a stack
	mov	esp, stack_top

	; call the main function
	extern	kmain
	call	kmain

	; start an infinite loop
	cli

.hang:
	hlt
	jmp .hang

.end:

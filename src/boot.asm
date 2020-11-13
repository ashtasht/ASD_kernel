; bootstrap

; multiboot flags
MBALIGN	equ	1 << 0
MEMINFO	equ	1 << 1
FLAGS	equ MBALIGN | MEMINFO

; multiboot magic number
MAGIC	equ	0xE85250D6

; CPU architecture (i386 protected mode)
ARCH	equ	0

; multiboot header length
HEADER_LEN	equ	(header_end - header_start)

; multiboot checksum
CHECKSUM	equ	- (MAGIC + ARCH + HEADER_LEN)

; multiboot header
section .multiboot
align	4
header_start:
	dd	MAGIC
	dd	ARCH
	dd	HEADER_LEN
	dd	CHECKSUM
	dw	0 ; type
	dw	0 ; flags
	dd	8 ; size
header_end:

; define a stack
section .bss
	align	16
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

	cli

; infinite loop
.hang:
	hlt
	jmp .hang

.end:

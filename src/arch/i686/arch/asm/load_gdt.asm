global load_gdt

load_gdt:
	lgdt	[esp+4]

	mov	ax, 0x10
	mov	ds, ax
	mov	ss, ax
	mov	es, ax
	mov	gs, ax
	mov	fs, ax

	jmp	0x08:.flush_2
.flush_2:
	ret

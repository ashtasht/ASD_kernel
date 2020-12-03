global load_gdt

load_gdt:
	cli
	lgdt	[esp]
	sli
	ret

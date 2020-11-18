global load_gdt

load_gdt:
	lgdt [esp]
	ret

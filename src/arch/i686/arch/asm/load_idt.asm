global load_idt

load_idt:
	lidt	[esp]
	ret
global irq0
global irq1

extern yo

irq0:
	pusha
	cld
	call	yo
	popa
	iret

irq1:
	pusha
	cld
	call	yo
	popa
	iret

global irq0
global irq1

extern yo

irq0:
	call	yo
	popa
	iret

irq1:
	call	yo
	popa
	iret

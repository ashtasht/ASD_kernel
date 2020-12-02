#include "arch/idt.h"

void get_idt(uint64_t * a)
{
	for (uint16_t i = 0; i < 256; i++)
	{
		a[i] = structure_idt_entry(& irq0, 0x008, 0x8E);
	}
	irq0();
}

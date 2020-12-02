#include "platform/pic.h"

#include "arch/asm/out_8.h"

/* PIC (i8259) base registers */
#define PIC_1_BASE 0x20
#define PIC_2_BASE 0xA0

/* TODO use APIC instead and TODO put it in the arch/ */
void pic_remap_irqs()
{
	out_8(PIC_1_BASE, 0x11);
	out_8(PIC_2_BASE, 0x11);
	out_8(PIC_1_BASE + 1, 0x20);
	out_8(PIC_2_BASE + 1, 0x28);
	out_8(PIC_1_BASE + 1, 0x04);
	out_8(PIC_2_BASE + 1, 0x02);
	out_8(PIC_1_BASE + 1, 0x01);
	out_8(PIC_2_BASE + 1, 0x01);
	out_8(PIC_1_BASE + 1, 0x0);
	out_8(PIC_2_BASE + 1, 0x0);
}

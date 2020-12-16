#include "arch/pic.h"

#include "arch/asm/out_8.h"

/* PIC (8259) base registers */
#define PIC_1_BASE 0x20
#define PIC_2_BASE 0xA0

void pics_init()
{
	out_8(PIC_1_BASE, 0x11);
	out_8(PIC_2_BASE, 0x11);
	out_8(PIC_1_BASE + 1, 0x20);
	out_8(PIC_2_BASE + 1, 0x28);
	out_8(PIC_1_BASE + 1, 0x04);
	out_8(PIC_2_BASE + 1, 0x02);
	out_8(PIC_1_BASE + 1, 0x01);
	out_8(PIC_2_BASE + 1, 0x01);
}

uint8_t pic_irq_set(uint8_t a, uint8_t value, uint8_t * pic_1_mask,
	uint8_t * pic_2_mask)
{
	if (value)
	{
		if (a < 8)
		{
			(* pic_1_mask) &= ~ (1 << a);
			return PIC_1_BASE;
		}
		else
		{
			(* pic_2_mask) &= ~ (1 << (a - 8));
			return PIC_2_BASE;
		}
	}
	else
	{
		if (a < 8)
		{
			(* pic_1_mask) |= 1 << a;
			return PIC_1_BASE;
		}
		else
		{
			(* pic_1_mask) |= 1 << (a - 8);
			return PIC_2_BASE;
		}
	}
}

void pic_write_irqs(uint8_t pic_base, uint8_t mask)
{
	out_8(pic_base + 1, mask);
}

void pic_send_eoi(uint8_t a)
{
	if (a >= 8)
	{
		out_8(PIC_2_BASE, 0x20);
	}
	out_8(PIC_1_BASE, 0x20);
}

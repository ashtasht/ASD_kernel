#ifndef IDT_H_
#define IDT_H_

#include <stdint.h>

#include "arch/irqs.h"

#define INTERRUPT_GATE 0x8E

/* encodes an IDT entry */
static inline uint64_t structure_idt_entry(void * handler,
	uint16_t segment_selector, uint8_t flags)
{
	uint64_t a = 0;

	uint32_t offset = (uint32_t) handler;

	a |= (offset & 0x0000FFFF) << 16;
	a |= segment_selector;
	a <<= 32;

	a |= flags << 16;
	a |= (offset & 0xFFFF0000) >> 16;

	return a;
}

void get_idt(uint64_t *);

#endif

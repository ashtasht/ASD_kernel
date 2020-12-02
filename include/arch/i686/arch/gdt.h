#ifndef GDT_H_
#define GDT_H_

#include <stdint.h>

/* encodes a GDT entry */
static inline uint64_t structure_gdt_entry(uint32_t base, uint32_t limit,
	uint8_t flags_0, uint8_t flags_1)
{
	/* See the AMD64 Architecture Programmer’s Manual, Volume 2 -- 4.7.1. */

	uint64_t a = 0;

	a |= base & 0xFF000000;
	a |= (flags_1 & 0x0F) << 20;
	a |= limit & 0x000F0000;
	a |= flags_0 << 8;
	a |= base & 0x00FF0000;
	a <<= 32;

	a |= (base & 0x0000FFFF) << 16;
	a |= limit & 0x0000FFFF;

	return a;
}

void get_gdt(uint64_t *);

#endif

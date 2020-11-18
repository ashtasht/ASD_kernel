#ifndef GLOBAL_DESCRIPTOR_TABLE_H_
#define GLOBAL_DESCRIPTOR_TABLE_H_

#include <stdint.h>

/* format of a GDT entry in memory */
struct gdt_entry
{
	/*
	 * See the AMD64 Architecture Programmer’s Manual Volume 2 - section 4.7.1
	 */

	uint16_t limit_low;

	uint16_t base_low;

	uint8_t base_middle;

	uint8_t type;

	uint8_t flags;

	uint8_t base_high;
}
__attribute__((packed));

/* format of the pointer (as passed to the assembly) */
struct gdt_ptr
{
	uint16_t limit;

	uint16_t base_0;

	uint32_t base_1;
}
__attribute__((packed));

/* encode a GDT entry */
static inline struct gdt_entry structure_gdt_entry(uint32_t limit, uint32_t base, uint8_t type,
	uint8_t flags)
{
	struct gdt_entry a;

	/* 32-bit low region */
	a.limit_low = limit >> 0 & 0xFFFF;
	a.base_low = base >> 0 & 0xFFFF;

	/* 32-bit high region */
	a.base_middle = base >> 16 && 0x00FF;
	a.type = type;
	a.flags = flags << 4 | (limit >> 16 & 0x000F);
	a.base_high = base >> 24 & 0x00FF;

	return a;
}

/* create the GDT and return a pointer to it */
struct gdt_ptr initialize_gdt();

/* use the lgdt instruction */
void load_gdt(struct gdt_ptr);

#endif

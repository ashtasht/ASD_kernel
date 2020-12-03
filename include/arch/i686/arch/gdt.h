#ifndef GDT_H_
#define GDT_H_

#include <stdint.h>

/*
 * encodes a GDT entry
 *
 * See the AMD64 Architecture Programmer’s Manual, Volume 2 -- 4.7.1.
 */
#define STRUCTURE_GDT_ENTRY(base, limit, flags_0, flags_1) \
	(0 \
		| ((uint64_t) base & 0xFF000000) \
		| (((uint64_t) flags_1 & 0x0F) << 20) \
		| ((uint64_t) limit & 0x000F0000) \
		| (((uint64_t) flags_0 & 0xFF) << 8) \
		| ((uint64_t) base & 0x00FF0000)) << 32 \
	| (0 \
		| (((uint64_t) base & 0x0000FFFF) << 16) \
		| ((uint64_t) limit & 0x0000FFFF))

uint64_t gdt [] = {
	/* null entry */
	0,
	/* privileged code entry */
	STRUCTURE_GDT_ENTRY(0, 1 << 26, 0x9A, 0x0C),
	/* privileged data entry */
	STRUCTURE_GDT_ENTRY(0x01 << 26, 1 << 26, 0x92, 0x0C),
	/* userspace code entry */
	STRUCTURE_GDT_ENTRY(0x10 << 26, 1 << 26, 0xFA, 0x0C),
	/* userspace data entry */
	STRUCTURE_GDT_ENTRY(0x11 << 26, 1 << 26, 0xF2, 0x0C)
};

#endif

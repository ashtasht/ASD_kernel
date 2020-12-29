/*!
 * \file include/arch/i686/arch/gdt.h
 *
 * Contains the definition of the contents of the global descriptor table
 */

#ifndef GDT_H_
#define GDT_H_

#include <stdint.h>

/*!
 * \brief Encodes a GDT entry as it should be encoded to memory
 *
 * \param base The base address of the memory segment
 * \param limit The size of the memory segment
 * \param flags_0,flags_1 The flags of the memory segment
 *
 * \returns The entry encoded as 8 bytes
 *
 */
/* See the AMD64 Architecture Programmer's Manual, Volume 2 --- 4.7 */
#define STRUCTURE_GDT_ENTRY(base, limit, flags_0, flags_1) \
	(0 \
		| ((uint64_t) (base) & 0xFF000000) \
		| (((uint64_t) (flags_1) & 0x0F) << 20) \
		| ((uint64_t) (limit) & 0x000F0000) \
		| (((uint64_t) (flags_0) & 0xFF) << 8) \
		| ((uint64_t) (base) & 0x00FF0000)) << 32 \
	| (0 \
		| (((uint64_t) (base) & 0x0000FFFF) << 16) \
		| ((uint64_t) (limit) & 0x0000FFFF))

/*!
 * The contents of the GDT (which will be coppied to a CPU
 * register using \ref load_gdt)
 */
uint64_t gdt [] = {
	/* null entry */
	0,
	/* privileged code entry */
	STRUCTURE_GDT_ENTRY(0, (1 << 20) - 1, 0x9A, 0x0C),
	/* privileged data entry */
	STRUCTURE_GDT_ENTRY(0, (1 << 20) - 1, 0x92, 0x0C),
	/* userspace code entry */
	STRUCTURE_GDT_ENTRY(0, (1 << 20) - 1, 0xFA, 0x0C),
	/* userspace data entry */
	STRUCTURE_GDT_ENTRY(0, (1 << 20) - 1, 0xF2, 0x0C),
};

#endif

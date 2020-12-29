/*!
 * \file include/arch/i686/arch/idt.h
 */

#ifndef IDT_H_
#define IDT_H_

#include <stdint.h>

#define INTERRUPT_GATE 0x8E

/*!
 * \brief Encodes an IDT entry as it should be encoded to memory
 *
 * \param address The address of the ISR function
 * \param segment The selector of the segment (see \ref gdt)
 * \param flags The flags of the entry
 *
 * \returns The entry encoded as 8 bytes
 */
#define STRUCTURE_IDT_ENTRY(address, segment, flags) \
	(0 \
		| ((uint64_t) (address) & 0xFFFF0000) \
		| (((uint64_t) (flags) & 0xFFFF) << 8)) << 32 \
	| (0 \
		| (((uint64_t) (segment) & 0xFFFF) << 16) \
		| ((uint64_t) (address) & 0x0000FFFF))

#endif

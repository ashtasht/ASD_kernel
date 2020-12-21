/*!
 * \file include/arch/i686/arch/idt.h
 */

#ifndef IDT_H_
#define IDT_H_

#include <stdint.h>

#include "arch/asm/isr.h"

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

/* TODO comments and yes... */
inline void get_idt(uint64_t * a)
{
	a[0] = STRUCTURE_IDT_ENTRY((unsigned long) isr_0, 8, INTERRUPT_GATE);
	a[1] = STRUCTURE_IDT_ENTRY((unsigned long) isr_1, 8, INTERRUPT_GATE);
	a[2] = STRUCTURE_IDT_ENTRY((unsigned long) isr_2, 8, INTERRUPT_GATE);
	a[3] = STRUCTURE_IDT_ENTRY((unsigned long) isr_3, 8, INTERRUPT_GATE);
	a[4] = STRUCTURE_IDT_ENTRY((unsigned long) isr_4, 8, INTERRUPT_GATE);
	a[5] = STRUCTURE_IDT_ENTRY((unsigned long) isr_5, 8, INTERRUPT_GATE);
	for (size_t i = 6; i < 32; i ++)
	{	
		a[i] = STRUCTURE_IDT_ENTRY((unsigned long) isr_other, 8, INTERRUPT_GATE);
	}
	for (size_t i = 32; i < 256; i ++)
	{	
		a[i] = 0;
	}
}

#endif

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
 * \param addr The address of the ISR function
 * \param segment The selector of the segment (see \ref gdt)
 * \param flags The flags of the entry
 *
 * \returns The entry encoded as 8 bytes
 */
#define STRUCTURE_IDT_ENTRY(addr, segment, flags) \
	(0 \
		| (((uint64_t) (addr) & 0x0000FFFF) << 16) \
		| (((uint64_t) (segment) & 0xFFFF))) << 32 \
	| (0 \
		| (((uint64_t) (flags) & 0xFFFF) << 16) \
		| (((uint64_t) (addr) & 0xFFFF0000) >> 16))

/* TODO comments and yes... */
inline void get_idt(uint64_t * a)
{
	a[0] = STRUCTURE_IDT_ENTRY(8, (unsigned long) isr_0, INTERRUPT_GATE);
	a[1] = STRUCTURE_IDT_ENTRY(8, (unsigned long) isr_1, INTERRUPT_GATE);
	a[2] = STRUCTURE_IDT_ENTRY(8, (unsigned long) isr_2, INTERRUPT_GATE);
	a[3] = STRUCTURE_IDT_ENTRY(8, (unsigned long) isr_3, INTERRUPT_GATE);
	a[4] = STRUCTURE_IDT_ENTRY(8, (unsigned long) isr_4, INTERRUPT_GATE);
	a[5] = STRUCTURE_IDT_ENTRY(8, (unsigned long) isr_5, INTERRUPT_GATE);
	for (size_t i = 6; i < 32; i ++)
	{	
		a[i] = STRUCTURE_IDT_ENTRY(8, (unsigned long) isr_other, INTERRUPT_GATE);
	}
	for (size_t i = 32; i < 256; i ++)
	{	
		a[i] = 0;
	}
}

#endif

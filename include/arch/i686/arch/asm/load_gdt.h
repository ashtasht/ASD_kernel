/*!
 * \file include/arch/i686/arch/asm/load_gdt.h
 */

#ifndef LOAD_GDT_H_
#define LOAD_GDT_H_

#include "arch/descriptor_table_selector.h"

/*!
 * \brief Uses the LGDT instruction
 */
extern void load_gdt(struct descriptor_table_selector);

#endif

/*!
 * \file include/arch/i686/arch/asm/load_idt.h
 */

#ifndef LOAD_IDT_H_
#define LOAD_IDT_H_

#include "arch/descriptor_table_selector.h"

/*!
 * \brief Uses the LIDT instruction
 */
extern void load_idt(struct descriptor_table_selector);

#endif

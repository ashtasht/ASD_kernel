#ifndef LOAD_IDT_H_
#define LOAD_IDT_H_

#include "arch/descriptor_table_selector.h"

/* uses the LIDT instruction */
extern void load_idt(struct descriptor_table_selector);

#endif

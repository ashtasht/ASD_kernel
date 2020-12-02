#ifndef LIDT_H_
#define LIDT_H_

#include "arch/descriptor_table_selector.h"

/* uses the LIDT instruction */
extern void lidt(struct descriptor_table_selector);

#endif

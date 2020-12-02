#ifndef LGDT_H_
#define LGDT_H_

#include "arch/descriptor_table_selector.h"

/* uses the LGDT instruction */
extern void lgdt(struct descriptor_table_selector);

#endif

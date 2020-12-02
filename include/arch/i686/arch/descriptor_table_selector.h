#ifndef DESCRIPTOR_TABLE_SELECTOR_H_
#define DESCRIPTOR_TABLE_SELECTOR_H_

/*
 * format of a selector as passed to the assembly (for the LGDT, LLDT and LIDT
 * instructions)
 */
struct descriptor_table_selector
{
	uint16_t limit;

	uint16_t base_low;

	uint32_t base_high;
}
__attribute__((packed));

#endif

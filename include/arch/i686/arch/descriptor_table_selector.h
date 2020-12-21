/*!
 * \file include/arch/i686/arch/descriptor_table_selector.h
 */

#ifndef DESCRIPTOR_TABLE_SELECTOR_H_
#define DESCRIPTOR_TABLE_SELECTOR_H_

/*!
 * \struct descriptor_table_selector
 * \brief format of a selector as passed to the assembly (for the LGDT, LLDT and
 * LIDT instructions)
 */
struct descriptor_table_selector
{
	uint16_t limit; /*!< The size of the table in bytes */

	uint32_t base; /*!< The base address of the table */
}
__attribute__((packed));

#endif

#ifndef PIC_H_
#define PIC_H_

#include <stdint.h>

/* TODO use APIC instead */

/*!
 * \brief Initializes both the 8259 PICs
 */
void pic_init();

/*!
 * \brief Enables or disables a given IRQ
 *
 * \param a[in] The number of the targeted IRQ
 * \param value[in] Whether to disable or enable the IRQ
 * \param pic_1_mask[in,out] The mask of PIC 1
 * \param pic_2_mask[in,out] The mask of PIC 2
 *
 * \returns The base address of the PIC of which mask was changed
 *
 * \see pic_write_irqs
 */
uint8_t pic_irq_set(uint8_t, uint8_t, uint8_t *, uint8_t *);

/*!
 * \brief Writes the IRQ mask to the given 8259 PIC
 *
 * \param pic_base[in] The base address of the targeted PIC
 * \param mask[in] The mask to write to the PIC
 *
 * \see pic_irq_set
 */
void pic_write_irqs(uint8_t, uint8_t);

/* send an end of interrupt signal */
/*!
 * \brief Sends an EOI (end of interrupt) signal
 */
void pic_send_eoi(uint8_t);

/* TODO __asm__ volatile bad, NASM good */
static inline uint8_t are_interrupts_enabled() {
	unsigned long flags;
	asm volatile ( "pushf\n\t"
		"pop %0"
		: "=g"(flags) );
	return flags & (1 << 9);
}

#endif

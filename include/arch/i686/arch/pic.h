/*!
 * \file include/arch/i686/arch/pic.h
 */

#ifndef PIC_H_
#define PIC_H_

/* The 8259 PICs bases */
#define PIC_1_BASE 0x20
#define PIC_2_BASE 0xA0

#include <stdint.h>

/* TODO use APIC instead */

/*!
 * \brief Remaps the PICs
 *
 * \param base_1 The target base for the master PIC
 * \param base_2 The target base for the slave PIC
 */
void pics_remap(uint16_t, uint16_t);

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
 * \see pics_write_irqs
 */
uint8_t pics_irq_set(uint8_t, uint8_t, uint8_t *, uint8_t *);

/*!
 * \brief Writes the IRQ mask to the given 8259 PIC
 *
 * \param pic_base[in] The base address of the targeted PIC
 * \param mask[in] The mask to write to the PIC
 *
 * \see pics_irq_set
 */
void pics_write_irqs(uint8_t, uint8_t);

/*!
 * \brief Sends an EOI (end of interrupt) signal
 *
 * \param a The interrupt number
 */
void pics_send_eoi(uint8_t);

#endif

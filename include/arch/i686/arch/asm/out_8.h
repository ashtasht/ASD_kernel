/*!
 * \file include/arch/i686/arch/asm/out_8.h
 */

#ifndef OUT_8_H_
#define OUT_8_H_

#include <stdint.h>

/*!
 * \brief Uses the OUTB instruction
 *
 * \param address The address to write to
 * \param value The value to write 
 */
extern void out_8(uint16_t, uint8_t);

#endif

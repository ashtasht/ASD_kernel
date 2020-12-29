/*!
 * \file include/arch/i686/arch/exceptions.h
 *
 * \brief CPU exceptions handlers
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include "arch/idt.h"

/*
 * TODO CPU exceptions should not be handled by the microkernel, but by a
 * userspace program.
 */

/*!
 * \brief Divide-by-Zero-Error handler
 */
extern void exception_de();

/*!
 * \brief Debug handler
 */
extern void exception_db();

/*!
 * \brief Non-Maskable-Interrupt handler
 */
extern void exception_nmi();

/*!
 * \brief Breakpoint handler
 */
extern void exception_bp();

/*!
 * \brief Overflow handler
 */
extern void exception_of();

/*!
 * \brief Bound-Range handler
 */
extern void exception_br();

/*!
 * \brief Invalid-Opcode handler
 */
extern void exception_ud();

/*!
 * \brief Device-Not-Available handler
 */
extern void exception_nm();

/*!
 * \brief Double-Fault handler
 */
extern void exception_df();

/*!
 * \brief Invalid-TSS handler
 */
extern void exception_ts();

/*!
 * \brief Segment-Not-Present handler
 */
extern void exception_np();

/*!
 * \brief Stack handler
 */
extern void exception_ss();

/*!
 * \brief General-Protection handler
 */
extern void exception_gp();

/*!
 * \brief Page-Fault handler
 */
extern void exception_pf();

/*!
 * \brief x87 Floating-Point Exception-Pending handler
 */
extern void exception_mf();

/*!
 * \brief Aligment-Check handler
 */
extern void exception_ac();

/*!
 * \brief Machine-Check handler
 */
extern void exception_mc();

/*!
 * \brief SIMD Floating-Point handler
 */
extern void exception_xf();

/*!
 * \brief Control-Protection Exception handler
 */
extern void exception_cp();

/*!
 * \brief Hypervisor Injection Exception handler
 */
extern void exception_hv();

/*!
 * \brief VMM Communication Exception handler
 */
extern void exception_vc();

/*!
 * \brief Security Exception handler
 */
extern void exception_sx();

/*!
 * \brief An handler for reserved exceptions
 */
extern void exception_other();

inline void set_up_exceptions(uint64_t * a)
{
	/* See AMD64 Architecture Programmer's Manual, Volume 2 --- 8.2 */
	a[0] = STRUCTURE_IDT_ENTRY((unsigned long) exception_de, 8, INTERRUPT_GATE);
	a[1] = STRUCTURE_IDT_ENTRY((unsigned long) exception_db, 8, INTERRUPT_GATE);
	a[2] = STRUCTURE_IDT_ENTRY((unsigned long) exception_nmi, 8, INTERRUPT_GATE);
	a[3] = STRUCTURE_IDT_ENTRY((unsigned long) exception_bp, 8, INTERRUPT_GATE);
	a[4] = STRUCTURE_IDT_ENTRY((unsigned long) exception_of, 8, INTERRUPT_GATE);
	a[5] = STRUCTURE_IDT_ENTRY((unsigned long) exception_br, 8, INTERRUPT_GATE);
	a[6] = STRUCTURE_IDT_ENTRY((unsigned long) exception_ud, 8, INTERRUPT_GATE);
	a[7] = STRUCTURE_IDT_ENTRY((unsigned long) exception_nm, 8, INTERRUPT_GATE);
	a[8] = STRUCTURE_IDT_ENTRY((unsigned long) exception_df, 8, INTERRUPT_GATE);
	a[9] = STRUCTURE_IDT_ENTRY((unsigned long) exception_other, 8,
		INTERRUPT_GATE);
	a[10] = STRUCTURE_IDT_ENTRY((unsigned long) exception_ts, 8, INTERRUPT_GATE);
	a[11] = STRUCTURE_IDT_ENTRY((unsigned long) exception_np, 8, INTERRUPT_GATE);
	a[12] = STRUCTURE_IDT_ENTRY((unsigned long) exception_ss, 8, INTERRUPT_GATE);
	a[13] = STRUCTURE_IDT_ENTRY((unsigned long) exception_gp, 8, INTERRUPT_GATE);
	a[14] = STRUCTURE_IDT_ENTRY((unsigned long) exception_pf, 8, INTERRUPT_GATE);
	a[15] = STRUCTURE_IDT_ENTRY((unsigned long) exception_other, 8,
		INTERRUPT_GATE);
	a[16] = STRUCTURE_IDT_ENTRY((unsigned long) exception_mf, 8, INTERRUPT_GATE);
	a[17] = STRUCTURE_IDT_ENTRY((unsigned long) exception_ac, 8, INTERRUPT_GATE);
	a[18] = STRUCTURE_IDT_ENTRY((unsigned long) exception_mc, 8, INTERRUPT_GATE);
	a[19] = STRUCTURE_IDT_ENTRY((unsigned long) exception_xf, 8, INTERRUPT_GATE);
	a[20] = STRUCTURE_IDT_ENTRY((unsigned long) exception_other, 8,
		INTERRUPT_GATE);
	a[21] = STRUCTURE_IDT_ENTRY((unsigned long) exception_cp, 8, INTERRUPT_GATE);
	a[22] = STRUCTURE_IDT_ENTRY((unsigned long) exception_other, 8, 
		INTERRUPT_GATE);
	a[23] = STRUCTURE_IDT_ENTRY((unsigned long) exception_other, 8, 
		INTERRUPT_GATE);
	a[24] = STRUCTURE_IDT_ENTRY((unsigned long) exception_other, 8, 
		INTERRUPT_GATE);
	a[25] = STRUCTURE_IDT_ENTRY((unsigned long) exception_other, 8, 
		INTERRUPT_GATE);
	a[26] = STRUCTURE_IDT_ENTRY((unsigned long) exception_other, 8, 
		INTERRUPT_GATE);
	a[27] = STRUCTURE_IDT_ENTRY((unsigned long) exception_other, 8, 
		INTERRUPT_GATE);
	a[28] = STRUCTURE_IDT_ENTRY((unsigned long) exception_hv, 8, INTERRUPT_GATE);
	a[29] = STRUCTURE_IDT_ENTRY((unsigned long) exception_vc, 8, INTERRUPT_GATE);
	a[30] = STRUCTURE_IDT_ENTRY((unsigned long) exception_sx, 8, INTERRUPT_GATE);
	a[31] = STRUCTURE_IDT_ENTRY((unsigned long) exception_other, 8, 
		INTERRUPT_GATE);
}

#endif

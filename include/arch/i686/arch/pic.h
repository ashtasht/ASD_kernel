#ifndef PIC_H_
#define PIC_H_

/* PIC (i8259) base registers */
#define PIC_1_BASE 0x20
#define PIC_2_BASE 0xA0

void pic_remap_irqs();

/* send an end of interrupt signal */
void send_eoi();

#endif

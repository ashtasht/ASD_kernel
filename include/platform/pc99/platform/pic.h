#ifndef PIC_H_
#define PIC_H_

void pic_remap_irqs();

/* send an end of interrupt signal */
void send_eoi();

#endif

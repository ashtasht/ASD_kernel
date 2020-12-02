#include "arch/gdt.h"

void get_gdt(uint64_t * a)
{
	/* null entry */
	a[0] = structure_gdt_entry(0, 0, 0, 0);

	/* privileged code entry */
	a[1] = structure_gdt_entry(0, 1 << 26, 0x9A, 0x0C);

	/* privileged data entry */
	a[2] = structure_gdt_entry(0x01 << 26, 1 << 26, 0x92, 0x0C);

	/* userspace code entry */
	a[3] = structure_gdt_entry(0x10 << 26, 1 << 26, 0xFA, 0x0C);

	/* userspace data entry */
	a[4] = structure_gdt_entry(0x11 << 26, 1 << 26, 0xF2, 0x0C);
}

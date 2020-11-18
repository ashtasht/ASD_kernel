#include "kernel/gdt.h"

#include <stdint.h>

struct gdt_ptr initialize_gdt()
{
	// TODO use the right flags

	struct gdt_entry gdt [] =
	{
		/* null entry */
		structure_gdt_entry(0, 0, 0x00, 0),

		/* code entry */
		structure_gdt_entry(1 << 26, 0, 0x9a, 0),

		/* data entry */
		structure_gdt_entry(1 << 26, 1 << 26, 0x92, 0)
	};

	struct gdt_ptr ptr;
	ptr.limit = sizeof(gdt);
	ptr.base_1 = & gdt;

	return ptr;
}

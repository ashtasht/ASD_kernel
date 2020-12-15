#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "arch/asm/load_gdt.h"
#include "arch/asm/load_idt.h"
#include "arch/asm/out_8.h"
#include "arch/descriptor_table_selector.h"
#include "arch/gdt.h"
#include "arch/idt.h"
#include "arch/pic.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define BUFF 0xB8000
#define BUFF_COUNT 0xBF080

/* Magenta foreground on black background */
#define COLOR 0x05

/* calculate the length of a given characters array */
size_t strlen(const char * s) 
{
	register const char * a;

	for (a = s; * a; a ++);

	return a - s;
}

void hex(uint64_t a, char * o)
{
	for (uint8_t i = 15; i < 16; i --)
	{
		o[i] = "0123456789ABCDEF"[a % 16];
		a >>= 4;
	}
}

/* clear any characters from the screen */
void clear_buffer() 
{
	uint16_t * buff = (uint16_t *) BUFF;
	uint16_t c = (uint16_t) ' ' | COLOR << 8;

	for (uint16_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i ++)
	{
		buff[i] = c;
	}
}

/* put a given character in the given position on the screen */
void put_char(char c, uint8_t x, uint8_t y)
{
	uint16_t * buff = (uint16_t *) BUFF;
	buff[VGA_WIDTH * y + x] = (uint16_t) c | COLOR << 8; 
}

/* writes a given message on the screen */
void log(const char * data)
{
	uint8_t * c_y = (uint8_t *) BUFF_COUNT;

	if (* c_y > VGA_HEIGHT)
	{
		* c_y = 0;
	}

	for (uint8_t x = 0; x < strlen(data); x ++)
	{
		put_char(data[x], x, * c_y);
	}

	(* c_y) ++;
}

static inline void log_hex(uint64_t a)
{
	char string [8];
	hex(a, string);
	log(string);
}

void yo()
{
	log("and her daddy has told her to go");
	send_eoi();
}

void kernel_main()
{
	/* load the global descriptor table */
	struct descriptor_table_selector gdt_ptr;
	gdt_ptr.limit = sizeof(gdt);
	gdt_ptr.base_low = 0x0;
	gdt_ptr.base_high = (uint32_t) & gdt;
	load_gdt(gdt_ptr);

	/* initialize the interrupt descriptor table */
	uint64_t idt [256];
	get_idt(idt);

	/*
	struct descriptor_table_selector idt_ptr;
	idt_ptr.limit = sizeof(idt);
	idt_ptr.base_low = 0x0;
	idt_ptr.base_high = (uint32_t) & idt;
	lidt(idt_ptr);
	asm volatile("sti");
	pic_remap_irqs();
	*/

	/* clear and initialize the screen */
	clear_buffer();
	log("Welcome to ASD version 0.0.1!");
	log("gdt[0]:");
	log_hex(gdt[0]);
	log("gdt[1]:");
	log_hex(gdt[1]);
	log("gdt[2]:");
	log_hex(gdt[2]);
	log("gdt[3]:");
	log_hex(gdt[3]);
	log("gdt[4]:");
	log_hex(STRUCTURE_GDT_ENTRY(0x11 << 26, 1 << 26, 0xF2, 0x0C));

	//asm volatile("int $49");
}

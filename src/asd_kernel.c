#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "arch/asm/lgdt.h"
#include "arch/asm/lidt.h"
#include "arch/asm/out_8.h"
#include "arch/descriptor_table_selector.h"
#include "arch/gdt.h"
#include "arch/idt.h"
#include "platform/pic.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

/* Magenta foreground on black background */
#define COLOR 0x05

/* calculate the length of a given characters array */
size_t strlen(const char * s) 
{
	register const char * a;

	for (a = s; * a; a ++);

	return a - s;
}

/* clear any characters from the screen */
void clear_buffer(uint16_t * buff) 
{
	uint16_t c = (uint16_t) ' ' | COLOR << 8;

	for (uint16_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i ++)
	{
		buff[i] = c;
	}
}

/* put a given character in the given position on the screen */
void put_char(uint16_t * buff, char c, uint8_t x, uint8_t y)
{
	buff[VGA_WIDTH * y + x] = (uint16_t) c | COLOR << 8; 
}

/* write a given message in a new line on the screen */
void log(uint16_t * buff, uint8_t * c_y, const char * data)
{
	for (uint8_t x = 0; x < strlen(data); x ++)
	{
		put_char(buff, data[x], x, * c_y);
	}

	(* c_y) ++;
}

char * itoa(char * p, uint32_t a)
{
	p += 11;
	*--p = 0;

	while (a)
	{
		*--p = '0' + a % 10;
		a /= 10;
	}
	return p;
}

void yo(uint32_t b)
{
	uint8_t a = 2;
	log((uint16_t *) 0xB8000, & a, "and her daddy has told her to go");
}

void kernel_main(void) 
{
	/* initialize the global descriptor table */
	uint64_t gdt [5];
	get_gdt(gdt);

	struct descriptor_table_selector gdt_ptr;
	gdt_ptr.limit = sizeof(gdt);
	gdt_ptr.base_low = 0x0;
	gdt_ptr.base_high = (uint32_t) & gdt;
	lgdt(gdt_ptr);

	/* initialize the interrupt descriptor table */
	uint64_t idt [256];
	get_idt(idt);

	struct descriptor_table_selector idt_ptr;
	idt_ptr.limit = sizeof(idt);
	idt_ptr.base_low = 0x0;
	idt_ptr.base_high = (uint32_t) & idt;
	lidt(idt_ptr);
	asm volatile("sti"); /* TODO no inline assembly... */
	pic_remap_irqs();

	/* initialize the screen */
	uint16_t * screen_buff = (uint16_t *) 0xB8000;

	/* cursor y position */
	uint8_t c_y = 0;

	clear_buffer(screen_buff);
	log(screen_buff, & c_y, "Welcome to ASD version 0.0.1!");

	/* beep */
	/* set the frequency to 1760 Hz (A6) */
	uint32_t div = 1193180 / 1760;
 	out_8(0x43, 0xb6);
 	out_8(0x42, (uint8_t) (div) );
 	out_8(0x42, (uint8_t) (div >> 8));
	/* play */
	out_8(0x61, 3);
}

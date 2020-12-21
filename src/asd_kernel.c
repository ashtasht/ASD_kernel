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
	log("man you got interruptssssssss");
	//pic_send_eoi(0);
}

static inline bool are_interrupts_enabled() {
	unsigned long flags;
	asm volatile ( "pushf\n\t"
		"pop %0"
		: "=g"(flags) );
	return flags & (1 << 9);
}

void kernel_main()
{
	/* initialize the screen */
	clear_buffer();
	log("VGA text mode screen cleared");

	/* load the global descriptor table */
	log("loading the GDT");
	struct descriptor_table_selector gdt_ptr;
	gdt_ptr.limit = sizeof(gdt);
	gdt_ptr.base_high = (uint32_t) & gdt;
	load_gdt(gdt_ptr);

	/* initialize the PICs */
	log("initializing the PICs");
	pics_init();
	uint8_t pic_1_mask = 0xFF;
	uint8_t pic_2_mask = 0xFF;
	//pic_irq_set(2, 1, & pic_1_mask, & pic_2_mask);
	pic_write_irqs(pic_1_mask, pic_2_mask);

	/* load the interrupt descriptor table */
	log("loading the IDT");
	uint64_t idt [256];
	get_idt(idt);
	log("idt[0]:");
	log_hex(idt[0]);
	log("idt[1]:");
	log_hex(idt[1]);
	log("idt[2]:");
	log_hex(idt[2]);
	struct descriptor_table_selector idt_ptr;
	idt_ptr.limit = sizeof(idt);
	idt_ptr.base_high = (uint32_t) & idt;
	load_idt(idt_ptr);
	/*
	 * TODO understand why the fuck does running sti makes the
	 * computer crash
	 */
	asm volatile("sti");

	log("checking if the interrupts are enabled");
	if (are_interrupts_enabled())
	{
		log("interrupts are enabled");
	}
	else
	{
		log("interrupts are not enabled");
	}

	// log("trying to raise an interrupt (division by 0)");
	// __asm__  ("div %0" :: "r"(0));

	/* clear and initialize the screen */
	log("Welcome to ASD version 0.0.1!");
}

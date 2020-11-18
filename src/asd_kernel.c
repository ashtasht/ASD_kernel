#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "kernel/gdt.h"

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

void kernel_main(void) 
{
	load_gdt(initialize_gdt());

	uint16_t * screen_buff = (uint16_t *) 0xB8000;

	/* cursor y position */
	uint8_t c_y = 0;

	log(screen_buff, & c_y, "sup you guys?");
	log(screen_buff, & c_y, "are you looking at this 10 years from now?");
	log(screen_buff, & c_y, "like this is thing succeeded...");
	log(screen_buff, & c_y, "btw listen to Forbidden Evil");
	log(screen_buff, & c_y, "and goodbye from ASD!");
}

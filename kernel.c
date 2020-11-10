#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Chcek OS target */
#ifdef __linux__
#error "a cross-compiler is not used"
#endif

/* TODO x86_64 support coming later */
#ifndef __i386__
#error "ix86-elf compiler is not used"
#endif

#define default_color 2 | 4 << 4 /* green, 'cause you are just like Neo */

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char  * str)
{
	/* TODO: look at the implementations in glibc, musl and uclibc-ng */

	size_t len = 0;
	while (str[len])
		len ++;
	return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint16_t * terminal_buffer;

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	for (size_t y = 0; y < VGA_HEIGHT; y ++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', default_color);
		}
	}
}

void terminal_putentryat(char c, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, default_color);
}

void terminal_putchar(char c)
{
	terminal_putentryat(c, terminal_column, terminal_row);
	if (++ terminal_column == VGA_WIDTH)
	{
		terminal_column = 0;
		if(++ terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_write(const char * data, size_t size)
{
	for (size_t i = 0; i < size; i ++)
	{
		terminal_putchar(data[i]);
	}
}

void terminal_write_string(const char * data)
{
	terminal_write(data, strlen(data));
}

void kernel_main(void)
{
	terminal_initialize();
	terminal_write_string("Hello! Fucking! World!\n");
}

/* vga.c - VGA driver */
#include <stdint.h>
#include "drivers/vga.h"

/* Define the width and height of the VGA Framebuffer */ 
#define width 80
#define height 25
uint16_t row = 0;
uint16_t column = 0;
/* Use a variable for the buffer's address */
uint16_t *const buf = (uint16_t *const) 0xC03FF000;

static inline uint8_t 
vga_entry_color(enum vga_colors fg, enum vga_colors bg) 
{
	return fg | bg << 4;
}

static inline uint16_t
vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

const uint16_t default_color = (VGA_COLOR_BLACK << 12) | (VGA_COLOR_WHITE << 8);

void
scroll() 
{
    for (uint16_t y = 1; y < height; y++) {
        for (uint16_t x = 0; x < width; x++) {
            buf[(y - 1) * width + x] = buf[y * width + x];
        }
    }
    for (uint16_t x = 0; x < width; x++) {
        buf[(height - 1) * width + x] = vga_entry(' ', VGA_COLOR_BLACK | VGA_COLOR_WHITE);
    }
}

void 
newline() 
{
  row = row + 1;
  column = 0;
  /* If row is 25, scroll a row */
  if (row == 25) {
    row = 24;
    scroll();
  }
}

void
screenColor(uint16_t color) 
{
	for (uint16_t y = 0; y < height; y++) {
		for (uint16_t x = 0; x < width; x++) {
			buf[y * width + x] = (buf[y * width + x] & 0x00FF) | (color << 12);
		}
	}
}

void 
print(const char* txt) 
{
	 while (*txt) {
		if (*txt == '\n') {
			newline();
		} else {
			if (column == width) {
				newline();
			}
			buf[row * width + (column++)] = (*txt & 0x00FF) | default_color;
		}
		txt++;
  }
}

void 
print_hex(const uint8_t *txt) 
{
	 while (*txt) {
		if (*txt == '\n') {
			newline();
		} else {
			if (column == width) {
				newline();
			}
			buf[row * width + (column++)] = (*txt & 0x00FF) | default_color;
		}
		txt++;
  }
}

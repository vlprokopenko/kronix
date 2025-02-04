/* tty-keyboard.c - keyboard driver */
#include <stdint.h>
#include "drivers/vga.h"
#include "asm/ports-common.h"
#include "drivers/tty.h"

static inline void 
flush_ps2_buffer() 
{
    while (inb(0x64) & 0x01) {
        (void)inb(0x60);
    }
}

void 
remap_pic_for_keyboard() 
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void
keyboard_handler() 
{
  __asm__("cli");
  __asm__("pushal");
  flush_ps2_buffer();
  uint8_t scancode = inb(0x60);
  print("Keyboard key pressed\n");
  outb(0x20, 0x20);
  __asm__("popal; leave; iret");
}

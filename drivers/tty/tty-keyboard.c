#include <stdint.h>
#include "../../include/drivers/vga.h"
#include "../../include/asm/ports-common.h"
#include "../../include/drivers/tty.h"

void remap_pic_for_keyboard() {
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

void keyboard_handler() {
  __asm__("cli");
  __asm__("pushal");
  uint8_t scancode = inb(0x60);
  print("Keyboard key pressed");
  outb(0x20, 0x20);
  __asm__("popal; leave");
}

/* main.c - main kernel file */
#include "arch/i686/gdt.h"
#include "drivers/vga.h"
#include "drivers/tty.h"
#include "arch/i686/idt.h"
#include "arch/i686/isr.h"
#include "asm/ports-common.h"
#include <stdbool.h>

static inline void
flush_ps2_buffer()
{
    while (inb(0x64) & 0x01) {
        (void)inb(0x60);
    }
}

void
kernel_init()
{
  print("[KERNEL_INIT] Kernel loaded!\n");
  loadGDT();
  loadIDT();
  flush_ps2_buffer();
  init_keyboard();
  flush_ps2_buffer();
  while (true) {
    asm("hlt");
  }
}

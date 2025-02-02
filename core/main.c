#include "../include/arch/i686/gdt.h"
#include "../include/drivers/vga.h"
#include "../include/arch/i686/idt.h"
#include "../include/arch/i686/isr.h"
#include "../include/asm/ports-common.h"
#include <stdbool.h>

void kernel_init() {
  print("[KERNEL_EARLY] Early Kernel loaded!\n");
  loadGDT();
  loadIDT();
  while (inb(0x64) & 0x01) {
        inb(0x60); 
    }
  outb(0x64, 0xAE);
  asm volatile("sti");
  while (true) {
    asm("hlt");
  }
}

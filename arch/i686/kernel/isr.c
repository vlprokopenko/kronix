#include "../../../include/arch/i686/isr.h"
#include "../../../include/drivers/vga.h"
#include "../../../include/asm/ports-common.h"
#include <stdbool.h>

typedef struct registers {
    const uint32_t eip, esp, ebp;
} registers_t;

struct registers regs[256];

void isr0() {
  __asm__("cli");
  __asm__("pushal");
  __asm__("push $0");
  __asm__("add $4, %esp");
  __asm__("popal; leave; iret");
}

void isr1() {
  __asm__("cli");
  __asm__("pushal");
  __asm__("push $1");
  __asm__("add $4, %esp");
  __asm__("popal; leave; iret");
}

void isr2() {
  __asm__("cli");
  __asm__("pushal");
  __asm__("push $2");
  __asm__("add $4, %esp");
  __asm__("popal; leave; iret");
}

void isr3() {
  __asm__("cli");
  __asm__("pushal");
  __asm__("push $3");
  __asm__("add $4, %esp");
  __asm__("popal; leave; iret");
}

void isr4() {
  __asm__("cli");
  __asm__("pushal");
  __asm__("push $4");
  __asm__("add $4, %esp");
  __asm__("popal; leave; iret");
}

void isr5() {
  __asm__("cli");
  __asm__("pushal");
  __asm__("push $5");
  __asm__("add $4, %esp");
  __asm__("popal; leave; iret");
}

void isr6() {
  __asm__("cli");
  __asm__("pushal");
  __asm__("push %eax");
  __asm__("push $6");
  __asm__("add $4, %esp");
  __asm__("popal; leave; iret");
}

void isr7() {
  __asm__("cli");
  __asm__("pushal");
  __asm__("push %eax");
  __asm__("push $7");
  __asm__("add $4, %esp");
  __asm__("popal; leave; iret");
}

void isr8() {
  __asm__("cli");
  screenColor(VGA_COLOR_RED);
  print("Double fault. Halting now\n");
  print("Most likely, an interrupt that does not exist has been called.");
  __asm__("pushal");
  __asm__("push %eax");
  __asm__("push $8");
  __asm__("add $4, %esp");
  __asm__("popal; leave");
  while (true) {
    __asm__("hlt");
  }
}

void isr10() {
  __asm__("cli");
  __asm__("pushal");
  __asm__("push %eax");
  __asm__("push $10");
  __asm__("add $4, %esp");
  __asm__("popal; leave; iret");
}

void isr11() {
  __asm__("cli");
  __asm__("pushal");
  __asm__("push %eax");
  __asm__("push $11");
  __asm__("add $4, %esp");
  __asm__("popal; leave; iret");
}

void isr12() {
  __asm__("cli");
  __asm__("pushal");
  __asm__("push %eax");
  __asm__("push $12");
  screenColor(VGA_COLOR_RED);
  print("Stack Segment Fault, halting now!\n");
  __asm__("add $4, %esp");
  __asm__("popal; leave");
  while (true) {
    __asm__("hlt");
  }
}

void isr13() {
  __asm__("cli");
  __asm__("pushal");
  __asm__("push %eax");
  __asm__("push $13");
  __asm__("add $4, %esp");
  __asm__("popal; leave; iret");
}

void isr14() {
  __asm__("cli");
  __asm__("pushal");
  __asm__("push %eax");
  __asm__("push $14");
  __asm__("add $4, %esp");
  __asm__("popal; leave");
  print("Page fault.");
  while (true) {
    asm("hlt");
  }
}  

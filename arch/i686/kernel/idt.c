#include <stdint.h>
#include "../../../include/arch/i686/idt.h"
#include "../../../include/drivers/vga.h"
#include "../../../include/arch/i686//isr.h"
#include "../../../include/drivers/tty.h"
#include "../../../include/asm/ports-common.h"

typedef struct
{
	uint16_t low;
	uint16_t sel;
	uint8_t zero;
	uint8_t type_attributes; 
	uint16_t high;
} __attribute__((packed)) IDT;

typedef struct
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) IDTRegister;

IDT idt[256];
IDTRegister idtreg;

void setIDTEntry(int num, uint32_t handler, uint8_t flags) {
	idt[num].low = handler & 0xffff;
	idt[num].sel = 8;
	idt[num].zero = 0;
	idt[num].type_attributes = flags; /* 0x8E should be used for most interrupts */
	idt[num].high = (handler>>16) & 0xffff;
}

void timer_placeholder(){
  /* placeholder code for now, when we get to the timer I will place it somewhere else */ 
  print("Blah");
  outb(0x20, 0x20);
}

void loadIDT() {
  setIDTEntry(0, (uint32_t)isr0, 0x8E);
  setIDTEntry(1, (uint32_t)isr1, 0x8E);
  setIDTEntry(2, (uint32_t)isr2, 0x8E);
  setIDTEntry(3, (uint32_t)isr3, 0x8E);
  setIDTEntry(4, (uint32_t)isr4, 0x8E);
  setIDTEntry(5, (uint32_t)isr5, 0x8E);
  setIDTEntry(6, (uint32_t)isr6, 0x8E);
  setIDTEntry(7, (uint32_t)isr7, 0x8E);
  setIDTEntry(8, (uint32_t)isr8, 0x8E);
  setIDTEntry(10, (uint32_t)isr10, 0x8E);
  setIDTEntry(11, (uint32_t)isr11, 0x8E);
  setIDTEntry(12, (uint32_t)isr12, 0x8E);
  setIDTEntry(13, (uint32_t)isr13, 0x8E);
  setIDTEntry(14, (uint32_t)isr14, 0x8E);
  setIDTEntry(32, (uint32_t)timer_placeholder, 0x8E);
  setIDTEntry(33, (uint32_t)keyboard_handler, 0x8E);  
  idtreg.base = (uint32_t)&idt;
	idtreg.limit = 256*sizeof(IDT)-1;
	asm volatile("lidt (%0)" : : "r" (&idtreg));
  remap_pic_for_keyboard();
  print("[IDT] IDT loaded\n");
}

/* gdt.c - load the GDT */
#include <stdint.h>
#include "drivers/vga.h"

struct __attribute__((packed)) tssEntry {
    uint32_t esp0;
    uint32_t ss0;
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax, ecx, edx, ebx;
    uint32_t esp, ebp, esi, edi;
    uint32_t es, cs, ss, ds, fs, gs;
    uint32_t ldt;
    uint16_t trap;
    uint16_t iomap_base;
} TSS;

typedef struct
{
  uint16_t limit;
	uint32_t base;
} __attribute__((packed)) GDTRegister;

typedef struct
{
  uint16_t limit_low;     
  uint16_t base_low;      
  uint8_t  base_mid;
  uint8_t  access;
  uint8_t  granularity;
  uint8_t  base_high;
} __attribute__((packed)) GDTEntry;

GDTEntry gdt[3];

void 
setGDTEntry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) 
{
    gdt[num].base_low = base & 0xFFFF;
    gdt[num].base_mid = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = limit & 0xFFFF;
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= (granularity & 0xF0);
    gdt[num].access = access;
}

GDTRegister gdtReg;
extern void flushgdt(GDTRegister *gdtReg);

void
loadGDT() 
{
    setGDTEntry(0, 0, 0x00000000, 0x00, 0x0);
    setGDTEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    setGDTEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    setGDTEntry(3, 0, 0xFFFFF, 0xFA, 0xC);
    setGDTEntry(4, 0, 0xFFFFF, 0xF2, 0xC);
    setGDTEntry(5, (uint32_t)&TSS, sizeof(TSS)-1, 0x89, 0x0); 

    gdtReg.limit = sizeof(gdt) - 1;
    gdtReg.base = (uint32_t)&gdt;
    flushgdt(&gdtReg);
    print("[GDT] GDT Loaded\n");
}

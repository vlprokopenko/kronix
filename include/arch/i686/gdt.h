#ifndef GDT_H
#define GDT_H

#include <stdint.h>

typedef struct
{
	uint32_t base;
} __attribute__((packed)) GDTRegister;

typedef struct
{
  uint16_t NULL;
  uint16_t KCODE;
  uint16_t KDATA;
  uint16_t UCODE;
  uint16_t UDATA;
  uint16_t TASK_SEG;
} __attribute__((packed)) GDT;

void setGDTEntry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void loadGDT();
#endif

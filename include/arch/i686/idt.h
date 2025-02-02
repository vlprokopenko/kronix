#ifndef IDT_H
#define IDT_H

#include <stdint.h>

void setIDTEntry(int num, uint32_t handler, uint8_t flags);
void loadIDT();

#endif

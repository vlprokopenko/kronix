# A cross compiler is expected for building
CC=i686-elf-gcc
AS=i686-elf-as
# For now, build the kernel with debugging symbols by default
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -g -I include/ 

all:
	$(AS) arch/i686/boot/boot.s -o build/boot.o
	$(CC) -c core/main.c -o build/main.o $(CFLAGS)
	$(CC) -c drivers/tty/vga.c -o build/vga_driver.o $(CFLAGS)
	$(CC) -c arch/i686/kernel/gdt.c -o build/gdt.o $(CFLAGS)
	$(AS) arch/i686/kernel/gdtflush.s -o build/gdtflush.o
	$(CC) -c arch/i686/kernel/idt.c -o build/idt.o $(CFLAGS)
	$(CC) -c arch/i686/kernel/isr.c -o build/isr.o $(CFLAGS)
	$(CC) -c drivers/tty/tty-keyboard.c -o build/tty_keyboard.o $(CFLAGS)
	$(CC) -T linker.ld -o build/kronix.bin -ffreestanding -O2 -nostdlib build/boot.o build/main.o build/vga_driver.o build/gdt.o build/gdtflush.o build/idt.o build/isr.o build/tty_keyboard.o -lgcc
	@cp build/kronix.bin arch/i686/boot/isodir/boot/kronix.bin
	grub-mkrescue -o arch/i686/boot/isoimage.iso arch/i686/boot/isodir/
	@echo "ISO Image ready at arch/i686/boot/isoimage.iso"
	@# To save keystrokes, we will automatically run the appropriate QEMU
	qemu-system-i386 -cdrom arch/i686/boot/isoimage.iso 
clean:
	rm build/*
	rm arch/i686/boot/isoimage.iso

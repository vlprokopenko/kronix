CC=i686-elf-gcc
AS=i686-elf-as
# For now, build the kernel with debugging symbols by default
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -g

all:
	@echo " AS arch/i686/boot/boot.s"
	@$(AS) arch/i686/boot/boot.s -o build/boot.o
	@echo " CC core/main.c"
	@$(CC) -c core/main.c -o build/main.o $(CFLAGS)
	@echo " CC drivers/tty/vga.c"
	@$(CC) -c drivers/tty/vga.c -o build/vga_driver.o $(CFLAGS)
	@echo " CC arch/i686/kernel/gdt.c"
	@$(CC) -c arch/i686/kernel/gdt.c -o build/gdt.o $(CFLAGS)
	@echo " AS arch/i686/kernel/gdtflush.s"
	@$(AS) arch/i686/kernel/gdtflush.s -o build/gdtflush.o
	@echo " CC arch/i686/kernel/gdt.c"
	@$(CC) -c arch/i686/kernel/idt.c -o build/idt.o $(CFLAGS)
	@echo " CC arch/i686/kernel/isr.c"
	@$(CC) -c arch/i686/kernel/isr.c -o build/isr.o
	@echo " CC drivers/tty/tty-keyboard.c"
	@$(CC) -c drivers/tty/tty-keyboard.c -o build/tty_keyboard.o
	@echo " LD linker.ld build/kronix.bin"
	@$(CC) -T linker.ld -o build/kronix.bin -ffreestanding -O2 -nostdlib build/boot.o build/main.o build/vga_driver.o build/gdt.o build/gdtflush.o build/idt.o build/isr.o build/tty_keyboard.o -lgcc
	@cp build/kronix.bin arch/i686/boot/isodir/boot/kronix.bin
	@grub-mkrescue -o arch/i686/boot/isoimage.iso arch/i686/boot/isodir/
	@echo "ISO Image ready at arch/i686/boot/isoimage.iso"
	@# To save keystrokes, we will automatically run the appropriate QEMU
	qemu-system-i386 -cdrom arch/i686/boot/isoimage.iso 
clean:
	rm build/*
	rm arch/i686/boot/isoimage.iso

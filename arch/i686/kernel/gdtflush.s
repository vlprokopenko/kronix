#gdtflush.s - flush GRUB's default gdt
.global flushgdt 

flushgdt:
	movl 4(%esp), %eax
        # load the gdt
	lgdt (%eax)
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	ret

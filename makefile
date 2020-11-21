all: linker iso

boot:
	i686-elf-as boot.s -o boot.o

kernel:
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

linker: boot kernel
	i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o

iso:
	cp myos.bin isodir/boot/myos.bin
	grub-mkrescue -o myos.iso isodir
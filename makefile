all: linker iso

boot:
	i686-elf-as src/boot.s -o build/boot.o

kernel:
	i686-elf-gcc -c src/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

linker: boot kernel
	i686-elf-gcc -T src/linker.ld -o bin/myos.bin -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o

iso:
	cp bin/myos.bin grub/boot/myos.bin
	grub-mkrescue -o bin/myos.iso grub
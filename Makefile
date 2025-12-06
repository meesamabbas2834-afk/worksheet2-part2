# Object files list updated to match current files
OBJS = source/loader.o source/kmain.o drivers/io.o drivers/frame_buffer.o drivers/pic.o drivers/interrupts.o drivers/interrupt_asm.o drivers/keyboard.o

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -c
LDFLAGS = -T source/link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJS)
	ld $(LDFLAGS) -o kernel.elf $(OBJS)

os.iso: kernel.elf
	cp kernel.elf iso/boot/
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o os.iso iso

run: os.iso
	qemu-system-i386 -nographic -boot d -cdrom os.iso -m 32 -d cpu -D logQ.txt

# C files compilation rule
%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Assembly files compilation rule
%.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	rm -rf source/*.o drivers/*.o kernel.elf os.iso logQ.txt iso/boot/kernel.elf

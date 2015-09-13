#!/usr/bin/env bash
SRCS = $(shell msys-find -name '*.[cs]')
OBJS = $(addsuffix .o, $(basename $(SRCS)))

CC = i586-elf-gcc
LD = i586-elf-ld
AS = nasm

CCFLAGS = -m32 \
	-ffreestanding \
	-nostdlib \
	-nostdinc \
	-nodefaultlibs \
	-fno-stack-protector \
	-fno-builtin \
	-finline-functions \
	-c \
	-Wall \
	-Wextra \
	-Werror
LDFLAGS = -T linker.ld -melf_i386
ASFLAGS = -f elf

all: kernel.elf
iso: os.iso

kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	mkisofs -R \
		-b boot/grub/stage2_eltorito \
		-no-emul-boot \
		-boot-load-size 4 \
		-A os \
		-input-charset utf8 \
		-quiet \
		-boot-info-table \
		-o os.iso \
		iso

run: os.iso
	qemu-system-i386 -cdrom os.iso -serial file:../serial1.log

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf os.iso
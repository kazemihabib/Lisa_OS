# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

SOURCES=boot.o main.o initrd.o kheap.o monitor.o common.o descriptor_tables.o isr.o fs.o interrupt.o gdt.o timer.o keyboard.o ./rlibc/stdio.o debug.o startmain.o ./rlibc/stdlib.o ./rlibc/ctype.o ./rlibc/string.o ./rlibc/loader.o ./rlibc/controller.o ./rlibc/execution.o ./rlibc/instruction_memory.o ./rlibc/data_memory.o ./rlibc/registers.o shell.o ./rlibc/ascii_to_GIF.o

CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS=-Tlink.ld -melf_i386
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<

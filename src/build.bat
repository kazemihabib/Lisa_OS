nasm -felf interrupt.s -o interrupt.o
nasm -felf gdt.s -o gdt.o
nasm -felf boot.s -o boot.o

gcc -lexternal -nostdlib -nostdinc -fno-builtin -c isr.c -o isr.o
gcc -lexternal -nostdlib -nostdinc -fno-builtin -c monitor.c -o monitor.o
gcc -lexternal -nostdlib -nostdinc -fno-builtin -c common.c -o common.o
gcc -lexternal -nostdlib -nostdinc -fno-builtin -c descriptor_tables.c -o descriptor_tables.o
gcc -lexternal -nostdlib -nostdinc -fno-builtin -c timer.c -o timer.o
gcc -lexternal -nostdlib -nostdinc -fno-builtin -c main.c -o main.o

ld -Tlink.ld -o kernel boot.o main.o monitor.o common.o descriptor_tables.o isr.o interrupt.o gdt.o timer.o

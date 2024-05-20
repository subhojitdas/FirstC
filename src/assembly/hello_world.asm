global _start

section .data
    msg db "Hello, world!", 0x0a
    len equ $ - msg

section .text
_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg
    mov edx, len
    int 0x80
    mov eax, 1
    mov ebx, 0
    int 0x80

; compiling to machine code - nasm -f elf32 hello_world.asm -o hello_world.o
; Linking - ld -m elf_i386 hello_world.o -o hello_world
; Running - ./hello_world

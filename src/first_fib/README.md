Generate the Pre-Processed file from the .c file -

```
gcc -E fib.c -o fib.i
```

It will add all the #include into one file

----

To generate the LLVM IR from a .c file
```
clang fib.c -S -emit-llvm
```

this is an intermediate step between preprocessed file to assembly file

----

Generate the assembly file from a .c file
```
gcc -S fib.c -o fib.s
```

This will generate assembly file for the machine architecture either x86 or arm or risc-v
In this project we are using x86 ISA

------

Generate the object file from the .c file

```
gcc -c fib.c -o fib.o
```

This is the object file ready to link with other files

------

If you wanna vieww the object file below command in ubuntu works - 
```
objdump -x fib.o
```
Below are the output, the layout of the object file can be understand from - https://en.wikipedia.org/wiki/Object_file

```
fib.o:     file format elf64-x86-64
fib.o
architecture: i386:x86-64, flags 0x00000011:
HAS_RELOC, HAS_SYMS
start address 0x0000000000000000

Sections:
Idx Name          Size      VMA               LMA               File off  Algn
  0 .text         0000004a  0000000000000000  0000000000000000  00000040  2**0
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000000  0000000000000000  0000000000000000  0000008a  2**0
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  0000000000000000  0000000000000000  0000008a  2**0
                  ALLOC
  3 .comment      00000027  0000000000000000  0000000000000000  0000008a  2**0
                  CONTENTS, READONLY
  4 .note.GNU-stack 00000000  0000000000000000  0000000000000000  000000b1  2**0
                  CONTENTS, READONLY
  5 .note.gnu.property 00000020  0000000000000000  0000000000000000  000000b8  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  6 .eh_frame     00000038  0000000000000000  0000000000000000  000000d8  2**3
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, DATA
SYMBOL TABLE:
0000000000000000 l    df *ABS*	0000000000000000 fib.c
0000000000000000 l    d  .text	0000000000000000 .text
0000000000000000 g     F .text	000000000000004a fib


RELOCATION RECORDS FOR [.text]:
OFFSET           TYPE              VALUE
000000000000002a R_X86_64_PLT32    fib-0x0000000000000004
000000000000003d R_X86_64_PLT32    fib-0x0000000000000004


RELOCATION RECORDS FOR [.eh_frame]:
OFFSET           TYPE              VALUE
0000000000000020 R_X86_64_PC32     .text
```

-----

Generate a executable file by linking two object files

```
gcc fib.o  run_fib.o  -o run_fib_18
```

It generates a executable file which can run directly by the kernel
```
./run_fib_18
``` 
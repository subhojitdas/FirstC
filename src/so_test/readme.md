Create the .o file after compilation , 

```
gcc -fPIC -O2 -c mylib.c -o mylib.o
```

Create the .so with linker , 

```
gcc -shared -o libmylib.so mylib.o
```

compile and link main.c with the .so generated , 

```
gcc -O2 main.c -L. -lmylib -Wl,-rpath,'$ORIGIN' -o main
```

Now you can run and check , 
```
./main
```

You can check the .so linking libs , 

```
ldd libmylib.so
	linux-vdso.so.1 (0x00007ffc956e8000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f1729e8a000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f172a439000)
```
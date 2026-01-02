#include <stdio.h>

int add(int,int);
void hello(const char*);

int main() {
    hello("world");
    printf("%d\n", add(2,3));
}

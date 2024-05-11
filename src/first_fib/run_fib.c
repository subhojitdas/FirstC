#include <stdio.h>
#include "common_util.h"

void main() {
    printf("Going to calculate the 18th fibonacci number in the worst way possible");
    int64_t f = fib(18);
    printf("18th fibonacci number is %d", f);
}
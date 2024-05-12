#include <stdio.h>
#include <unistd.h>

int main() {
    long num_cores = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Number of logical cores: %ld\n", num_cores);
    return 0;
}
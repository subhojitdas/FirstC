#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

// Compile command - "gcc -O2 -Wall -Wextra -std=c11 hwinfo.c -ldl -o hwinfo"

#if defined(__x86_64__) || defined(__i386__)
static inline void cpuid(uint32_t leaf, uint32_t subleaf,
                         uint32_t *eax, uint32_t *ebx,
                         uint32_t *ecx, uint32_t *edx) {
#if defined(__i386__) && defined(__PIC__)
    // Preserve ebx for PIC on 32-bit
    __asm__ __volatile__(
        "xchgl %%ebx, %1\n\t"
        "cpuid\n\t"
        "xchgl %%ebx, %1\n\t"
        : "=a"(*eax), "=&r"(*ebx), "=c"(*ecx), "=d"(*edx)
        : "a"(leaf), "c"(subleaf)
    );
#else
    __asm__ __volatile__(
        "cpuid\n\t"
        : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
        : "a"(leaf), "c"(subleaf)
    );
#endif
}
#else
#error "This program currently supports x86/x86_64 only (EC2 G5 is x86_64)."
#endif


static void print_vendor_brand(void) {
    uint32_t eax, ebx, ecx, edx;

    cpuid(0, 0, &eax, &ebx, &ecx, &edx);
    char vendor[13];
    memcpy(&vendor[0], &ebx, 4);
    memcpy(&vendor[4], &edx, 4);
    memcpy(&vendor[8], &ecx, 4);
    vendor[12] = 0;

    printf("CPU Vendor: %s\n", vendor);

    // Brand string (if supported)
    cpuid(0x80000000u, 0, &eax, &ebx, &ecx, &edx);
    if (eax >= 0x80000004u) {
        char brand[49];
        uint32_t regs[4];
        for (int i = 0; i < 3; i++) {
            cpuid(0x80000002u + i, 0, &regs[0], &regs[1], &regs[2], &regs[3]);
            memcpy(brand + i*16 + 0, &regs[0], 4);
            memcpy(brand + i*16 + 4, &regs[1], 4);
            memcpy(brand + i*16 + 8, &regs[2], 4);
            memcpy(brand + i*16 + 12, &regs[3], 4);
        }
        brand[48] = 0;
        // trim leading spaces
        char *p = brand;
        while (*p && isspace((unsigned char)*p)) p++;
        printf("CPU Brand : %s\n", p);
    }
}


int main(void) {
    printf("=== Hardware Introspection (C) ===\n\n");

    print_vendor_brand();
    printf("\n");
//    print_family_model_features();
//    print_cache_info();
//    print_numa_info();
//    print_gpu_info_nvml_or_fallback();

    printf("\nNotes:\n");
    printf("  - CPU features come from CPUID (authoritative).\n");
    printf("  - Cache/NUMA come from sysfs; may require Linux >= 3.x and proper mounts.\n");
    printf("  - GPU details prefer NVML (libnvidia-ml); fallback reads /proc/driver/nvidia.\n");
    printf("  - CUDA Compute Capability (SM version, e.g., 8.6) is easiest via CUDA runtime or torch.\n");
    return 0;
}
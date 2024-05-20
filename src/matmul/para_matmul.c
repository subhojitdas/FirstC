#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <sched.h>
#include <unistd.h>

#define N 1000

double A[N][N];
double B[N][N];
double C[N][N];

float time_diff(struct timespec *start, struct timespec *end) {
    return (end->tv_sec - start->tv_sec) + 
            1e-9*(end->tv_nsec - start->tv_nsec);
}

void main() {

    long long int total_flops = 0;
    double gflops;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = (double)rand() / (double) RAND_MAX;
            B[i][j] = (double)rand() / (double) RAND_MAX;
            C[i][j] = 0;
        }
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int i, j, k;

    // parallel ijk
    #pragma omp parallel for private(i, j, k) shared(A, B, C)
    for (i = 0; i < N; ++i) {
        for (k = 0; k < N; ++k) {
            for (j = 0; j < N; ++j) {
                C[i][j] += A[i][k] * B[k][j];
                // printf("openmp thread number: %d\n", sched_getcpu());
                total_flops += 2;
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed_time = time_diff(&start, &end);

    gflops = (total_flops / elapsed_time) / 1e9;

    printf("Time taken: %0.6f seconds\n", time_diff(&start, &end));
    printf("Total flops: %lld\n", total_flops);
    printf("GFLOPS: %f\n", gflops);

}
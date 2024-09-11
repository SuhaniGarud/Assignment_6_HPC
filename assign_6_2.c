#include <omp.h>
#include <stdio.h>
#define sz 1000

void mat_vec_seq(int A[sz][sz], int B[sz], int C[sz], int n) {
    for (int i = 0; i < n; i++) {
        C[i] = 0;
        for (int j = 0; j < n; j++) {
            C[i] += A[i][j] * B[j];
        }
    }
}

void mat_vec_par(int A[sz][sz], int B[sz], int C[sz], int n) {
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        C[i] = 0;
        for (int j = 0; j < n; j++) {
            C[i] += A[i][j] * B[j];
        }
    }
}

int main() {
    int A[sz][sz], B[sz], C[sz];
    int n = sz;


    for (int i = 0; i < n; i++) {
        B[i] = i;
        for (int j = 0; j < n; j++) {
            A[i][j] = i + j;
        }
    }

    double stime, etime, seqtime, partime, speedup;

    // Sequential execution
    stime = omp_get_wtime();
    mat_vec_seq(A, B, C, n);
    etime = omp_get_wtime();
    seqtime = etime - stime;
    printf("SequentialTime taken: %f seconds\n", seqtime);

    // Parallel execution
    stime = omp_get_wtime();
    mat_vec_par(A, B, C, n);
    etime = omp_get_wtime();
    partime = etime - stime;
    printf("Parallel Time taken: %f seconds\n", partime);

    // Speedup calculation
    speedup = seqtime / partime;
    printf("Speedup: %f\n", speedup);

    return 0;
}

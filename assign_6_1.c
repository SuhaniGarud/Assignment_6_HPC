#include <omp.h>
#include <stdio.h>

#define sz 100

void mat_mul_seq(int A[sz][sz], int B[sz][sz], int C[sz][sz], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void mat_mul_par(int A[sz][sz], int B[sz][sz], int C[sz][sz], int n) {
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int A[sz][sz], B[sz][sz], C[sz][sz];
    int n = sz;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }

    double stime, etime, seqtime, partime, speedup;

    
    stime = omp_get_wtime();
    mat_mul_seq(A, B, C, n);
    etime = omp_get_wtime();
    seqtime = etime - stime;
    printf("Sequential Time taken: %f seconds\n", seqtime);

  
    stime = omp_get_wtime();
    mat_mul_par(A, B, C, n);
    etime = omp_get_wtime();
    partime = etime - stime;
    printf("Parallel Time taken: %f seconds\n", partime);

    // Speedup calculation
    speedup = seqtime / partime;
    printf("Speedup: %f\n", speedup);

    return 0;
}

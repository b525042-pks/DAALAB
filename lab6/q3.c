/*
 * Question 3: Convolution operation on vectors of size n
 * The convolution of two vectors A and B is a new vector C such that
 * C[k] = \sum_{j=0}^{m-1} A[j]B[k-j]
 * Assuming the lengths of A and B are of length m and n, respectively, and the indexing of
 * the vectors starts from 0, find an O(n log n) divide and conquer algorithm for this operation.
 * Consider, n >= m for your implementation and analysis.
 * By choosing the proper input representation, write a program in C to validate your algorithm.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#define PI 3.14159265358979323846
void fft(double complex* x, int N, int invert) {
    if (N <= 1) return;

    double complex* even = malloc(N / 2 * sizeof(double complex));
    double complex* odd = malloc(N / 2 * sizeof(double complex));

    for (int i = 0; i < N / 2; i++) {
        even[i] = x[i * 2];
        odd[i] = x[i * 2 + 1];
    }

    fft(even, N / 2, invert);
    fft(odd, N / 2, invert);

    double angle = 2 * PI / N * (invert ? -1 : 1);
    double complex w = 1;
    double complex wn = cexp(I * angle);

    for (int i = 0; i < N / 2; i++) {
        x[i] = even[i] + w * odd[i];
        x[i + N / 2] = even[i] - w * odd[i];
        if (invert) {
            x[i] /= 2;
            x[i + N / 2] /= 2;
        }
        w *= wn;
    }
    free(even);
    free(odd);
}
/* 
 * Complexity Analysis (Fast Fourier Transform Utility):
 * Worst-case: O(L log L). Cooley-Tukey algorithm limits depth to log L, with O(L) work per level.
 */

void fast_convolution(double* A, int m, double* B, int n) {
    int out_len = m + n - 1;
    int L = 1;
    while (L < out_len) L *= 2;

    double complex* A_comp = calloc(L, sizeof(double complex));
    double complex* B_comp = calloc(L, sizeof(double complex));
    double complex* C_comp = calloc(L, sizeof(double complex));

    for (int i = 0; i < m; i++) A_comp[i] = A[i];
    for (int i = 0; i < n; i++) B_comp[i] = B[i];

    fft(A_comp, L, 0);
    fft(B_comp, L, 0);

    for (int i = 0; i < L; i++) {
        C_comp[i] = A_comp[i] * B_comp[i];
    }

    fft(C_comp, L, 1);

    printf("Convolution Output:\n");
    for (int i = 0; i < out_len; i++) {
        printf("%.2f ", creal(C_comp[i]));
    }
    printf("\n");

    free(A_comp); free(B_comp); free(C_comp);
}
/* 
 * Complexity Analysis (Fast Convolution Algorithm):
 * Worst-case: O(n log n). The runtime is strictly dominated by the FFT conversion steps back 
 * and forth from the frequency domain.
 */

int main() {
    double A[] = {1, 2, 3}; // Length m = 3
    double B[] = {4, 5, 6, 7}; // Length n = 4
    
    printf("\n--- Question 3 Outputs ---\n");
    printf("Input Vector A: ");
    for(int i=0; i<3; i++) printf("%.0f ", A[i]);
    
    printf("\nInput Vector B: ");
    for(int i=0; i<4; i++) printf("%.0f ", B[i]);
    printf("\n");
    
    fast_convolution(A, 3, B, 4);
    
    return 0;
}
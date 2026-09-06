/*
 * Question 2: 2D square matrix operations and their complexities
 * Given square matrices with n rows and n columns, what is the worst-case computational complexity of the following matrix algorithms in terms of n:
 * (i) Matrix Addition.
 * (ii) Matrix Multiplication.
 * (iii) Finding if the given matrix is a zero matrix.
 * (iv) Finding if the given matrix is a symmetric matrix.
 * (v) Computing the determinant of the given matrix.
 * (vi) Transposing the matrix in situ (in place).
 * (vii) Finding the eigenvalue and eigenvector of the matrix.
 * By choosing the proper input representation, write a program in C to validate your procedures and derive the corresponding complexity analysis.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define N 3
void addMatrix(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C[i][j] = A[i][j] + B[i][j];
}
/* 
 * Complexity Analysis (Matrix Addition):
 * Worst-case: O(n^2). Performs one addition per cell for all n^2 elements.
 */
void multiplyMatrix(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}
/* 
 * Complexity Analysis (Matrix Multiplication):
 * Worst-case: O(n^3). Three nested loops running to n.
 */
bool isZeroMatrix(int A[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (A[i][j] != 0) return false;
    return true;
}
/* 
 * Complexity Analysis (Finding if zero matrix):
 * Worst-case: O(n^2). Checks all n^2 elements before confirming.
 */
bool isSymmetricMatrix(int A[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < i; j++)
            if (A[i][j] != A[j][i]) return false;
    return true;
}
/* 
 * Complexity Analysis (Finding if symmetric matrix):
 * Worst-case: O(n^2). Checks the upper triangle against the lower triangle.
 */
double determinantMatrix(double mat[N][N]) {
    double temp[N][N];
    for(int i=0; i<N; i++) for(int j=0; j<N; j++) temp[i][j] = mat[i][j];
    double det = 1.0;
    for (int i = 0; i < N; i++) {
        if (temp[i][i] == 0) return 0; 
        for (int j = i + 1; j < N; j++) {
            double ratio = temp[j][i] / temp[i][i];
            for (int k = 0; k < N; k++) {
                temp[j][k] -= ratio * temp[i][k];
            }
        }
        det *= temp[i][i];
    }
    return det;
}
/* 
 * Complexity Analysis (Computing the determinant):
 * Worst-case: O(n^3). Gaussian elimination logic runs in O(n^3).
 */

void transposeInSitu(int A[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}
/* 
 * Complexity Analysis (Transposing in situ):
 * Worst-case: O(n^2). Swaps n(n-1)/2 pairs.
 */

double dominantEigen(double A[N][N], double v[N]) {
    double v_new[N];
    double lambda = 0, lambda_old = 0;
    for(int i=0; i<N; i++) v[i] = 1.0; 
    
    for (int iter = 0; iter < 100; iter++) {
        for (int i = 0; i < N; i++) {
            v_new[i] = 0;
            for (int j = 0; j < N; j++) v_new[i] += A[i][j] * v[j];
        }
        lambda_old = lambda;
        lambda = 0;
        for (int i = 0; i < N; i++) {
            if (fabs(v_new[i]) > fabs(lambda)) lambda = v_new[i];
        }
        for (int i = 0; i < N; i++) v[i] = v_new[i] / lambda;
        if (fabs(lambda - lambda_old) < 1e-6) break;
    }
    return lambda;
}
/* 
 * Complexity Analysis (Finding eigenvalue and eigenvector):
 * Worst-case: O(k * n^2). Power iteration requires k matrix-vector multiplications.
 */
void printMatrix(int A[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int A[N][N] = {
        {2, -1, 0},
        {-1, 2, -1},
        {0, -1, 2}
    };
    int B[N][N] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    int C[N][N];
    double double_A[N][N] = {
        {2.0, -1.0, 0.0},
        {-1.0, 2.0, -1.0},
        {0.0, -1.0, 2.0}
    };
    double eigen_vec[N];
    printf("\n--- Question 2 Outputs ---\n");
    printf("Matrix A:\n");
    printMatrix(A);
    printf("Matrix B (Identity):\n");
    printMatrix(B);
    // (i)
    addMatrix(A, B, C);
    printf("\n(i) Addition Result:\n");
    printMatrix(C);
    // (ii)
    multiplyMatrix(A, B, C);
    printf("\n(ii) Multiplication Result (A * I):\n");
    printMatrix(C);
    // (iii)
    printf("\n(iii) Is A a zero matrix? %s\n", isZeroMatrix(A) ? "True" : "False");
    // (iv)
    printf("(iv) Is A a symmetric matrix? %s\n", isSymmetricMatrix(A) ? "True" : "False");
    // (v)
    printf("(v) Determinant of A: %.2f\n", determinantMatrix(double_A));
    // (vi)
    int transposeTest[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    transposeInSitu(transposeTest);
    printf("(vi) Transpose In Situ (1-9 Matrix):\n");
    printMatrix(transposeTest);

    // (vii)
    double dom_eigen = dominantEigen(double_A, eigen_vec);
    printf("(vii) Dominant Eigenvalue of A: %.4f\n", dom_eigen);
    printf("      Associated Eigenvector: [%.4f, %.4f, %.4f]\n", eigen_vec[0], eigen_vec[1], eigen_vec[2]);

    return 0;
}
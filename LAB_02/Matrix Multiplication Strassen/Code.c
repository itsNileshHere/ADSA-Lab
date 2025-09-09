#include <stdio.h>
#include <stdlib.h>

// Add two matrices (C = A + B)
void add(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Subtract two matrices (C = A - B)
void subtract(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Recursive Strassen multiplication (C = A * B)
void strassen(int n, int A[n][n], int B[n][n], int C[n][n]) {
    // For 2x2 matrix
    if(n == 2) {
        int m1 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
        int m2 = (A[1][0] + A[1][1]) * B[0][0];
        int m3 = A[0][0] * (B[0][1] - B[1][1]);
        int m4 = A[1][1] * (B[1][0] - B[0][0]);
        int m5 = (A[0][0] + A[0][1]) * B[1][1];
        int m6 = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]);
        int m7 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);

        // Combine intermediate products to get the final matrix
        C[0][0] = m1 + m4 - m5 + m7;
        C[0][1] = m3 + m5;
        C[1][0] = m2 + m4;
        C[1][1] = m1 - m2 + m3 + m6;
        return;
    }

    int half = n / 2;  // Size after splitting
    int i, j;

    // Declare Submatrices
    int A11[half][half], A12[half][half], A21[half][half], A22[half][half];
    int B11[half][half], B12[half][half], B21[half][half], B22[half][half];
    int C11[half][half], C12[half][half], C21[half][half], C22[half][half];
    int M1[half][half], M2[half][half], M3[half][half], M4[half][half];
    int M5[half][half], M6[half][half], M7[half][half];
    int ARes[half][half], BRes[half][half];

    // Splitting matrices A and B into four submatrices
    for(i = 0; i < half; i++)
        for(j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }

    // Compute the Strassen products recursively
    add(half, A11, A22, ARes);
    add(half, B11, B22, BRes);
    strassen(half, ARes, BRes, M1);     // M1 = (A11 + A22) * (B11 + B22)

    add(half, A21, A22, ARes);
    strassen(half, ARes, B11, M2);      // M2 = (A21 + A22) * B11

    subtract(half, B12, B22, BRes);
    strassen(half, A11, BRes, M3);      // M3 = A11 * (B12 - B22)

    subtract(half, B21, B11, BRes);
    strassen(half, A22, BRes, M4);      // M4 = A22 * (B21 - B11)

    add(half, A11, A12, ARes);
    strassen(half, ARes, B22, M5);      // M5 = (A11 + A12) * B22

    subtract(half, A21, A11, ARes);
    add(half, B11, B12, BRes);
    strassen(half, ARes, BRes, M6);     // M6 = (A21 - A11) * (B11 + B12)

    subtract(half, A12, A22, ARes);
    add(half, B21, B22, BRes);
    strassen(half, ARes, BRes, M7);     // M7 = (A12 - A22) * (B21 + B22)

    // Compute C submatrices by combining M1-M7
    add(half, M1, M4, ARes);
    subtract(half, ARes, M5, BRes);
    add(half, BRes, M7, C11);       // C11 = M1 + M4 - M5 + M7

    add(half, M3, M5, C12);     // C12 = M3 + M5
    add(half, M2, M4, C21);     // C21 = M2 + M4

    subtract(half, M1, M2, ARes);
    add(half, ARes, M3, BRes);
    add(half, BRes, M6, C22);   // C22 = M1 - M2 + M3 + M6

    // Merge submatrices into result matrix C
    for(i = 0; i < half; i++)
        for(j = 0; j < half; j++) {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
}

int main() {
    int n = 4;  // Size of the matrices
    int A[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    int B[4][4] = {
        {16, 15, 14, 13},
        {12, 11, 10, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    };
    int C[4][4]; // Result matrix

    strassen(n, A, B, C);

    printf("Product matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            printf("%d\t", C[i][j]);
        printf("\n");
    }

    return 0;
}

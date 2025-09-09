#include <stdio.h>
#include <math.h>

#define N 3   // size of matrix (3x3 for demo)

// Function to perform LUP decomposition
void lupDecomposition(double A[N][N], double L[N][N], double U[N][N], int P[N]) {
    // Initialize P as identity permutation
    for (int i = 0; i < N; i++) {
        P[i] = i;
    }

    for (int k = 0; k < N; k++) {
        // Find row with max absolute value in column k
        double pivotValue = 0.0;
        int pivotRow = k;
        for (int i = k; i < N; i++) {
            if (fabs(A[i][k]) > pivotValue) {
                pivotValue = fabs(A[i][k]);
                pivotRow = i;
            }
        }

        // Swap rows k and pivotRow in A and record in P
        if (pivotRow != k) {
            for (int j = 0; j < N; j++) {
                double temp = A[k][j];
                A[k][j] = A[pivotRow][j];
                A[pivotRow][j] = temp;
            }
            int tempP = P[k];
            P[k] = P[pivotRow];
            P[pivotRow] = tempP;
        }

        // Elimination step
        for (int i = k+1; i < N; i++) {
            A[i][k] /= A[k][k];
            for (int j = k+1; j < N; j++) {
                A[i][j] -= A[i][k] * A[k][j];
            }
        }
    }

    // Extract L and U from modified A
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i > j) {
                L[i][j] = A[i][j];
                U[i][j] = 0;
            } else if (i == j) {
                L[i][j] = 1;
                U[i][j] = A[i][j];
            } else {
                L[i][j] = 0;
                U[i][j] = A[i][j];
            }
        }
    }
}

int main() {
    // Example matrix
    double A[N][N] = {
        {4,  2,  3},
        {6, -5,  2},
        {1,  3, -1}
    };

    double L[N][N], U[N][N];
    int P[N];

    lupDecomposition(A, L, U, P);

    // Permutation Matrix
    printf("P =\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (P[i] == j) printf(" 1 ");
            else printf(" 0 ");
        }
        printf("\n");
    }
    printf("\n");

    // L
    printf("L =\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%6.3f ", L[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // U
    printf("U =\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%6.3f ", U[i][j]);
        }
        printf("\n");
    }

    return 0;
}

#include <stdio.h>
#include <math.h>

#define N 3

// LUP decomposition
void lupDecomposition(double A[N][N], double L[N][N], double U[N][N], int P[N]) {
    for (int i = 0; i < N; i++) P[i] = i;

    for (int k = 0; k < N; k++) {
        double pivotValue = 0.0;
        int pivotRow = k;
        for (int i = k; i < N; i++)
            if (fabs(A[i][k]) > pivotValue) { pivotValue = fabs(A[i][k]); pivotRow = i; }

        if (pivotRow != k) {
            for (int j = 0; j < N; j++) { double tmp = A[k][j]; A[k][j] = A[pivotRow][j]; A[pivotRow][j] = tmp; }
            int tmpP = P[k]; P[k] = P[pivotRow]; P[pivotRow] = tmpP;
        }

        for (int i = k+1; i < N; i++) {
            A[i][k] /= A[k][k];
            for (int j = k+1; j < N; j++)
                A[i][j] -= A[i][k] * A[k][j];
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if (i > j) { L[i][j] = A[i][j]; U[i][j] = 0; }
            else if (i == j) { L[i][j] = 1; U[i][j] = A[i][j]; }
            else { L[i][j] = 0; U[i][j] = A[i][j]; }
        }
}

// Forward substitution: solve Ly = Pb
void forwardSubstitution(double L[N][N], double b[N], double y[N]) {
    for (int i = 0; i < N; i++) {
        y[i] = b[i];
        for (int j = 0; j < i; j++)
            y[i] -= L[i][j] * y[j];
    }
}

// Backward substitution: solve Ux = y
void backwardSubstitution(double U[N][N], double y[N], double x[N]) {
    for (int i = N-1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i+1; j < N; j++)
            x[i] -= U[i][j] * x[j];
        x[i] /= U[i][i];
    }
}

int main() {
    // Example matrix
    double A[N][N] = {
        {4, 2, 3},
        {3, -5, 2},
        {1, 3, -1}
    };

    double b[N] = {8, -14, 2};  // Example RHS
    double L[N][N], U[N][N], y[N], x[N];
    int P[N];

    lupDecomposition(A, L, U, P);

    // Apply permutation to b: Pb
    double Pb[N];
    for (int i = 0; i < N; i++)
        Pb[i] = b[P[i]];

    forwardSubstitution(L, Pb, y);
    backwardSubstitution(U, y, x);

    printf("Solution x =\n");
    for (int i = 0; i < N; i++)
        printf("%8.3f\n", x[i]);

    return 0;
}

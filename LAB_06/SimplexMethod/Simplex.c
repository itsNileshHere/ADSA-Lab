#include <stdio.h>

#define MAX 10

void print_tableau(float A[MAX][MAX], int m, int n) {
    printf("\nCurrent Simplex Tableau:\n");
    for (int i = 0; i <= m; i++) {
        for (int j = 1; j <= n + 1; j++)
            printf("%8.2f ", A[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main() {
    int m = 2;  // number of constraints
    int n = 2;  // number of variables

    float A[MAX][MAX] = {0};

    // Constraint coefficients
    A[1][1] = 1;  A[1][2] = 2;
    A[2][1] = 3;  A[2][2] = 2;

    // RHS values
    A[1][n + m + 1] = 8;
    A[2][n + m + 1] = 12;

    // Add slack variables
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++)
            A[i][n + j] = (i == j) ? 1.0 : 0.0;
    }

    // Objective function (Z = 3x1 + 5x2)
    A[0][1] = -3;
    A[0][2] = -5;

    int total_vars = n + m;

    printf("Maximize Z = 3x1 + 5x2\n");
    printf("Subject to:\n");
    printf("  x1 + 2x2 <= 8\n");
    printf("  3x1 + 2x2 <= 12\n");
    printf("  x1, x2 >= 0\n");

    int iteration = 1;

    // Simplex iterations
    while (1) {
        printf("\n========================");
        printf("\nIteration %d\n", iteration++);
        print_tableau(A, m, total_vars);

        // Find entering variable (most negative in row 0)
        int pivot_col = 1;
        float min = A[0][1];
        for (int j = 2; j <= total_vars; j++) {
            if (A[0][j] < min) {
                min = A[0][j];
                pivot_col = j;
            }
        }
        if (min >= 0)
            break; // optimal

        printf("Entering variable: x%d (column %d)\n", pivot_col, pivot_col);

        // Find leaving variable
        int pivot_row = -1;
        float min_ratio = 1e9;
        for (int i = 1; i <= m; i++) {
            if (A[i][pivot_col] > 0) {
                float ratio = A[i][n + m + 1] / A[i][pivot_col];
                if (ratio < min_ratio) {
                    min_ratio = ratio;
                    pivot_row = i;
                }
            }
        }

        if (pivot_row == -1) {
            printf("Unbounded solution!\n");
            return 0;
        }

        printf("Leaving variable: Row %d\n", pivot_row);

        // Pivot operation
        float pivot = A[pivot_row][pivot_col];
        printf("Pivot element = A[%d][%d] = %.2f\n", pivot_row, pivot_col, pivot);

        // Normalize pivot row
        printf("\n-- Divide Row %d by %.2f --\n", pivot_row, pivot);
        for (int j = 1; j <= total_vars + 1; j++)
            A[pivot_row][j] /= pivot;

        // Eliminate pivot column from other rows
        for (int i = 0; i <= m; i++) {
            if (i != pivot_row) {
                float factor = A[i][pivot_col];
                if (factor != 0) {
                    printf("-- Row %d = Row %d - (%.2f)*Row %d --\n", i, i, factor, pivot_row);
                    for (int j = 1; j <= total_vars + 1; j++)
                        A[i][j] -= factor * A[pivot_row][j];
                }
            }
        }
    }

    // Print final result
    printf("\n========================\n");
    printf("Final Tableau (Optimal):\n");
    print_tableau(A, m, total_vars);
    printf("Optimal Solution Found!\n");
    printf("Z = %.2f\n", A[0][n + m + 1]);

    // Variable values (basic variables)
    float x[MAX] = {0};
    for (int j = 1; j <= n; j++) {
        int count = 0, pos = -1;
        for (int i = 1; i <= m; i++) {
            if (A[i][j] == 1) { count++; pos = i; }
            else if (A[i][j] != 0) { count = -1; break; }
        }
        if (count == 1)
            x[j] = A[pos][n + m + 1];
    }

    printf("\nVariable Values:\n");
    for (int j = 1; j <= n; j++)
        printf("x%d = %.2f\n", j, x[j]);

    return 0;
}

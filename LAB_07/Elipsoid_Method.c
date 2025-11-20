#include <stdio.h>
#include <math.h>

#define MAXN 20
#define ITER 2000
#define EPS 1e-6

// Multiply matrix R (n×n) with vector v
void mat_vec(double R[MAXN][MAXN], double *v, double *out, int n) {
    for (int i = 0; i < n; i++) {
        out[i] = 0;
        for (int j = 0; j < n; j++)
            out[i] += R[i][j] * v[j];
    }
}

// Outer product u vᵀ
void outer(double *u, double *v, double out[MAXN][MAXN], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out[i][j] = u[i] * v[j];
}

// Subtract matrices
void mat_sub(double A[MAXN][MAXN], double B[MAXN][MAXN], double out[MAXN][MAXN], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out[i][j] = A[i][j] - B[i][j];
}

// Scale a matrix
void mat_scale(double A[MAXN][MAXN], double c, double out[MAXN][MAXN], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out[i][j] = A[i][j] * c;
}

int main() {

    int m = 3;
    int n = 2;

    double A[3][20] = {
        {-1, -1},   // x + y ≥ 5   -> -x - y ≤ -5
        {-1,  0},   // x ≥ 1       -> -x ≤ -1
        { 0, -1}    // y ≥ 2       -> -y ≤ -2
    };

    double b[3] = {-5, -1, -2};


    // =======================================

    double x[MAXN] = {0};  // starting center (at origin)

    // Initial ellipsoid Q = R² * I
    double R = 10.0;
    double Q[MAXN][MAXN];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Q[i][j] = (i == j ? R * R : 0);

    printf("Running ellipsoid method...\n");

    for (int it = 0; it < ITER; it++) {

        int violated = -1;

        // Find a violated constraint
        for (int i = 0; i < m; i++) {
            double lhs = 0;
            for (int j = 0; j < n; j++)
                lhs += A[i][j] * x[j];

            if (lhs > b[i] + EPS) {
                violated = i;
                break;
            }
        }

        // If no constraint violated → feasible
        if (violated == -1) {
            printf("Feasible point found:\n");
            for (int i = 0; i < n; i++)
                printf("x[%d] = %.6f\n", i, x[i]);
            return 0;
        }

        double *a = A[violated];

        // Compute Q a
        double Qa[MAXN];
        mat_vec(Q, a, Qa, n);

        // denom = sqrt(aᵀ Q a)
        double denom = 0;
        for (int i = 0; i < n; i++)
            denom += a[i] * Qa[i];
        denom = sqrt(denom);

        // Update center
        for (int i = 0; i < n; i++)
            x[i] = x[i] - (Qa[i] / ((n + 1) * denom));

        // u = Qa / denom
        double u[MAXN];
        for (int i = 0; i < n; i++)
            u[i] = Qa[i] / denom;

        // uuᵀ
        double uuT[MAXN][MAXN];
        outer(u, u, uuT, n);

        // term = (2/(n+1)) * uuᵀ
        double term[MAXN][MAXN];
        mat_scale(uuT, 2.0 / (n + 1), term, n);

        // tmp = Q - term
        double tmp[MAXN][MAXN];
        mat_sub(Q, term, tmp, n);

        // Q_new = (n²/(n² - 1)) * tmp
        double Qnew[MAXN][MAXN];
        double scale = ((double)n * n) / (n * n - 1);
        mat_scale(tmp, scale, Qnew, n);

        // Copy Qnew into Q
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                Q[i][j] = Qnew[i][j];
    }

    printf("No feasible point found (max iterations reached).\n");
    return 0;
}

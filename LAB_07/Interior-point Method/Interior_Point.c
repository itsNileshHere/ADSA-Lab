#include <stdio.h>
#include <stdlib.h>

#define MAX_ITER 50
#define TOL 1e-6

// Simplified interior point method for LP
// minimize c^T x subject to Ax = b, x >= 0

typedef struct {
    int m;  // number of constraints
    int n;  // number of variables
    double **A;  // constraint matrix (m x n)
    double *b;   // RHS vector (m)
    double *c;   // cost vector (n)
} LP;

// Allocate matrix
double** alloc_matrix(int rows, int cols) {
    double **mat = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        mat[i] = (double*)malloc(cols * sizeof(double));
    }
    return mat;
}

// Free matrix
void free_matrix(double **mat, int rows) {
    for (int i = 0; i < rows; i++) {
        free(mat[i]);
    }
    free(mat);
}

// Matrix-vector multiplication: result = A * x
void mat_vec_mult(double **A, double *x, double *result, int m, int n) {
    for (int i = 0; i < m; i++) {
        result[i] = 0;
        for (int j = 0; j < n; j++) {
            result[i] += A[i][j] * x[j];
        }
    }
}

// Simple absolute value
double my_fabs(double x) {
    return (x < 0) ? -x : x;
}

// Simple sqrt implementation
double my_sqrt(double x) {
    if (x <= 0) return 0;
    double guess = x / 2.0;
    for (int i = 0; i < 20; i++) {
        guess = (guess + x / guess) / 2.0;
    }
    return guess;
}

// Simple min function
double my_min(double a, double b) {
    return (a < b) ? a : b;
}

// Vector norm
double vec_norm(double *v, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += v[i] * v[i];
    }
    return my_sqrt(sum);
}

// Dot product
double dot_product(double *a, double *b, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

// Solve (A * D * A^T) * y = rhs using Gaussian elimination
void solve_normal_equations(double **A, double *D, double *rhs, double *y, int m, int n) {
    // Create matrix M = A * D * A^T
    double **M = alloc_matrix(m, m);
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            M[i][j] = 0;
            for (int k = 0; k < n; k++) {
                M[i][j] += A[i][k] * D[k] * A[j][k];
            }
        }
    }
    
    // Augmented matrix for Gaussian elimination
    double **aug = alloc_matrix(m, m + 1);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            aug[i][j] = M[i][j];
        }
        aug[i][m] = rhs[i];
    }
    
    // Forward elimination with partial pivoting
    for (int i = 0; i < m; i++) {
        // Find pivot
        int max_row = i;
        for (int k = i + 1; k < m; k++) {
            if (my_fabs(aug[k][i]) > my_fabs(aug[max_row][i])) {
                max_row = k;
            }
        }
        
        // Swap rows
        double *temp = aug[i];
        aug[i] = aug[max_row];
        aug[max_row] = temp;
        
        // Check for singular matrix
        if (my_fabs(aug[i][i]) < 1e-10) {
            printf("Warning: Nearly singular matrix\n");
            aug[i][i] = 1e-10;
        }
        
        // Eliminate
        for (int k = i + 1; k < m; k++) {
            double factor = aug[k][i] / aug[i][i];
            for (int j = i; j <= m; j++) {
                aug[k][j] -= factor * aug[i][j];
            }
        }
    }
    
    // Back substitution
    for (int i = m - 1; i >= 0; i--) {
        y[i] = aug[i][m];
        for (int j = i + 1; j < m; j++) {
            y[i] -= aug[i][j] * y[j];
        }
        y[i] /= aug[i][i];
    }
    
    free_matrix(M, m);
    free_matrix(aug, m);
}

// Simplified interior point method
int interior_point(LP *lp, double *x, double *lambda, double *s) {
    int m = lp->m;
    int n = lp->n;
    
    // Better initialization
    for (int i = 0; i < n; i++) {
        x[i] = 1.0;
        s[i] = 1.0;
    }
    for (int i = 0; i < m; i++) {
        lambda[i] = 0.0;
    }
    
    // Allocate working arrays
    double *Ax = (double*)malloc(m * sizeof(double));
    double *ATlambda = (double*)malloc(n * sizeof(double));
    double *rc = (double*)malloc(n * sizeof(double));
    double *rb = (double*)malloc(m * sizeof(double));
    double *rxs = (double*)malloc(n * sizeof(double));
    double *dx = (double*)malloc(n * sizeof(double));
    double *dlambda = (double*)malloc(m * sizeof(double));
    double *ds = (double*)malloc(n * sizeof(double));
    double *D = (double*)malloc(n * sizeof(double));
    double *rhs = (double*)malloc(m * sizeof(double));
    
    printf("\nStarting interior point method...\n");
    
    for (int iter = 0; iter < MAX_ITER; iter++) {
        // Compute complementarity gap
        double mu = 0;
        for (int i = 0; i < n; i++) {
            mu += x[i] * s[i];
        }
        mu /= n;
        
        // Check convergence
        if (mu < TOL) {
            printf("Converged at iteration %d\n", iter);
            break;
        }
        
        // Compute residuals
        // rc = A^T * lambda + s - c
        for (int i = 0; i < n; i++) {
            ATlambda[i] = 0;
            for (int j = 0; j < m; j++) {
                ATlambda[i] += lp->A[j][i] * lambda[j];
            }
            rc[i] = ATlambda[i] + s[i] - lp->c[i];
        }
        
        // rb = Ax - b
        mat_vec_mult(lp->A, x, Ax, m, n);
        for (int i = 0; i < m; i++) {
            rb[i] = Ax[i] - lp->b[i];
        }
        
        // rxs = X*S*e - sigma*mu*e
        double sigma = 0.1;
        for (int i = 0; i < n; i++) {
            rxs[i] = x[i] * s[i] - sigma * mu;
        }
        
        // Check residuals
        double rc_norm = vec_norm(rc, n);
        double rb_norm = vec_norm(rb, m);
        
        if (iter % 5 == 0) {
            printf("Iter %2d: mu=%.2e, ||rc||=%.2e, ||rb||=%.2e\n", 
                   iter, mu, rc_norm, rb_norm);
        }
        
        // Solve Newton system
        // Form D = X / S (diagonal matrix stored as vector)
        for (int i = 0; i < n; i++) {
            if (s[i] > 1e-10) {
                D[i] = x[i] / s[i];
            } else {
                D[i] = 1e-10;
            }
        }
        
        // Form RHS for normal equations
        for (int i = 0; i < m; i++) {
            rhs[i] = -rb[i];
            for (int j = 0; j < n; j++) {
                rhs[i] -= lp->A[i][j] * D[j] * (rc[j] - rxs[j] / x[j]);
            }
        }
        
        // Solve for dlambda
        solve_normal_equations(lp->A, D, rhs, dlambda, m, n);
        
        // Recover ds and dx
        for (int i = 0; i < n; i++) {
            ds[i] = -rc[i];
            for (int j = 0; j < m; j++) {
                ds[i] -= lp->A[j][i] * dlambda[j];
            }
            
            dx[i] = (-rxs[i] - x[i] * ds[i]) / s[i];
        }
        
        // Line search to maintain positivity
        double alpha_p = 1.0;
        double alpha_d = 1.0;
        
        for (int i = 0; i < n; i++) {
            if (dx[i] < 0) {
                double alpha_temp = -x[i] / dx[i];
                if (alpha_temp < alpha_p) alpha_p = alpha_temp;
            }
            if (ds[i] < 0) {
                double alpha_temp = -s[i] / ds[i];
                if (alpha_temp < alpha_d) alpha_d = alpha_temp;
            }
        }
        
        // Take 99% of maximum step to stay interior
        alpha_p = my_min(0.995 * alpha_p, 1.0);
        alpha_d = my_min(0.995 * alpha_d, 1.0);
        
        // Update variables
        for (int i = 0; i < n; i++) {
            x[i] += alpha_p * dx[i];
            s[i] += alpha_d * ds[i];
            
            // Safety: ensure positivity
            if (x[i] < 1e-10) x[i] = 1e-10;
            if (s[i] < 1e-10) s[i] = 1e-10;
        }
        
        for (int i = 0; i < m; i++) {
            lambda[i] += alpha_d * dlambda[i];
        }
    }
    
    // Cleanup
    free(Ax); free(ATlambda); free(rc); free(rb); free(rxs);
    free(dx); free(dlambda); free(ds); free(D); free(rhs);
    
    return 0;
}

int main() {
    // Example: minimize -x1 - 2*x2
    //          subject to: x1 + x2 <= 3
    //                      x1, x2 >= 0
    //
    // Standard form: minimize -x1 - 2*x2
    //                subject to: x1 + x2 + x3 = 3
    //                            x1, x2, x3 >= 0
    
    LP lp;
    lp.m = 1;  // 1 equality constraint
    lp.n = 3;  // 3 variables
    
    lp.A = alloc_matrix(lp.m, lp.n);
    lp.b = (double*)malloc(lp.m * sizeof(double));
    lp.c = (double*)malloc(lp.n * sizeof(double));
    
    // Constraint: x1 + x2 + x3 = 3
    lp.A[0][0] = 1.0;
    lp.A[0][1] = 1.0;
    lp.A[0][2] = 1.0;
    lp.b[0] = 3.0;
    
    // Objective: minimize -x1 - 2*x2 + 0*x3
    lp.c[0] = -1.0;
    lp.c[1] = -2.0;
    lp.c[2] = 0.0;
    
    double *x = (double*)malloc(lp.n * sizeof(double));
    double *lambda = (double*)malloc(lp.m * sizeof(double));
    double *s = (double*)malloc(lp.n * sizeof(double));
    
    printf("Solving LP:\n");
    printf("  minimize: -x1 - 2*x2\n");
    printf("  subject to: x1 + x2 <= 3\n");
    printf("              x1, x2 >= 0\n");
    
    interior_point(&lp, x, lambda, s);
    
    printf("\n=== SOLUTION ===\n");
    printf("x1 = %.6f\n", x[0]);
    printf("x2 = %.6f\n", x[1]);
    printf("x3 = %.6f (slack variable)\n", x[2]);
    
    double obj = lp.c[0] * x[0] + lp.c[1] * x[1] + lp.c[2] * x[2];
    printf("\nObjective value: %.6f\n", obj);
    printf("(Expected: -6.0 with x1=0, x2=3)\n");
    
    // Cleanup
    free_matrix(lp.A, lp.m);
    free(lp.b);
    free(lp.c);
    free(x);
    free(lambda);
    free(s);
    
    return 0;
}
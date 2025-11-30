## Problem

This program implements the Ellipsoid Method, an iterative algorithm used in convex optimization to find a feasible point within a given convex set. It's particularly notable for its theoretical significance in proving the polynomial-time solvability of linear programming problems.

## Theory

The Ellipsoid Method is a powerful algorithm in convex optimization. It operates by maintaining an ellipsoid that is guaranteed to contain the feasible region (or the minimizer of a convex function). In each iteration, the ellipsoid is updated to a smaller one that still contains the feasible region.

The core idea is:
1.  **Initial Ellipsoid:** Start with a large ellipsoid known to contain the solution space.
2.  **Query Center:** Query a "separation oracle" at the center of the current ellipsoid. For a feasibility problem (like finding a point in a convex set defined by inequalities), the oracle checks if the current center `x` satisfies all constraints.
3.  **Generate Cutting Plane:**
    *   If `x` is feasible, then it's a solution, and the algorithm terminates.
    *   If `x` is not feasible, there must be at least one constraint that `x` violates. This violated constraint defines a hyperplane that "cuts" off the infeasible part of the current ellipsoid.
4.  **Update Ellipsoid:** A new, smaller ellipsoid is then constructed such that it encloses the portion of the previous ellipsoid that lies on the "feasible side" of the cutting plane. The volume of the ellipsoid is guaranteed to decrease by a certain factor in each step.
5.  **Iteration:** This process repeats until a feasible point is found or a maximum number of iterations is reached (or the ellipsoid becomes too small, indicating no feasible point).

### Significance in Linear Programming

The Ellipsoid Method achieved fame in 1979 when Leonid Khachiyan used it to demonstrate that Linear Programming Problems (LPPs) can be solved in polynomial time. Prior to this, while the Simplex Method was (and still is) very efficient in practice, its worst-case time complexity was exponential. Thus, the Ellipsoid Method provided the first theoretical polynomial-time algorithm for LPPs.

However, despite its theoretical importance, the Ellipsoid Method is generally not used for practical LPPs because:
-   It is often slower in practice compared to the Simplex Method or Interior-Point Methods.
-   It can suffer from numerical instability.

Its main practical applications are in theoretical computer science, particularly in combinatorial optimization, where it can prove the polynomial-time solvability of problems and handle problems with exponentially many constraints if an efficient separation oracle exists.

## Approach

The `Elipsoid_Method.c` program implements the Ellipsoid Method to find a feasible point for a system of linear inequalities. The problem is stated as finding `x` such that `A*x <= b`.

-   **`m`, `n`:** Represent the number of constraints and the number of variables (dimension of `x`).
-   **`A[MAXN][MAXN]`, `b[MAXN]`:** Store the coefficients of the linear inequalities and their right-hand side values. Note that inequalities are transformed to `a*x <= b`. If the original problem has `a*x >= b`, it's rewritten as `-a*x <= -b`.
-   **`x[MAXN]`:** Represents the current center of the ellipsoid.
-   **`Q[MAXN][MAXN]`:** Represents the ellipsoid, specifically its shape matrix. Initially, it's a scaled identity matrix.
-   **Helper Functions (`mat_vec`, `outer`, `mat_sub`, `mat_scale`):** Perform basic matrix and vector operations (multiplication, outer product, subtraction, scaling) required for ellipsoid updates.
-   **Main Iteration Loop (`for (int it = 0; it < ITER; it++)`):**
    1.  **Find Violated Constraint:** It iterates through all constraints to check if the current center `x` satisfies them. If `A[i]*x > b[i] + EPS`, then constraint `i` is violated.
    2.  **Feasibility Check:** If no constraint is violated (`violated == -1`), `x` is a feasible point, and the algorithm terminates successfully.
    3.  **Update Ellipsoid:** If a constraint is violated, the ellipsoid's center `x` and shape matrix `Q` are updated using a series of matrix/vector operations based on the violated constraint (`a = A[violated]`). These operations involve calculating `Qa`, `denom`, `u`, `uuT`, and finally `Q_new`.

## Usage

To compile and run the code:

```bash
gcc Elipsoid_Method.c -o Elipsoid_Method -lm
./Elipsoid_Method
```

The program has a hardcoded example system of inequalities:
-   `x + y >= 5`  (converted to `-x - y <= -5`)
-   `x >= 1`      (converted to `-x <= -1`)
-   `y >= 2`      (converted to `-y <= -2`)

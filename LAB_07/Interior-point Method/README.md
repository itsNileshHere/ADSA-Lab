## Problem

This program implements a simplified version of an Interior-Point Method (specifically, a primal-dual path-following method) to solve Linear Programming Problems (LPPs). It aims to find the optimal solution for problems of the form:
minimize `c^T * x`
subject to `A * x = b`
and `x >= 0`

## Theory

Interior-Point Methods (IPMs), also known as barrier methods, are a class of algorithms used in mathematical optimization to solve linear and non-linear convex optimization problems. Unlike the Simplex Method, which traverses the vertices along the boundary of the feasible region, IPMs approach the optimal solution by moving through the *interior* of the feasible region.

The core idea of IPMs involves:
1.  **Barrier Function:** Transforming the constrained optimization problem into a sequence of unconstrained problems by adding a "barrier function" to the objective function. This barrier function penalizes solutions that get too close to the boundary of the feasible region, ensuring the algorithm stays in the interior.
2.  **Central Path:** As the algorithm progresses, the influence of the barrier function is gradually reduced, guiding the solution along a "central path" that converges to the optimal solution on the boundary of the feasible region.
3.  **Newton's Method:** Each unconstrained problem in the sequence is typically solved using Newton's method or a similar iterative technique, which involves solving a system of linear equations at each step.

### Advantages of Interior-Point Methods:

-   **Polynomial-Time Complexity:** A significant theoretical advantage is their proven polynomial-time complexity in the worst case, guaranteeing that the time required to solve a problem grows polynomially with its size. This contrasts with the Simplex Method, which can have exponential worst-case runtime.
-   **Efficiency for Large-Scale Problems:** IPMs are often very efficient for large-scale LPPs, sometimes outperforming the Simplex Method for very large instances.


## Approach

The `Interior_Point.c` program implements a simplified primal-dual interior-point method.

-   **`LP` struct:** Defines the Linear Programming problem, storing the constraint matrix `A` (m x n), RHS vector `b` (m), and cost vector `c` (n).
-   **Helper Functions (`alloc_matrix`, `free_matrix`, `mat_vec_mult`, `my_fabs`, `my_sqrt`, `my_min`, `vec_norm`, `dot_product`):** Provide basic matrix/vector operations and mathematical utilities.
-   **`solve_normal_equations()`:** Solves a system of linear equations, which is a key step in Newton's method used within the IPM. This implementation uses Gaussian elimination with partial pivoting.
-   **`interior_point()` function:** The core IPM implementation:
    1.  **Initialization:** Initializes primal variables (`x`), dual variables (`lambda`), and slack variables (`s`) to positive values (an initial interior point).
    2.  **Main Loop (`MAX_ITER` iterations):**
        *   **Complementarity Gap (`mu`):** Calculates the duality gap, which is a measure of optimality. The algorithm aims to drive `mu` to zero.
        *   **Convergence Check:** If `mu` falls below a specified `TOL` (tolerance), the algorithm is considered converged.
        *   **Residuals Calculation:** Computes the primal and dual residuals (`rc`, `rb`, `rxs`), which indicate how well the current solution satisfies the KKT (Karush-Kuhn-Tucker) conditions.
        *   **Newton System:** Sets up and solves a Newton system to determine the search directions (`dx`, `dlambda`, `ds`). This involves forming a diagonal matrix `D` and solving normal equations.
        *   **Line Search:** Performs a line search to find appropriate step lengths (`alpha_p`, `alpha_d`) while maintaining positivity constraints on `x` and `s`.
        *   **Update Variables:** Updates `x`, `lambda`, and `s` using the calculated search directions and step lengths, moving towards the optimal solution along the central path.
    3.  **Cleanup:** Frees dynamically allocated memory.
-   **`main()`:**
    *   Sets up a hardcoded example LP problem (minimize `-x1 - 2*x2` subject to `x1 + x2 <= 3`, `x1, x2 >= 0`). This is converted to standard form with an equality constraint `x1 + x2 + x3 = 3` and non-negativity `x1, x2, x3 >= 0`.
    *   Calls `interior_point()` to solve the LP.
    *   Prints the optimal variable values and the objective function value.

## Usage

To compile and run the code:

```bash
gcc Interior_Point.c -o Interior_Point
./Interior_Point
```

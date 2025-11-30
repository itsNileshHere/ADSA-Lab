## Problem

This program implements the Simplex Method, a widely used algorithm for solving Linear Programming Problems (LPPs). It aims to find the optimal solution (maximum or minimum) of a linear objective function subject to a set of linear constraints. The current implementation focuses on maximization problems.

## Theory

The Simplex Method is an iterative algebraic procedure for solving LPPs. It works on the principle that the optimal solution to an LPP always lies at one of the vertices (corner points) of the feasible region, which is defined by the problem's constraints. The algorithm systematically moves from one vertex to an adjacent one, always improving (or at least not worsening) the objective function value, until the optimal solution is reached.

The key steps and concepts involved are:

1.  **Standard Form:** An LPP must be converted into a standard form before applying the Simplex Method. This typically means:
    *   Maximizing the objective function.
    *   All constraints are "less than or equal to" inequalities.
    *   All decision variables are non-negative.
2.  **Slack Variables:** For "less than or equal to" constraints, **slack variables** are introduced to convert them into equalities. A slack variable represents the unused resource or difference between the left and right sides of the inequality.
3.  **Simplex Tableau:** The problem is represented in a tabular format called the simplex tableau. This matrix includes the coefficients of the objective function (usually in the first row, negated for maximization), the constraint coefficients, and the right-hand side (RHS) values. Slack variables are introduced as basic variables.
4.  **Pivot Operations:** The algorithm iteratively performs pivot operations:
    *   **Entering Variable:** Select the non-basic variable that, if increased, would most improve the objective function. In a maximization problem, this is usually the variable with the most negative coefficient in the objective function row (Row 0 of the tableau). The column containing this variable is called the **pivot column**.
    *   **Leaving Variable:** Determine which basic variable will leave the basis. This is found by calculating the "ratio test": dividing the RHS values by the corresponding positive coefficients in the pivot column. The row with the minimum non-negative ratio becomes the **pivot row**.
    *   **Pivoting:** The pivot row is normalized (divided by the pivot element), and then row operations are performed to make all other entries in the pivot column zero. This transforms the tableau to a new basic feasible solution.
5.  **Optimality Check:** The process continues until all coefficients in the objective function row (Row 0) are non-negative (for maximization). At this point, the optimal solution has been found.

## Approach

The `SimplexMethod.c` program implements the Simplex Method using a 2D float array `A[MAX][MAX]` to represent the simplex tableau.

-   **`m`, `n`:** Represent the number of constraints and original decision variables, respectively.
-   **`A[MAX][MAX]`:** The simplex tableau. Row 0 is for the objective function, and subsequent rows are for constraints. Columns are for decision variables, slack variables, and RHS.
-   **Initialization:**
    *   The constraint coefficients and RHS values are hardcoded into the `A` matrix.
    *   Slack variables are added with coefficients of 1 in their respective rows and 0 elsewhere.
    *   The objective function coefficients are set (negated) in the first row.
-   **`print_tableau()`:** A helper function to display the current state of the simplex tableau.
-   **Main Loop (`while(1)`):**
    1.  **Find Entering Variable:** It scans Row 0 to find the most negative value, determining the `pivot_col`. If no negative values exist, the tableau is optimal, and the loop breaks.
    2.  **Find Leaving Variable:** It performs the ratio test for positive entries in the `pivot_col` to find the `pivot_row` (minimum non-negative ratio). If no positive entry is found, the solution is unbounded.
    3.  **Pivot Operation:**
        *   The `pivot_row` is normalized by dividing all its elements by the `pivot` element.
        *   Row operations are performed on all other rows to make the entries in the `pivot_col` zero.
-   **Result Output:** After reaching optimality, it prints the final tableau, the optimal value of the objective function (Z), and the values of the decision variables.

## Usage

To compile and run the code:

```bash
gcc SimplexMethod.c -o SimplexMethod
./SimplexMethod
```

The current implementation has a hardcoded example LPP:
Maximize Z = 3x1 + 5x2
Subject to:
  x1 + 2x2 <= 8
  3x1 + 2x2 <= 12
  x1, x2 >= 0

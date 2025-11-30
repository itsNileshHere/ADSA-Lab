## Problem

This program implements Strassen's matrix multiplication algorithm, an efficient divide-and-conquer approach to multiply two square matrices.

## Theory

Strassen's algorithm is a recursive algorithm for matrix multiplication that is asymptotically faster than the standard (naive) matrix multiplication algorithm for large matrices. While the naive method requires 8 multiplications of sub-matrices for two N x N matrices, Strassen's algorithm reduces this to 7 multiplications. This reduction comes at the cost of more matrix additions and subtractions.

The core idea is:
1.  **Divide:** The input matrices A and B (of size N x N) are divided into four N/2 x N/2 sub-matrices.
    ```
    A = | A11 A12 |    B = | B11 B12 |
        | A21 A22 |        | B21 B22 |
    ```
2.  **Conquer (7 products):** Instead of 8 recursive multiplications, it computes 7 products of these sub-matrices:
    *   M1 = (A11 + A22) * (B11 + B22)
    *   M2 = (A21 + A22) * B11
    *   M3 = A11 * (B12 - B22)
    *   M4 = A22 * (B21 - B11)
    *   M5 = (A11 + A12) * B22
    *   M6 = (A21 - A11) * (B11 + B12)
    *   M7 = (A12 - A22) * (B21 + B22)
3.  **Combine (Resultant Matrix C):** The resultant sub-matrices C11, C12, C21, C22 are calculated using these 7 products with additions and subtractions:
    *   C11 = M1 + M4 - M5 + M7
    *   C12 = M3 + M5
    *   C21 = M2 + M4
    *   C22 = M1 - M2 + M3 + M6

This recursive process continues until the sub-matrices are small enough to be multiplied directly (base case, typically 1x1 matrices).

The time complexity of Strassen's algorithm is approximately O(N^log2(7)), which is roughly O(N^2.8074), compared to O(N^3) for the naive algorithm. This makes it significantly faster for very large matrices, though it has higher constant factors and increased memory usage due to temporary matrices.

## Approach

The `Strassen_Algo.c` program implements this algorithm:

-   **`addMatrix()` and `subMatrix()`:** Helper functions for matrix addition and subtraction, respectively.
-   **`strassen()`:** The main recursive function.
    -   **Base Case:** If the matrix size `n` is 1, it performs a direct multiplication.
    -   **Recursive Step:**
        1.  It divides the input matrices `A` and `B` into eight `n/2 x n/2` sub-matrices.
        2.  It then performs the 7 recursive matrix multiplications (`M1` to `M7`) using combinations of `addMatrix()`, `subMatrix()`, and recursive calls to `strassen()`.
        3.  Finally, it combines these `M` matrices using `addMatrix()` and `subMatrix()` to form the four sub-matrices of the result `C`.
-   **`main()`:**
    *   Prompts the user to enter the size of the square matrices (emphasizing that it should be a power of 2 for this simplified implementation).
    *   Takes input for the elements of matrices A and B.
    *   Calls `strassen()` to perform the multiplication.
    *   Prints the resultant matrix C.

The `MAX` constant is defined for the maximum size of the matrices, which should be a power of 2 for simplicity in this implementation.

## Usage

To compile and run the code:

```bash
gcc Strassen_Algo.c -o Strassen_Algo
./Strassen_Algo
```

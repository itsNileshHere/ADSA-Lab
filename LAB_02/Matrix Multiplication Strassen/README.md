# Strassen Matrix Multiplication

## About

This program implements Strassen's algorithm for matrix multiplication, which reduces the time complexity from O(n^3) to approximately O(n^{2.807}) for multiplying two square matrices. The algorithm uses a divide-and-conquer approach, recursively splitting matrices into smaller submatrices and computing seven products to combine the results.

## Usage

To compile and run the program:

```bash
gcc Code.c
./a.out
```

The program includes an example for 4×4 matrices, but you can modify the matrix size ( n ) and the input matrices ( A ) and ( B ) in the `main` function to multiply other matrices. Note that the matrix size must be a power of 2 for the algorithm to work correctly.

## Example

For the example 4×4 matrices:

**Matrix A:**

```
[ 1   2   3   4]
[ 5   6   7   8]
[ 9  10  11  12]
[13  14  15  16]
```

**Matrix B:**

```
[16  15  14  13]
[12  11  10   9]
[ 8   7   6   5]
[ 4   3   2   1]
```

The program computes the product ( C = A x B ) using Strassen's algorithm.

### Example Output

The program outputs the product matrix ( C ):

```
Product matrix:
80    70    60    50
240   214   188   162
400   358   316   274
560   502   444   386
```

## Code Structure

- **add**: Adds two matrices ( C = A + B ).
- **subtract**: Subtracts two matrices ( C = A - B ).
- **strassen**: Implements Strassen's algorithm for matrix multiplication. For 2×2 matrices, it computes seven intermediate products directly. For larger matrices, it recursively splits matrices into four submatrices and combines results.
- **main**: Sets up example 4×4 matrices ( A ) and ( B ), calls the Strassen function, and prints the resulting matrix ( C ).

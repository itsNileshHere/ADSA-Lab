# LUP Decomposition Solver

## About LUP Decomposition Solver

This program implements LUP decomposition to solve a system of linear equations ( Ax = b ). The algorithm decomposes the input matrix ( A ) into lower triangular ( L ), upper triangular ( U ), and permutation ( P ) matrices, such that ( PA = LU ). It then uses forward and backward substitution to solve for the solution vector ( x ).

The algorithm modifies the input matrix ( A ) during computation and tracks row swaps in the permutation array ( P ).

## Usage

To compile and run the program:

```bash
gcc Code.c
./a.out
```

The program includes an example 3×3 matrix and right-hand side vector, but you can modify the matrix ( A ) and vector ( b ) in the `main` function to solve other systems.

## Example

For the example 3×3 matrix:

```
[4   2   3]
[3  -5   2]
[1   3  -1]
```

With the right-hand side vector ( b ):

```
[ 8 ]
[-14]
[ 2 ]
```

The program performs LUP decomposition and solves the system ( Ax = b ). The output includes the solution vector ( x ).

### Example Output

The program outputs the solution vector ( x ):

```
Solution x =
   1.000
   2.000
  -1.000
```

## Code Structure

- **lupDecomposition**: Performs LUP decomposition on the input matrix ( A ), producing matrices ( L ), ( U ), and permutation array ( P ).
- **forwardSubstitution**: Solves ( Ly = Pb ) using forward substitution.
- **backwardSubstitution**: Solves ( Ux = y ) using backward substitution.
- **main**: Sets up an example matrix ( A ) and vector ( b ), calls the decomposition and substitution functions, and prints the solution.
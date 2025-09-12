# LUP Decomposition

## About LUP Decomposition

The algorithm modifies the input matrix A during computation and tracks row swaps in the permutation array P.

## Usage

To run the analysis program:

```bash
gcc Code.c
./a.out
```

## Example Output

For the example 3×3 matrix:

```
[4   2   3]
[6  -5   2]  
[1   3  -1]
```

The program outputs:

**P =**

```
 0  1  0 
 1  0  0 
 0  0  1 
```

**L =**

```
 1.000  0.000  0.000
 0.667  1.000  0.000
 0.167  0.719  1.000
```

**U =**

```
 6.000 -5.000  2.000
 0.000  5.333  1.667
 0.000  0.000 -2.531
```
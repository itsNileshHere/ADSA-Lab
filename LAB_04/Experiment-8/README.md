## Problem

This program finds the length and one instance of the Longest Common Subsequence (LCS) for two given strings. A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements. The characters of the LCS do not need to be contiguous in the original strings.

## Theory

The Longest Common Subsequence problem is a classic example that can be efficiently solved using **Dynamic Programming**. Dynamic programming is an algorithmic technique that breaks down a problem into smaller overlapping subproblems, solves each subproblem once, and stores their solutions to avoid recomputing them.

The core idea for LCS using dynamic programming involves building a 2D table (often called a DP table). Let the two input strings be `X` (of length `m`) and `Y` (of length `n`). We construct a table `dp[m+1][n+1]`, where `dp[i][j]` stores the length of the LCS of `X[0...i-1]` and `Y[0...j-1]`.

The recurrence relation is:
-   If `i = 0` or `j = 0`, then `dp[i][j] = 0` (LCS with an empty string is 0).
-   If `X[i-1] == Y[j-1]` (characters match), then `dp[i][j] = dp[i-1][j-1] + 1`. This means we extend the LCS found for the previous prefixes by one matching character.
-   If `X[i-1] != Y[j-1]` (characters do not match), then `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`. This means we take the maximum LCS length obtained by either ignoring the last character of `X` or ignoring the last character of `Y`.

After filling the entire `dp` table, `dp[m][n]` will contain the length of the LCS of the full strings `X` and `Y`.

To reconstruct the actual LCS string, we backtrack through the `dp` table starting from `dp[m][n]`. If `X[i-1] == Y[j-1]`, it means this character is part of the LCS, so we add it and move diagonally up-left (`i--`, `j--`). If they don't match, we move to the cell (either `dp[i-1][j]` or `dp[i][j-1]`) that contributed to the maximum value, indicating which character was "ignored".

The time complexity of this dynamic programming approach is O(m*n), and the space complexity is also O(m*n), where `m` and `n` are the lengths of the two strings.

## Approach

The `Longest_Common_Subsequence.c` program implements the LCS algorithm:

1.  **DP Table Initialization:** A `dp[101][101]` 2D array is used to store the lengths of common subsequences for all prefixes. The first row and column are initialized to 0.
2.  **Filling the DP Table:**
    *   It iterates through the strings `X` and `Y` using nested loops.
    *   If `X[i-1]` matches `Y[j-1]`, `dp[i][j]` is set to `dp[i-1][j-1] + 1`.
    *   Otherwise, `dp[i][j]` is set to the maximum of `dp[i-1][j]` and `dp[i][j-1]`.
3.  **Printing LCS Length:** After the `dp` table is filled, `dp[m][n]` gives the length of the LCS, which is printed.
4.  **Reconstructing LCS String:**
    *   A character array `lcs` is declared to store the LCS string.
    *   It backtracks through the `dp` table from `dp[m][n]`.
    *   If `X[i-1] == Y[j-1]`, the character `X[i-1]` (or `Y[j-1]`) is added to the `lcs` string, and both `i` and `j` are decremented.
    *   If characters do not match, it moves to the cell that corresponds to the larger value in `dp[i-1][j]` or `dp[i][j-1]`, decrementing either `i` or `j` accordingly.
    *   The `lcs` string is built in reverse, so its characters are placed from the end towards the beginning.
    *   Finally, the reconstructed LCS string is printed.

## Usage

To compile and run the code:

```bash
gcc Longest_Common_Subsequence.c -o Longest_Common_Subsequence
./Longest_Common_Subsequence
```

The program has example strings `X = "ABCBDAB"` and `Y = "BDCAB"` hardcoded for demonstration.
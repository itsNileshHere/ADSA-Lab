## Problem

This program implements the Knuth-Morris-Pratt (KMP) string searching algorithm. It efficiently finds all occurrences of a given `pattern` string within a larger `text` string, avoiding redundant comparisons when mismatches occur.

## Theory

The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that operates in linear time. It achieves this by preprocessing the `pattern` string to build an auxiliary data structure called the **Longest Proper Prefix which is also Suffix (LPS) array** (also known as the "failure function" or "prefix function").

### LPS Array

The `lps` array, of the same length as the `pattern` (`m`), stores for each index `i`, the length of the longest proper prefix of `pattern[0...i]` that is also a suffix of `pattern[0...i]`.
-   A **proper prefix** of a string is a prefix that is not the string itself.
-   A **proper suffix** of a string is a suffix that is not the string itself.

**Example for pattern "ABABCABAB":**
-   `lps[0] = 0` (for "A")
-   `lps[1] = 0` (for "AB")
-   `lps[2] = 1` (for "ABA", longest proper prefix "A" is also a suffix)
-   `lps[3] = 2` (for "ABAB", longest proper prefix "AB" is also a suffix)
-   ... and so on.

The LPS array helps the algorithm determine how much to shift the `pattern` forward when a mismatch occurs without re-examining characters in the `text` that have already been matched.

### KMP Algorithm Phases:

1.  **Preprocessing (Building LPS Array):** The `lps` array is constructed for the `pattern` in O(m) time. It iterates through the `pattern`, comparing characters and updating `lps` values based on previous matches.
2.  **Searching (Matching Phase):** The algorithm compares characters from the `text` and `pattern`.
    *   If `text[i]` and `pattern[j]` match, both `i` (text pointer) and `j` (pattern pointer) are incremented.
    *   If `j` reaches the `pattern`'s length (`m`), it means an occurrence of the pattern has been found at index `i-j` in the `text`. The algorithm then uses `lps[j-1]` to determine where to resume searching in the pattern, avoiding re-comparisons.
    *   If a mismatch occurs (`text[i] != pattern[j]`):
        *   If `j > 0`, the pattern is shifted forward by setting `j = lps[j-1]`.
        *   If `j = 0` (meaning the first character of the pattern mismatched), `i` is simply incremented to move to the next character in the text.

**Time Complexity:** O(n + m), where `n` is the length of the text and `m` is the length of the pattern.
**Space Complexity:** O(m) for the LPS array.

## Approach

The `StringSearchKMP.c` program implements the KMP algorithm:

-   **`buildLPS(char pattern[], int lps[])`:** This function constructs the LPS array for the given `pattern`. It uses a `while` loop and two pointers (`len` and `i`) to iterate through the pattern and fill the `lps` array based on character matches and mismatches.
-   **`KMP(char text[], char pattern[])`:** This function performs the actual KMP search:
    1.  It first calls `buildLPS()` to generate the LPS array for the `pattern`.
    2.  It then uses two pointers `i` (for `text`) and `j` (for `pattern`) to compare characters.
    3.  When a match is found (`j == m`), it prints the index and updates `j` using the `lps` array.
    4.  When a mismatch occurs, it uses the `lps` array to efficiently shift the `pattern` without backtracking `i` in the `text`.
-   **`main()`:** Contains hardcoded `text` and `pattern` strings for demonstration. It prints these strings and then calls `KMP()` to perform the search and print the results.

## Usage

To compile and run the code:

```bash
gcc StringSearchKMP.c -o StringSearchKMP
./StringSearchKMP
```

The `text` and `pattern` strings are hardcoded in the `main` function.
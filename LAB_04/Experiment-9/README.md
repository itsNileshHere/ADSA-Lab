## Problem

This program implements two fundamental string searching algorithms:
1.  **Knuth-Morris-Pratt (KMP) Algorithm:** An efficient algorithm that avoids re-examining characters in the text that have already been matched.
2.  **Rabin-Karp Algorithm:** A string searching algorithm that uses hashing to find patterns, particularly efficient for multiple pattern searches.

The program searches for occurrences of a given `pattern` string within a larger `text` string.

## Theory

### Knuth-Morris-Pratt (KMP) Algorithm

KMP is an optimized string searching algorithm. Its efficiency comes from preprocessing the `pattern` to avoid unnecessary comparisons when a mismatch occurs.

The key component of KMP is the **Longest Proper Prefix which is also Suffix (LPS) array** (also known as the "failure function"). This array, `lps[]`, stores for each index `i` in the pattern, the length of the longest proper prefix of `pattern[0...i]` that is also a suffix of `pattern[0...i]`.

The algorithm works in two phases:
1.  **Preprocessing (Building LPS Array):** The `lps` array is constructed for the `pattern` in O(m) time (where `m` is the length of the pattern). This array guides the shifts when a mismatch happens.
2.  **Searching (Matching Phase):** The algorithm compares `text` and `pattern` characters. If a mismatch occurs at `text[i]` and `pattern[j]`, instead of shifting the pattern by just one and re-comparing, it uses `lps[j-1]` to determine the next position `j` in the pattern to compare from. This ensures that no character in the `text` is compared more than once.

KMP has a time complexity of O(n + m) (n for text, m for pattern) and a space complexity of O(m).

### Rabin-Karp Algorithm

The Rabin-Karp algorithm uses hashing to quickly filter out non-matching text windows.

The core idea:
1.  **Hashing:** It computes a hash value for the `pattern` and for every window of the `text` (of the same length as the pattern).
2.  **Rolling Hash:** A special "rolling hash" function is used to efficiently compute the hash of the next text window from the previous one in O(1) time. This avoids recomputing the hash for each window from scratch.
3.  **Comparison:**
    *   If the hash values of the `pattern` and a `text` window match, a character-by-character comparison is performed to confirm an actual match (to handle "hash collisions" where different strings can have the same hash).
    *   If hash values do not match, a mismatch is guaranteed.

The performance of Rabin-Karp depends heavily on the hash function and the frequency of collisions.
-   Average time complexity: O(n + m)
-   Worst-case time complexity: O(n * m) (if many hash collisions occur)
-   Space complexity: O(1) (excluding input strings)

The parameters `D` (number of characters in the alphabet, 256 for ASCII) and `PRIME` (a large prime number) are crucial for the hashing function.

## Approach

The `KMP_RK_Fingerprinting.c` program implements both algorithms:

### KMP Algorithm Implementation

1.  **LPS Array Construction:** A loop calculates the `lps` array. It maintains two pointers, `i` for the pattern (current character) and `j` for the length of the previous longest prefix suffix.
2.  **KMP Search:**
    *   Two pointers `i` (for text) and `j` (for pattern) are used.
    *   If `text[i]` and `pattern[j]` match, both `i` and `j` are incremented.
    *   If `j` reaches the `pattern` length `m`, a match is found, and the starting index (`i-j`) is printed. `j` is then updated using `lps[j-1]` to continue searching.
    *   If a mismatch occurs (`text[i] != pattern[j]`), `j` is reduced using `lps[j-1]` (if `j > 0`); otherwise, `i` is simply incremented.

### Rabin-Karp Algorithm Implementation

1.  **Hash Calculation:**
    *   A value `h` is precomputed as `D^(m-1) % PRIME`, used for efficiently removing the leading digit from the rolling hash.
    *   Initial hash values `p` (for pattern) and `t` (for the first text window) are calculated.
2.  **Sliding Window:**
    *   A loop iterates through the text to slide the window.
    *   If `p == t`, a potential match is found. A character-by-character comparison is then performed to confirm.
    *   For the next window, the `t` hash value is updated using the rolling hash formula: `t = (D * (t - text[i] * h) + text[i + m]) % PRIME`. Negative results are adjusted by adding `PRIME`.

## Usage

To compile and run the code:

```bash
gcc KMP_RK_Fingerprinting.c -o KMP_RK_Fingerprinting
./KMP_RK_Fingerprinting
```

The `text` and `pattern` strings are hardcoded in the `main` function.
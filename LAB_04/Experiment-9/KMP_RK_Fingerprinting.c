#include <stdio.h>
#include <string.h>

#define D 256
#define PRIME 101

int main() {
    // You can change these strings directly
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABABC";

    int n = strlen(text);
    int m = strlen(pattern);

    printf("Text: %s\n", text);
    printf("Pattern: %s\n\n", pattern);

    // ===================== SIMPLE KMP =====================

    int lps[200];
    int i, j;

    // Build the LPS array in a simple way
    lps[0] = 0;
    j = 0;

    for (i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = lps[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        lps[i] = j;
    }

    // KMP Search
    printf("KMP matches at: ");
    i = 0;
    j = 0;

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            printf("%d ", i - j);
            j = lps[j - 1];
        } else if (i < n && text[i] != pattern[j]) {
            if (j > 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    printf("\n");

    // ===================== SIMPLE RABIN-KARP =====================

    int p = 0, t = 0;
    int h = 1;

    // h = (d^(m-1)) % PRIME
    for (i = 0; i < m - 1; i++) {
        h = (h * D) % PRIME;
    }

    // Compute hash of pattern and first window
    for (i = 0; i < m; i++) {
        p = (D * p + pattern[i]) % PRIME;
        t = (D * t + text[i]) % PRIME;
    }

    printf("Rabin-Karp matches at: ");

    // Slide window
    for (i = 0; i <= n - m; i++) {

        if (p == t) {
            int ok = 1;
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                printf("%d ", i);
            }
        }

        if (i < n - m) {
            t = (D * (t - text[i] * h) + text[i + m]) % PRIME;
            if (t < 0)
                t = t + PRIME;
        }
    }

    printf("\n");

    return 0;
}

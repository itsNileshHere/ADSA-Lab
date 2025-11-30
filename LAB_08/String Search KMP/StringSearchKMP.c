#include <stdio.h>
#include <string.h>

// Function to create the LPS (Longest Prefix Suffix) array
void buildLPS(char pattern[], int lps[]) {
    int m = strlen(pattern);
    int len = 0;   // length of previous longest prefix suffix
    int i = 1;

    lps[0] = 0;    // first lps value is always 0

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];  // go back using LPS
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP search function
void KMP(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);

    int lps[m];
    buildLPS(pattern, lps);

    int i = 0;  // text pointer
    int j = 0;  // pattern pointer

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];  // continue searching
        }

        else if (i < n && text[i] != pattern[j]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main() {
    // Hardcoded text and pattern for simplicity
    char text[] = "ababcabcabababd";
    char pattern[] = "ababd";

    printf("Text: %s\n", text);
    printf("Pattern: %s\n\n", pattern);

    KMP(text, pattern);

    return 0;
}

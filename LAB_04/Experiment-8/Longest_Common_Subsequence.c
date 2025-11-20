#include <stdio.h>
#include <string.h>

int main() {
    char X[] = "ABCBDAB";   // Example strings
    char Y[] = "BDCAB";     // Strings to test

    int m = strlen(X);
    int n = strlen(Y);

    int dp[101][101];

    // Fill DP table in a very simple way
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else {
                if (X[i - 1] == Y[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    if (dp[i - 1][j] > dp[i][j - 1])
                        dp[i][j] = dp[i - 1][j];
                    else
                        dp[i][j] = dp[i][j - 1];
                }
            }
        }
    }

    // Print LCS length
    printf("LCS Length: %d\n", dp[m][n]);

    // Now print one actual LCS
    char lcs[101];
    int idx = dp[m][n];
    lcs[idx] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[idx - 1] = X[i - 1];
            i--;
            j--;
            idx--;
        } else {
            if (dp[i - 1][j] > dp[i][j - 1])
                i--;
            else
                j--;
        }
    }

    printf("LCS: %s\n", lcs);

    return 0;
}

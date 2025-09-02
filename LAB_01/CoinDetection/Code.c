#include <stdio.h>

int balanceScale(int coins[], int left, int right, int size) {
    int sumLeft = 0, sumRight = 0;
    for (int i = 0; i < size; i++) {
        sumLeft += coins[left + i];
        sumRight += coins[right + i];
    }
    if (sumLeft < sumRight) return -1;
    else if (sumLeft > sumRight) return 1;
    return 0;
}

// Recursive DnC search
int findDefective(int coins[], int l, int r) {
    if (l == r) return l;
    
    int mid = (l + r) / 2;
    int size = (mid - l + 1);

    int result = balanceScale(coins, l, mid + 1, size);

    if (result == -1) return findDefective(coins, l, mid);
    else if (result == 1) return findDefective(coins, mid + 1, r);
    else return -1;
}

int main() {
    int coins[] = {16, 16, 16, 10, 16};
    int n1 = sizeof(coins) / sizeof(coins[0]);

    int defectiveIDX = findDefective(coins, 0, n1 - 1);
    if (defectiveIDX == -1) {
        printf("No defective coin found.\n");
    } else {
        int ref = 0;
        if (defectiveIDX == 0)
            ref = 1;
        if (coins[defectiveIDX] < coins[ref])
            printf("Defective coin found at index %d with weight %d.\n",
                   defectiveIDX, coins[defectiveIDX]);
        else
            printf("No defective coin found.\n");
    }

    return 0;
}

// Implementation of Binary Search and Ternary Search

#include <stdio.h>

// Ternary Search
int tSearch(int arr[], int l, int r, int x) {
    if (r >= l) {
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;

        if (arr[mid1] == x) return mid1;
        if (arr[mid2] == x) return mid2;

        if (x < arr[mid1])
            return tSearch(arr, l, mid1 - 1, x);
        else if (x > arr[mid2])
            return tSearch(arr, mid2 + 1, r, x);
        else
            return tSearch(arr, mid1 + 1, mid2 - 1, x);
    }
    return -1;
}

// Binary Search
int bSearch(int arr[], int l, int r, int x) {
    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (arr[mid] == x)
            return mid;
        else if (arr[mid] < x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}

int main() {
    int arr[] = {2, 4, 7, 18, 19, 22, 28, 35, 46, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 7;      // To search

    printf("Array elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nElement to search: %d\n\n", x);

    // Ternary Search
    int tSearchResult = tSearch(arr, 0, n - 1, x);
    if (tSearchResult == -1)
        printf("Not found.\n");
    else
        printf("Ternary Search: Element found at %d\n", tSearchResult);

    // Binary Search
    int bSearchResult = bSearch(arr, 0, n - 1, x);
    if (bSearchResult == -1)
        printf("Not found.\n");
    else
        printf("Binary Search: Element found at %d\n", bSearchResult);

    return 0;
}

## Problem

This program finds a specific element (key) in a sorted array using a recursive implementation of the Binary Search algorithm.

## Theory

Binary Search is a highly efficient algorithm for finding an item from a sorted list of items. It works by repeatedly dividing the search interval in half. This recursive implementation uses the function call stack to manage the sub-problems.

The core idea is:
1.  Compare the `key` with the middle element of the array.
2.  If the `key` matches the middle element, the search is successful.
3.  If the `key` is smaller than the middle element, recursively call the binary search for the left sub-array.
4.  If the `key` is larger than the middle element, recursively call the binary search for the right sub-array.
5.  The recursion stops when the sub-array has a size of 0 (the `low` index becomes greater than the `high` index), which means the element is not present.

The time complexity is O(log n), but this recursive version has a space complexity of O(log n) due to the overhead of the recursive calls on the function stack.

## Approach

The `RecursiveBinarySearch.c` program implements the algorithm as follows:

1.  **`binarySearchRecursive()` function:**
    *   This function serves as the recursive engine.
    *   **Base Case:** The recursion terminates if `low` becomes greater than `high`, returning `-1` to indicate that the key was not found.
    *   **Recursive Step:** It calculates the `mid` index and compares `arr[mid]` with the `key`.
        *   If they are equal, it returns `mid`.
        *   If `arr[mid]` is less than the `key`, it makes a recursive call on the right half of the array: `binarySearchRecursive(arr, mid + 1, high, key)`.
        *   If `arr[mid]` is greater than the `key`, it makes a recursive call on the left half of the array: `binarySearchRecursive(arr, low, mid - 1, key)`.

2.  **`main()` function:**
    *   It initializes a sorted array and a `key` to be searched.
    *   It calls `binarySearchRecursive()` with the initial search space (the entire array).
    *   It prints the result, indicating whether the key was found and at which index.

## Usage

To compile and run the code:

```bash
gcc RecursiveBinarySearch.c -o RecursiveBinarySearch
./RecursiveBinarySearch
```

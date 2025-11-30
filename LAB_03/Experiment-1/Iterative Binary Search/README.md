## Problem

This program implements an iterative version of the Binary Search algorithm to find a specific element (key) within a sorted array.

## Theory

Binary Search is a highly efficient searching algorithm that works on sorted arrays. It operates on a "divide and conquer" strategy. The core idea is to repeatedly divide the search interval in half. If the value of the search key is less than the item in the middle of the interval, narrow the interval to the lower half. Otherwise, narrow it to the upper half. This process is continued until the value is found or the interval is empty.

The iterative approach uses a `while` loop to manage the search interval, avoiding recursive function calls. This can be more memory-efficient as it does not consume stack space for recursion.

The time complexity of Binary Search is O(log n), and the space complexity for the iterative version is O(1).

## Approach

The `IterativeBinarySearch.c` code implements the algorithm as follows:

1.  **Initialization:** Two variables, `low` and `high`, are initialized to the first and last indices of the array, respectively.
2.  **Looping:** A `while` loop continues as long as `low` is less than or equal to `high`.
3.  **Midpoint Calculation:** Inside the loop, the `mid` index is calculated as the average of `low` and `high`.
4.  **Comparison:**
    *   The element at the `mid` index is compared with the `key`.
    *   If they are equal, the index `mid` is returned.
    *   If the `key` is greater than the middle element, the search continues in the right half of the array by updating `low` to `mid + 1`.
    *   If the `key` is smaller, the search continues in the left half by updating `high` to `mid - 1`.
5.  **Not Found:** If the loop terminates without finding the key, the function returns `-1`.

## Usage

To compile and run the code:

```bash
gcc IterativeBinarySearch.c -o IterativeBinarySearch
./IterativeBinarySearch
```

## Problem

This directory contains two implementations of the Quick Sort algorithm, a widely used, efficient sorting algorithm.
- `QuickSort.c`: A standard implementation using the last element as the pivot.
- `QuickSort_MedianPivot.c`: An optimized version that uses the "median-of-three" method for pivot selection to improve performance and avoid worst-case scenarios.

## Theory

Quick Sort is a divide-and-conquer algorithm. Its main steps are:
1.  **Pivot Selection:** Choose an element from the array, called the pivot.
2.  **Partitioning:** Rearrange the array so that all elements smaller than the pivot are on its left, and all elements greater are on its right. The pivot is now in its final sorted position.
3.  **Recursion:** Recursively apply the above steps to the sub-arrays of elements with smaller and larger values.

The efficiency of Quick Sort heavily depends on the pivot selection. A good pivot splits the array into roughly equal halves, leading to an average time complexity of O(n log n). A poor pivot (like the smallest or largest element) can lead to unbalanced partitions and a worst-case time complexity of O(n^2).

### Median-of-Three Pivot Strategy

To mitigate the risk of a worst-case scenario, the "median-of-three" pivot selection can be used. This technique involves:
1.  Selecting three elements from the array (usually the first, middle, and last).
2.  Choosing the median of these three elements as the pivot.
This makes it more likely that the pivot will be close to the actual median of the array, leading to more balanced partitions.

## Approach

### `QuickSort.c`

-   **`partition()` function:** This function takes the last element of the array as the pivot. It iterates through the array, moving all elements smaller than or equal to the pivot to the left side. Finally, it places the pivot in its correct sorted position.
-   **`quickSort()` function:** This is the recursive driver function. It partitions the array and then recursively calls itself for the two sub-arrays to the left and right of the pivot.

### `QuickSort_MedianPivot.c`

-   **`medianOfThree()` function:** This function selects the first, middle, and last elements, sorts them, and uses the median as the pivot. To simplify partitioning, it swaps the median with the element at the `high - 1` position.
-   **`partition()` function:** This function is adapted for the median-of-three pivot. It uses two pointers (`i` and `j`) moving towards each other from both ends of the sub-array to partition the elements around the pivot.
-   **`quickSort()` function:** This functions the same as in the standard implementation, driving the recursive sorting process.

## Usage

To compile and run either version:

```bash
# For the standard implementation
gcc QuickSort.c -o QuickSort
./QuickSort

# For the median-of-three implementation
gcc QuickSort_MedianPivot.c -o QuickSort_MedianPivot
./QuickSort_MedianPivot
```

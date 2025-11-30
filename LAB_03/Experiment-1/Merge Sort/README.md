## Problem

This program sorts an array of integers using the Merge Sort algorithm, which is a classic example of a "divide and conquer" strategy in computer science.

## Theory

Merge Sort is a highly efficient, stable, and comparison-based sorting algorithm. It works by following these steps:

1.  **Divide:** The algorithm starts by dividing the unsorted array into two halves.
2.  **Conquer:** It recursively calls itself for the two halves until the sub-arrays have only one element. A single-element array is inherently sorted.
3.  **Combine (Merge):** It then merges the two sorted sub-arrays back into one larger, sorted array. This merge step is the core of the algorithm. It compares elements from the two sub-arrays and copies the smaller element into a temporary array, repeating until all elements from both sub-arrays are merged.

Merge Sort has a time complexity of O(n log n) in all cases (worst, average, and best), making it very predictable. Its main drawback is that it requires O(n) additional memory for the temporary arrays used during the merge process.

## Approach

The `MergeSort.c` program implements the algorithm as follows:

1.  **`mergeSort()` function:** This is the main recursive function.
    *   It checks if the `left` index is less than the `right` index to determine if the array has more than one element.
    *   It calculates the `mid` point and recursively calls itself for the left half (`left` to `mid`) and the right half (`mid + 1` to `right`).
    *   After the two halves are sorted, it calls the `merge()` function to combine them.

2.  **`merge()` function:**
    *   It creates two temporary arrays, `L[]` and `R[]`, to hold the elements of the two halves.
    *   It then iterates through both temporary arrays, comparing elements and placing the smaller one into the correct position in the original array (`arr[]`).
    *   After one of the temporary arrays is exhausted, it copies the remaining elements from the other temporary array into the original array.

## Usage

To compile and run the code:

```bash
gcc MergeSort.c -o MergeSort
./MergeSort
```

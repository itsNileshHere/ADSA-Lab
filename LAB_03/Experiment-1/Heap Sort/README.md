## Problem

This program implements the Heap Sort algorithm to sort an array of integers in ascending order.

## Theory

Heap Sort is an efficient, in-place, comparison-based sorting algorithm that uses a binary heap data structure. The core idea is to turn the input array into a max-heap, where the largest element is at the root. The algorithm then repeatedly swaps the root element with the last element of the heap, reduces the heap size by one, and reconstructs the max-heap property.

The process consists of two main phases:
1.  **Build Max-Heap:** The initial unsorted array is rearranged to create a max-heap, a complete binary tree where the value of each parent node is greater than or equal to the values of its children.
2.  **Heap Extraction:** The largest element (at the root) is moved to its correct sorted position at the end of the array. The heap is then reconstructed for the remaining elements, and this process is repeated until the entire array is sorted.

Heap Sort has a time complexity of O(n log n) for all cases (worst, average, and best).

## Approach

The `HeapSort.c` code implements the algorithm as follows:

1.  **`heapify()` function:** This function is responsible for maintaining the max-heap property. Given a subtree rooted at index `i`, it compares the root with its left and right children and swaps it with the largest of the three if necessary. This process is applied recursively down the heap to ensure the subtree satisfies the max-heap property.
2.  **`heapSort()` function:**
    *   It first builds the max-heap from the input array. This is done by calling `heapify()` for all non-leaf nodes, starting from the last one and moving up to the root.
    *   Once the max-heap is built, it enters the sorting phase. It iterates from the end of the array to the beginning, repeatedly swapping the current root (`arr[0]`) with the element at the end of the unsorted portion (`arr[i]`).
    *   After each swap, it calls `heapify()` on the reduced heap (of size `i`) to restore the max-heap property.

## Usage

To compile and run the code:

```bash
gcc HeapSort.c -o HeapSort
./HeapSort
```

## Problem

Ternary Search: Like binary search, in ternary search an n element list is divided into nearly three equal intervals. Then the search will be in one of the interval. Design and implement an algorithm to search an element x in a sorted list of size n using ternary search. Explain the complexity analysis of your algorithm. Is it better than binary search? Justify by comparing the growth of binary search and ternary search algorithms through implementation.


## Algorithms

### Binary Search
Binary search repeatedly divides the array into two halves:

1. Find the middle index
2. If the middle element matches the target, return its index
3. If the target is smaller, search the left half; otherwise, search the right half
4. Repeat until the element is found or the subarray is empty

**Time Complexity:** O(log2 n)

### Ternary Search
Ternary search divides the array into three parts:

1. Compute two mid points `mid1` and `mid2`
2. If the target equals `arr[mid1]` or `arr[mid2]`, return the index
3. If the target is less than `arr[mid1]`, search the first third
4. If the target is greater than `arr[mid2]`, search the last third
5. Otherwise, search the middle third recursively

**Time Complexity:** O(log3 n)

## Approach
The C program:

- Initializes a sorted array of integers
- Implements iterative binary search and recursive ternary search functions
- Prints the array and the element to search
- Executes both searches and prints the index if found, or a "Not found" message

## Usage
To run the  program:

```bash
gcc Code.c
./a.out
```

## Example Output
```
Array: [1, 3, 5, 7, 9, 11, 13, 15, 17, 19]
Searching for: 7

Binary Search: Found at index 3
Ternary Search: Found at index 3
```
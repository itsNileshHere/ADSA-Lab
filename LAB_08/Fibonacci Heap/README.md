## Problem

This program implements a Fibonacci Heap, a complex but highly efficient priority queue data structure. It supports key operations such as insertion, extraction of the minimum element, decreasing a key, and deletion of a node. Fibonacci heaps are often used in graph algorithms like Dijkstra's and Prim's where `decrease_key` operations are frequent.

## Theory

A Fibonacci Heap is a collection of heap-ordered trees. Unlike binary heaps, a Fibonacci heap does not need to be perfectly balanced, which allows for some operations to be performed in amortized constant time. This efficiency comes from a "lazy" approach to some operations, deferring the work until it's absolutely necessary (e.g., during `extract_min`).

Key properties and operations:

-   **Structure:** A Fibonacci heap is a set of min-heap-ordered trees. The roots of these trees are stored in a circular doubly linked list called the root list.
-   **`min` pointer:** A pointer to the node with the minimum key in the entire heap (specifically, in the root list).
-   **`degree`:** The number of children a node has.
-   **`mark`:** A boolean flag (0 or 1) indicating if a node has lost a child since it was made a child of its current parent. This is crucial for the `cascading_cut` operation.
-   **Amortized Analysis:** Many operations have a better amortized time complexity than their worst-case, meaning the average performance over a sequence of operations is efficient.

### Main Operations:

1.  **`fib_heap_insert(H, x)`:** Inserts a new node `x` into the root list of the heap `H`. This operation has O(1) amortized time complexity.
2.  **`fib_heap_union(H1, H2)`:** Merges two Fibonacci heaps `H1` and `H2` into a single heap. This is also O(1) amortized time.
3.  **`fib_heap_extract_min(H)`:** Removes and returns the node with the minimum key. This is the most complex operation, involving consolidating the heap structure. It has O(log n) amortized time complexity.
    *   It removes the minimum node `z`.
    *   Adds all children of `z` to the root list.
    *   Performs a **consolidation** process (`fib_heap_consolidate`) to reduce the number of trees in the root list by linking trees of the same degree.
4.  **`fib_heap_decrease_key(H, x, k)`:** Decreases the key of node `x` to `k`. If this violates the min-heap property with its parent, `x` is **cut** from its parent and moved to the root list. This can trigger **cascading cuts** up the tree if marked nodes lose more children. This operation has O(1) amortized time complexity.
5.  **`fib_heap_delete(H, x)`:** Deletes node `x` by decreasing its key to negative infinity (`INT_MIN`) and then performing an `extract_min`. This has O(log n) amortized time complexity.

## Approach

The `FibonacciHeap.c` program implements the Fibonacci Heap data structure.

-   **`FibNode` struct:** Defines a node in the heap, containing `key`, `degree`, `mark`, `parent`, `child`, `left`, and `right` pointers for the circular doubly linked lists.
-   **`FibHeap` struct:** Defines the heap itself, holding a pointer to the `min` node and the total number of nodes `n`.
-   **`create_node(key)`:** Allocates and initializes a new `FibNode`.
-   **`create_heap()`:** Allocates and initializes an empty `FibHeap`.
-   **`fib_heap_insert(H, x)`:** Inserts node `x` into the root list of heap `H` and updates `H->min` if `x` has a smaller key.
-   **`fib_heap_union(H1, H2)`:** Merges the root lists of two heaps and updates the minimum pointer and total node count.
-   **`fib_heap_link(H, y, x)`:** A helper function that makes tree `y` a child of tree `x`, used during consolidation. `y` is removed from the root list and added to `x`'s child list.
-   **`fib_heap_consolidate(H)`:** This is a crucial function called by `extract_min`. It iterates through the root list, merging trees of the same degree until all trees in the root list have unique degrees. An array `A[]` is used to keep track of trees by their degree.
-   **`fib_heap_extract_min(H)`:** Extracts the minimum node. It first moves the children of the minimum node to the root list, removes the minimum node from the root list, and then calls `fib_heap_consolidate()` to reorganize the heap.
-   **`cut(H, x, y)`:** Removes node `x` from `y`'s child list and adds `x` to the root list of heap `H`.
-   **`cascading_cut(H, y)`:** Recursively performs cuts up the tree when a node `y` has lost too many children.
-   **`fib_heap_decrease_key(H, x, k)`:** Decreases `x`'s key. If heap property is violated with its parent, it performs `cut` and `cascading_cut`.
-   **`fib_heap_delete(H, x)`:** Deletes a node `x` by decreasing its key to `INT_MIN` and then extracting the minimum node.
-   **`main()`:** Contains a simple demonstration of inserting nodes and then extracting the minimum.

## Usage

To compile and run the code:

```bash
gcc FibonacciHeap.c -o FibonacciHeap
./FibonacciHeap
```

The `main` function demonstrates basic insertion and `extract_min` operations.
## Problem

This program demonstrates the basic operations of a B-Tree, specifically focusing on insertion and a simplified deletion. B-Trees are self-balancing tree data structures designed for efficient disk access, commonly used in database and file systems.

## Theory

A B-Tree is a self-balancing tree data structure that maintains sorted data and allows searches, sequential access, insertions, and deletions in logarithmic time. Unlike binary trees, B-tree nodes can have more than two children. Each node in a B-tree can store multiple keys and have multiple child pointers, specified by an order (or minimum degree `t`).

Key properties of a B-Tree of order `m` (where `m = MAX + 1` in this code):
-   Every node, except the root, must have at least `ceil(m/2)-1` keys and at most `m-1` keys.
-   Every node, except the root, must have at least `ceil(m/2)` children and at most `m` children.
-   The root must have at least 1 key (if not a leaf) and at most `m-1` keys.
-   All leaves are at the same level.

### Key Operations:

-   **Insertion:** New keys are always inserted into leaf nodes. If inserting a key causes a node to exceed its maximum capacity, the node is `split`. The median key is promoted to the parent, and the node is divided into two. This splitting can propagate up the tree, potentially increasing the height of the tree.
-   **Deletion (Simplified in this demo):** Deleting from a B-tree is complex as it needs to maintain the minimum key property. If a node becomes underfull after deletion, it might need to `borrow` keys from a sibling or `merge` with a sibling. The provided demo code has a very basic deletion that does not rebalance the tree.
-   **Splitting:** Occurs during insertion when a node becomes full. The node is divided, and the median key is pushed up to the parent.
-   **Merging:** Occurs during deletion when a node becomes underfull. An underfull node might merge with a sibling node, pulling a key down from the parent.

## Approach

The `B-Tree_Operations.c` program implements a B-Tree using a `struct BTreeNode` for each node, which contains an array for keys (`val`), a count of current keys (`count`), and an array of child pointers (`link`). The maximum number of keys per node is defined by `MAX`.

-   **`createNode()`:** Allocates and initializes a new B-Tree node.
-   **`addValToNode()`:** Inserts a value into an existing node in the correct sorted position, along with its child pointer.
-   **`splitNode()`:** Handles node splitting when a node becomes full during insertion. It identifies the median, creates a new node for the larger half of the keys, and promotes the median key.
-   **`setValue()`:** A recursive helper function for insertion. It traverses the tree to find the appropriate position for the new value. If a node is full, it calls `splitNode()`. It also handles duplicate values.
-   **`insert()`:** The main insertion function. It calls `setValue()` and if a split propagates up to the root, it creates a new root node.
-   **`display()`:** Performs an in-order traversal to print the keys of the B-Tree, demonstrating its structure.
-   **`deleteDemo()`:** This function provides a *very basic* deletion. It searches for the key and removes it if found within a node. **Crucially, this function does not implement the complex rebalancing (borrowing or merging) required for a proper B-Tree deletion after a key is removed, which is explicitly noted in the code's comment.**

## Usage

To compile and run the code:

```bash
gcc B-Tree_Operations.c -o B_Tree_Operations
./B_Tree_Operations
```

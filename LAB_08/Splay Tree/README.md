## Problem

This program implements a Splay Tree, a self-adjusting binary search tree. It demonstrates the core operations of insertion, searching, and deletion, all of which leverage the "splaying" mechanism to bring frequently accessed nodes to the root, optimizing performance over time.

## Theory

A Splay Tree is a type of self-balancing Binary Search Tree (BST) that automatically moves recently accessed elements to the root of the tree. This process, called **splaying**, is performed after every access (insertion, search, or deletion). The idea is that recently accessed nodes are likely to be accessed again soon (locality of reference), and by moving them to the root, future access times for these nodes are reduced. While the worst-case time complexity for a single operation can be O(n) (where n is the number of nodes), the amortized time complexity for a sequence of operations is O(log n).

### Splaying Mechanism

Splaying involves a series of rotations to move a target node `x` to the root of the tree. The rotations are performed in pairs, based on the relationship between `x`, its parent `p`, and its grandparent `g`:

1.  **Zig Step:** If `x` is a child of the root `p`, a single rotation is performed to make `x` the new root.
2.  **Zig-Zig Step:** If `x` and `p` are both left children, or both right children, of their respective parents. Two rotations in the same direction are performed (e.g., if both are left children, `p` is rotated right, then `x` is rotated right).
3.  **Zig-Zag Step:** If `x` is a right child and `p` is a left child, or vice-versa. Two rotations in opposite directions are performed (e.g., if `x` is a right child of `p` and `p` is a left child of `g`, then `x` is rotated left, then `x` is rotated right).

These rotations ensure that the target node reaches the root and also help to rebalance the tree structure.

### Key Operations:

-   **Insertion:** A new node is inserted as in a standard BST. After insertion, the newly inserted node is splayed to the root of the tree.
-   **Search:** The search operation proceeds like a standard BST search. If the key is found, that node is splayed to the root. If the key is not found, the last accessed node (the one where the search terminates) is splayed to the root.
-   **Deletion:** The node to be deleted is first splayed to the root. Once at the root, it is deleted, which results in two subtrees (left and right). These two subtrees are then joined. One common joining method is to splay the largest node of the left subtree (which becomes the new root of the left subtree) and then attach the right subtree to its right child.

## Approach

The `SplayTree.c` program implements a Splay Tree using a `struct Node` for each node, storing its `key` and pointers to its `left` and `right` children.

-   **`createNode()`:** Allocates and initializes a new tree node.
-   **`rotateRight()` and `rotateLeft()`:** Implement the fundamental tree rotation operations.
-   **`splay(root, key)`:** This is the core splaying function. It takes the current root of a subtree and a key. It recursively applies the zig, zig-zig, and zig-zag rotation patterns to bring the node with the `key` (or the last accessed node if the key isn't found) to the root of the given subtree.
-   **`insert(root, key)`:** Inserts a `key` into the splay tree. It first calls `splay()` to bring the node with the closest value to the `key` to the root. Then, it creates a new node, and based on the comparison with the (new) root, attaches it, effectively splitting and joining the tree.
-   **`search(root, key)`:** Searches for a `key`. It calls `splay()` to bring the found node (or the last accessed node) to the root and returns the new root.
-   **`deleteKey(root, key)`:** Deletes a `key` from the splay tree. It first splay the node to be deleted (or the last accessed node if not found) to the root. If the key is found and deleted, it then joins the left and right subtrees (by splaying the maximum of the left subtree and attaching the right subtree to it).
-   **`inorder(root)`:** Performs an in-order traversal to print the elements of the tree in ascending order.
-   **`main()`:** Demonstrates insertion, search, and deletion operations, showing the tree's state (via in-order traversal) after each significant modification.

## Usage

To compile and run the code:

```bash
gcc SplayTree.c -o SplayTree
./SplayTree
```

The `main` function includes hardcoded examples of insertion, searching, and deletion.
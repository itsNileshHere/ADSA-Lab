## Problem

This program demonstrates the fundamental operations of a Binary Search Tree (BST), including insertion, deletion, and the three main types of tree traversal (in-order, pre-order, and post-order).

## Theory

A Binary Search Tree is a node-based binary tree data structure that has the following properties:
- The left subtree of a node contains only nodes with keys lesser than the node's key.
- The right subtree of a node contains only nodes with keys greater than the node's key.
- The left and right subtrees must also be binary search trees.
- There must be no duplicate nodes.

This structure allows for efficient searching, insertion, and deletion of nodes.

### Key Operations

-   **Insertion:** A new key is always inserted at a leaf. The algorithm traverses the tree from the root, deciding whether to go left or right at each node until an empty spot is found. The time complexity is O(h), where 'h' is the height of the tree.
-   **Deletion:** This is more complex and handles three cases:
    1.  **Node is a leaf:** Simply remove the node.
    2.  **Node has one child:** Replace the node with its child.
    3.  **Node has two children:** Replace the node with its in-order successor (the smallest node in the right subtree) or in-order predecessor, and then delete that successor/predecessor node.
-   **Traversal:**
    -   **In-order (Left, Root, Right):** Visits nodes in ascending order.
    -   **Pre-order (Root, Left, Right):** Useful for creating a copy of the tree.
    -   **Post-order (Left, Right, Root):** Useful for deleting a tree from memory.

## Approach

The `BST_Operations.c` program implements these operations using a `struct Node` to represent each node in the tree.

-   **`insert()`:** A recursive function that traverses the tree to find the correct position for the new key and inserts a new node there.
-   **`deleteNode()`:** A recursive function that finds the node with the given key and deletes it according to the three cases described above. It uses a helper function, `minValueNode()`, to find the in-order successor when deleting a node with two children.
-   **`inorder()`, `preorder()`, `postorder()`:** Each of these is a recursive function that traverses the tree and prints the node keys according to its specific traversal order.
-   **`main()`:** The `main` function builds a sample BST, performs and prints the three traversals, deletes a couple of nodes to demonstrate the deletion logic, and then prints the final traversals of the modified tree.

## Usage

To compile and run the code:

```bash
gcc BST_Operations.c -o BST_Operations
./BST_Operations
```

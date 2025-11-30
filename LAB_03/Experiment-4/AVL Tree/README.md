## Problem

This program implements the core operations of an AVL (Adelson-Velsky and Landis) Tree, a self-balancing binary search tree. The implemented operations include insertion, deletion, and in-order traversal, along with the necessary rotation mechanisms to maintain the AVL tree's balance property.

## Theory

An AVL tree is a self-balancing Binary Search Tree (BST) where the difference between the heights of the left and right subtrees (known as the balance factor) of any node is at most 1. This strict balance condition ensures that AVL trees maintain a logarithmic time complexity (O(log n)) for search, insertion, and deletion operations, even in the worst-case scenarios, unlike unbalanced BSTs which can degrade to O(n) complexity.

The balance is maintained by performing tree rotations whenever an insertion or deletion causes the balance factor of any node to violate the AVL property (i.e., become greater than 1 or less than -1).

### Key Operations:

-   **Insertion:** New nodes are initially inserted as in a standard BST. After insertion, the tree is traversed upwards from the new node to the root, updating heights and checking balance factors. If an imbalance is detected, appropriate rotations are performed.
-   **Deletion:** A node is first deleted as in a standard BST. Similar to insertion, the tree is then rebalanced by traversing upwards from the deleted node's parent, updating heights, checking balance factors, and performing rotations as needed.
-   **Rotations:** These are structural changes to the tree that restore balance without violating the BST property. There are four main types of rotations:
    -   **Left Rotation (LL Imbalance):** When a node's right subtree is too tall, and the imbalance is on the right child's right subtree.
    -   **Right Rotation (RR Imbalance):** When a node's left subtree is too tall, and the imbalance is on the left child's left subtree.
    -   **Left-Right Rotation (LR Imbalance):** A double rotation involving a left rotation on the left child followed by a right rotation on the parent.
    -   **Right-Left Rotation (RL Imbalance):** A double rotation involving a right rotation on the right child followed by a left rotation on the parent.

## Approach

The `AVL-Tree_Operations.c` program defines a `struct Node` for the tree nodes, storing the key, left and right child pointers, and the height of the subtree rooted at that node.

-   **`height()` and `max()`:** Helper functions to get the height of a node and the maximum of two integers, respectively.
-   **`newNode()`:** Creates a new AVL tree node.
-   **`rightRotate()` and `leftRotate()`:** Implement the basic tree rotations, updating node heights after rotation.
-   **`getBalance()`:** Calculates the balance factor of a given node.
-   **`insert()`:** Recursively inserts a new key. After the standard BST insertion, it updates the height of the current node and checks its balance factor. If unbalanced, it performs the necessary single or double rotation (LL, RR, LR, RL cases).
-   **`minValueNode()`:** A helper function to find the node with the minimum key value in a given subtree, used during deletion.
-   **`deleteNode()`:** Recursively deletes a node with a given key. It first performs standard BST deletion. After deletion, it checks for imbalance and performs rotations if necessary to restore the AVL property.
-   **`inorder()`:** Performs an in-order traversal of the AVL tree, which prints the elements in ascending order.
-   **`main()`:** Demonstrates insertion and deletion operations, showing the tree's state (via in-order traversal) after each significant modification.

## Usage

To compile and run the code:

```bash
gcc AVL-Tree_Operations.c -o AVL_Tree_Operations
./AVL_Tree_Operations
```

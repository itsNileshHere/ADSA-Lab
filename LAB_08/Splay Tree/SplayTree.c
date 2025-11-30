#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left;
    struct Node *right;
};

/* Create a new node */
struct Node* createNode(int key) {
    struct Node* n = malloc(sizeof(struct Node));
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    return n;
}

/* Right rotation */
struct Node* rotateRight(struct Node* root) {
    struct Node* x = root->left;
    root->left = x->right;
    x->right = root;
    return x;
}

/* Left rotation */
struct Node* rotateLeft(struct Node* root) {
    struct Node* x = root->right;
    root->right = x->left;
    x->left = root;
    return x;
}

/* Splay operation */
struct Node* splay(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    /* Key in left subtree */
    if (key < root->key) {
        if (root->left == NULL)
            return root;

        if (key < root->left->key) {
            /* Zig-Zig (left-left) */
            root->left->left = splay(root->left->left, key);
            root = rotateRight(root);
        } 
        else if (key > root->left->key) {
            /* Zig-Zag (left-right) */
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = rotateLeft(root->left);
        }

        if (root->left == NULL)
            return root;
        else
            return rotateRight(root);
    }

    /* Key in right subtree */
    else {
        if (root->right == NULL)
            return root;

        if (key > root->right->key) {
            /* Zig-Zig (right-right) */
            root->right->right = splay(root->right->right, key);
            root = rotateLeft(root);
        }
        else if (key < root->right->key) {
            /* Zig-Zag (right-left) */
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rotateRight(root->right);
        }

        if (root->right == NULL)
            return root;
        else
            return rotateLeft(root);
    }
}

/* Insert */
struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return createNode(key);

    root = splay(root, key);

    if (root->key == key)
        return root;  // already exists

    struct Node* n = createNode(key);

    if (key < root->key) {
        n->right = root;
        n->left = root->left;
        root->left = NULL;
    } else {
        n->left = root;
        n->right = root->right;
        root->right = NULL;
    }

    return n;
}

/* Search */
struct Node* search(struct Node* root, int key) {
    return splay(root, key);
}

/* Delete */
struct Node* deleteKey(struct Node* root, int key) {
    if (root == NULL)
        return NULL;

    root = splay(root, key);

    if (root->key != key)
        return root;  // not found, no delete

    struct Node* temp;

    if (root->left == NULL) {
        temp = root->right;
    } else {
        temp = splay(root->left, key);
        temp->right = root->right;
    }

    free(root);
    return temp;
}

/* Inorder print */
void inorder(struct Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

int main() {
    struct Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = insert(root, 15);

    printf("Inorder: ");
    inorder(root);

    root = search(root, 15);
    printf("\nAfter searching 15: ");
    inorder(root);

    root = deleteKey(root, 10);
    printf("\nAfter deleting 10: ");
    inorder(root);

    printf("\n");
    return 0;
}

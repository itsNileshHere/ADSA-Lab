#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
 * ---------------------------
 * Node structure of heap
 * ---------------------------
 * Each node belongs to a tree.
 * All siblings form a circular doubly linked list.
 */
typedef struct FibNode {
    int key;                    // Value stored in the node
    int degree;                 // Number of children
    int mark;                   // Used for decrease-key operation

    struct FibNode *parent;     // Pointer to parent node
    struct FibNode *child;      // Pointer to one of its children
    struct FibNode *left;       // Left sibling
    struct FibNode *right;      // Right sibling
} FibNode;


/*
 * ---------------------------
 * Main heap structure
 * ---------------------------
 * It stores the minimum node pointer
 * and the total number of nodes.
 */
typedef struct FibHeap {
    FibNode *min;   // Pointer to minimum node in root list
    int size;       // Number of nodes stored in heap
} FibHeap;


/*
 * Create a new node with a given key
 * and initialize all pointers.
 */
FibNode* create_node(int key) {
    FibNode *node = (FibNode*)malloc(sizeof(FibNode));

    node->key = key;
    node->degree = 0;
    node->mark = 0;

    node->parent = NULL;
    node->child = NULL;

    // A single node is a circular doubly linked list
    node->left = node;
    node->right = node;

    return  node;
}


/*
 * Create an empty Fibonacci heap
 */
FibHeap* create_heap() {
    FibHeap *heap = (FibHeap*)malloc(sizeof(FibHeap));
    heap->min = NULL;
    heap->size = 0;
    return heap;
}


/*
 * Insert a node into the heap
 * This simply adds it to the root list
 * and updates the min pointer if needed.
 */
void fib_heap_insert(FibHeap *heap, FibNode *node) {

    // Case 1: heap is empty
    if (heap->min == NULL) {
        heap->min = node;
    }

    // Case 2: add node to root list (right next to min)
    else {
        node->right = heap->min->right;
        node->left = heap->min;
        heap->min->right->left = node;
        heap->min->right = node;

        // Update minimum pointer
        if (node->key < heap->min->key)
            heap->min = node;
    }

    heap->size++;
}


/*
 * Combine the root lists of two heaps
 * and return the merged heap.
 */
FibHeap* fib_heap_union(FibHeap *h1, FibHeap *h2) {

    // If one heap is empty, return the other
    if (!h1->min) return h2;
    if (!h2->min) return h1;

    // Merge root lists by linking min nodes
    FibNode *h1Right = h1->min->right;
    FibNode *h2Left  = h2->min->left;

    h1->min->right = h2->min;
    h2->min->left = h1->min;

    h2Left->right = h1Right;
    h1Right->left = h2Left;

    // Update min pointer
    if (h2->min->key < h1->min->key)
        h1->min = h2->min;

    h1->size += h2->size;
    return h1;
}


/*
 * Make node y a child of node x.
 * This is used during consolidation.
 */
void fib_heap_link(FibHeap *heap, FibNode *y, FibNode *x) {

    // Remove y from root list
    y->left->right = y->right;
    y->right->left = y->left;

    // Set parent pointer
    y->parent = x;

    // If x has no children, y becomes first child
    if (x->child == NULL) {
        x->child = y;
        y->left = y;
        y->right = y;
    }

    // Otherwise insert y into x's child list
    else {
        y->right = x->child->right;
        y->left = x->child;
        x->child->right->left = y;
        x->child->right = y;
    }

    x->degree++;
    y->mark = 0;   // Reset mark because it's freshly moved
}


/*
 * After removing the minimum node,
 * we must consolidate trees so that
 * no two trees have the same degree.
 */
void fib_heap_consolidate(FibHeap *heap) {

    // Max possible degree for n nodes in Fibonacci heap is about log(n)
    FibNode *degreeArray[50] = {NULL};

    FibNode *start = heap->min;
    if (!start) return;

    FibNode *current = start;
    int rootCount = 0;

    // Count number of nodes in root list#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct FibNode {
    int key;
    int degree;
    int mark;
    struct FibNode *parent;
    struct FibNode *child;
    struct FibNode *left;
    struct FibNode *right;
} FibNode;

typedef struct FibHeap {
    FibNode *min;
    int n;
} FibHeap;

FibNode* create_node(int key) {
    FibNode *node = (FibNode*)malloc(sizeof(FibNode));
    node->key = key;
    node->degree = 0;
    node->mark = 0;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    return node;
}

FibHeap* create_heap() {
    FibHeap *H = (FibHeap*)malloc(sizeof(FibHeap));
    H->min = NULL;
    H->n = 0;
    return H;
}

void fib_heap_insert(FibHeap *H, FibNode *x) {
    if (H->min == NULL) {
        H->min = x;
    } else {
        x->left = H->min;
        x->right = H->min->right;
        H->min->right->left = x;
        H->min->right = x;
        if (x->key < H->min->key)
            H->min = x;
    }
    H->n++;
}

FibHeap* fib_heap_union(FibHeap *H1, FibHeap *H2) {
    if (!H1->min) return H2;
    if (!H2->min) return H1;

    FibNode *H1_right = H1->min->right;
    FibNode *H2_left = H2->min->left;

    H1->min->right = H2->min;
    H2->min->left = H1->min;

    H2_left->right = H1_right;
    H1_right->left = H2_left;

    if (H2->min->key < H1->min->key)
        H1->min = H2->min;

    H1->n += H2->n;
    return H1;
}

void fib_heap_link(FibHeap *H, FibNode *y, FibNode *x) {
    y->left->right = y->right;
    y->right->left = y->left;

    y->parent = x;
    if (x->child == NULL) {
        x->child = y;
        y->left = y;
        y->right = y;
    } else {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }

    x->degree++;
    y->mark = 0;
}

void fib_heap_consolidate(FibHeap *H) {
    int D = 45;  
    FibNode *A[45] = {NULL};

    FibNode *w = H->min;
    int root_count = 0;

    if (!w) return;

    FibNode *current = w;
    do {
        root_count++;
        current = current->right;
    } while (current != w);

    while (root_count--) {
        FibNode *x = w;
        int d = x->degree;
        w = w->right;

        while (A[d]) {
            FibNode *y = A[d];
            if (x->key > y->key) {
                FibNode *temp = x;
                x = y;
                y = temp;
            }
            fib_heap_link(H, y, x);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
    }

    H->min = NULL;
    for (int i = 0; i < D; i++) {
        if (A[i]) {
            if (!H->min)
                H->min = A[i];
            else {
                A[i]->left = H->min;
                A[i]->right = H->min->right;
                H->min->right->left = A[i];
                H->min->right = A[i];

                if (A[i]->key < H->min->key)
                    H->min = A[i];
            }
        }
    }
}

FibNode* fib_heap_extract_min(FibHeap *H) {
    FibNode *z = H->min;
    if (z) {
        if (z->child) {
            FibNode *c = z->child;
            do {
                FibNode *next = c->right;

                c->parent = NULL;
                c->left = H->min;
                c->right = H->min->right;
                H->min->right->left = c;
                H->min->right = c;

                c = next;
            } while (c != z->child);
        }

        z->left->right = z->right;
        z->right->left = z->left;

        if (z == z->right) {
            H->min = NULL;
        } else {
            H->min = z->right;
            fib_heap_consolidate(H);
        }
        H->n--;
    }
    return z;
}

void cut(FibHeap *H, FibNode *x, FibNode *y) {
    if (x->right == x)
        y->child = NULL;
    else {
        x->right->left = x->left;
        x->left->right = x->right;
        if (y->child == x)
            y->child = x->right;
    }

    y->degree--;

    x->left = H->min;
    x->right = H->min->right;
    H->min->right->left = x;
    H->min->right = x;

    x->parent = NULL;
    x->mark = 0;
}

void cascading_cut(FibHeap *H, FibNode *y) {
    FibNode *z = y->parent;
    if (z) {
        if (!y->mark)
            y->mark = 1;
        else {
            cut(H, y, z);
            cascading_cut(H, z);
        }
    }
}

void fib_heap_decrease_key(FibHeap *H, FibNode *x, int k) {
    if (k > x->key) {
        printf("New key is greater.\n");
        return;
    }

    x->key = k;
    FibNode *y = x->parent;

    if (y && x->key < y->key) {
        cut(H, x, y);
        cascading_cut(H, y);
    }

    if (x->key < H->min->key)
        H->min = x;
}

void fib_heap_delete(FibHeap *H, FibNode *x) {
    fib_heap_decrease_key(H, x, INT_MIN);
    fib_heap_extract_min(H);
}

int main() {
    FibHeap *H = create_heap();
    fib_heap_insert(H, create_node(10));
    fib_heap_insert(H, create_node(3));
    fib_heap_insert(H, create_node(15));
    fib_heap_insert(H, create_node(6));

    FibNode *m = fib_heap_extract_min(H);
    printf("Extracted min: %d\n", m->key);

    return 0;
}

    do {
        rootCount++;
        current = current->right;
    } while (current != start);

    // Process each root
    while (rootCount--) {

        FibNode *x = start;
        int d = x->degree;

        start = start->right;

        // If another tree has same degree, merge them
        while (degreeArray[d] != NULL) {

            FibNode *y = degreeArray[d];

            // Ensure x has smaller key
            if (y->key < x->key) {
                FibNode *temp = x;
                x = y;
                y = temp;
            }

            // Make y a child of x
            fib_heap_link(heap, y, x);

            degreeArray[d] = NULL;
            d++;
        }

        degreeArray[d] = x;
    }#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct FibNode {
    int key;
    int degree;
    int mark;
    struct FibNode *parent;
    struct FibNode *child;
    struct FibNode *left;
    struct FibNode *right;
} FibNode;

typedef struct FibHeap {
    FibNode *min;
    int n;
} FibHeap;

FibNode* create_node(int key) {
    FibNode *node = (FibNode*)malloc(sizeof(FibNode));
    node->key = key;
    node->degree = 0;
    node->mark = 0;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    return node;
}

FibHeap* create_heap() {
    FibHeap *H = (FibHeap*)malloc(sizeof(FibHeap));
    H->min = NULL;
    H->n = 0;
    return H;
}

void fib_heap_insert(FibHeap *H, FibNode *x) {
    if (H->min == NULL) {
        H->min = x;
    } else {
        x->left = H->min;
        x->right = H->min->right;
        H->min->right->left = x;
        H->min->right = x;
        if (x->key < H->min->key)
            H->min = x;
    }
    H->n++;
}

FibHeap* fib_heap_union(FibHeap *H1, FibHeap *H2) {
    if (!H1->min) return H2;
    if (!H2->min) return H1;

    FibNode *H1_right = H1->min->right;
    FibNode *H2_left = H2->min->left;

    H1->min->right = H2->min;
    H2->min->left = H1->min;

    H2_left->right = H1_right;
    H1_right->left = H2_left;

    if (H2->min->key < H1->min->key)
        H1->min = H2->min;

    H1->n += H2->n;
    return H1;
}

void fib_heap_link(FibHeap *H, FibNode *y, FibNode *x) {
    y->left->right = y->right;
    y->right->left = y->left;

    y->parent = x;
    if (x->child == NULL) {
        x->child = y;
        y->left = y;
        y->right = y;
    } else {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }

    x->degree++;
    y->mark = 0;
}

void fib_heap_consolidate(FibHeap *H) {
    int D = 45;  
    FibNode *A[45] = {NULL};

    FibNode *w = H->min;
    int root_count = 0;

    if (!w) return;

    FibNode *current = w;
    do {
        root_count++;
        current = current->right;
    } while (current != w);

    while (root_count--) {
        FibNode *x = w;
        int d = x->degree;
        w = w->right;

        while (A[d]) {
            FibNode *y = A[d];
            if (x->key > y->key) {
                FibNode *temp = x;
                x = y;
                y = temp;
            }
            fib_heap_link(H, y, x);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
    }

    H->min = NULL;
    for (int i = 0; i < D; i++) {
        if (A[i]) {
            if (!H->min)
                H->min = A[i];
            else {
                A[i]->left = H->min;
                A[i]->right = H->min->right;
                H->min->right->left = A[i];
                H->min->right = A[i];

                if (A[i]->key < H->min->key)
                    H->min = A[i];
            }
        }
    }
}

FibNode* fib_heap_extract_min(FibHeap *H) {
    FibNode *z = H->min;
    if (z) {
        if (z->child) {
            FibNode *c = z->child;
            do {
                FibNode *next = c->right;

                c->parent = NULL;
                c->left = H->min;
                c->right = H->min->right;
                H->min->right->left = c;
                H->min->right = c;

                c = next;
            } while (c != z->child);
        }

        z->left->right = z->right;
        z->right->left = z->left;

        if (z == z->right) {
            H->min = NULL;
        } else {
            H->min = z->right;
            fib_heap_consolidate(H);
        }
        H->n--;
    }
    return z;
}

void cut(FibHeap *H, FibNode *x, FibNode *y) {
    if (x->right == x)
        y->child = NULL;
    else {
        x->right->left = x->left;
        x->left->right = x->right;
        if (y->child == x)
            y->child = x->right;
    }

    y->degree--;

    x->left = H->min;
    x->right = H->min->right;
    H->min->right->left = x;
    H->min->right = x;

    x->parent = NULL;
    x->mark = 0;
}

void cascading_cut(FibHeap *H, FibNode *y) {
    FibNode *z = y->parent;
    if (z) {
        if (!y->mark)
            y->mark = 1;
        else {
            cut(H, y, z);
            cascading_cut(H, z);
        }
    }
}

void fib_heap_decrease_key(FibHeap *H, FibNode *x, int k) {
    if (k > x->key) {
        printf("New key is greater.\n");
        return;
    }

    x->key = k;
    FibNode *y = x->parent;

    if (y && x->key < y->key) {
        cut(H, x, y);
        cascading_cut(H, y);
    }

    if (x->key < H->min->key)
        H->min = x;
}

void fib_heap_delete(FibHeap *H, FibNode *x) {
    fib_heap_decrease_key(H, x, INT_MIN);
    fib_heap_extract_min(H);
}

int main() {
    FibHeap *H = create_heap();
    fib_heap_insert(H, create_node(10));
    fib_heap_insert(H, create_node(3));
    fib_heap_insert(H, create_node(15));
    fib_heap_insert(H, create_node(6));

    FibNode *m = fib_heap_extract_min(H);
    printf("Extracted min: %d\n", m->key);

    return 0;
}


    // Rebuild the root list and find new min
    heap->min = NULL;

    for (int i = 0; i < 50; i++) {
        if (degreeArray[i] != NULL) {
            FibNode *node = degreeArray[i];

            if (heap->min == NULL)
                heap->min = node;

            else {
                // Insert in root list
                node->right = heap->min->right;
                node->left = heap->min;
                heap->min->right->left = node;
                heap->min->right = node;

                // Update minimum
                if (node->key < heap->min->key)
                    heap->min = node;
            }
        }
    }
}


/*
 * Remove and return the node with minimum key
 */
FibNode* fib_heap_extract_min(FibHeap *heap) {

    FibNode *minNode = heap->min;

    if (minNode != NULL) {

        // Add all children of minNode to root list
        if (minNode->child != NULL) {

            FibNode *c = minNode->child;
            FibNode *start = c;

            do {
                FibNode *next = c->right;

                // Remove parent link
                c->parent = NULL;

                // Add child to root list
                c->left = heap->min;
                c->right = heap->min->right;
                heap->min->right->left = c;
                heap->min->right = c;

                c = next;
            } while (c != start);
        }

        // Remove minNode from root list
        minNode->left->right = minNode->right;
        minNode->right->left = minNode->left;

        // If it was the only node
        if (minNode == minNode->right) {
            heap->min = NULL;
        }

        // Otherwise consolidate
        else {
            heap->min = minNode->right;
            fib_heap_consolidate(heap);
        }

        heap->size--;
    }

    return minNode;
}


/*
 * Cut node x from its parent and add it to root list.
 */
void cut(FibHeap *heap, FibNode *x, FibNode *parent) {

    // Remove x from parent's child list
    if (x->right == x)
        parent->child = NULL;
    else {
        x->right->left = x->left;
        x->left->right = x->right;

        if (parent->child == x)
            parent->child = x->right;
    }

    parent->degree--;

    // Add x to root list
    x->left = heap->min;
    x->right = heap->min->right;
    heap->min->right->left = x;
    heap->min->right = x;

    x->parent = NULL;
    x->mark = 0;
}


/*
 * Cascading cut keeps heap balanced after decrease-key.
 */
void cascading_cut(FibHeap *heap, FibNode *y) {
    FibNode *parent = y->parent;

    if (parent != NULL) {
        if (y->mark == 0)
            y->mark = 1;
        else {
            cut(heap, y, parent);
            cascading_cut(heap, parent);
        }
    }
}


/*
 * Decrease the key of a given node.
 */
void fib_heap_decrease_key(FibHeap *heap, FibNode *x, int newKey) {

    if (newKey > x->key) {
        printf("Error: new key is larger.\n");
        return;
    }

    x->key = newKey;
    FibNode *parent = x->parent;

    // If heap property violated
    if (parent != NULL && x->key < parent->key) {
        cut(heap, x, parent);
        cascading_cut(heap, parent);
    }

    if (x->key < heap->min->key)
        heap->min = x;
}


/*
 * Delete a node by decreasing it to -∞ and then extracting min
 */
void fib_heap_delete(FibHeap *heap, FibNode *x) {
    fib_heap_decrease_key(heap, x, INT_MIN);
    fib_heap_extract_min(heap);
}


/*
 * Simple demo
 */
int main() {
    FibHeap *heap = create_heap();

    fib_heap_insert(heap, create_node(10));
    fib_heap_insert(heap, create_node(3));
    fib_heap_insert(heap, create_node(18));
    fib_heap_insert(heap, create_node(7));

    FibNode *min = fib_heap_extract_min(heap);

    printf("Extracted minimum: %d\n", min->key);

    return 0;
}

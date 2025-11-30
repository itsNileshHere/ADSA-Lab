## Problem

This program implements Kruskal's algorithm to find the Minimum Spanning Tree (MST) of a connected, undirected, and weighted graph. The graph is provided as an input file.

## Theory

Kruskal's algorithm is a greedy algorithm that finds an MST for a connected, undirected, and edge-weighted graph. An MST is a subset of the edges of a connected, edge-weighted undirected graph that connects all the vertices together, without any cycles and with the minimum possible total edge weight.

The algorithm works as follows:
1.  **Sort Edges:** All edges in the graph are sorted in non-decreasing order of their weights.
2.  **Initialize Disjoint Sets:** Each vertex is treated as a separate, disjoint set (a forest of single-vertex trees). The Union-Find data structure is used to manage these sets.
3.  **Iterate and Select Edges:** The algorithm iterates through the sorted edges:
    *   For each edge, it checks if adding this edge would connect two vertices that are already in the same set (i.e., create a cycle). This is done using the `findParent()` operation of the Union-Find data structure.
    *   If the vertices are in different sets, the edge is added to the MST, and the two sets are merged using the `unionSet()` operation.
    *   If adding the edge would create a cycle, it is discarded.
4.  **Termination:** The process continues until `V-1` edges have been added to the MST (where V is the number of vertices) or all edges have been processed.

### Union-Find Data Structure

The Union-Find (or Disjoint Set Union) data structure is crucial for efficient cycle detection and merging of components in Kruskal's algorithm. It supports two main operations:
-   **`Find(x)`:** Determines the representative (root) of the set containing element `x`. Path compression optimization is often used to flatten the tree structure during find operations, improving efficiency.
-   **`Union(x, y)`:** Merges the sets containing `x` and `y`. Union by rank (or size) optimization is used to attach the smaller tree under the root of the larger tree, keeping the trees balanced.

## Approach

The `Kruskal_MST.c` program implements Kruskal's algorithm using these components:

-   **`Edge` struct:** Represents an edge with `src` (source vertex name), `dest` (destination vertex name), and `weight`.
-   **`Vertex` struct:** Stores the `name` of a vertex.
-   **`findVertexIndex()`:** A helper function to get the index of a vertex by its name, creating it if it doesn't exist. This is a simplification for managing vertex IDs.
-   **`findParent()`:** Implements the `Find` operation with path compression.
-   **`unionSet()`:** Implements the `Union` operation with union by rank.
-   **`compareEdges()`:** A comparison function used by `qsort()` to sort edges based on their weights.
-   **`kruskalMST()`:** The main Kruskal's algorithm implementation:
    1.  Sorts all edges using `qsort()`.
    2.  Initializes `parent[]` and `rank[]` arrays for the Union-Find data structure.
    3.  Iterates through the sorted edges, using `findParent()` to check for cycles and `unionSet()` to merge components and add edges to the MST.
    4.  Calculates and prints the total cost of the MST.
-   **`main()`:**
    *   Prompts the user for a SIF file name (a simple format where each line is `source destination weight`).
    *   Reads the graph edges and vertices from the specified file.
    *   Calls `kruskalMST()` to find and print the MST.

## Usage

To compile and run the code:

```bash
gcc Kruskal_MST.c -o Kruskal_MST
./Kruskal_MST
```

The program expects an input file (e.g., `graph.txt`) where each line defines an edge with a source vertex name, a destination vertex name, and its weight, separated by spaces.
Example `graph.txt`:
```
A B 1
A C 4
B C 2
B D 5
C D 3
```

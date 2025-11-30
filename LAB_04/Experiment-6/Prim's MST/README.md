## Problem

This program implements Prim's algorithm to find the Minimum Spanning Tree (MST) of a connected, undirected, and weighted graph. The graph is read from an input file.

## Theory

Prim's algorithm is a greedy algorithm that finds an MST for a connected, undirected, and edge-weighted graph. It starts from an arbitrary vertex and continuously adds the cheapest edge that connects a vertex already in the MST to a vertex not yet in the MST. This process ensures that the selected edges always form a tree and never create a cycle.

The algorithm proceeds as follows:
1.  **Initialization:**
    *   Initialize `key[]` values for all vertices to infinity, except for the starting vertex (usually the first one), which is set to 0. This `key[]` array stores the minimum weight edge connecting a vertex to the MST.
    *   Initialize `mstSet[]` to `false` for all vertices. This array keeps track of vertices already included in the MST.
    *   Initialize `parent[]` to store the MST structure.
2.  **Iteration:**
    *   Repeat `V-1` times (where `V` is the number of vertices):
        *   Select the vertex `u` not yet included in `mstSet` that has the minimum `key` value.
        *   Add `u` to `mstSet`.
        *   For all adjacent vertices `v` of `u`:
            *   If `v` is not in `mstSet` and the weight of the edge `(u, v)` is less than `key[v]`, then update `key[v]` to the weight of `(u, v)` and set `parent[v] = u`.
3.  **Construction:** Once the loop finishes, the `parent[]` array defines the edges of the MST.

The time complexity of Prim's algorithm is typically O(V^2) when implemented with an adjacency matrix (as in this code) or O(E log V) if a min-priority queue is used (where E is the number of edges and V is the number of vertices).

## Approach

The `Prim_MST.c` program implements Prim's algorithm:

-   **`Vertex` struct:** Stores the `name` of a vertex.
-   **`findVertexIndex()`:** A helper function to map vertex names to integer indices, creating new entries if a vertex is encountered for the first time.
-   **`minKey()`:** This helper function finds the vertex with the minimum `key` value from the set of vertices not yet included in the MST.
-   **`primMST()`:** The main Prim's algorithm implementation:
    1.  Initializes `key[]` to `INF`, `mstSet[]` to `0` (false), and `parent[]`. The `key` of the starting vertex (index 0) is set to 0.
    2.  It then iterates `n-1` times. In each iteration:
        *   It selects a vertex `u` with the minimum `key` from the unvisited set using `minKey()`.
        *   It marks `u` as included in the MST (`mstSet[u] = 1`).
        *   It updates the `key` values and `parent` for all adjacent vertices `v` that are not yet in the MST if a smaller edge weight is found.
    3.  Finally, it prints the edges of the MST and calculates the total minimum cost.
-   **`main()`:**
    *   Prompts the user for a SIF file name.
    *   Reads the graph edges and their weights from the specified file. It builds an adjacency matrix `graph[MAX][MAX]` where `graph[i][j]` stores the weight of the edge between vertex `i` and vertex `j`.
    *   Calls `primMST()` to find and print the MST.

## Usage

To compile and run the code:

```bash
gcc Prim_MST.c -o Prim_MST
./Prim_MST
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

## Problem

This program implements the Floyd-Warshall algorithm to find the shortest paths between all pairs of vertices in a given weighted graph.

## Theory

The Floyd-Warshall algorithm is a dynamic programming algorithm used to find the shortest paths between all pairs of vertices in a weighted graph. It can handle both directed and undirected graphs, and it works correctly with negative edge weights, but not with negative cycles (where the sum of weights in a cycle is negative).

The algorithm's core idea is to consider every vertex `k` as a potential intermediate vertex for a path between any two other vertices `i` and `j`. It iteratively updates the shortest path distance `dist[i][j]` by checking if going through `k` provides a shorter path (i.e., `dist[i][k] + dist[k][j] < dist[i][j]`).

The steps are:
1.  **Initialization:** Create a distance matrix `dist[V][V]` and initialize it with the direct edge weights from the input graph. If there's no direct edge between `i` and `j`, set `dist[i][j]` to a large value representing infinity.
2.  **Iteration:** For each vertex `k` from `0` to `n-1` (where `n` is the number of vertices):
    *   For each pair of vertices `i` and `j`:
        *   Update `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])`.
This process ensures that after considering all possible intermediate vertices, `dist[i][j]` will hold the shortest path between `i` and `j`.

The time complexity of the Floyd-Warshall algorithm is O(V^3), where V is the number of vertices, due to the three nested loops. The space complexity is O(V^2) for storing the distance matrix.

## Approach

The `Floyd_Warshall_Algo.c` program implements the algorithm as follows:

-   **`printSolution()`:** A helper function to neatly print the final all-pairs shortest path matrix.
-   **`floydWarshall()`:**
    1.  Initializes a `dist[V][V]` matrix by copying the input `graph` adjacency matrix. It uses a predefined `INF` (infinity) value for non-existent edges.
    2.  It then enters the core triple-nested loop structure:
        *   The outer loop iterates through all possible intermediate vertices `k`.
        *   The two inner loops iterate through all possible source vertices `i` and destination vertices `j`.
        *   Inside the innermost loop, it checks if the path from `i` to `j` via `k` is shorter than the currently known shortest path and updates `dist[i][j]` if a shorter path is found.
    3.  Finally, it calls `printSolution()` to display the computed all-pairs shortest paths.
-   **`main()`:**
    *   Prompts the user to enter the number of vertices and the adjacency matrix of the graph (using `INF` for no direct edge).
    *   Calls `floydWarshall()` to execute the algorithm and print the results.

## Usage

To compile and run the code:

```bash
gcc Floyd_Warshall_Algo.c -o Floyd_Warshall_Algo
./Floyd_Warshall_Algo
```

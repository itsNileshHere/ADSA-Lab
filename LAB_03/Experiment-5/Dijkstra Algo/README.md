## Problem

This program implements Dijkstra's algorithm to find the shortest path from a single source vertex to all other vertices in a given weighted graph.

## Theory

Dijkstra's algorithm is a greedy algorithm used to solve the single-source shortest path problem for a graph with non-negative edge weights. It works by building a set of vertices whose shortest distance from the source has been finalized.

The algorithm proceeds as follows:
1.  Initialize distances: Assign a distance value of 0 to the source vertex and infinity to all other vertices.
2.  Maintain a set of "shortest path tree" vertices (sptSet): Initially empty, this set will contain vertices for which the shortest path from the source has been finalized.
3.  Iteratively select the unvisited vertex with the minimum distance from the source.
4.  Add the selected vertex to `sptSet`.
5.  Update the distance values of all adjacent vertices of the newly added vertex. For each adjacent vertex `v`, if the sum of the distance to the current vertex `u` and the weight of the edge `u-v` is less than the currently known distance to `v`, update `dist[v]`.
6.  Repeat steps 3-5 until all vertices are included in the `sptSet` or the shortest paths to all reachable vertices are found.

The time complexity of Dijkstra's algorithm is typically O(V^2) for adjacency matrix representation or O(E log V) with a min-priority queue (where V is the number of vertices and E is the number of edges). The provided implementation, using an adjacency matrix and linear scan for `minDistance`, has a time complexity of O(V^2).

## Approach

The `Dijkstra.c` program implements Dijkstra's algorithm for a graph represented by an adjacency matrix.

-   **`minDistance()`:** This helper function finds the vertex with the minimum distance value from the set of vertices not yet included in the shortest path tree (`sptSet`).
-   **`printSolution()`:** Prints the calculated shortest distances from the source to all other vertices.
-   **`dijkstra()`:**
    1.  Initializes `dist[]` (distances) to `INT_MAX` for all vertices and `sptSet[]` (shortest path tree set) to `false`. The distance of the source vertex `src` is set to 0.
    2.  It then iterates `n-1` times (where `n` is the number of vertices). In each iteration:
        *   It selects a vertex `u` with the minimum distance from the unvisited set using `minDistance()`.
        *   It marks `u` as visited (`sptSet[u] = true`).
        *   It updates the distance values of the adjacent vertices of `u`. If a shorter path to an adjacent vertex `v` is found through `u`, `dist[v]` is updated.
    3.  Finally, it calls `printSolution()` to display the results.
-   **`main()`:**
    *   Prompts the user to enter the number of vertices and the adjacency matrix of the graph.
    *   Prompts for the source vertex.
    *   Calls the `dijkstra()` function to compute and print the shortest paths.

## Usage

To compile and run the code:

```bash
gcc Dijkstra.c -o Dijkstra
./Dijkstra
```

## Problem

This program finds the maximum cardinality matching in a bipartite graph. It takes the bipartite graph's adjacency matrix as input and determines the maximum number of edges that can be selected such that no two edges share a common vertex.

## Theory

A **bipartite graph** is a graph whose vertices can be divided into two disjoint and independent sets, usually denoted as U and V. Edges only connect vertices from set U to vertices in set V, and no edges exist between vertices within the same set.

A **matching** in a graph is a set of edges where no two edges share a common vertex. In a bipartite graph, a matching pairs vertices from U with vertices from V. A **maximum cardinality matching** (or simply maximum matching) is a matching that contains the largest possible number of edges.

This program uses a **DFS (Depth-First Search) based approach** to find the maximum bipartite matching. This method is often described as finding a set of **augmenting paths**. An augmenting path is a path that starts from an unmatched vertex in U, ends at an unmatched vertex in V, and alternates between edges not in the current matching and edges that are in the current matching. If such a path is found, we can "augment" the matching by flipping the edges along this path (edges not in matching become part of it, and vice-versa), which increases the size of the matching by one.

The algorithm iteratively tries to find an augmenting path for each unmatched vertex in U. If an augmenting path is found, the matching is increased. This process continues until no more augmenting paths can be found.

The time complexity of this DFS-based approach is typically O(V * E) in the worst case, where V is the number of vertices and E is the number of edges. More advanced algorithms like Hopcroft-Karp can achieve O(E√V) but are more complex to implement.

## Approach

The `Bipartite_Matching.c` program implements the DFS-based approach:

-   **`nU`, `nV`:** Global variables to store the number of vertices in set U and set V, respectively.
-   **`graph[MAX][MAX]`:** An adjacency matrix representing the bipartite graph. `graph[u][v] = 1` indicates an edge between vertex `u` in set U and vertex `v` in set V.
-   **`matchV[MAX]`:** An array where `matchV[v] = u` indicates that vertex `v` in set V is matched with vertex `u` in set U. Initialized to -1 (unmatched).
-   **`visited[MAX]`:** A boolean array used during DFS to keep track of visited vertices in set V for the current augmenting path search.
-   **`bpm(int u)` function (Bipartite Path Matching):**
    *   This is the core recursive DFS function that attempts to find an augmenting path starting from vertex `u` in set U.
    *   It iterates through all vertices `v` in set V. If there's an edge `(u,v)` and `v` has not been visited in the current DFS traversal:
        *   Mark `v` as visited.
        *   If `v` is currently unmatched (`matchV[v] == -1`) or if its matched partner (`matchV[v]`) can find an alternative augmenting path (`bpm(matchV[v])` returns true), then `u` can be matched with `v`. Update `matchV[v] = u` and return `true`.
    *   If no such `v` is found, return `false`.
-   **`maxBPM()` function:**
    *   Initializes `matchV` to all -1s.
    *   Iterates through each vertex `u` in set U.
    *   For each `u`, it resets the `visited` array and calls `bpm(u)`. If `bpm(u)` returns true, it means an augmenting path was found and the matching size is incremented.
    *   Returns the total number of matched edges.
-   **`main()`:**
    *   Prompts the user to enter the number of vertices in sets U and V.
    *   Prompts for the adjacency matrix.
    *   Calls `maxBPM()` to compute the maximum matching.
    *   Prints the maximum matching size and the matched pairs.

## Usage

To compile and run the code:

```bash
gcc Bipartite_Matching.c -o Bipartite_Matching
./Bipartite_Matching
```

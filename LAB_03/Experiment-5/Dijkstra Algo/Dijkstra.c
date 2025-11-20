#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 10   // maximum number of vertices

// Find the vertex with minimum distance value
int minDistance(int dist[], bool sptSet[], int n) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Print shortest path distances
void printSolution(int dist[], int n, int src) {
    printf("Vertex \t Distance from Source (%d)\n", src);
    for (int i = 0; i < n; i++) {
        if (dist[i] == INT_MAX)
            printf("%d \t INF\n", i);
        else
            printf("%d \t %d\n", i, dist[i]);
    }
}

// Dijkstra’s algorithm
void dijkstra(int graph[V][V], int n, int src) {
    int dist[V];      // shortest distance from src to i
    bool sptSet[V];   // true if vertex i is included in shortest path tree

    // Initialize
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < n-1; count++) {
        int u = minDistance(dist, sptSet, n);
        sptSet[u] = true;

        // Update distances of adjacent vertices
        for (int v = 0; v < n; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print result
    printSolution(dist, n, src);
}

int main() {
    int n;
    printf("Enter number of vertices (<= %d): ", V);
    scanf("%d", &n);

    int graph[V][V];
    printf("Enter adjacency matrix (0 if no edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int src;
    printf("Enter source vertex (0 to %d): ", n-1);
    scanf("%d", &src);

    dijkstra(graph, n, src);

    return 0;
}

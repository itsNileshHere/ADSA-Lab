#include <stdio.h>

#define V 10      // maximum number of vertices
#define INF 99999 // a large number representing infinity

// Function to print the solution matrix
void printSolution(int dist[V][V], int n) {
    printf("All Pairs Shortest Path Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

// Floyd-Warshall algorithm
void floydWarshall(int graph[V][V], int n) {
    int dist[V][V];

    // Initialize distance matrix with graph values
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = graph[i][j];

    // Update distances considering intermediate vertices
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printSolution(dist, n);
}

int main() {
    int n;
    printf("Enter number of vertices (<= %d): ", V);
    scanf("%d", &n);

    int graph[V][V];
    printf("Enter adjacency matrix (use %d for no edge):\n", INF);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    floydWarshall(graph, n);

    return 0;
}

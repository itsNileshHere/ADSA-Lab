#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 100
#define INF 999999

// Structure for mapping node names to indices
typedef struct {
    char name[10];
} Vertex;

int findVertexIndex(Vertex vertices[], int *count, char name[]) {
    for (int i = 0; i < *count; i++) {
        if (strcmp(vertices[i].name, name) == 0)
            return i;
    }
    strcpy(vertices[*count].name, name);
    (*count)++;
    return *count - 1;
}

int minKey(int key[], int mstSet[], int n) {
    int min = INF, min_index = -1;
    for (int v = 0; v < n; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void primMST(int graph[MAX][MAX], Vertex vertices[], int n) {
    int parent[MAX];
    int key[MAX];
    int mstSet[MAX];

    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1; // First node is root

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("\nMinimum Spanning Tree using Prim's Algorithm:\n");
    int total = 0;
    for (int i = 1; i < n; i++) {
        printf("%s - %s : %d\n", vertices[parent[i]].name, vertices[i].name, graph[i][parent[i]]);
        total += graph[i][parent[i]];
    }
    printf("Total Minimum Cost = %d\n", total);
}

int main() {
    FILE *fp;
    char fileName[50];
    printf("Enter SIF file name: ");
    scanf("%s", fileName);

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    Vertex vertices[MAX];
    int graph[MAX][MAX] = {0};
    int count = 0;

    char u[10], v[10];
    int w;
    while (fscanf(fp, "%s %s %d", u, v, &w) == 3) {
        int i = findVertexIndex(vertices, &count, u);
        int j = findVertexIndex(vertices, &count, v);
        graph[i][j] = graph[j][i] = w;
    }
    fclose(fp);

    if (count == 0) {
        printf("Empty or invalid graph.\n");
        return 1;
    }

    primMST(graph, vertices, count);
    return 0;
}

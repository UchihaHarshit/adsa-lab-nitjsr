#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6   // Number of vertices in the graph

// Find the vertex with the minimum key value
int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, minIndex = -1;
    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Print the constructed MST
void printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
    }
}

// Function to construct MST using Prim’s Algorithm
void prims(int graph[V][V]) {
    int parent[V];   // Stores MST structure
    int key[V];      // Minimum weight edge for each vertex
    bool mstSet[V];  // True if vertex is included in MST

    // Initialize all keys as infinite and mstSet[] as false
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;     // Start with vertex 0
    parent[0] = -1; // Root node has no parent

    for (int j = 0; j < V - 1; j++) {
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph);
}

// Driver code
int main() {
    int graph[V][V] = {
        {0, 2, 0, 6, 0, 0},
        {2, 0, 3, 8, 5, 0},
        {0, 3, 0, 0, 7, 9},
        {6, 8, 0, 0, 9, 0},
        {0, 5, 7, 9, 0, 11},
        {0, 0, 9, 0, 11, 0}
    };

    prims(graph);

    return 0;
}

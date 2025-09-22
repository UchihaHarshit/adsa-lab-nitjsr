#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX];   // Adjacency matrix
int visited[MAX];      // 0 = unvisited, 1 = visiting, 2 = finished
int discovery[MAX];    // Discovery time
int finish[MAX];       // Finishing time
int timeCounter = 0;
int V; // number of vertices

void DFS_visit(int u) {
    visited[u] = 1;
    discovery[u] = ++timeCounter;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) { // edge u -> v exists
            if (visited[v] == 0) {
                printf("Tree Edge: %d -> %d\n", u, v);
                DFS_visit(v);
            } 
            else if (visited[v] == 1) {
                printf("Back Edge: %d -> %d\n", u, v);
            } 
            else if (visited[v] == 2) {
                if (discovery[u] < discovery[v])
                    printf("Forward Edge: %d -> %d\n", u, v);
                else
                    printf("Cross Edge: %d -> %d\n", u, v);
            }
        }
    }

    visited[u] = 2;
    finish[u] = ++timeCounter;
}

void DFS() {
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
        discovery[i] = 0;
        finish[i] = 0;
    }

    for (int i = 0; i < V; i++) {
        if (visited[i] == 0)
            DFS_visit(i);
    }
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter adjacency matrix (%d x %d):\n", V, V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nClassifying edges using DFS:\n");
    DFS();

    printf("\nDiscovery and Finishing Times:\n");
    for (int i = 0; i < V; i++) {
        printf("Vertex %d: discovery=%d, finish=%d\n", i, discovery[i], finish[i]);
    }

    return 0;
}

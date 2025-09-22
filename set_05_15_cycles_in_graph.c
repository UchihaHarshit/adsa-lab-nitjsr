#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int graph[MAX][MAX];   // adjacency matrix
int visited[MAX];      // 0=unvisited, 1=visiting, 2=finished
int path[MAX];         // stack to store current path
int pathIndex = 0;
int V;                 // number of vertices

int smallestCycle = MAX;
int largestCycle = -1;

// Function to check for cycle and record lengths
void DFS(int u, int parent, int directed) {
    visited[u] = 1;
    path[pathIndex++] = u;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            // For undirected graph, avoid immediate parent edge
            if (!directed && v == parent) continue;

            if (visited[v] == 0) {
                DFS(v, u, directed);
            }
            else if (visited[v] == 1) { // Back edge found
                // Find cycle length
                int cycleLength = 0;
                for (int i = pathIndex - 1; i >= 0; i--) {
                    cycleLength++;
                    if (path[i] == v) break;
                }
                if (cycleLength > 1) {
                    if (cycleLength < smallestCycle) smallestCycle = cycleLength;
                    if (cycleLength > largestCycle) largestCycle = cycleLength;
                }
            }
        }
    }

    visited[u] = 2;
    pathIndex--;
}

void findCycles(int directed) {
    for (int i = 0; i < V; i++) visited[i] = 0;

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            DFS(i, -1, directed);
    }

    if (largestCycle == -1) {
        printf("No cycles found.\n");
    } else {
        printf("Smallest cycle length: %d\n", smallestCycle);
        printf("Largest cycle length: %d\n", largestCycle);
    }
}

int main() {
    int directed;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter 1 for Directed graph, 0 for Undirected graph: ");
    scanf("%d", &directed);

    printf("Enter adjacency matrix (%d x %d):\n", V, V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    findCycles(directed);

    return 0;
}

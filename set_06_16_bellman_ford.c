#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// directed edge in the graph
typedef struct {
    int src, dest, weight;
} Edge;

// graph
typedef struct {
    int V, E;
    Edge* edges;
} Graph;

// Function to create a graph with V vertices and E edges
Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (Edge*)malloc(graph->E * sizeof(Edge));
    return graph;
}

void BellmanFord(Graph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    int dist[V];

    // Step 1: Initialize distances from src to all other vertices as infinity
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edges[j].src;
            int v = graph->edges[j].dest;
            int weight = graph->edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Step 3: Check for negative-weight cycles
    for (int i = 0; i < E; i++) {
        int u = graph->edges[i].src;
        int v = graph->edges[i].dest;
        int weight = graph->edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle!\n");
            return;
        }
    }

    // Print the shortest distances
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }

    return;
}

int main() {
    int V = 5;
    int E = 8;
    Graph* graph = createGraph(V, E);

    graph->edges[0].src = 0;
    graph->edges[0].dest = 1;
    graph->edges[0].weight = -1;

    graph->edges[1].src = 0;
    graph->edges[1].dest = 2;
    graph->edges[1].weight = 4;

    graph->edges[2].src = 1;
    graph->edges[2].dest = 2;
    graph->edges[2].weight = 3;

    graph->edges[3].src = 1;
    graph->edges[3].dest = 3;
    graph->edges[3].weight = 2;

    graph->edges[4].src = 1;
    graph->edges[4].dest = 4;
    graph->edges[4].weight = 2;

    graph->edges[5].src = 3;
    graph->edges[5].dest = 2;
    graph->edges[5].weight = 5;

    graph->edges[6].src = 3;
    graph->edges[6].dest = 1;
    graph->edges[6].weight = 1;

    graph->edges[7].src = 4;
    graph->edges[7].dest = 3;
    graph->edges[7].weight = -3;

    BellmanFord(graph, 0);

    free(graph->edges);
    free(graph);

    return 0;
}
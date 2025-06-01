#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define V 1000 // Number of vertices in the graph

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to read the CSV file and populate the graph
void readCSV(const char *filename, int graph[V][V]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        exit(1);
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (fscanf(file, "%d,", &graph[i][j]) != 1) {
                printf("Error reading CSV data.\n");
                exit(1);
            }
        }
    }

    fclose(file);
}

// Function to print the graph matrix for debugging
void printGraph(int graph[V][V]) {
    printf("Graph Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

// Dijkstra's algorithm for finding the shortest path from source
void dijkstra(int graph[V][V], int src) {
    int dist[V];  // Array to store the shortest distance from src to i
    bool sptSet[V]; // Shortest path tree set (whether a vertex is included in the shortest path tree)

    // Initialize all distances to infinity and sptSet to false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance to the source node is 0
    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the vertex with the minimum distance that has not been processed yet
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        // Update the dist[] value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            // Only update dist[v] if there is an edge between u and v
            // and the new path is shorter than the current distance
            if (!sptSet[v] && graph[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the distance array
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            printf("%d\tNo Path\n", i);
        } else {
            printf("%d\t%d\n", i, dist[i]);
        }
    }
}

int main() {
    int graph[V][V];

    // Start timer
    clock_t start_time = clock();

    // Read graph data from the CSV file
    readCSV("graph_1000.csv", graph);

    // Uncomment this line to print the graph for debugging
    // printGraph(graph);

    // Choose the source vertex (for example, vertex 0)
    int source = 0;

    // Call Dijkstra's algorithm
    dijkstra(graph, source);

    // End timer and calculate the time taken
    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // Print the time taken by the algorithm
    printf("\nDijkstra's Algorithm Execution Time: %f seconds\n", time_taken);

    return 0;
}

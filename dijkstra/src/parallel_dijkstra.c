#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define V 5000 // Number of vertices in the graph

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
void readCSV(const char *filename, int **graph) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open file: %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (fscanf(file, "%d,", &graph[i][j]) != 1) {
                printf("Error reading CSV data.\n");
                fclose(file);
                exit(1);
            }
        }
    }

    fclose(file);
    printf("CSV file loaded successfully: %s\n", filename);
}

// Dijkstra's algorithm for finding the shortest path from source
void dijkstra(int **graph, int src) {
    int dist[V];       // Array to store the shortest distance from src to i
    bool sptSet[V];    // Shortest path tree set (whether a vertex is included)

    // Initialize all distances to infinity and sptSet to false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance to the source node is 0
    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        // Update the dist[] value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the shortest distances
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
    // Dynamically allocate memory for the graph (using malloc)
    int **graph = (int **)malloc(V * sizeof(int *));
    if (graph == NULL) {
        printf("Memory allocation failed for graph rows.\n");
        return 1;
    }

    for (int i = 0; i < V; i++) {
        graph[i] = (int *)malloc(V * sizeof(int));
        if (graph[i] == NULL) {
            printf("Memory allocation failed for graph columns.\n");
            return 1;
        }
    }

    const char *csv_file = "graph_5000.csv"; // CSV file location for Docker

    // Start timer
    clock_t start_time = clock();

    // Read graph data from the CSV file
    readCSV(csv_file, graph);

    // Choose the source vertex (for example, vertex 0)
    int source = 0;
    printf("\nStarting Dijkstra's Algorithm from Source: %d\n", source);

    // Call Dijkstra's algorithm
    dijkstra(graph, source);

    // End timer and calculate the time taken
    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\nDijkstra's Algorithm Execution Time: %f seconds\n", time_taken);

    // Free dynamically allocated memory
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
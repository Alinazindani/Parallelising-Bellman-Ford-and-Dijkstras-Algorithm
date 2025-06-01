#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define V 5000 // Number of vertices change for diff vertices

// Function to generate a random graph and write it to a CSV file
void generateCSV(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open file for writing.\n");
        exit(1);
    }

    // Seed for random number generation
    srand(time(NULL));

    // Generate the graph with random weights between 1 and 100
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j) {
                fprintf(file, "%d,", rand() % 100 + 1); // Random edge weight between 1 and 100
            } else {
                fprintf(file, "0,"); // No self-loops (distance to itself is 0)
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("CSV file generated: %s\n", filename);
}

int main() {
    // Generate a graph and save it as a CSV file
    generateCSV("graph_5000.csv");
    return 0;
}
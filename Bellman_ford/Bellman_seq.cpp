
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <unordered_set>

using namespace std;
using namespace chrono;  // For accurate time measurement

struct Edge {
    int src, dest, weight;
};

// Bellman-Ford Algorithm
void bellmanFord(const vector<Edge> &edges, const unordered_set<int> &nodes, int source) {
    unordered_map<int, int> dist;
    for (int node : nodes)
        dist[node] = numeric_limits<int>::max();
    
    dist[source] = 0;

    auto start = high_resolution_clock::now();

    for (size_t i = 0; i < nodes.size() - 1; ++i) {
        for (const auto &edge : edges) {
            if (dist[edge.src] != numeric_limits<int>::max() &&
                dist[edge.src] + edge.weight < dist[edge.dest]) {
                dist[edge.dest] = dist[edge.src] + edge.weight;
            }
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Bellman-Ford execution time: " << duration.count() << " milli-sec\n";
}

int main() {
    ifstream file("bellman_graphs/graph_1000V_5000E.txt");
    if (!file) {
        cerr << "Error opening file!\n";
        return 1;
    }

    int V, E;
    file >> V >> E;

    unordered_map<int, vector<pair<int, int>>> graph;
    vector<Edge> edges;
    unordered_set<int> nodes;

    int src, dest, weight;
    while (file >> src >> dest >> weight) {
        graph[src].push_back({dest, weight});
        edges.push_back({src, dest, weight});
        nodes.insert(src);
        nodes.insert(dest);
    }
    file.close();

    // Detect source node with outgoing edges
    int source = -1;
    for (const auto &entry : graph) {
        if (!entry.second.empty()) {
            source = entry.first;
            break;
        }
    }

    if (source == -1) {
        cerr << "No valid source node found!\n";
        return 1;
    }

    cout << "Detected source node: " << source << endl;

    bellmanFord(edges, nodes, source);

    return 0;
}

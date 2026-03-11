// Bellman-Ford Algorithm Implementation
// --------------------------------------
// To find the shortest distances from a source vertex to all other nodes in a weighted graph.
// It works for graphs with negative edge weights and can detect negative-weight cycles.
//
// Key Steps:
// 1. Initialize distances: distance[source] = 0, all others = ∞.
// 2. Relax all edges V-1 times (where V = number of vertices).
// 3. Check for negative-weight cycles.
// 4. Print shortest distances from the source.

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Edge structure: represents a directed edge from src to dest with a given weight.
struct Edge {
    int src, dest, weight;
};

// Bellman-Ford function: computes shortest paths and detects negative cycles.
// Parameters:
//   edges  - list of all edges in the graph
//   V      - number of vertices
//   E      - number of edges
//   source - starting vertex
void bellmanFord(vector<Edge> &edges, int V, int E, int source) {
    // Step 1: Initialize distances
    vector<int> distance(V, INT_MAX);
    distance[source] = 0;

    // Step 2: Relax all edges V-1 times
    // Each pass tries to improve the shortest path estimate for every vertex
    for (int i = 1; i <= V - 1; ++i) {
        for (int j = 0; j < E; ++j) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            // If the path through u improves the distance to v, update it
            if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
            }
        }
    }

    // Step 3: Check for negative-weight cycles
    // If we can still relax any edge, there is a negative cycle
    for (int i = 0; i < E; ++i) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int w = edges[i].weight;

        if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
            cout << "Graph contains negative weight cycle!" << endl;
            return;
        }
    }

    // Step 4: Output the shortest distances from the source
    cout << "Vertex   Distance from Source" << endl;
    for (int i = 0; i < V; ++i) {
        cout << i << "\t\t" << distance[i] << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);

    cout << "Enter the source, destination, and weight for each edge:" << endl;
    for (int i = 0; i < E; ++i) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    bellmanFord(edges, V, E, source);

    return 0;
}
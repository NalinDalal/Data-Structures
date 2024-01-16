//bellmann ford algo
/*
From a source vertx v,find shortest dist to all other node in graph
Idea
1. Initially d[v] = 0 and for all other elements d[] = ∞
2. In each pass, relax all the edges.
i.e for edge (a,b) having weight w,
d[b] = min(d[b], d[a] + w)
3. Assuming no negative edge cycle, since there are n vertices, shortest path can only contain 'n-1' edges. Therefore, we will get our answer in at most 'n-1' passes.

What makes it better than dijkstra
Negative Edges!!
→ It will work for negative edges and negative cycles.
→ It can detect negative cycles as well.
*/
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int src, dest, weight;
};

void bellmanFord(vector<Edge> &edges, int V, int E, int source) {
    vector<int> distance(V, INT_MAX);
    distance[source] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i <= V - 1; ++i) {
        for (int j = 0; j < E; ++j) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
            }
        }
    }

    // Check for negative-weight cycles
    for (int i = 0; i < E; ++i) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int w = edges[i].weight;

        if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
            cout << "Graph contains negative weight cycle!" << endl;
            return;
        }
    }

    // Print the distances from the source vertex
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
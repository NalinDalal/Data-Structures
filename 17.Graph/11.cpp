/*
Floyd Warshall Algorithm
To find all pair shortest paths.
i.e. for every u,v in Graph G, find the shortest path from u to v.

PseudoCode:
for(int k=0;k<n;++k){
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            d[i][j]=min(d[i][j],d[i][k]+d[k][j])
        }
    }
}
*/
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

void floydWarshall(vector<vector<int> >& graph, int V) {
    // Initialize the distance matrix with the graph's adjacency matrix
    vector<vector<int> > dist(graph);

    // Iterate through intermediate vertices
    for (int k = 0; k < V; ++k) {
        // Iterate through source vertices
        for (int i = 0; i < V; ++i) {
            // Iterate through destination vertices
            for (int j = 0; j < V; ++j) {
                // If vertex k is on the shortest path from i to j,
                // update the distance from i to j through k
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print the shortest distances between all pairs of vertices
    cout << "Shortest distances between all pairs of vertices:" << endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF) {
                cout << "INF\t";
            } else {
                cout << dist[i][j] << "\t";
            }
        }
        cout << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    // Initialize the graph's adjacency matrix with INF for unconnected vertices
    vector<vector<int> > graph(V, vector<int>(V, INF));

    cout << "Enter the source, destination, and weight for each edge:" << endl;
    for (int i = 0; i < E; ++i) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph[src][dest] = weight;
    }

    // Run the Floyd-Warshall algorithm
    floydWarshall(graph, V);

    return 0;
}

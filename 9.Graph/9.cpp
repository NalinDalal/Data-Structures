//Dijkstra's algo
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int dest, weight;
};

class Graph {
public:
    int V; // Number of vertices
    vector<vector<Edge> > adjList;

    Graph(int vertices) : V(vertices), adjList(vertices) {}

    void addEdge(int src, int dest, int weight) {
        adjList[src].push_back({dest, weight});
        adjList[dest].push_back({src, weight}); // For undirected graph
    }

    void dijkstra(int source) {
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
        vector<int> distance(V, INT_MAX);

        pq.push({0, source});
        distance[source] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (const Edge& edge : adjList[u]) {
                int v = edge.dest;
                int weight = edge.weight;

                if (distance[v] > distance[u] + weight) {
                    distance[v] = distance[u] + weight;
                    pq.push({distance[v], v});
                }
            }
        }

        cout << "Vertex   Distance from Source" << endl;
        for (int i = 0; i < V; ++i) {
            cout << i << "\t\t" << distance[i] << endl;
        }
    }
};

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    Graph g(V);

    cout << "Enter the source, destination, and weight for each edge:" << endl;
    for (int i = 0; i < E; ++i) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        g.addEdge(src, dest, weight);
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    g.dijkstra(source);

    return 0;
}
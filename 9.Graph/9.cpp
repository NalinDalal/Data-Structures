// Dijkstra's algo
/*What is Dijkstra’s Algorithm?
Purpose:
Find the shortest path from a source node to all other nodes in a graph with
non-negative edge weights.

Why it works:
It always expands the node with the currently known shortest distance and uses a
priority queue (min-heap) to efficiently find the next node to explore.


*/
/*  Intuition
1. Start at the source node.

2. Initialize all distances as ∞ except the source (0).

3. Use a priority queue to always expand the node with the smallest distance.

4. Relax all its adjacent edges (i.e., update their distances if a shorter path
is found).

5. Repeat until all nodes are processed.

Preconditions
1. Works on graphs with non-negative weights only

2. Can be used on:
    - Directed or undirected graphs
    - Sparse graphs → efficient with min-heap

*/
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int dest, weight;
};

class Graph {
public:
  int V; // Number of vertices
  vector<vector<Edge>> adjList;

  Graph(int vertices) : V(vertices), adjList(vertices) {}

  void addEdge(int src, int dest, int weight) {
    adjList[src].push_back({dest, weight});
    adjList[dest].push_back({src, weight}); // For undirected graph
  }

  void dijkstra(int source) {
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;
    vector<int> distance(V, INT_MAX);

    pq.push({0, source});
    distance[source] = 0;

    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();

      for (const Edge &edge : adjList[u]) {
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

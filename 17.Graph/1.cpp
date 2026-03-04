// BFS (Breadth-First Search) on an undirected unweighted graph
// Input : n (nodes), m (edges), followed by m pairs of edges (1-indexed)
// Output: BFS traversal order starting from node 1
// Time  : O(V + E)   Space: O(V + E) for adjacency list + visited array

#include <iostream>
#include <queue>

using namespace std;

const int N = 1e5 + 2;   // max number of nodes (+2 as safety margin)
bool vis[N];              // visited array — tracks discovered vertices
vector<int> adj[N];       // adjacency list representation of the graph

int main() {
  // Initialise all vertices as unvisited
  for (int i = 0; i < N; i++) {
    vis[i] = 0;
  }

  int n, m; // n = number of vertices, m = number of edges
  cin >> n >> m;

  // Build the adjacency list (undirected graph → add edge both ways)
  int x, y;
  for (int i = 0; i < m; i++) {
    cin >> x >> y;

    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // --- BFS from source node 1 ---
  queue<int> q;     // FIFO queue holds the frontier (GRAY vertices)
  q.push(1);        // enqueue source
  vis[1] = true;    // mark source as discovered (GRAY)

  while (!q.empty()) {
    int node = q.front(); // dequeue the next vertex to process
    q.pop();
    cout << node << endl; // process / print the current vertex

    // Explore all neighbours of the current vertex
    vector<int>::iterator it;
    for (it = adj[node].begin(); it != adj[node].end(); it++) {
      if (!vis[*it]) {    // only enqueue undiscovered (WHITE) neighbours
        vis[*it] = 1;     // mark neighbour as discovered (GRAY)
        q.push(*it);      // add to queue for later processing
      }
    }
    // After scanning all neighbours, node is now fully explored (BLACK)
  }

  return 0;
}

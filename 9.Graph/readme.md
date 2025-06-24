# 📘 Graph Data Structure: Basics

### 🔹 Definition:

A **Graph** is a **non-linear data structure** consisting of:

- **Vertices (nodes)**
- **Edges (connections between nodes)**

It's used to represent relationships (networks, paths, connections).

---

## 🎯 Types of Graphs

| Property         | Description                           |
| ---------------- | ------------------------------------- |
| **Directed**     | Edges have direction (A → B)          |
| **Undirected**   | Edges don't have direction (A — B)    |
| **Weighted**     | Edges have weights (cost/time/etc.)   |
| **Unweighted**   | All edges are equal                   |
| **Cyclic**       | Contains at least one cycle           |
| **Acyclic**      | No cycles (e.g., trees, DAGs)         |
| **Connected**    | Every node can reach every other node |
| **Disconnected** | Some nodes can't reach others         |

---

## 📌 Representation of Graphs

### 1. **Adjacency Matrix**

- 2D matrix `G[n][n]`
- `G[i][j] = 1` if there's an edge from i → j
- Good for dense graphs

```cpp
int graph[4][4] = {
  {0, 1, 1, 0},
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {0, 1, 1, 0}
};
```

### 2. **Adjacency List**

- Array of vectors
- Efficient for sparse graphs

```cpp
vector<int> graph[5];
graph[0].push_back(1);
graph[1].push_back(0);
graph[0].push_back(2);
// etc.
```

---

## 🔍 Common Graph Algorithms

| Algorithm                 | Purpose                              |
| ------------------------- | ------------------------------------ |
| **DFS**                   | Depth-first traversal                |
| **BFS**                   | Breadth-first traversal              |
| **Dijkstra**              | Shortest path (non-negative weights) |
| **Bellman-Ford**          | Shortest path (can handle negatives) |
| **Floyd-Warshall**        | All-pairs shortest path              |
| **Kruskal’s / Prim’s**    | Minimum spanning tree (MST)          |
| **Topological Sort**      | Linear ordering (DAGs only)          |
| **Tarjan’s / Kosaraju’s** | Strongly connected components        |

---

## 🛠️ Example: Graph in C++

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int N = 5;
vector<int> graph[N];

void addEdge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u); // remove if directed
}

int main() {
    addEdge(0, 1);
    addEdge(0, 4);
    addEdge(1, 2);
    addEdge(1, 3);
    addEdge(1, 4);
    addEdge(2, 3);
    addEdge(3, 4);

    for (int i = 0; i < N; i++) {
        cout << "Node " << i << " -> ";
        for (int v : graph[i]) cout << v << " ";
        cout << endl;
    }

    return 0;
}
```

---

## 🧠 Why Graph Works?

Because it’s flexible to model:

- **Maps** and **GPS**
- **Social networks**
- **Internet links**
- **Dependency resolution**
- **Games**, **AI**, **Compilers** (AST → DAG)

---

## 🧾 Real-World Applications

- Google Maps (shortest path)
- Facebook (mutual friends, graph traversal)
- Git (topological sorting of commits)
- Networking (routing protocols)
- OS (deadlock detection → graph cycles)

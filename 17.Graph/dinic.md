# Dinic's Algorithm (Maximum Flow)

Dinic's algorithm finds maximum flow in O(V^2 * E) time, which is faster than Ford-Fulkerson's O(E * |f*|) and Edmonds-Karp's O(V * E^2). It uses BFS to build a level graph and DFS to find blocking flows.

---

## Key Concepts

1. **Level Graph**: BFS from source assigns levels. Only edges from level i to level i+1 are kept.
2. **Blocking Flow**: A flow where every source-to-sink path has at least one saturated edge.
3. **DFS with current arc optimization**: Each DFS finds augmenting paths efficiently.

---

## Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev;    // to node, index of reverse edge
    int cap, flow;  // capacity, current flow
};

vector<Edge> adj[MAXN];
int level[MAXN], ptr[MAXN];

void addEdge(int u, int v, int cap) {
    adj[u].push_back({v, (int)adj[v].size(), cap, 0});
    adj[v].push_back({u, (int)adj[u].size() - 1, 0, 0});
}

bool bfs(int s, int t) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& e : adj[u]) {
            if (level[e.to] == -1 && e.cap > e.flow) {
                level[e.to] = level[u] + 1;
                q.push(e.to);
            }
        }
    }
    return level[t] != -1;
}

int dfs(int u, int t, int pushed) {
    if (u == t || pushed == 0) return pushed;
    
    for (int& i = ptr[u]; i < (int)adj[u].size(); i++) {
        Edge& e = adj[u][i];
        if (level[e.to] != level[u] + 1) continue;
        
        int tr = dfs(e.to, t, min(pushed, e.cap - e.flow));
        if (tr == 0) continue;
        
        e.flow += tr;
        adj[e.to][e.rev].flow -= tr;
        return tr;
    }
    return 0;
}

int dinic(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        memset(ptr, 0, sizeof(ptr));
        while (int pushed = dfs(s, t, INT_MAX))
            flow += pushed;
    }
    return flow;
}
```

---

## How It Works

### Step 1: BFS — Build Level Graph

```
Source (s) = level 0
All nodes reachable from s via non-saturated edges get levels.
If sink (t) is not reachable → done.
```

### Step 2: DFS — Find Blocking Flow

```
Only follow edges from level i to level i+1.
Use "current arc" optimization: ptr[u] tracks which edges have been tried.
Find augmenting paths and push flow.
Repeat until no more augmenting paths in level graph.
```

### Step 3: Repeat

Go back to Step 1 with updated flows. Repeat until BFS can't reach sink.

---

## Current Arc Optimization

Instead of scanning all edges each time, maintain `ptr[u]` — the first edge not yet exhausted. Edges before `ptr[u]` have been fully explored and can be skipped.

This gives O(V^2 * E) total complexity.

---

## Complexity

| Component | Complexity |
|-----------|-----------|
| BFS (level graph) | O(E) |
| DFS (blocking flow) | O(V * E) |
| Number of phases | O(V) |
| **Total** | **O(V^2 * E)** |

For unit capacities: O(min(V^(2/3), E^(1/2)) * E)

---

## Example: Network Flow

```
    10     5
s -----> a -----> t
|        |        ^
| 3      | 8      | 7
v        v        |
b -----> c -------+
    6
```

```cpp
addEdge(s, a, 10);
addEdge(s, b, 3);
addEdge(a, t, 5);
addEdge(a, c, 8);
addEdge(b, c, 6);
addEdge(c, t, 7);

cout << dinic(s, t); // Maximum flow = 13
```

---

## Min-Cost Max-Flow Extension

To find maximum flow with minimum cost, add costs to edges and use Dijkstra (with potentials) instead of BFS.

```cpp
struct Edge {
    int to, rev, cap, flow, cost;
};

// Replace BFS with SPFA/Dijkstra for cost-based level graph
// Use potentials for non-negative edge costs
```

---

## Comparison with Other Max Flow Algorithms

| Algorithm | Time Complexity | Use Case |
|-----------|----------------|----------|
| Ford-Fulkerson | O(E * \|f*\|) | Integer capacities, small flow |
| Edmonds-Karp | O(V * E^2) | Simple implementation |
| **Dinic's** | **O(V^2 * E)** | **General purpose, fast** |
| Push-Relabel | O(V^2 * E) or O(V^3) | Very dense graphs |
| ISAP | O(V^2 * E) | Similar to Dinic's |

---

## Applications

| Problem | Reduction |
|---------|-----------|
| Maximum bipartite matching | Add source/sink, all edges cap 1 |
| Minimum vertex cover | Max flow min-cut on bipartite graph |
| Network connectivity | Max flow = min cut |
| Multiple-source multiple-sink | Add super-source, super-sink |
| Airline scheduling | Flow with capacity constraints |
| Image segmentation | Min-cut formulation |

---

## Bipartite Matching with Dinic's

```cpp
// Left nodes: 0..L-1, Right nodes: L..L+R-1
// Source: L+R, Sink: L+R+1

for (int i = 0; i < L; i++)
    addEdge(source, i, 1); // source to left
for (int j = 0; j < R; j++)
    addEdge(L + j, sink, 1); // right to sink
for (each edge (i,j) in bipartite graph)
    addEdge(i, L + j, 1); // left to right

int matching = dinic(source, sink);
```

---

## When to Use

| Scenario | Algorithm |
|----------|-----------|
| General max flow | Dinic's |
| Unit capacity graph | Dinic's (faster) |
| Very dense graph | Push-Relabel |
| Need min cost | Min-cost max-flow |
| Bipartite matching | Dinic's or Hopcroft-Karp |

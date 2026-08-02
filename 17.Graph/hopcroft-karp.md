# Hopcroft-Karp Algorithm

Finds maximum matching in a bipartite graph in O(E * sqrt(V)) time, faster than the O(V * E) augmenting path algorithm.

---

## Key Idea

Instead of finding one augmenting path at a time, find a **maximal set of shortest augmenting paths** in each phase using BFS + DFS.

Each phase increases the matching by the number of shortest augmenting paths found. After sqrt(V) phases, all augmenting paths are at least sqrt(V) long, so at most sqrt(V) phases are needed.

---

## Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;

vector<int> adj[MAXN];
int matchL[MAXN], matchR[MAXN], dist[MAXN];
int n, m; // left and right set sizes

bool bfs() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (matchL[i] == 0) {
            dist[i] = 0;
            q.push(i);
        } else {
            dist[i] = INT_MAX;
        }
    }
    dist[0] = INT_MAX;
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (dist[u] < dist[0]) {
            for (int v : adj[u]) {
                if (dist[matchR[v]] == INT_MAX) {
                    dist[matchR[v]] = dist[u] + 1;
                    q.push(matchR[v]);
                }
            }
        }
    }
    
    return dist[0] != INT_MAX;
}

bool dfs(int u) {
    if (u == 0) return true;
    
    for (int v : adj[u]) {
        if (dist[matchR[v]] == dist[u] + 1 && dfs(matchR[v])) {
            matchR[v] = u;
            matchL[u] = v;
            return true;
        }
    }
    
    dist[u] = INT_MAX;
    return false;
}

int hopcroftKarp() {
    memset(matchL, 0, sizeof(matchL));
    memset(matchR, 0, sizeof(matchR));
    
    int matching = 0;
    while (bfs()) {
        for (int i = 1; i <= n; i++) {
            if (matchL[i] == 0 && dfs(i))
                matching++;
        }
    }
    return matching;
}
```

---

## Usage

```cpp
int main() {
    int e;
    cin >> n >> m >> e;
    
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    
    cout << hopcroftKarp() << "\n";
}
```

---

## How It Works

### BFS Phase

Build a layered graph from unmatched left nodes:
- Layer 0: all unmatched left nodes
- Layer 1: neighbors of layer 0
- Layer 2: neighbors of matched right nodes from layer 1
- ... continue until reaching unmatched right nodes

### DFS Phase

Find augmenting paths using only edges between consecutive layers. Multiple DFS calls can find multiple augmenting paths simultaneously.

### Why O(E * sqrt(V))?

- Each BFS+DFS phase finds a maximal set of shortest augmenting paths
- After sqrt(V) phases, remaining augmenting paths have length >= sqrt(V)
- At most sqrt(V) such paths exist (each uses at least sqrt(V) edges)
- Each BFS = O(E), each DFS = O(E), total phases = O(sqrt(V))

---

## Comparison with Ford-Fulkerson on Bipartite

| Algorithm | Time | Notes |
|-----------|------|-------|
| DFS augmenting paths | O(V * E) | Simple |
| **Hopcroft-Karp** | **O(E * sqrt(V))** | **Faster** |
| Dinic's | O(V^2 * E) | General max flow |

For bipartite matching, Hopcroft-Karp is the standard choice.

---

## Example: Maximum Bipartite Matching

```
Left: {1, 2, 3}
Right: {A, B, C}
Edges: 1-A, 1-B, 2-B, 3-A, 3-C

Maximum matching: {1-A, 2-B, 3-C} → size 3
```

---

## Applications

### 1. Job Assignment

Each worker can do certain jobs. Find maximum jobs that can be assigned.

### 2. Maximum Independent Set in Bipartite Graph

By Konig's theorem: max independent set = |V| - max matching.

### 3. Minimum Vertex Cover in Bipartite Graph

Also by Konig's theorem: min vertex cover = max matching.

### 4. Stable Marriage Problem

Related but uses Gale-Shapley, not Hopcroft-Karp.

### 5. Chain Decomposition

Minimum path cover in DAG = |V| - max matching in bipartite graph.

---

## When to Use

| Problem | Algorithm |
|---------|-----------|
| Bipartite matching | Hopcroft-Karp |
| General max flow | Dinic's |
| Dense bipartite | Dinic's might be competitive |
| Small graph | Simple DFS augmenting paths |

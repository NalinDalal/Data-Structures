# A* Search Algorithm

A* is a pathfinding algorithm that combines Dijkstra's guarantees with heuristic guidance. It finds the shortest path from a start node to a goal node while exploring fewer nodes than Dijkstra's.

---

## Key Formula

```
f(n) = g(n) + h(n)
```

- **g(n)**: actual cost from start to node n
- **h(n)**: heuristic estimate from node n to goal
- **f(n)**: total estimated cost through n

A* expands the node with the **lowest f(n)**.

---

## Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii; // {f(n), node}

struct Node {
    int g, h;
    bool operator>(const Node& other) const {
        return g + h > other.g + other.h;
    }
};

int astar(vector<vector<pair<int,int>>>& adj, int start, int goal, 
          function<int(int,int)> heuristic) {
    
    vector<int> dist(adj.size(), INT_MAX);
    vector<int> parent(adj.size(), -1);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    
    dist[start] = 0;
    pq.push({heuristic(start, goal), start});
    
    while (!pq.empty()) {
        auto [f, u] = pq.top(); pq.pop();
        
        if (u == goal) return dist[goal];
        
        if (f > dist[u] + heuristic(u, goal)) continue;
        
        for (auto [v, w] : adj[u]) {
            int newDist = dist[u] + w;
            if (newDist < dist[v]) {
                dist[v] = newDist;
                parent[v] = u;
                pq.push({newDist + heuristic(v, goal), v});
            }
        }
    }
    
    return -1; // no path
}
```

---

## Common Heuristics

### Grid-Based (2D)

**Manhattan Distance** (4-directional movement):
```cpp
int heuristic(int a, int b) {
    int ax = a / cols, ay = a % cols;
    int bx = b / cols, by = b % cols;
    return abs(ax - bx) + abs(ay - by);
}
```

**Chebyshev Distance** (8-directional movement):
```cpp
int heuristic(int a, int b) {
    int ax = a / cols, ay = a % cols;
    int bx = b / cols, by = b % cols;
    return max(abs(ax - bx), abs(ay - by));
}
```

**Euclidean Distance** (any direction):
```cpp
int heuristic(int a, int b) {
    int ax = a / cols, ay = a % cols;
    int bx = b / cols, by = b % cols;
    return (int)sqrt((ax-bx)*(ax-bx) + (ay-by)*(ay-by));
}
```

### Graph-Based

**Straight-line distance** (precomputed from coordinates):
```cpp
int heuristic(int u, int v) {
    return (int)(1000 * sqrt(
        (x[u]-x[v])*(x[u]-x[v]) + (y[u]-y[v])*(y[u]-y[v])
    ));
}
```

---

## Admissibility & Consistency

### Admissible Heuristic

A heuristic h(n) is **admissible** if it never overestimates:
```
h(n) <= h*(n)  for all n
```
where h*(n) is the true shortest distance to goal.

**If h is admissible, A* finds the optimal path.**

### Consistent Heuristic

A heuristic h(n) is **consistent** if:
```
h(n) <= cost(n, n') + h(n')  for every edge (n, n')
```

**If h is consistent, A* is optimal and never re-opens closed nodes.**

---

## Comparison with Other Algorithms

| Algorithm | Heuristic | Optimal | Speed |
|-----------|-----------|---------|-------|
| Dijkstra's | h(n) = 0 | Yes | Slow (explores all directions) |
| Greedy Best-First | f(n) = h(n) | No | Fast (but may not find shortest) |
| **A*** | **f(n) = g(n) + h(n)** | **Yes (if h admissible)** | **Balanced** |

---

## Example: Grid Pathfinding

```cpp
int gridPath(vector<vector<int>>& grid, pair<int,int> start, pair<int,int> goal) {
    int rows = grid.size(), cols = grid[0].size();
    auto toIdx = [&](int r, int c) { return r * cols + c; };
    
    auto h = [&](int u, int v) {
        int ur = u / cols, uc = u % cols;
        int vr = v / cols, vc = v % cols;
        return abs(ur - vr) + abs(uc - vc);
    };
    
    vector<vector<pair<int,int>>> adj(rows * cols);
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1) continue; // wall
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] != 1)
                    adj[toIdx(r,c)].push_back({toIdx(nr,nc), 1});
            }
        }
    }
    
    int s = toIdx(start.first, start.second);
    int g = toIdx(goal.first, goal.second);
    
    vector<int> dist(rows * cols, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    
    dist[s] = 0;
    pq.push({h(s, g), s});
    
    while (!pq.empty()) {
        auto [f, u] = pq.top(); pq.pop();
        if (u == g) return dist[g];
        if (f > dist[u] + h(u, g)) continue;
        
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v] + h(v, g), v});
            }
        }
    }
    return -1;
}
```

---

## IDA* (Iterative Deepening A*)

Uses iterative deepening with f-cost limits. Uses O(d) space (d = solution depth).

```cpp
bool idaStar(int start, int goal, function<int(int)> h) {
    int threshold = h(start);
    
    function<bool(int, int, int)> dfs = [&](int u, int g, int threshold) {
        int f = g + h(u);
        if (f > threshold) return false;
        if (u == goal) return true;
        
        for (auto [v, w] : adj[u]) {
            if (dfs(v, g + w, threshold)) return true;
        }
        return false;
    };
    
    while (true) {
        if (dfs(start, 0, threshold)) return true;
        threshold++; // could also use next threshold from min f exceeded
    }
}
```

---

## Applications

| Application | Use Case |
|-------------|----------|
| Video games | NPC pathfinding |
| Robotics | Motion planning |
| Maps / GPS | Route finding |
| Puzzle solving | 8-puzzle, 15-puzzle |
| Network routing | Shortest path with estimates |

---

## When to Use

| Scenario | Algorithm |
|----------|-----------|
| Need shortest path + have heuristic | A* |
| No heuristic available | Dijkstra's |
| Memory constrained | IDA* |
| Large graphs, approximate OK | Greedy Best-First |
| Dynamic graphs | D* Lite |

# Disjoint Set Union (DSU) / Union-Find

A data structure that maintains a collection of disjoint (non-overlapping) sets. Supports two operations in near-constant time:
- **Find**: Which set does element x belong to?
- **Union**: Merge two sets into one.

---

## Core Operations

### MakeSet(x)

Create a new set containing only element x.

```cpp
void makeSet(int x) {
    parent[x] = x;
    rank[x] = 0;
}
```

### Find(x) — Amortized O(alpha(n))

Find the representative (root) of the set containing x.

```cpp
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]); // path compression
    return parent[x];
}
```

**Path Compression**: After finding the root, make every node on the path point directly to the root. This flattens the tree structure.

### Union(x, y) — Amortized O(alpha(n))

Merge the sets containing x and y.

```cpp
void unite(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry) return; // already in same set
    
    if (rank[rx] < rank[ry]) swap(rx, ry);
    parent[ry] = rx; // attach smaller tree under larger
    if (rank[rx] == rank[ry]) rank[rx]++;
}
```

**Union by Rank**: Attach the shorter tree under the root of the taller tree. This keeps the tree balanced.

---

## Complete Implementation

```cpp
struct DSU {
    vector<int> parent, rank;
    
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        
        if (rank[rx] < rank[ry]) swap(rx, ry);
        parent[ry] = rx;
        if (rank[rx] == rank[ry]) rank[rx]++;
        return true;
    }
    
    bool sameSet(int x, int y) {
        return find(x) == find(y);
    }
};
```

---

## Complexity Analysis

| Operation | Without Optimization | With Path Compression + Union by Rank |
|-----------|---------------------|---------------------------------------|
| Find      | O(n)                | O(alpha(n)) ≈ O(1)                   |
| Union     | O(n)                | O(alpha(n)) ≈ O(1)                   |

**alpha(n)** is the inverse Ackermann function — grows so slowly it's effectively constant for all practical n (alpha(10^80) ≤ 4).

---

## Union by Size (Alternative)

Instead of rank, track the size of each set.

```cpp
struct DSU {
    vector<int> parent, sz;
    
    DSU(int n) {
        parent.resize(n);
        sz.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        
        if (sz[rx] < sz[ry]) swap(rx, ry);
        parent[ry] = rx;
        sz[rx] += sz[ry];
        return true;
    }
};
```

---

## Applications

### 1. Connected Components

Count connected components in an undirected graph.

```cpp
int countComponents(int n, vector<vector<int>>& edges) {
    DSU dsu(n);
    for (auto& e : edges)
        dsu.unite(e[0], e[1]);
    
    set<int> components;
    for (int i = 0; i < n; i++)
        components.insert(dsu.find(i));
    return components.size();
}
```

### 2. Cycle Detection in Undirected Graph

Add edges one by one. If both endpoints are already in the same set, a cycle exists.

```cpp
bool hasCycle(int n, vector<vector<int>>& edges) {
    DSU dsu(n);
    for (auto& e : edges) {
        if (dsu.sameSet(e[0], e[1]))
            return true;
        dsu.unite(e[0], e[1]);
    }
    return false;
}
```

### 3. Kruskal's MST

Sort edges by weight. Add an edge only if its endpoints are in different sets (no cycle).

### 4. Percolation Problem

Determine if a system percolates (top connects to bottom) by unioning adjacent open cells.

### 5. Dynamic Connectivity

Process a sequence of edge additions and connectivity queries online.

---

## Path Splitting and Path Halving

Alternatives to full path compression that are simpler but slightly less effective in practice.

### Path Splitting

```cpp
int find(int x) {
    while (parent[x] != x) {
        int next = parent[x];
        parent[x] = parent[parent[x]]; // point to grandparent
        x = next;
    }
    return x;
}
```

### Path Halving

```cpp
int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]]; // halve the path
        x = parent[x];
    }
    return x;
}
```

---

## Weighted Union-Find (Potential DSU)

Maintains additional weights on edges to support relative distance queries.

```cpp
struct WeightedDSU {
    vector<int> parent, rank;
    vector<int> diff; // diff[x] = weight(x) - weight(parent[x])
    
    WeightedDSU(int n) : parent(n), rank(n, 0), diff(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    
    pair<int,int> find(int x) {
        if (parent[x] == x) return {x, 0};
        auto [root, w] = find(parent[x]);
        diff[x] += w;
        parent[x] = root;
        return {root, diff[x]};
    }
    
    // Returns the weight difference: weight(x) - weight(y)
    // Returns -1 if x and y are not connected
    int query(int x, int y) {
        auto [rx, wx] = find(x);
        auto [ry, wy] = find(y);
        if (rx != ry) return -1;
        return wx - wy;
    }
    
    // Set weight(x) - weight(y) = w
    bool unite(int x, int y, int w) {
        auto [rx, wx] = find(x);
        auto [ry, wy] = find(y);
        if (rx == ry) return (wx - wy) == w;
        
        w = w + wy - wx; // w for: weight(rx) - weight(ry)
        if (rank[rx] < rank[ry]) { swap(rx, ry); w = -w; }
        parent[ry] = rx;
        diff[ry] = w;
        if (rank[rx] == rank[ry]) rank[rx]++;
        return true;
    }
};
```

---

## When to Use

| Problem | Technique |
|---------|-----------|
| Connected components | Basic DSU |
| Cycle detection | Basic DSU |
| Kruskal's MST | Basic DSU |
| Relative distances | Weighted DSU |
| Dynamic connectivity | Basic DSU |
| Groups with constraints | Weighted DSU |

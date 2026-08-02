# Heavy-Light Decomposition (HLD)

A technique to decompose a tree into chains so that any path from root to a node crosses at most O(log n) chains. This allows answering path queries (sum, max, etc.) using a segment tree on the chains.

---

## Core Idea

For each node, classify edges as **heavy** or **light**:
- **Heavy edge**: connects to the child with the largest subtree
- **Light edge**: connects to all other children

Every root-to-node path has at most O(log n) light edges, so at most O(log n) chains.

---

## Definitions

```cpp
int sz[MAXN], parent[MAXN], depth[MAXN];
int head[MAXN], pos[MAXN]; // head of chain, position in base array
int curPos = 0;

// First DFS: compute subtree sizes, parent, depth
void dfs(int u, int p, int d) {
    parent[u] = p;
    depth[u] = d;
    sz[u] = 1;
    int maxSize = 0;
    for (auto [v, w] : adj[u]) {
        if (v == p) continue;
        dfs(v, u, d + 1);
        sz[u] += sz[v];
        if (sz[v] > maxSize) {
            maxSize = sz[v];
            heavy[u] = v; // heavy child
        }
    }
}

// Second DFS: decompose into chains
void decompose(int u, int h) {
    head[u] = h;
    pos[u] = curPos++;
    
    if (heavy[u] != -1)
        decompose(heavy[u], h); // same chain
    
    for (auto [v, w] : adj[u]) {
        if (v == parent[u] || v == heavy[u]) continue;
        decompose(v, v); // new chain starts at v
    }
}
```

---

## Path Query — O(log^2 n)

To query on path from u to v, jump up the tree following chains:

```cpp
int queryPath(int u, int v) {
    int result = 0; // identity for your operation
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) swap(u, v);
        // Query segment tree on [pos[head[u]], pos[u]]
        result = combine(result, segTree.query(pos[head[u]], pos[u]));
        u = parent[head[u]];
    }
    // Now on same chain
    if (depth[u] > depth[v]) swap(u, v);
    result = combine(result, segTree.query(pos[u], pos[v]));
    return result;
}
```

---

## Point Update — O(log n)

```cpp
void updateNode(int u, int val) {
    segTree.update(pos[u], val);
}
```

---

## LCA Using HLD — O(log n)

```cpp
int lca(int u, int v) {
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) swap(u, v);
        u = parent[head[u]];
    }
    return depth[u] < depth[v] ? u : v;
}
```

---

## Complete Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

vector<pair<int,int>> adj[MAXN];
int heavy[MAXN], parent[MAXN], depth[MAXN], sz[MAXN];
int head[MAXN], pos[MAXN], curPos = 0;
int val[MAXN]; // node values
int segTree[4 * MAXN];

void buildSeg(int node, int l, int r) {
    if (l == r) {
        segTree[node] = val[l];
        return;
    }
    int mid = (l + r) / 2;
    buildSeg(2*node, l, mid);
    buildSeg(2*node+1, mid+1, r);
    segTree[node] = segTree[2*node] + segTree[2*node+1]; // sum
}

void updateSeg(int node, int l, int r, int idx, int v) {
    if (l == r) { segTree[node] = v; return; }
    int mid = (l + r) / 2;
    if (idx <= mid) updateSeg(2*node, l, mid, idx, v);
    else updateSeg(2*node+1, mid+1, r, idx, v);
    segTree[node] = segTree[2*node] + segTree[2*node+1];
}

int querySeg(int node, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return segTree[node];
    int mid = (l + r) / 2;
    return querySeg(2*node, l, mid, ql, qr) +
           querySeg(2*node+1, mid+1, r, ql, qr);
}

void dfs(int u, int p, int d) {
    parent[u] = p; depth[u] = d; sz[u] = 1;
    heavy[u] = -1;
    int maxSize = 0;
    for (auto [v, w] : adj[u]) {
        if (v == p) continue;
        val[v] = w; // store edge weight on child
        dfs(v, u, d + 1);
        sz[u] += sz[v];
        if (sz[v] > maxSize) { maxSize = sz[v]; heavy[u] = v; }
    }
}

void decompose(int u, int h) {
    head[u] = h; pos[u] = curPos++;
    if (heavy[u] != -1) decompose(heavy[u], h);
    for (auto [v, w] : adj[u]) {
        if (v == parent[u] || v == heavy[u]) continue;
        decompose(v, v);
    }
}

int queryPath(int u, int v) {
    int res = 0;
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) swap(u, v);
        res += querySeg(1, 0, curPos-1, pos[head[u]], pos[u]);
        u = parent[head[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    res += querySeg(1, 0, curPos-1, pos[u]+1, pos[v]); // +1 to skip LCA
    return res;
}

void init(int root, int n) {
    dfs(root, -1, 0);
    decompose(root, root);
    buildSeg(1, 0, curPos-1);
}
```

---

## Complexity

| Operation | Time |
|-----------|------|
| Build | O(n) |
| Path query | O(log^2 n) |
| Point update | O(log n) |
| LCA | O(log n) |

---

## Applications

| Problem | How HLD helps |
|---------|---------------|
| Path sum/max on tree | Decompose path into O(log n) segments |
| Update node value | O(log n) point update |
| LCA queries | O(log n) via chain jumping |
| K-th node on path | Binary search on chains |
| Path with conditions | Combine segment tree with path queries |

---

## Comparison with Euler Tour

| Feature | HLD | Euler Tour |
|---------|-----|------------|
| Path queries | O(log^2 n) | O(log n) with careful setup |
| Subtree queries | O(log n) | O(log n) |
| Implementation | Moderate | Simpler |
| Flexibility | More general | Subtree-focused |

---

## When to Use

| Problem | Use HLD? |
|---------|----------|
| Path sum/max queries | Yes |
| Update node on path | Yes |
| Subtree sum | Use Euler Tour instead |
| LCA only | HLD works but simpler methods exist |
| Dynamic tree connectivity | No (use Link-Cut Tree) |

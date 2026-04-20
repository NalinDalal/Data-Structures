## Disjoint Set (Union-Find) — Deep Notes

Maintains a collection of **disjoint sets** with efficient merge and lookup.

---

## 1. Basic Idea

Each element belongs to a set identified by a **representative (root)**

```
parent[x] = representative of x
```

Example from whiteboard:

```
p = [2, 2, 3, 2, 3, 5, 8, 8]
     1  2  3  4  5  6  7  8
```

→ elements with same root (via following parents) belong to the same set  
→ e.g. p[1]=2, p[4]=2, p[2]=2 → {1, 2, 4} are in the same set  
→ p[8]=8 → 8 is its own root

---

## 2. Core Operations

### find(x)

Returns the **representative (root)** of the set containing x.

Naive (iterative):

```
find(x):
    while p(x) ≠ x:
        x = p(x)
    return x
```

Complexity: O(h) where h = height of tree

---

### union(x, y)

Merges the sets containing x and y.

```
union(x, y):
    x = find(x)
    y = find(y)
    if r[x] > r[y]:
        swap(x, y)
    p[x] = y
    if r[x] == r[y]:
        r[y]++
```

---

### Complexity (Naive — no optimizations)

| Operation | Cost   |
|-----------|--------|
| find      | O(n)   |
| union     | O(n)   |
| Total     | O(n²)  |

---

## 3. Optimization 1 — Rank Heuristic (Union by Rank)

**Rank** = upper bound on the height of a subtree rooted at x.

### Rule:
Always attach the **shorter tree under the taller tree**.

```
if r(x) < r(y):
    p(x) = y           // x goes under y, y stays root
    r(y) unchanged      // r(y) >= r(x)+1 already

if r(x) == r(y):
    p(x) = y
    r(y)++              // height increases by 1
```

### Visual (from whiteboard):

```
Before:         After (r(x) = r(y)):
  x    y    →       y        (r(y) becomes r(y)+1)
 /\   /\           /|\
...  x  ...
```

### Why it works:

A tree of rank r must have **at least 2^r nodes**  
→ max rank = log n  
→ max tree height = O(log n)

### Complexity with Rank only:

| Operation | Cost      |
|-----------|-----------|
| find      | O(log n)  |
| union     | O(log n)  |

---

## 4. Optimization 2 — Path Compression

Every time we run `find(x)`, we **flatten the path** by pointing all visited nodes **directly to the root**.

### Idea (from whiteboard diagram):

```
Before find(x):           After find(x):
    root                      root
     |                      / | | \
     a                     a  b  c  x
     |
     b
     |
     c
     |
     x
```

All nodes on the path now point directly to root — future finds are O(1).

### Implementation (two-pass):

```
find(x):
    y = x
    while p(y) ≠ y:        // pass 1: find root
        y = p(y)
    while p(x) ≠ x:        // pass 2: compress path
        z = p(x)
        p(x) = y            // point directly to root
        x = z
    return x                // y is the root (but return x which == root after loop)
```

> Note: the whiteboard uses `return x` but at loop exit, x = root since p(x) = x.

### Amortized Complexity (Path Compression alone):

```
T̃(find) = O(log n)   amortized
```

---

## 5. Combined: Path Compression + Rank Heuristic

This is the **standard DSU** used in competitive programming and interviews.

```cpp
// Find with path compression (recursive)
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

// Union by rank
void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (rank[a] < rank[b]) swap(a, b);
    parent[b] = a;
    if (rank[a] == rank[b]) rank[a]++;
}
```

### Final Complexity:

```
T̃(find) = O(α(m, n))
```

Where:
- α = inverse Ackermann function
- m = number of find operations
- n = size of the tree

### Properties of α(m, n):

| Condition           | Value of α     |
|---------------------|----------------|
| n↑, m fixed         | α↑ (grows)     |
| m↑, n fixed         | α↓ (shrinks)   |
| m = n               | α(n,n) = lg*n  |

`lg*n` = iterated logarithm ≈ 5 for all practical n  
→ α(m,n) is **effectively constant** in practice

---

## 6. Complexity Summary Table

| Strategy                        | find       | union      | Total (n ops) |
|---------------------------------|------------|------------|---------------|
| Naive                           | O(n)       | O(n)       | O(n²)         |
| Union by Rank only              | O(log n)   | O(log n)   | O(n log n)    |
| Path Compression only           | O(log n) ã | O(log n) ã | O(n log n)    |
| Path Compression + Rank         | O(α(n)) ã  | O(α(n)) ã  | O(n · α(n))   |

ã = amortized

---

## 7. Intuition Behind Each Optimization

### Why Rank Heuristic helps:
- Prevents tall, chain-like trees
- Guarantees height ≤ log n
- Rank only increases when two equal-rank trees merge

### Why Path Compression helps:
- Doesn't change the tree's correctness
- Future finds on the same path become O(1)
- Amortizes the cost over sequences of operations

### Why Together they're near O(1):
- Rank keeps trees balanced → compression has less to do
- Compression flattens aggressively → future operations are trivially fast
- The synergy gives the α(n) bound — one of the best in CS theory

---

## 8. Parent Array Walkthrough (from whiteboard)

```
Index:  1  2  3  4  5  6  7  8
p[]:    2  2  3  2  3  5  8  8
```

Tracing sets:
- find(1): 1→2→2 ✓  root = 2
- find(4): 4→2→2 ✓  root = 2
- find(6): 6→5→3→3 ✓  root = 3
- find(7): 7→8→8 ✓  root = 8

Sets: {1,2,4}, {3,5,6}, {7,8}  
Matches the Venn diagram on the left of the whiteboard.

---

## 9. Key Observations (Interview / Exam)

- Rank ≠ size — rank is an upper bound on height, not the count of nodes
- Path compression modifies `parent[]` but **never changes rank**
- Union operates on **roots only** — always call find() first
- After path compression, ranks may be stale but remain valid upper bounds
- α(n) is so slow it's ≤ 4 for n < 10^(10^(10^(10^...))) — truly constant for real inputs
- DSU with only path compression (no rank) is O(log n) amortized, not α(n)

---

## 10. Use Cases

| Problem                        | How DSU helps                              |
|--------------------------------|--------------------------------------------|
| Cycle detection (undirected)   | Union edges; cycle if find(u) == find(v)   |
| Kruskal's MST                  | Add edge only if endpoints in diff sets    |
| Connected components           | Union all edges; count distinct roots      |
| Dynamic connectivity           | Online union-find queries                  |
| Percolation (grid problems)    | Union adjacent open cells                  |
| Redundant connection (LeetCode 684) | Classic DSU application             |

---

## 11. Template (Copy-Paste Ready)

```cpp
struct DSU {
    vector<int> parent, rank_;

    DSU(int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);  // path compression
        return parent[x];
    }

    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;         // already same set
        if (rank_[a] < rank_[b]) swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
        return true;
    }

    bool connected(int a, int b) {
        return find(a) == find(b);
    }
};
```

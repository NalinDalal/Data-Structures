
## 1. Breadth First Search
expands the frontier between discovered and undiscovered vertices uniformly across the breadth of the frontier.

Given a graph G= (V, E) and a distinguished source vertex s, breadth-first
search systematically explores the edges of G to “discover” every vertex that is
reachable from s.

the algorithm discovers all vertices at distance k from s before discovering any
vertices at distance k +1.

the adjacency list of an already discovered vertex u, the vertex v
and the edge (u, v) are added to the tree. We say that u is the predecessor or parent
of v in the breadth-first tree.

```
BFS(G,s):
1   for each vertex u ∈V [G]−{s}
2       do color[u] ←WHITE
3           d[u] ←∞
4           π [u] ←NIL
5   color[s] ←GRAY
6   d[s] ←0
7   π [s] ←NIL
8   Q ←∅
9   ENQUEUE(Q, s)
10  while Q ̸=∅
11      do u ←DEQUEUE(Q)
12          for each v ∈Adj[u]
13              do if color[v]=WHITE
14                  then color[v] ←GRAY
15                      d[v] ←d[u] +1
16                      π [v] ←u
17                      ENQUEUE(Q, v)
18          color[u] ←BLACK
```

---

## 2. Analysis

- After initialization, no vertex is ever whitened, so the test in line 13 ensures that each vertex is enqueued at most once, and hence dequeued at most once.
- The operations of enqueuing and dequeuing take O(1) time, so the total time devoted to queue operations is **O(V)**.
- The adjacency list of each vertex is scanned only when the vertex is dequeued. Since the sum of the lengths of all the adjacency lists is **Θ(E)**, the total time spent scanning adjacency lists is **O(E)**.
- The overhead for initialization is **O(V)**.
- **Total running time of BFS: O(V + E)** — linear in the size of the adjacency-list representation of G.

---

## 3. Shortest Paths

BFS finds the **shortest-path distance** δ(s, v) from source s to every reachable vertex v, where δ(s, v) is the minimum number of edges in any path from s to v. If no path exists, δ(s, v) = ∞.

**Lemma 22.1:** For any edge (u, v) ∈ E,
> δ(s, v) ≤ δ(s, u) + 1

**Lemma 22.2:** Upon termination of BFS from source s, for each vertex v ∈ V, d[v] ≥ δ(s, v).

**Lemma 22.3 (Monotonicity of queue):** During execution of BFS, if the queue Q contains vertices ⟨v₁, v₂, …, vᵣ⟩ (v₁ = head, vᵣ = tail), then:
- d[vᵣ] ≤ d[v₁] + 1
- d[vᵢ] ≤ d[vᵢ₊₁] for i = 1, 2, …, r − 1

This means the d values in the queue are monotonically non-decreasing, and there are at most two distinct d values at any time.

**Corollary 22.4:** If vᵢ is enqueued before vⱼ, then d[vᵢ] ≤ d[vⱼ] at the time vⱼ is enqueued.

**Theorem 22.5 (Correctness of BFS):**
Let G = (V, E) be a directed or undirected graph, and suppose BFS is run from source vertex s ∈ V. Then:
1. BFS discovers every vertex v ∈ V reachable from s.
2. Upon termination, d[v] = δ(s, v) for all v ∈ V.
3. For any vertex v ≠ s reachable from s, one of the shortest paths from s to v is a shortest path from s to π[v] followed by the edge (π[v], v).

---

## 4. Breadth-First Trees

BFS builds a **breadth-first tree** as it searches. The tree is represented by the π field in each vertex.

**Predecessor subgraph** Gπ = (Vπ, Eπ), where:
- Vπ = { v ∈ V : π[v] ≠ NIL } ∪ {s}
- Eπ = { (π[v], v) : v ∈ Vπ − {s} }

Gπ is a **breadth-first tree** if:
- Vπ consists of the vertices reachable from s
- For all v ∈ Vπ, there is a unique simple path from s to v in Gπ that is also a shortest path from s to v in G
- |Eπ| = |Vπ| − 1

The edges in Eπ are called **tree edges**.

**Lemma 22.6:** When applied to a directed or undirected graph G = (V, E), procedure BFS constructs π so that Gπ is a breadth-first tree.

---

## 5. Printing Shortest Path

```
PRINT-PATH(G, s, v):
1   if v = s
2       then print s
3   else if π[v] = NIL
4       then print "no path from" s "to" v "exists"
5   else PRINT-PATH(G, s, π[v])
6       print v
```

Runs in time linear in the number of vertices in the path (each recursive call is one vertex shorter).

---

## 6. C++ Implementation (Adjacency List)

```cpp
#include <bits/stdc++.h>
using namespace std;

// BFS from source node x
// adj[i] = adjacency list of node i
// N = number of nodes

queue<int> q;
bool visited[N];
int distance[N];

visited[x] = true;
distance[x] = 0;
q.push(x);
while (!q.empty()) {
    int s = q.front(); q.pop();
    // process node s
    for (auto u : adj[s]) {
        if (visited[u]) continue;
        visited[u] = true;
        distance[u] = distance[s] + 1;
        q.push(u);
    }
}
```

### Alternative (using distance as visited marker — Halim style)

```cpp
// inside int main() — no recursion
vi d(V, INF);           // distance from source s to all vertices
d[s] = 0;               // distance from source s to s is 0
queue<int> q;
q.push(s);              // start from source

while (!q.empty()) {
    int u = q.front(); q.pop();         // queue: layer by layer!
    for (int j = 0; j < (int)AdjList[u].size(); j++) {
        ii v = AdjList[u][j];           // for each neighbor of u
        if (d[v.first] == INF) {        // if v.first is unvisited + reachable
            d[v.first] = d[u] + 1;      // make d[v.first] != INF to flag it
            q.push(v.first);            // enqueue v.first for the next iteration
        }
    }
}
```

---

## 7. Example Walkthrough

Consider the graph with 6 nodes:
```
1 — 2 — 3
|   |   |
4   5 — 6
```

BFS starting at node 1:
1. Visit node 1 (distance 0). Enqueue neighbors: 2, 4
2. Visit node 2 (distance 1). Enqueue neighbor: 3, 5
3. Visit node 4 (distance 1). No new neighbors.
4. Visit node 3 (distance 2). Enqueue neighbor: 6
5. Visit node 5 (distance 2). No new unvisited neighbors.
6. Visit node 6 (distance 3). Done.

| Node | Distance |
|------|----------|
| 1    | 0        |
| 2    | 1        |
| 3    | 2        |
| 4    | 1        |
| 5    | 2        |
| 6    | 3        |

---

## 8. Key Takeaways

- BFS visits nodes **level by level** (increasing distance from source).
- Uses a **queue** (FIFO) data structure.
- Computes **shortest paths** on unweighted graphs (both directed and undirected).
- Time complexity: **O(V + E)** with adjacency list, **O(V²)** with adjacency matrix.
- Produces a **breadth-first tree** via predecessor pointers π.
- Three-color scheme (WHITE → GRAY → BLACK) tracks vertex states:
  - **WHITE**: undiscovered
  - **GRAY**: discovered, in queue (frontier)
  - **BLACK**: fully processed (all neighbors explored)
- BFS is the archetype for Prim's MST algorithm (§23.2) and Dijkstra's SSSP algorithm (§24.3).
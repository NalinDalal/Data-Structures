# Graph

A **Graph** is a **non-linear data structure** consisting of:

- **Vertices (nodes)**
- **Edges (connections between nodes)**

It's used to represent relationships (networks, paths, connections).

---

## Types of Graphs

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

## Representation of Graphs

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

since it is a undirected graph hence A=AT

if G=(V, E) is a weighted
graph with edge-weight function w, the weight w(u, v) of the edge (u, v) ∈ E is
simply stored as the entry in row u and column v of the adjacency matrix.

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

for graph G= (V, E) consists of an array Adj of |V |lists, one for each vertex in V.
For each u ∈ V , the adjacency list Adj[u] contains all the vertices v such that there is an edge (u, v) ∈ E. 
That is, Adj[u] consists of all the vertices adjacent to u in G.

If G is a directed graph, the sum of the lengths of all the adjacency lists is |E|,
since an edge of the form (u, v) is represented by having v appear in Adj[u].

If G is an undirected graph, the sum of the lengths of all the adjacency lists is 2 |E|, since if (u, v) is an undirected edge, then u appears in v’s adjacency list and vice versa.

amount of memory it requires is O(V +E).

---

# Common Graph Algorithms

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

The operations of enqueuing and dequeuing take O(1) time, so the total time devoted to queue operations is O(V ).
sum of the lengths
of all the adjacency lists is Omega(E), the total time spent in scanning adjacency lists is
O(E).
overhead for initialization is O(V ), and thus the total running time of
BFS is O(V +E).

---

# Complete Graph Study Plan (19 Days)

> **You will read EVERYTHING.** "Primary" = read first for clarity. "Also Read" = read same day, after primary.

## Phase 1: Foundations (Days 1-4)

| Day | Topic | Primary Read | Code | Also Read |
|-----|-------|-------------|------|-----------|
| 1 | Graph terminology & representation | CP Handbook §11 (pg 109-116) | — | Halim §4.1 (pg 121), Algorithms ch5 |
| 2 | BFS + SSSP on unweighted graphs | CP Handbook §12.2 (pg 119-121) | `1.cpp` | Halim §4.2.2 (pg 123), Halim §4.4.1-4.4.2 (pg 146-148) |
| 3 | DFS | CP Handbook §12.1 (pg 117-119) | `2.cpp` | Halim §4.2.1 (pg 122), Algo Advanced §2 (pg 562-569), Algorithms ch6 |
| 4 | DFS apps: cycle detection, edge properties | CP Handbook §12.3 + §16.4 (pg 121, 155) | `3.cpp`, `4.cpp` | Halim §4.2.7 (pg 128-130) |

## Phase 2: Ordering & Connectivity (Days 5-7)

| Day | Topic | Primary Read | Code | Also Read |
|-----|-------|-------------|------|-----------|
| 5 | Topological sort + DP on DAGs | CP Handbook §16.1-16.2 (pg 149-153) | `8.cpp` | Halim §4.2.5 (pg 126-128), Algo Advanced §3 (pg 571-573) |
| 6 | Connected components, flood fill, bipartite check | Halim §4.2.3-4.2.6 (pg 125-128) | — | CP Handbook §12.3 (pg 121) |
| 7 | Articulation points & bridges | Halim §4.2.8 (pg 130-133) | — | Algorithms ch6 |

## Phase 3: Tree Algorithms (Day 8) ← was missing before

| Day | Topic | Primary Read | Code | Also Read |
|-----|-------|-------------|------|-----------|
| 8 | Tree traversal, diameter, all longest paths, binary trees | CP Handbook §14 (pg 133-139) | — | Halim §4.7.2 (pg 178) |

## Phase 4: MST (Days 9-10)

| Day | Topic | Primary Read | Code | Also Read |
|-----|-------|-------------|------|-----------|
| 9 | Union-Find + Kruskal's algorithm | CP Handbook §15.1-15.2 (pg 141-147) | `5.cpp`, `6.cpp` | Halim §4.3.1-4.3.2 (pg 138-139), Algo Advanced §4 (pg 589-595), Algorithms ch7 |
| 10 | Prim's algorithm + MST applications | CP Handbook §15.3 (pg 147-148) | `7.cpp` | Halim §4.3.3-4.3.4 (pg 139-141) |

## Phase 5: Shortest Paths (Days 11-13)

| Day | Topic | Primary Read | Code | Also Read |
|-----|-------|-------------|------|-----------|
| 11 | Dijkstra (SSSP, non-negative weights) | CP Handbook §13.2 (pg 126-129) | `9.cpp` | Halim §4.4.3 (pg 148-151), Algo Advanced §5 (pg 602-627), Algorithms ch8 |
| 12 | Bellman-Ford (SSSP, negative weights) | CP Handbook §13.1 (pg 123-126) | `10.cpp` | Halim §4.4.4 (pg 151-155) |
| 13 | Floyd-Warshall (APSP) + APSP applications | CP Handbook §13.3 (pg 129-132) | `11.cpp` | Halim §4.5.1-4.5.3 (pg 155-158), Algo Advanced §6 (pg 642-661), Algorithms ch9 |

## Phase 6: SCC & Directed Graphs (Days 14-15)

| Day | Topic | Primary Read | Code | Also Read |
|-----|-------|-------------|------|-----------|
| 14 | Kosaraju's algorithm (SCC) | CP Handbook §17.1 (pg 157-160) | — | Halim §4.2.9 (pg 133-137) |
| 15 | 2SAT + successor paths + DP on directed graphs | CP Handbook §16.3 + §17.2 (pg 154-155, 160-162) | — | Halim §4.7.1 (pg 171-178) |

## Phase 7: Network Flow (Days 16-17)

| Day | Topic | Primary Read | Code | Also Read |
|-----|-------|-------------|------|-----------|
| 16 | Ford-Fulkerson & Edmonds-Karp | CP Handbook §20.1 (pg 181-186) | — | Halim §4.6.1-4.6.3 (pg 163-166), Algo Advanced §7 (pg 665-718), Algorithms ch10 |
| 17 | Flow apps: disjoint paths, matchings, path covers, modeling | CP Handbook §20.2-20.4 (pg 186-190) | — | Halim §4.6.4-4.6.6 (pg 166-168), Algorithms ch11 |

## Phase 8: Tree Queries & Special Graphs (Days 18-19)

| Day | Topic | Primary Read | Code | Also Read |
|-----|-------|-------------|------|-----------|
| 18 | Tree queries: ancestors, subtrees, LCA, offline algorithms | CP Handbook §18 (pg 163-172) | — | Halim §4.7.2 (pg 178) |
| 19 | Eulerian paths, Hamiltonian paths, De Bruijn, Knight's tours, bipartite | CP Handbook §19 (pg 173-180) | — | Halim §4.7.3-4.7.4 (pg 179-180) |

---

### How to use this plan
1. **Each day:** read "Primary Read" first → then read everything in "Also Read" → code the file
2. **If no code file listed:** implement the algorithm yourself in a new `.cpp` file and add it here
3. **Every section from all 4 books is assigned to a day — nothing is skipped**
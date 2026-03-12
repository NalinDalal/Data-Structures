# All-Pairs Shortest Paths (Advanced)

## Introduction

In the previous chapter, we discussed several algorithms to find the shortest paths from a single source vertex $s$ to every other vertex of the graph, by constructing a shortest path tree rooted at $s$. The shortest path tree specifies two pieces of information for each node $v$ in the graph:
- $\text{dist}(v)$ is the length of the shortest path from $s$ to $v$;
- $\text{pred}(v)$ is the second-to-last vertex in the shortest path from $s$ to $v$.

In this chapter, we consider the more general all pairs shortest path problem, which asks for the shortest path from every possible source to every possible destination. For every pair of vertices $u$ and $v$, we want to compute the following information:
- $\text{dist}(u, v)$ is the length of the shortest path from $u$ to $v$;
- $\text{pred}(u, v)$ is the second-to-last vertex on the shortest path from $u$ to $v$.

These intuitive definitions exclude a few boundary cases:
- If there is no path from $u$ to $v$, then $\text{dist}(u, v) = \infty$ and $\text{pred}(u, v) = \text{NULL}$.
- If there is a negative cycle between $u$ and $v$, then $\text{dist}(u, v) = -\infty$ and $\text{pred}(u, v) = \text{NULL}$.
- If $u$ does not lie on a negative cycle, then $\text{dist}(u, u) = 0$ and $\text{pred}(u, u) = \text{NULL}$.

The desired output of the all-pairs shortest path problem is a pair of $V \times V$ arrays, one storing all $V^2$ shortest-path distances, the other storing all $V^2$ predecessors. The predecessor array, from which we can compute the actual shortest paths, can be computed with only minor modifications.

## Lots of Single Sources

The most obvious solution to the all-pairs shortest path problem is to run a single-source shortest path algorithm $V$ times, once for each possible source vertex. Specifically, to fill the one-dimensional subarray $\text{dist}[s, \cdot]$, we invoke a single-source algorithm starting at the source vertex $s$.

**ObviousAPSP(V, E, w):**
for every vertex $s$
    $\text{dist}[s, \cdot] \leftarrow \text{SSSP}(V, E, w, s)$

The running time depends on which single-source shortest path algorithm we use:
- If the edges are unweighted, BFS gives $O(VE) = O(V^3)$.
- If the graph is acyclic, scanning in topological order gives $O(VE) = O(V^3)$.
- If all edge weights are non-negative, Dijkstra's gives $O(VE \log V) = O(V^3 \log V)$.
- If the most general setting, Bellman-Ford gives $O(V^2E) = O(V^4)$.

## Reweighting

Negative edges slow us down significantly. One subtle method for reweighting edges that preserves shortest paths is Johnson's algorithm. It computes a cost $\pi(v)$ for each vertex, so that the new weight of every edge is non-negative, and then computes shortest paths with respect to the new weights using Dijkstra's algorithm.

The new weight function is:
$w'(u \to v) = \pi(u) + w(u \to v) - \pi(v)$

## Johnson’s Algorithm

Johnson’s all-pairs shortest path algorithm computes a cost $\pi(v)$ for each vertex, so that the new weight of every edge is non-negative, and then computes shortest paths with respect to the new weights using Dijkstra’s algorithm.

Pseudocode:

**JohnsonAPSP(V, E, w):**
- Add an artificial source $s$
- for every vertex $v$, add a new edge $s \to v$ with $w(s \to v) = 0$
- $\text{dist}[s, \cdot] \leftarrow \text{BellmanFord}(V, E, w, s)$
- if BellmanFord found a negative cycle, fail gracefully
- for every edge $u \to v \in E$, $w'(u \to v) \leftarrow \text{dist}[s, u] + w(u \to v) - \text{dist}[s, v]$
- for every vertex $u$, $\text{dist}'[u, \cdot] \leftarrow \text{Dijkstra}(V, E, w', u)$
- for every vertex $u$, for every vertex $v$, $\text{dist}[u, v] \leftarrow \text{dist}'[u, v] - \text{dist}[s, u] + \text{dist}[s, v]$

## Dynamic Programming

For dense graphs, the dynamic programming approach is both simpler and (slightly) faster than Johnson’s algorithm. Assume the input graph contains no negative cycles.

The recurrence:

$$
\text{dist}(u, v) = \begin{cases}
0 & \text{if } u = v \\
\min_{x \to v}(\text{dist}(u, x) + w(x \to v)) & \text{otherwise}
\end{cases}
$$

This only works for DAGs. For general graphs, introduce $\ell$ as the max number of edges:

$$
\text{dist}(u, v, \ell) = \begin{cases}
0 & \ell = 0 \text{ and } u = v \\
\infty & \ell = 0 \text{ and } u \neq v \\
\min\left\{\text{dist}(u, v, \ell-1), \min_{x \to v}(\text{dist}(u, x, \ell-1) + w(x \to v))\right\} & \text{otherwise}
\end{cases}
$$

Pseudocode:

**ShimbelAPSP(V, E, w):**
for all vertices $u$
    for all vertices $v$
        if $u = v$ $\text{dist}[u, v, 0] \leftarrow 0$
        else $\text{dist}[u, v, 0] \leftarrow \infty$
for $\ell \leftarrow 1$ to $V-1$
    for all vertices $u$
        for all vertices $v$
            $\text{dist}[u, v, \ell] \leftarrow \text{dist}[u, v, \ell-1]$
            for all edges $x \to v$
                if $\text{dist}[u, v, \ell] > \text{dist}[u, x, \ell-1] + w(x \to v)$
                    $\text{dist}[u, v, \ell] \leftarrow \text{dist}[u, x, \ell-1] + w(x \to v)$

**AllPairsBellmanFord(V, E, w):**
for all vertices $u$
    for all vertices $v$
        if $u = v$ $\text{dist}[u, v] \leftarrow 0$
        else $\text{dist}[u, v] \leftarrow \infty$
for $\ell \leftarrow 1$ to $V-1$
    for all vertices $u$
        for all edges $x \to v$
            if $\text{dist}[u, v] > \text{dist}[u, x] + w(x \to v)$
                $\text{dist}[u, v] \leftarrow \text{dist}[u, x] + w(x \to v)$

## Divide and Conquer

Bellman’s recurrence breaks the shortest path into a slightly shorter path and a single edge. Instead, break the shortest paths at the middle vertex:

$$
\text{dist}(u, v, \ell) = \begin{cases}
w(u \to v) & \ell = 1 \\
\min_x(\text{dist}(u, x, \ell/2) + \text{dist}(x, v, \ell/2)) & \text{otherwise}
\end{cases}
$$

Pseudocode:

**FischerMeyerAPSP(V, E, w):**
for all vertices $u$
    for all vertices $v$
        $\text{dist}[u, v, 0] \leftarrow w(u \to v)$
for $i \leftarrow 1$ to $\lceil \log V \rceil$
    for all vertices $u$
        for all vertices $v$
            $\text{dist}[u, v, i] \leftarrow \infty$
            for all vertices $x$
                if $\text{dist}[u, v, i] > \text{dist}[u, x, i-1] + \text{dist}[x, v, i-1]$
                    $\text{dist}[u, v, i] \leftarrow \text{dist}[u, x, i-1] + \text{dist}[x, v, i-1]$

**LeyzorekAPSP(V, E, w):**
for all vertices $u$
    for all vertices $v$
        $\text{dist}[u, v] \leftarrow w(u \to v)$
for $i \leftarrow 1$ to $\lceil \log V \rceil$
    for all vertices $u$
        for all vertices $v$
            for all vertices $x$
                if $\text{dist}[u, v] > \text{dist}[u, x] + \text{dist}[x, v]$
                    $\text{dist}[u, v] \leftarrow \text{dist}[u, x] + \text{dist}[x, v]$

## Funny Matrix Multiplication

There is a close connection between computing shortest paths in a directed graph and computing powers of a square matrix. The shortest path inner loop is sometimes referred to as “min-plus” or “distance” or “funny” matrix multiplication.

**MatrixSquare(A):**
for $i \leftarrow 1$ to $n$
    for $j \leftarrow 1$ to $n$
        $A'[i, j] \leftarrow 0$
        for $k \leftarrow 1$ to $n$
            $A'[i, j] \leftarrow A'[i, j] + A[i, k] \cdot A[k, j]$

**FischerMeyerInnerLoop(D):**
for all vertices $u$
    for all vertices $v$
        $D'[u, v] \leftarrow \infty$
        for all vertices $x$
            $D'[u, v] \leftarrow \min\{D'[u, v], D[u, x] + D[x, v]\}$

## (Kleene-Roy-)Floyd-Warshall(-Ingerman)

A different formulation of shortest paths that removes the logarithmic factor was proposed by Floyd, Roy, and Ingerman. Instead of considering paths with a limited number of edges, they considered paths that can pass through only certain vertices.

Let $\pi(u, v, r)$ be the shortest path (if any) from $u$ to $v$ that passes through only vertices numbered at most $r$.

- The path $\pi(u, v, 0)$ can’t pass through any intermediate vertices, so it must be the edge (if any) from $u$ to $v$.
- For any integer $r > 0$, either $\pi(u, v, r)$ passes through vertex $r$ or it doesn’t.
    - If $\pi(u, v, r)$ passes through vertex $r$, it consists of a subpath from $u$ to $r$, followed by a subpath from $r$ to $v$. Both subpaths pass through only vertices numbered at most $r-1$.
    - Otherwise, $\pi(u, v, r) = \pi(u, v, r-1)$.

Let $\text{dist}(u, v, r)$ denote the length of the path $\pi(u, v, r)$. The recursive structure immediately implies:

$$
\text{dist}(u, v, r) = \begin{cases}
w(u \to v) & r = 0 \\
\min\left\{\text{dist}(u, v, r-1), \text{dist}(u, r, r-1) + \text{dist}(r, v, r-1)\right\} & \text{otherwise}
\end{cases}
$$

Pseudocode:

**KleeneAPSP(V, E, w):**
for all vertices $u$
    for all vertices $v$
        $\text{dist}[u, v, 0] \leftarrow w(u \to v)$
for $r \leftarrow 1$ to $V$
    for all vertices $u$
        for all vertices $v$
            $\text{dist}[u, v, r] \leftarrow \min\left\{\text{dist}[u, v, r-1], \text{dist}[u, r, r-1] + \text{dist}[r, v, r-1]\right\}$

This can be simplified by removing the third dimension, arriving at Floyd’s improvement:

**FloydWarshall(V, E, w):**
for all vertices $u$
    for all vertices $v$
        $\text{dist}[u, v] \leftarrow w(u \to v)$
for all vertices $r$
    for all vertices $u$
        for all vertices $v$
            if $\text{dist}[u, v] > \text{dist}[u, r] + \text{dist}[r, v]$
                $\text{dist}[u, v] \leftarrow \text{dist}[u, r] + \text{dist}[r, v]$

---

**Example:**

Consider the following graph:

```
    3---7---4
   /      / \
 2      9   2
 /      /     \
2---5---1---1---5
```

The initial distance matrix is:

|   | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|
| 1 | 0 | 5 | ∞ | 9 | 1 |
| 2 | 5 | 0 | 2 | ∞ | ∞ |
| 3 | ∞ | 2 | 0 | 7 | ∞ |
| 4 | 9 | ∞ | 7 | 0 | 2 |
| 5 | 1 | ∞ | ∞ | 2 | 0 |

The algorithm proceeds in rounds, updating the matrix as follows:

**Round 1 (intermediate node 1):**
|   | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|
| 1 | 0 | 5 | ∞ | 9 | 1 |
| 2 | 5 | 0 | 2 | 14 | 6 |
| 3 | ∞ | 2 | 0 | 7 | ∞ |
| 4 | 9 | 14 | 7 | 0 | 2 |
| 5 | 1 | 6 | ∞ | 2 | 0 |

**Round 2 (intermediate node 2):**
|   | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|
| 1 | 0 | 5 | 7 | 9 | 1 |
| 2 | 5 | 0 | 2 | 14 | 6 |
| 3 | 7 | 2 | 0 | 7 | 8 |
| 4 | 9 | 14 | 7 | 0 | 2 |
| 5 | 1 | 6 | 8 | 2 | 0 |

**Round 3 (intermediate node 3):**
|   | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|
| 1 | 0 | 5 | 7 | 9 | 1 |
| 2 | 5 | 0 | 2 | 9 | 6 |
| 3 | 7 | 2 | 0 | 7 | 8 |
| 4 | 9 | 9 | 7 | 0 | 2 |
| 5 | 1 | 6 | 8 | 2 | 0 |

**Final matrix (after all rounds):**
|   | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|
| 1 | 0 | 5 | 7 | 3 | 1 |
| 2 | 5 | 0 | 2 | 8 | 6 |
| 3 | 7 | 2 | 0 | 7 | 8 |
| 4 | 3 | 8 | 7 | 0 | 2 |
| 5 | 1 | 6 | 8 | 2 | 0 |

The shortest path from node 2 to node 4 is 8, corresponding to the path: 2 → 1 → 5 → 4.

-------

**Implementation**:
constructs a distance matrix where distance[a][b] is the shortest distance between nodes a and b
algorithm initializes distance using the adjacency matrix adj of the graph
find shortest distance

```cpp
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
        if (i == j) distance[i][j] = 0;
        else if (adj[i][j]) distance[i][j] = adj[i][j];
        else distance[i][j] = INF;
    }
}

for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            distance[i][j] = min(distance[i][j],distance[i][k]+distance[k][j]);
        }
    }
}
```

Time Complexity: $O(n^{3})$
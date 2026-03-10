# Dijkstra Algorithm/ Single-Source Shortest Paths

It finds shortest paths from the starting node to all nodes of the weighted graph.
All edge weight are non-negative
we assume that w(u, v) ≥0 for each edge (u, v) ∈ E

Benefit: more efficient and can be used for processing large graphs.

maintains distances to the nodes and reduces them during the search.


The distance to itself is 0 and to every other node in initialised to infinity
select a node that has been not processed and distance is smallest
When a node is selected, the algorithm goes through all edges that start at the node and reduces the distances using them

hence when you go to the smallest length node the infinite is now set to previous cost + smallest length you just traversed

A remarkable property in Dijkstra’s algorithm is that whenever a node is
selected, its distance is final.

it is best only for when edges weight are positive
if they are negative say, then we may lose a more efficient approach, hence giving incorrect results

algorithm repeatedly selects the vertex u ∈V−S with the minimum shortest-path estimate, 
adds u to S, and relaxes all edges leaving u. 

**Implementation:**
calculates the minimum distances from a node x to other nodes of the graph

stored as adjacency list; `adj[a]` contains a `pair (b,w)` always when there is an edge from node `a` to node `b` with weight `w`.

Use a priority queue that contains the nodes ordered by their distances.
sorted based on increasing distance from the source, and if tie, by vertex number.

base case (0, s) which is true for the source vertex.

repeats the following process until pq is empty: 
It greedily takes out vertex information pair (d, u) from the front of pq. 
If the distance to u from source recorded in d greater than dist[u], it ignores u; 
otherwise, it process u.

```
DIJKSTRA(G, w, s):
    INITIALIZE-SINGLE-SOURCE(G, s)
    S ←∅
    Q ←V [G]
    while Q !=∅
        do u ←EXTRACT-MIN(Q)
        S ←S ∪{u}
        for each vertex v ∈Adj[u]
            do RELAX(u, v, w)
```


```cpp
for (int i = 1; i <= n; i++) distance[i] = INF;
distance[x] = 0;
q.push({0,x});
while (!q.empty()) {
    int a = q.top().second; q.pop();
    if (processed[a]) continue;
    processed[a] = true;
    
    for (auto u : adj[a]) {
        int b = u.first, w = u.second;
        if (distance[a]+w < distance[b]) {
            distance[b] = distance[a]+w;
            q.push({-distance[b],b});
        }
    }
}
```

```cpp
vi dist(V, INF); dist[s] = 0; // INF = 1B to avoid overflow
priority_queue< ii, vector<ii>, greater<ii> > pq; pq.push(ii(0, s));
while (!pq.empty()) { // main loop
    ii front = pq.top(); pq.pop(); // greedy: get shortest unvisited vertex
    int d = front.first, u = front.second;
    if (d > dist[u]) continue; 
    
    for (int j = 0; j < (int)AdjList[u].size(); j++) {
        ii v = AdjList[u][j]; // this is a very important check
        // all outgoing edges from u
    
        if (dist[u] + v.second < dist[v.first]) {
            dist[v.first] = dist[u] + v.second; // relax operation
            pq.push(ii(dist[v.first], v.first));
        } 
    }
} // this variant can cause duplicate items in the priority queue
```


Time Complexity: O(n+ mlog m)

# Analysis
How fast is Dijkstra’s algorithm? It maintains the min-priority queue $Q$ by calling three priority-queue operations: INSERT (implicit in line 3), EXTRACT-MIN (line 5), and DECREASE-KEY (implicit in RELAX, which is called in line 8). INSERT is invoked once per vertex, as is EXTRACT-MIN. Because each vertex $v \in V$ is added to set $S$ exactly once, each edge in the adjacency list $Adj[v]$ is examined in the for loop of lines 7–8 exactly once during the course of the algorithm. Since the total number of edges in all the adjacency lists is $|E|$, there are a total of $|E|$ iterations of this for loop, and thus a total of at most $|E|$ DECREASE-KEY operations. (Observe once again that we are using aggregate analysis.)

The running time of Dijkstra’s algorithm depends on how the min-priority queue is implemented. Consider first the case in which we maintain the min-priority queue by taking advantage of the vertices being numbered 1 to $|V|$. We simply store $d[v]$ in the $v$th entry of an array. Each INSERT and DECREASE-KEY operation takes $O(1)$ time, and each EXTRACT-MIN operation takes $O(V)$ time (since we have to search through the entire array), for a total time of $O(V^2+E) = O(V^2)$.

If the graph is sufficiently sparse—in particular, $E = o(V^2 / \lg V)$—it is practical to implement the min-priority queue with a binary min-heap. Each EXTRACT-MIN operation then takes time $O(\lg V)$. As before, there are $|V|$ such operations. The time to build the binary min-heap is $O(V)$. Each DECREASE-KEY operation takes time $O(\lg V)$, and there are still at most $|E|$ such operations. The total running time is therefore $O((V + E) \lg V)$, which is $O(E \lg V)$ if all vertices are reachable from the source. This running time is an improvement over the straightforward $O(V^2)$-time implementation if $E = o(V^2 / \lg V)$.

We can in fact achieve a running time of $O(V \lg V + E)$ by implementing the min-priority queue with a Fibonacci heap. The amortized cost of each of the $|V|$ EXTRACT-MIN operations is $O(\lg V)$, and each DECREASE-KEY call, of which there are at most $|E|$, takes only $O(1)$ amortized time. Historically, the development of Fibonacci heaps was motivated by the observation that in Dijkstra’s algorithm there are typically many more DECREASE-KEY calls than EXTRACT-MIN calls, so any method of reducing the amortized time of each DECREASE-KEY operation to $o(\lg V)$ without increasing the amortized time of EXTRACT-MIN would yield an asymptotically faster implementation than with binary heaps.

Dijkstra’s algorithm bears some similarity to both breadth-first search and Prim’s algorithm for computing minimum spanning trees. It is like breadth-first search in that set $S$ corresponds to the set of black vertices in a breadth-first search; just as vertices in $S$ have their final shortest-path weights, so do black vertices in a breadth-first search have their correct breadth-first distances. Dijkstra’s algorithm is like Prim’s algorithm in that both algorithms use a min-priority queue to find the “lightest” vertex outside a given set (the set $S$ in Dijkstra’s algorithm and the tree being grown in Prim’s algorithm), add this vertex into the set, and adjust the weights of the remaining vertices outside the set accordingly.

# Best-First: Dijkstra’s Algorithm
If we replace the FIFO queue in breadth-first search with a priority queue, where the key of a vertex $v$ is its tentative distance $dist(v)$, we obtain Dijkstra’s algorithm. The algorithm was independently discovered by Edsger Dijkstra in 1956 (published in 1959), and also by others, but is now universally known as Dijkstra’s algorithm.

## Intuition and Correctness
Dijkstra’s algorithm expands a wavefront outward from the source vertex $s$, passing over vertices in increasing order of their distance from $s$, similar to breadth-first search. At all times, an edge $u \to v$ is tense if and only if $u$ is either in the priority queue or is the vertex most recently extracted. The algorithm is correct for graphs with no negative cycles.

## No Negative Edges
Dijkstra’s algorithm is particularly well-behaved when the input graph has no negative-weight edges. In this setting, the algorithm expands outward in increasing order of distance. Each vertex is extracted at most once, and each edge is relaxed at most once. When Dijkstra ends, $dist(v)$ is the length of the shortest path from $s$ to $v$ for every vertex $v$.

## Simplified Version for Non-Negative Graphs
If we know in advance that the input graph has no negative edges, we can simplify Dijkstra’s algorithm by inserting every vertex into the priority queue in the initialization phase, then only calling DECREASE-KEY in the main loop. This is the version used in most textbooks and references.

## Negative Edges
Dijkstra’s algorithm does not correctly compute shortest paths in graphs with negative edges. Even when all edge weights are positive, the algorithm is no faster than the original brute-force scan. When negative edges are present, the expanding wavefront intuition fails: vertices can be extracted multiple times, edges can be relaxed multiple times, and distances may not be discovered in increasing order. In the worst case, Dijkstra’s algorithm can run in exponential time for graphs with negative edges.

## Summary
- Use Dijkstra’s algorithm for graphs with non-negative edge weights.
- For graphs with negative edges, use Bellman-Ford or other algorithms.
- Dijkstra’s algorithm is fast and correct for most practical cases, but not for graphs with negative-weight edges.
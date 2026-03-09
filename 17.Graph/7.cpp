/*
Prim's Algorithm (MST using Min-Heap)
-------------------------------------
Finds a minimum spanning tree (MST) for a connected, undirected, weighted graph.

Idea:
- Start from an arbitrary vertex (here, node 1).
- Use a min-heap (priority queue) to always select the minimum-weight edge that connects a tree vertex to a non-tree vertex.
- Add the selected edge and vertex to the MST/tree.
- Repeat until all vertices are included.
*/

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <queue>
#include <iostream>

using std::vector;
using std::unordered_map;
using std::unordered_set;
using std::pair;
using std::tuple;
using std::get;
using std::make_tuple;
using std::make_pair;
using std::priority_queue;
using std::greater;

// Given a list of edges of a connected undirected graph,
// with nodes numbered from 1 to n,
// return a list of edges making up the minimum spanning tree.
vector<pair<int, int>> mst(vector<vector<int>>& edges, int n) {
    unordered_map<int, vector<pair<int, int>>> adj;
    // Build adjacency list
    for (int i = 1; i < n + 1; i++) {
        adj[i] = vector<pair<int, int>>();
    }
    for (vector<int> edge : edges) {
        int n1 = edge[0], n2 = edge[1], weight = edge[2];
        adj[n1].push_back(make_pair(n2, weight));
        adj[n2].push_back(make_pair(n1, weight));
    }

    // Min-heap: (weight, from, to)
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> minHeap;
    // Start from node 1: push all its neighbors
    for (pair<int, int> neighbor : adj[1]) {
        int node = neighbor.first, weight = neighbor.second;
        minHeap.push({weight, 1, node});
    }
    
    vector<pair<int, int>> mst; // Store MST edges (from, to)
    unordered_set<int> visit;   // Track visited nodes
    visit.insert(1);
    while (visit.size() < n) {
        tuple<int, int, int> cur = minHeap.top();
        minHeap.pop();
        int w1 = get<0>(cur), n1 = get<1>(cur), n2 = get<2>(cur);

        if (visit.count(n2) > 0) {
            continue; // Skip if already in MST
        }
        mst.push_back({n1, n2}); // Add edge to MST
        visit.insert(n2);        // Mark node as visited
        // Add all edges from new node to heap
        for (pair<int, int> p : adj[n2]) {
            int neighbor = p.first, weight = p.second;
            if (visit.count(neighbor) == 0) {
                minHeap.push({weight, n2, neighbor});
            }
        }
    }
    return mst;
}

int main() {
    // Example usage: vector of ints
    std::vector<int> myVector;
    myVector.push_back(1);
    myVector.push_back(2);
    myVector.push_back(3);

    // Print elements
    for (int i : myVector) {
        std::cout << i << " ";
    }
    return 0;
}
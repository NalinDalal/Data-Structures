/*
Kruskal's Algorithm for Minimum Spanning Tree (MST)
--------------------------------------------------
Finds MST of a weighted undirected graph using union-find.

Steps:
1. Sort all edges by weight.
2. Iterate through sorted edges:
   - If adding edge forms a cycle, skip it.
   - Otherwise, include edge in MST and merge sets.

Time Complexity: O(E log V)
Space Complexity: O(E + V)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e5 + 6;
vector<int> parent(N); // parent[i] = parent of node i
vector<int> sz(N);     // sz[i] = size of set rooted at i

// Initialize set for element v
void make_set(int v) {
    parent[v] = v;
    sz[v] = 1;
}

// Find representative of set containing v (with path compression)
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

// Merge sets containing a and b (by size)
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sz[a] < sz[b])
            swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
    }
}

int32_t main() {
    // Initialize all sets
    for (int i = 0; i < N; i++) {
        make_set(i);
    }

    int n, m;
    cin >> n >> m;
    vector<vector<int>> edges;
    // Read edges: u, v, w
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, u, v}); // Store as (weight, u, v)
    }

    // Sort edges by weight
    sort(edges.begin(), edges.end());
    int cost = 0;
    // Kruskal's algorithm: build MST
    for (auto i : edges) {
        int w = i[0];
        int u = i[1];
        int v = i[2];
        int x = find_set(u);
        int y = find_set(v);
        if (x == y) {
            continue; // Skip edge if it forms a cycle
        } else {
            cout << u << " " << v << "\n"; // Output MST edge
            cost += w; // Add edge weight to total cost
            union_sets(u, v); // Merge sets
        }
    }
    cout << cost; // Output total cost of MST
}
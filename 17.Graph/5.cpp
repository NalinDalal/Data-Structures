/*
Union-Find (Disjoint Set Union) Data Structure
----------------------------------------------
Efficiently supports union and find operations for disjoint sets.
Used for cycle detection, connected components, and Kruskal's algorithm.

- make_set(v): Initializes set for element v.
- find_set(v): Finds representative of set containing v (with path compression).
- union_sets(a, b): Merges sets containing a and b (by size).
*/

#include <iostream>
#include <vector>
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
    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }

    bool cycle = false;
    // Check for cycles using union-find
    for (auto i : edges) {
        int u = i[0];
        int v = i[1];
        int x = find_set(u);
        int y = find_set(v);
        if (x == y) {
            cycle = true; // Cycle detected
        } else {
            union_sets(u, v); // Merge sets
        }
    }
    if (cycle) {
        cout << "cycle present";
    } else {
        cout << "no cycle";
    }
}
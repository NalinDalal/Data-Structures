#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <queue>
#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int cnt = 0;
    vector<vector<int> > adj_list(n);
    vector<int> indeg(n, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v); // Corrected from adj[u] to adj_list[u]
        indeg[v]++;
    }

    queue<int> pq;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) {
            pq.push(i);
        }
    }

    while (!pq.empty()) {
        cnt++;
        int x = pq.front();
        pq.pop();
        cout << x << " ";

        for (auto it : adj_list[x]) {
            indeg[it]--;
            if (indeg[it] == 0)
                pq.push(it);
        }
    }

    return 0;
}
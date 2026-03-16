// Ford-Fulkerson Algorithm (C++ Skeleton)
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
    int to, rev;
    int cap;
};

class MaxFlow {
public:
    vector<vector<Edge>> G;
    vector<bool> used;
    MaxFlow(int n) : G(n), used(n) {}
    void add_edge(int from, int to, int cap) {
        G[from].push_back({to, (int)G[to].size(), cap});
        G[to].push_back({from, (int)G[from].size() - 1, 0});
    }
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        used[v] = true;
        for (auto &e : G[v]) {
            if (!used[e.to] && e.cap > 0) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    int max_flow(int s, int t) {
        int flow = 0;
        while (true) {
            fill(used.begin(), used.end(), false);
            int f = dfs(s, t, 1e9);
            if (f == 0) break;
            flow += f;
        }
        return flow;
    }
};

// Edmonds-Karp Algorithm (C++ Skeleton)
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
    vector<int> level, iter;
    MaxFlow(int n) : G(n), level(n), iter(n) {}
    void add_edge(int from, int to, int cap) {
        G[from].push_back({to, (int)G[to].size(), cap});
        G[to].push_back({from, (int)G[from].size() - 1, 0});
    }
    void bfs(int s) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &e : G[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
    }
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int &i = iter[v]; i < G[v].size(); ++i) {
            Edge &e = G[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
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
            bfs(s);
            if (level[t] < 0) break;
            fill(iter.begin(), iter.end(), 0);
            int f;
            while ((f = dfs(s, t, 1e9)) > 0) flow += f;
        }
        return flow;
    }
};

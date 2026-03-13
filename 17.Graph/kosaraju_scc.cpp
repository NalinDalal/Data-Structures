// Program to find Strongly Connected Components (SCCs) using Kosaraju's Algorithm
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;
    vector<vector<int>> rev_adj;
public:
    Graph(int V) : V(V), adj(V), rev_adj(V) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }
    void dfs(int u, vector<bool>& visited, stack<int>& finish) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) dfs(v, visited, finish);
        }
        finish.push(u);
    }
    void rev_dfs(int u, vector<bool>& visited, vector<int>& component) {
        visited[u] = true;
        component.push_back(u);
        for (int v : rev_adj[u]) {
            if (!visited[v]) rev_dfs(v, visited, component);
        }
    }
    void findSCCs() {
        vector<bool> visited(V, false);
        stack<int> finish;
        // 1st DFS: record finish order
        for (int i = 0; i < V; ++i)
            if (!visited[i]) dfs(i, visited, finish);
        // 2nd DFS: on reversed graph
        fill(visited.begin(), visited.end(), false);
        cout << "Strongly Connected Components:\n";
        while (!finish.empty()) {
            int u = finish.top(); finish.pop();
            if (!visited[u]) {
                vector<int> component;
                rev_dfs(u, visited, component);
                for (int v : component) cout << v << " ";
                cout << endl;
            }
        }
    }
};

int main() {
    Graph g(8);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(6, 4);
    g.addEdge(6, 7);
    g.addEdge(7, 3);
    g.findSCCs();
    return 0;
}

/*
Cycle Detection in an Directed Graph
1. Mark the current node as visited and also mark the index in recursion stack.
2. Find all the vertices which are not visited and are adjacent to the current node.
3. If the adjacent vertices are already marked in recursion stack than a cycle is found
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

bool iscycle(int src, vector<vector<int> > &adj, vector<bool> &visited, stack<int> &recStack) {
    if (!visited[src]) {
        visited[src] = true;
        recStack.push(src);

        for (auto i : adj[src]) {
            if (!visited[i] && iscycle(i, adj, visited, recStack)) {
                return true;
            }
            else if (recStack.top() == i) {
                return true;
            }
        }
    }

    recStack.pop();
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int> > adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    bool cycle = false;
    stack<int> recStack;
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        if (!visited[i] && iscycle(i, adj, visited, recStack)) {
            cycle = true;
            break;
        }
    }

    if (cycle)
        cout << "Cycle is present";
    else
        cout << "Cycle not present";

    return 0;
}
// Topological Sort
/* A Topological Ordering is an ordering of the nodes in a directed graph where for each directed edge from node A to node B, node
A appears before node B in the ordering.

Dircted Cyclic Graph->topological sort(x)
Directd Acyclic Graph->topological sort(valid)

        A
       / \    \
      B   C    D
     / \   \
    E   F   G

Topological Sort-E F G D

Indegree
The number of inward directed edges on vertex in a directed graph.

Algorithm:
While(All the nodes are not visited){
    Nodes with zero indegree can be added to the output array.
    All the nodes which are adjacent to terminal nodes, gets their indegree subtracted.
}

Pseudo Code:
map<int,int> in_deg;
for(edge it: edges){
    adj_list[it[1]].push_back(it[0]);
    in_deg[it[0]]++;
}
queue<int> pq;
for(int i = 0;i<n;i++){
    if(in_deg[i]==0){
        pq.push(i);
    }
}
cnt = 0;
while(queue is not empty){
    cnt++;
    int x = pq.front();
    pq.pop();
    for(node it : adj_list[x]){
        in_deg[it]-;
        if(in_deg[it]==0){
            pq.push(it);
        }
    }
}
*/

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <queue>
#include <iostream>

using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    int cnt=0;
    vector<vector<int>> adj_list(n);
    vector<int> indeg(n,0);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        indeg[v]++;
    }
    queue<int> pq;
    for(int i=0;i<n;i++){
        if(indeg[i]==0){pq.push(i);}
    }
    while(!pq.empty()){
        cnt++;
        int x=pq.front();
        pq.pop();
        cout<<x<<" ";

        for(auto it:adj_list[x]){
            indeg[it]--;
            if(indeg[it]==0)
                pq.push(it);
        }
    }
}
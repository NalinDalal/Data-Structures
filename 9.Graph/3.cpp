//cycle detection in undirected graph
/*
keep traversing graph
if found an edge pointing to an already visitd node(except parent)->cycle is found
*/

//#include "bits/stdc++.h"
#include <iostream>
using namespace std;
bool iscycle(int src,vector<vector<int> > &adj,vector<bool> &visited,int parent){
    visited[src]=true;
    for(auto i:adj[src]){
        if(i!=parent){
            if(visited[i])
                return true;
            if(!visited[i] and iscycle(i,adj,visited,src)){
                return true;
            }
        }
    }
    return false;
}
int32_t main(){
    int n,m;
    cin>>n>>m;

    vector<vector<int> > adj(n);
    for(int i=0;i<m;i++){
        int u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bool cycle=false;
    vector<bool> visited(n,false);
    for(int i=0;i<n;i++){
        if(!visited[i] and iscycle(i,adj,visited,-1)){
            cycle=true;
        }
    }
    if(cycle)
        cout<<"Cycle is present";
    else{
        cout<<"Cycle not present";
    }
    return 0;
}

/*
4 3
0 1
1 2
2 0
Cycle is present% 

4 8
22 56
345 78
34 68
21 67
44 89
214 57
23 69
20 30
Cycle not present%
*/
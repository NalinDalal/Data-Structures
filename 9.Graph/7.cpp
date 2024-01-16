/*
Prim's Algorithm:

Idea:
Select an arbitrary vertex s to start the tree from.
    While (there are still nontree vertices)
        Select the edge of minimum weight between a tree and nontree vertex.
        Add the selected edge and vertex to the tree.
*/
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>

using namespace std;
int n,m;
const int N=1e5+3;

vector<pair<int,int> > g[N];
int cost=0;

vector<int> dist(N),parent(N);
vector<bool> vis(N);
const int INF=1e9;

struct ComparePairs {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
        return a.first < b.first || (a.first == b.first && a.second < b.second);
    }
};

void primsMST(int source){
    for(int i=0;i<n;i++){dist[i]=INF;}
    set<vector<int> > s;
    dist[source]=0;
    s.insert({0,source});
    while(!s.empty()){
        auto x=*(s.begin());
        s.erase(x);
        vis[x.second]=true;
        int u=x.second;
        int v=parent[x.second];
        int w=x.first;
        cout<<u<<" "<<v<<" "<<w<<"\n";
        cost+=w;
        for(auto it:g[x.second]){
            if(vis[it.first])
                continue;
            if(dist[it.first]>it.second){
                s.erase({dist[it.first],it.first});
                dist[it.first]=it.second;
                s.insert({dist[it.first],it.first});
                parent[it.first]=x.second;
            }
        }
    }
}

int32_t main(){
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    primsMST(0);
    cout<<cost;
}
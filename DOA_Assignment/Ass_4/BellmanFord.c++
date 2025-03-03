#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX
struct Edge {
    int u, v, w;
};

void bellmanFord(int n,int s,vector<Edge>& edges) {
    vector<int>dist(n,INF);
    dist[s]=0;

    for(int i=0;i<n-1;i++){
      for(const auto& edge:edges){
        if(dist[edge.u]!=INF && dist[edge.u]+edge.w<dist[edge.v]){
            dist[edge.v]=dist[edge.u]+edge.w;
          }
      }
    }

    for (const auto& edge:edges) {
      if (dist[edge.u]!=INF && dist[edge.u]+edge.w<dist[edge.v]) {
        cout<<"Negative weight cycle detected."<<endl;
        return;
      }
    }

    cout << "Vertex Distance from Source" << endl;
    for(int i=0;i<n;i++){
      if(dist[i]==INF)
        cout<<i<<"\t\t"<<"∞"<<endl;
      else
        cout<<i<<"\t\t"<<dist[i]<<endl;
    }
}

int main() {
    int n=5; 
    int s=0; 
    vector<Edge>edges={{0, 1, -1},
                      {0, 2, 4},
                      {1, 2, 3},
                      {1, 3, 2},
                      {1, 4, 2},
                      {3, 2, 5},
                      {3, 1, 1},
                      {4, 3, -3}};
    bellmanFord(n,s,edges);
    return 0;
}

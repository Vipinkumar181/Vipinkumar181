#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cfloat>
#include<tuple>
#include<queue>
using namespace std;

typedef pair<int,int>minheap;

pair<vector<tuple<int,int,int>>,int>prims(const vector<vector<float>>&graph){
  int V=graph.size();
  vector<int>parent(V,-1);
  vector<int>key(V,INT_MAX);
  vector<bool>inMST(V,false);
  priority_queue<minheap,vector<minheap>,greater<minheap>>pq;
  key[0]=0;
  pq.push({0,0});
  int totalw=0;
  while(!pq.empty()){
    int u=pq.top().second;
    pq.pop();
    if(inMST[u]) continue;
    inMST[u]=true;
    totalw+=key[u];
    for(int v=0;v<V;v++){
      if(graph[u][v]!=__FLT_MAX__ && !inMST[v] && graph[u][v]<key[v]){
        key[v]=graph[u][v];
        parent[v]=u;
        pq.push({key[v],v});
      }
    }
  }

  vector<tuple<int,int,int>>mstedges;
  for(int i=0;i<V;i++){
    if(parent[i]!=-1){
      mstedges.push_back({parent[i],i,(int)graph[i][parent[i]]});
    }
  }
  return {mstedges,totalw};
}

int main(){
  vector<vector<float>>graph={
    {0, 4, 3, FLT_MAX, FLT_MAX},
    {4, 0, 1, 2, FLT_MAX},
    {3, 1, 0, 4, 5},
    {FLT_MAX, 2, 4, 0, 3},
    {FLT_MAX, FLT_MAX, 5, 3, 0}
  };
  auto result=prims(graph);
  vector<tuple<int,int,int>>mstedges=result.first;
  int totalW=result.second;
  cout<<"Edges in the MST:\n";
  cout<<" u "<<"v "<<"w "<<endl;
  for(const auto& edge:mstedges){
    cout<<"("<<get<0>(edge)<<","<<get<1>(edge)<<","<<get<2>(edge)<<")\n";
  }
  cout<<"Total weight in MST: "<<totalW<<endl;
  return 0;
}
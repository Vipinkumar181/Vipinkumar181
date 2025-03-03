#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct edge{
  int u,v,w;
};

bool compare(edge a ,edge b){
  return a.w<b.w;
}

int findroot(vector<int>&parent,int node){
  if(parent[node]!=node)
    parent[node]=findroot(parent,parent[node]);
  return parent[node];
}

void unionsets(vector<int>&parent,vector<int>&rank,int u,int v){
  int rootu=findroot(parent,u);
  int rootv=findroot(parent,v);
  if(rootu!=rootv){
    if(rank[rootu]<rank[rootv])
      parent[rootu]=rootv;
    else if(rank[rootu]>rank[rootv])
      parent[rootv]=rootu;
    else{
      parent[rootv]=rootu;
      rank[rootu]++;
    }
  }
}

pair<vector<edge>,int>kruskal(vector<edge>&edges,int V){
  sort(edges.begin(),edges.end(),compare);
  vector<int>parent(V),rank(V,0);

  for(int i=0;i<V;i++)
    parent[i]=i;

  vector<edge>mst;
  int totalW=0;
  for(edge& ege:edges){
    int u=ege.u;
    int v=ege.v;
    if(findroot(parent,u)!=findroot(parent,v)){
      mst.push_back(ege);
      totalW+=ege.w;
      unionsets(parent,rank,u,v);
    }
  }
  return {mst,totalW};
}

int main(){
  // vector<edge>edges={{0,1,4},{0,2,3},{1,2,1},{1,3,2},{2,3,4}};
  vector<edge>edges={{0, 1, 10},{1, 3, 15},{2,3,4},{2,0,6},{0,3,5}};
  int V=4;
  auto result=kruskal(edges,V);
  vector<edge>mst=result.first;
  int totalW=result.second;
  cout<<"Edges in MST:\n";
  for(edge& ege:mst){
    cout<<"("<< ege.u <<", "<<ege.v<<", "<<ege.w << ")\n";
  }
  cout<<"Total weight of the MST: "<<totalW<<endl;
  return 0;
}
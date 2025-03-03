#include<iostream>
#include<vector>
#include<utility>
using namespace std;

int findroot(vector<int>&parent,int node){
  if(parent[node]!=node)
    parent[node]=findroot(parent,parent[node]);
  return parent[node];
}

bool unionsets(vector<int>&parent,vector<int>&rank,int u,int v){
  int rootu=findroot(parent,u);
  int rootv=findroot(parent,v);
  if(rootu==rootv) return false;
  
  if(rank[rootu]<rank[rootv])
    parent[rootu]=rootv;
  else if(rank[rootu]>rank[rootv])
    parent[rootv]=rootu;
  else{
    parent[rootv]=rootu;
    rank[rootu]++;
  }

  return true;
}

bool isST(vector<pair<int,int>>&edges,int V){
  if(edges.size()!=V-1) return false;
  vector<int>parent(V);
  vector<int>rank(V,0);
  for(int i=0;i<V;i++){
    parent[i]=i;
  }
  for(const auto &edge:edges){
    int u=edge.first;
    int v=edge.second;
    if(!unionsets(parent,rank,u,v)) return false;
  }
  return true;
}

int main(){
  vector<pair<int,int>>edges={{0,1},{1,2},{2,3}};
  int V=4;
  if(isST(edges,V)){
    cout<<"The edges form a valid spanning tree.";
  }
  else{
    cout<<"The edges do not form a valid spanning tree.";
  }
  return 0;
}
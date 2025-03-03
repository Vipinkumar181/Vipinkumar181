#include<bits/stdc++.h>
using namespace std;
#define V 6


bool bfs(int rG[V][V],int s,int t,int parent[]){
    bool visited[V];
    memset(visited,0,sizeof(visited));
    queue<int>q;
    q.push(s);
    visited[s]=true;
    parent[s]=-1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int v=0;v<V;v++){
            if(!visited[v] && rG[u][v]>0){
                if(v==t){
                    parent[v]=u;
                    return true;}
                q.push(v);
                parent[v]=u;
                visited[v]=true;
            }
        }
    }
    return false;
}

int FF(int g[V][V],int s,int t) {
    int rG[V][V];
    for (int u=0;u<V;u++){
        for (int v=0;v<V;v++){
            rG[u][v]=g[u][v];
        }
    }
    int parent[V],mf=0;

    while(bfs(rG,s,t,parent)){
        int pf=INT_MAX;
        for(int v=t;v!=s;v=parent[v]){
            int u=parent[v];
            pf=min(pf,rG[u][v]);
        }

        for(int v=t;v!=s;v=parent[v]){
            int u=parent[v];
            rG[u][v]-=pf;
            rG[v][u]+=pf;
        }

        mf+=pf;
    }
    return mf;
}

int main() {
    int g[V][V]={{0, 2, 0, 0, 0, 0},{0, 0, 3, 0, 0, 0},
                    {0, 0, 0, 10, 0, 0},{0, 0, 0, 0, 15, 0},
                    {0, 0, 0, 0, -5, 0},{0, 0, 0, 0, 0, 0}};

    cout <<"The maximum possible flow is "<<FF(g,0,5);
    return 0;
}
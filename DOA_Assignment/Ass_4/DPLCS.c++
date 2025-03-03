#include<bits/stdc++.h>
#include<string>
#include<algorithm>
using namespace std;
int LCS(string& X,string& Y){
  int m=X.length();
  int n=Y.length();
  int dp[m+1][n+1];
  for(int i=0;i<=m;i++) dp[i][0]=0;
  for(int j=0;j<=n;j++) dp[0][j]=0;
  for(int i=1;i<=m;i++){
    for(int j=1;j<=n;j++){
      if(X[i-1]==Y[j-1]){
        dp[i][j]=dp[i-1][j-1]+1;
      }
      else{
        dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
      }
    }
  }
  return dp[m][n];
}
int main(){
  string X="VipinKumar";
  string Y="vipin all";
  cout<<"LCS length: "<<LCS(X,Y)<<endl;
  return 0;
}
// m*n 
#include<bits/stdc++.h>
#include<string>
#include<algorithm>
using namespace std;
int RodCut(vector<int>& prices){
  int l=prices.size();
  int dp[l+1]={0};
  for(int i=1;i<=l;i++){
    int ans=0;
    for(int j=0;j<i;j++){
      ans=max(ans,prices[j]+dp[i-j-1]);
    }
    dp[i]=ans;
  }
  return dp[l];
}
int main(){
  vector<int>prices={2,4,5,7,8,8,11};
  cout<<"Max price: "<<RodCut(prices)<<endl;
  return 0;
}
// l^2 ,l
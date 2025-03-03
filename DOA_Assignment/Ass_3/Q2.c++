#include<iostream>
#include<limits.h>
using namespace std;
int partition(int arr[],int low,int high){
    int pivot=arr[high];
    int i=low;
    for(int j=low;j<high;j++){
      if(arr[j]<=pivot){
          swap(arr[i],arr[j]);
          i++;
      }
    }
    swap(arr[i],arr[high]);
    // for(int l=low;l<high;l++){
    //   cout<<arr[l]<<" ";
    // }
    // cout<<endl;
    cout<<i<<" "<<arr[i]<<endl;
    return i;
}

int QuickSelect(int arr[],int low,int high,int k){
  if(low==high){
    return arr[low];
  }
  int pi=partition(arr,low,high);
  
  if(k==pi){
  return arr[pi];
  }
  else if(k>pi){
    return QuickSelect(arr,pi+1,high,k);
  }
  else{
    return QuickSelect(arr,low,pi-1,k);
  }
  
  return 0;
}
int main(){
  int arr[]={12,3,5,7,4,19,26}; /* {3,4,5,7,12,19,26} */
  int n=sizeof(arr)/sizeof(int);
  int k=5;
  cout<<k<<"th Small Element "<<QuickSelect(arr,0,n-1,k-1)<<endl;
  
  
}
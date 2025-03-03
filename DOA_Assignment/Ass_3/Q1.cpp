#include<iostream>
#include<limits.h>
using namespace std;
void findMINMAX(int arr[],int n,int &Min,int &Max){
   
    for(int i=1;i<n;i++){
      if(arr[i]>Max){
        Max=arr[i];
      }
      else{
        Min=arr[i];
      }
      
    }
    cout<<"Minimum value of array "<<Min<<endl;
    cout<<"Maximum value of array "<<Max<<endl;
}
int main(){
  int arr[]={1,2,3,4,5,6,7};
  int n=sizeof(arr)/sizeof(int);
  
  int Min=arr[0];
  int Max=arr[0];
  findMINMAX(arr,n,Min,Max);
  
}
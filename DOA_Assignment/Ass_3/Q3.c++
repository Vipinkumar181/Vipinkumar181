#include<iostream>
#include<limits.h>
#include<algorithm>
#include<vector>
using namespace std;
int Median(vector<int>&arr,int start,int s){
    sort(arr.begin()+start,arr.begin()+start+s);
    return arr[start+s/2];
}

int partition(vector<int>&arr,int low,int high,int pivot){
	for(int i=low;i<high;i++){
		if(arr[i]==pivot){
			swap(arr[i],arr[high]);
			break;
		}
	}
	int i=low;
	for(int j=low;j<high;j++){
		if(arr[j]<=pivot){
			swap(arr[i],arr[j]);
			i++;
		}
	}
	swap(arr[i],arr[high]);
	return i;

}
int Median_median(vector<int>&arr,int low,int high,int k){
	if(k>0 && k<=high-low+1){
		int al=high-low+1;
		vector<int>medians((al+4)/5);
		for(int i=0;i<al/5;i++){
			medians[i]=Median(arr,low+i*5,5);
		}
		if(al%5!=0){
			medians[al/5]=Median(arr,low+(al/5)*5,al%5);
		}

		int MedianMedians=(medians.size()==1) ? medians[0] : Median_median(medians,0,medians.size()-1,medians.size()/2);
		
		int pi=partition(arr,low,high,MedianMedians);
		int rank=pi-low+1;
		
		if(rank==k){
			return arr[pi];
		}
		else if(rank<k){
			return Median_median(arr,pi+1,high,k-rank);
		}
		else{
			return Median_median(arr,low,pi-1,k);
		}
	}
	return 0;
}

int main(){
//   vector<int>arr={12, 3, 5, 7, 4, 19, 26, 15, 9, 30, 11, 6, 14, 22, 18, 25, 21, 2, 8, 24, 28, 17, 16};
  vector<int>arr={12, 3, 5, 7, 4, 19, 26, 15, 9};
  int n=arr.size();
  int k=(n+1)/2;
  cout<<"Median of array is "<<Median_median(arr,0,n-1,k);
  
}
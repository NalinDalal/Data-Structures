/*
{5,3,2,1} in ascending order;we use sorting
Selection Sort:
traverse the whole array till last 
then go to the minimum element and place it at the first place
the 2nd element the same way
so swap it accordingly & so on
*/
/*
2 loops:
i from 0 to i-2
j from 1 to i-1
Compare it accordingly
*/
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main(){
	int n;
	cin>>n;

	int arr[n];
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(arr[j]<arr[i]){	//now swap them
				int temp=arr[j];
				arr[j]=arr[i];
				arr[i]=temp;
			}
		}
	}

	for(int i=0;i<n;i++){
		cout<<arr[i]<<" ";
	}cout<<endl;
	cin.get();
}

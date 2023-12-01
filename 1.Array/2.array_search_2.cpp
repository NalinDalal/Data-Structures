/*we will do binary search here🥲, for that:
Complexity must be less than O(n)
elements must be in sorted order
suppose key=27
{8,10,12,21,27,34,42}
mid element taken and compare with key

hence every time we will do comparison the elements get havled at every step
mid element=21;
mid element<key
	go for right sub part
	starting point updated=21
	now the mid element=34;mid element<key
	starting point updated=27
element found;after every operation the data is halved
*/
#include <iostream>
using std::cin;
using std::cout;

int binarySearch(int arr[], int n, int key){
	int s=0;	//start point defined
	int e=n;	//end point defined
	while(s<=e){
	int mid=(s+e)/2;	//mid element counter

	if(arr[mid]==key){
		return mid;
	}
	else if(arr[mid]>key){
		e=mid-1;
		}
	else{s=mid+1;
		}
	}
return -1;
}
int main(){
int n;
cout<<"Enter no of elements: ";
cin>>n;

int arr[n];
for(int i=0;i<n;i++){
	cin>>arr[i];
}
int key;
cin>>key;

cout<<binarySearch(arr,n,key)<<std::endl;
return 0;}

/*
Time Complexity:

After first iteration,length of array->n
a/f 2nd,length=n/2
a/f 3rd,length=(n/2)/2=n/2^2
a/f k iteration, length = 1

so n/2^k=1
=>n=2^k
=>log(n) to base 2=k

Time Complexity:O(log n base 2)

Linear search=O(n)
*/

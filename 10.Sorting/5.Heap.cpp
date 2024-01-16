#include <iostream>
using namespace std;

template<class T>
void heapsort(T data[], int n) {
for (int i=n/2-1;i>= 0; --i) // create a heap; moveDown (data,i,n-1);
for (int i = n-1; i >= 1; --i) {
swap(data[0],data[i]); // move the largest item to data[i]; moveDown(data,0,i-1); // restore the heap property;
} }

int main()
{
    int arr[]={1,2,367,35,23,356};
    int arr_size=sizeof(arr)/sizeof(arr[0]);
    heapsort(arr,6);
    
    for(int i=0;i<arr_size;i++){cout<<arr[i]<<" ";}
    return 0;
}
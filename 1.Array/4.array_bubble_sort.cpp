/*
Reapetedly swap two adjacent elements if they are in wrong order
Wrong Order=L>R;swap them
right order do nothing

It is like swap 2 adjacent till no one left
the elements get sorted in reverse order

we get the first smallest at last

no of elements(n)=(n-1)iteration b/f we get one array
ith iteration = n-i iteration
*/

#include <iostream>

int main(){
    int n;
    std::cin>>n;

    int arr[n];
    for(int i=0;i<n;i++){
        std::cin>>arr[i];
    }

    int counter=1;
    while(counter<n ){
        for(int i=0;i<n-counter;i++){
            if(arr[i]>arr[i+1]){    //swap element if in wrong order
                int temp=arr[i];
                arr[i]=arr[i+1];
                arr[i+1]=temp;
            }
        }
        counter++;
    }

    for(int i=0;i<n;i++){
        std::cout<<arr[i]<<" ";
    }std::cout<<std::endl;

    return 0;
}
#include <iostream>
using std::cin;
using std::cout;

int main(){
int n;
cin>>n;

int array[n];
for(int i=0;i<n;i++){
cin>>array[i];
}
for(int i=0;i<n;i++){
cout<<array[i]<<" ";
}
return 0;
}

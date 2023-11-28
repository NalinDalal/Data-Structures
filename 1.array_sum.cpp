#include <iostream>

int main(){
    int i=1,n;
    std::cin>>n;

    int a[n];
    for(int i=0;i<n;i++){
        std::cin>>a[i];
    }
    for(int i=0;i<n;++i){
        int sum=a[0];   //initiate sum for each subarray
        for(int j=1;j<=i;++j){
            sum+=a[j];
        }
        std::cout<<"Sum for Subarray 0 through "<<i<<" is "<<sum<<std::endl;
    }
    return 0;
}
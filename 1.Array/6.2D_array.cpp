/*
2D arrays are just matrices

Declaration:
    int arr[n][m];
*/
#include <iostream>

int main(){
    int n,m,flag;    //row and column declared
    std::cin>>n>>m;  //input taken
    bool arr[n][m];

    //taking input{row by row}
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            std::cin>>arr[i][j];
        }
    }

    std::cout<<"Matrix is:"<<std::endl;

    //for output:
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            std::cout<<arr[i][j]<<" ";
        }
        std::cout<<"\n";
    }

    int x;
    std::cin>>x;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(arr[i][j]==x){
                std::cout<<"Element is found:\n";
                flag=true;
            }
        }
    }

    if(flag){
        std::cout<<"Element is found\n";
    }
    else{
        std::cout<<"Element is not found\n";
    }
    std::cin.get();
}
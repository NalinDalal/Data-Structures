#include <iostream>

void iterativeEquivalentOfTail(int i){
    for(;i>0;i--){
        std::cout<<i<<std::endl;
    }
}

int main(){
    iterativeEquivalentOfTail(5);
    std::cin.get();
}

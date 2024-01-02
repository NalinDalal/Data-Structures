/*
Catalan Numbers-
it is a concept,convert one problem into another
Sequence of natural no that occur in various counting problems,often involving recursively defined objects.

Their closed form is in term of binomial coefficients:
Cn=2n(C)n x (1/n+1)
  =summation(CiCn-i),i=0 to n-1

C0=1
C1=1
C2=C0C1+C1C0=2
C3=C0C2+C1C1+C2C0=5
C4=C0C3+C1C2+C2C1+C3C0=14
*/

#include <iostream>
using namespace std;

int catalan(int n){
    if(n<=1){return 1;}
    int res=0;
    for(int i=0;i<=n-1;i++){
        res+=catalan(i)*catalan(n-i-1);
    }
    return res;
}

int main(){
    for(int i=0;i<10;i++){cout<<catalan(i)<<" ";}
    cout<<endl;
    return 0;
}
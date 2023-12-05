#include <iostream>
using namespace std;
struct node{
    int data;
    node *link;
};
int main(){
    node *first,*temp,*last;
    int n;
    cout<<"enter the no. of elements you want to insert"<<endl;
    cin>>n;
    cout<<"enter the data of element 1"<<endl;
    first=new node;
    cin>>first->data;
    first->link=NULL;
    temp=new node;
    temp=first;
    for(int i=1;i<n;i++){
        last=new node;
        cout<<"enter the data of element "<<i+1<<endl;
        cin>>last->data;
        last->link=NULL;
        first->link=last;
        last=temp;
    }
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->link;
    }
    return 0;
}
/*
the list takes first no of elements to keep in
then takes all input of the each node's data
after the insertion is done it just logs out/give output of the 1st and last element
*/

#include <iostream> 
using namespace std;

struct node
{ 
    int data;
    node *link;
};

int main(){
    node *first, *temp, *last;
    int n;
    cout<<"enter the no. of elements you want to insert"<<endl;
    cin>>n;
    cout<<"enter the data of element 1"<<endl;
    first=new node; 
    cin>>first->data; 
    first->link=NULL;
    temp=new node;
    temp=first;

    for (int i=1;i<n;i++)  
    {
        last=new node;
        cout<<"enter the data of element "<<i+1<<endl; 
        cin>>last->data; 
        last->link=NULL; 
        temp->link=last;
        temp=last;
    }
    while (temp!=NULL)
    {
        cout <<temp->data<<" ";
        temp=temp->link;
    }
return 0;
}
#include <iostream>

struct node
{ 
    int data;
    node *llink;
    node *rlink;
};

int main()
{
    int val,N,i;
    node* first=nullptr;
    node* last=nullptr;
    node* temp=nullptr;
    std::cout<<"Enter the size of Doubly linked list : ";
    std::cin>>N;

    first = new node;
    std::cout<<"Enter the data of Node 1 : ";
    std::cin>>first->data;
    first->llink=nullptr;
    first->rlink=nullptr;

    temp=first;

    for(i=1; i<N; i++){
            last = new node; 
            std::cout<<"Enter the data of node"<<i+1<<std::endl;
            std::cin>>last->data;
            last->rlink=nullptr;
            last->llink=temp;
            temp->rlink=last;
            temp=last;
    }

//Traversing
    std::cout<<"First element are : ";
    temp=first;
    while(temp!=nullptr)
    {
        std::cout<<temp->data<<std::endl;
        temp=temp->rlink;
        }
    std::cout<<std::endl;
    temp=first;
    while (temp!=nullptr){
        node* next=temp->rlink;
        delete temp;
        temp=next;
        }
        return 0;
}
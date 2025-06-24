#include <iostream>
using namespace std;

class node{
    public:
    int data;
    node* next;

    node(int val){
        data=val;
        next=NULL;
    }
};

//Insertion
void insertAthead(node* &head, int val){
    node* n=new node(val);
    n->next=head;
    head=n;
}

void insertAtTail(node* head, int val){
    node* n=new node(val);  //node n ke data field me val

    if(head==NULL){
        head=n; //n is first node
        return;
    }

    node* temp=head;    //iterator
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=n;
}

//printing
void display(node* head){
    node* temp=head;
    while(temp!=NULL){
        cout<<temp->data<<"->";
        temp=temp->next;
    }
    cout<<"NULL"<<endl;
}

//searching
bool search(node* head, int key){
    node* temp=head;
    while(temp!=NULL){
        if(temp->data==key){
            return true;
        }
        temp=temp->next;    //moves the pointer otherwise the loop will run forever
    }
    return false;
}

//reverse linked list
node* reverse(node* &head){
    node* prevptr=NULL;
    node* currptr=head;
    node* nextptr;

    while(cerr!=NULL){
        nextptr=currptr->next;
        currptr->next=prevptr;

        prevptr=currptr;
        currptr=nextptr;

    }

    return prevptr;
}

/*
head->1->2->3->4->NULL

head->4->3->2->1->NULL

2 Methods: Iterative and Recursive

Iterative:
3 Pointers:previous,current,next
    current at head
    previous at null
    next at current->next=previous

    update head->link=previous

    increase pointers
    same procedure

    for last node=current
    current->next=previous

    break loop at current=NULL

    update head thru previous

    complexity:O(n)
*/
node *reverseRecursive(node* &head){

    if(head==NULL||head->next==NULL){
        return head;
    }

    node* newhead=reverseRecursive(head->next);
    head->next->next=head;
    head->next=NULL;

    return newhead;
}

/////////////////////////////////////////////////////////////////////
/*
reverse k nodes of linked list like k=2 :first 2 then next 2 then next 2
time complexity:O(n)
*/

node* reversek(node* &head,int k){
    node* prevptr=NULL;
    node* currptr=head;
    node* nextptr;

    int count=0;
    while(currptr!=NULL && count<k){
        nextptr=currptr->next;
        currptr->next=prevptr;
        prevptr=currptr;
        currptr=nextptr;
        count++;
    }

    //recursive call for rest of linked list
    if(nextptr!=NULL){
        head->next=reversek(nextptr,k);
    }
    head->next=reversek(nextptr,k);
}


int main(){

    //to run it

    node* head=NULL;
    insertAtTail(head,1);
    insertAtTail(head,2);
    insertAtTail(head,3);
    display(head);
    insertAthead(head,4);
    display(head);
    //--------------------
    node* newhead=reverse(head);
    node* newhead=reverseRecursive(head->next);
    display(newhead);
    //--------------------
    cout<<search(head,5)<<endl; //output=0
    cout<<search(head,3)<<endl;

    //well it is done

    //reverse k nodes of linked list
    int k=2;
    node* newHead=reversek(head,k);
    display(newhead);

    cin.get();
}
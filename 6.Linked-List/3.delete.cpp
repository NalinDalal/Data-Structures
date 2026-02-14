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
    cout<<endl;
}

//searching
bool search(node* head, int key){
    node* temp=head;
    while(temp!=NULL){
        if(temp->data==key){
            return true;
        }
        return false;
    }
}

//deleting

void deleteAtHead(node* &head){
    node* todelete=head;
    head=head->next;

    delete todelete;    //necessary otherwise memory will be leaked
}
void deletion(node* &head,int val){

    if(head==NULL){
        return;
    }
    if(head->next==NULL){   //only one element
        deleteAtHead(head);
        return;
    }
    node* temp=head;
    while(temp->next->data!=val){
        temp=temp->next;
    }
    node* todelete=temp->next;
    temp->next=temp->next->next;

    delete todelete;
}

int main(){

    //to run it

    node* head=NULL;
    insertAtTail(head,1);
    insertAtTail(head,2);
    insertAtTail(head,3);
    //display(head);
    insertAthead(head,4);
    //display(head);
    cout<<search(head,5)<<endl;
    deletion(head,3);
    deleteAtHead(head);
    //display(head);

    cin.get();
}
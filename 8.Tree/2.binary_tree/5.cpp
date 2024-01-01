/*
Level Order Traversal:
traverse level wise
to traverse nth level n-1 th must be traversed first

        1
    2        3
4     5   6    7    

insert 1 and null then remove them
insert 2,3,null
then insert child of 2 and remove it
then child of 3 and remove it
next remove NULL and insert at rear end again

then comes last level
just print the data and remove them
at last a NULL object is removed
Queue becomes empty
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Node{
    int data;
    struct Node* left;
    struct Node* right;

    Node(int val){
        data=val;
        left=NULL;
        right=NULL;
    }
};

void printLevelOrder(Node* root){
    if(root==NULL){
        return;
    }

    queue<Node*> q;
    q.push(root);
    q.push(NULL);

    while(!q.empty()){
        Node* node=q.front();
        q.pop();
        if(node!=NULL){
            cout<<node->data<<" ";
            if(node->left)
                q.push(node->left);
            if(node->right)
                q.push(node->right);
        }
        else if(!q.empty())
            q.push(NULL);
    }
}

int main(){
    Node* root=new Node(1);  //root node
    root->left=new Node(2);
    root->right=new Node(3);

    root->left->left=new Node(4);
    root->left->right=new Node(5);

    root->right->left=new Node(6);
    root->right->right=new Node(7);

    printLevelOrder(root);

    cin.get();
}
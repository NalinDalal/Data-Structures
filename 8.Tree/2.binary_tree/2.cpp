/*
Well we have 3 traversing method:
-[]Preorder-node then left subtree
        1
    2       3
  4   5   6     7

  PreOrder:1,2,4,5,3,6,7

-[]InOrder-root whole left subtree then it's value,then right subtree
    InOrder:4,2,5,1,6,3,7

-[]PostOrder-root whole left subtree,then right subtree,then value of node
    PostOrder:4,5,2,6,7,3,1    
*/

//#include <bits/stdc+.h>
#include <iostream>
#include <vector>
#include <algorithm>

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

//function for preorder
void preorder(struct Node* root){

    if(root==NULL){return;} //base condition
    cout<<"PreOrder: ";
    cout<<root->data<<endl;
    preorder(root->left);
    preorder(root->right);
}
//function for inorder
void inorder(struct Node* root){
    cout<<"Inorder:";
    if(root==NULL){
        return;
    }
    // cout<<"Inorder:";
    inorder(root->left);
    cout<<root->data<<endl;
    inorder(root->right);
}

void postorder(struct Node* root){
    cout<<"Post Order:";
    if(root==NULL){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}

int main(){
    struct Node* root=new Node(1);  //root node
    root->left=new Node(2);
    root->right=new Node(3);

    root->left->left=new Node(4);
    root->left->right=new Node(5);

    root->right->left=new Node(6);
    root->right->right=new Node(7);

    preorder(root);

    inorder(root);

    postorder(root);

    cin.get();
}
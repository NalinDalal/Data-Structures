/*
Given a binary tree,flatten it into linked list in-place.
After flattening, left of each node should point to NULL,right contain next node in preorder sequence.

Binary Tree:
        1
       / \
      2   3
         /
        4

Flat Binary Tree:
1
 \
  2
   \
    3
     \
      4

Algorithm:
1.Recursively,flatten left & right subtree
2.Store left tail & right tail
3.Store right subtree in 'temp' & make left subtree as right subtree
4.Join right subtree with left tail
5.return right tail
*/

#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *left, *right;
    Node(int val){
        data=val;
        left=NULL;
        right=NULL;
    }
};

void flatten(Node* root){
    if(root==NULL || (root->left==NULL && root->right==NULL){return;})
    if(root->left!=NULL){
        flatten(root->left);

        Node* temp=root->right;
        root->right=root->left;
        root->left=NULL;

        Node* t=root->right;//phele ye root ka left that
        while(t->right!=NULL){t=t->right;}
        t->right=temp;
    }
    flatten(root->right);
}

void inorderPrint(Node* root){
    if(root==NULL){return;}
    inorderPrint(root->left);
    cout<<root->data<<" ";
    inorderPrint(root->right);
}

int main(){
    Node *root=new Node(4);
    root->left=new Node(9);
    root->right=new Node(5);

    flatten(root);
    inorderPrint(root);
    cout<<endl;
}
/*sum replacement in binary tree
Replace value of each node with sum of all subtree nodes and itself
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
/*
        1
       /  \
      2    3
     / \  / \
    4   5 6  7
*/
void sumReplace(Node* root){
    if(root==NULL){
        return;
        }
    sumReplace(root->left);
    sumReplace(root->right);

    if(root->left!=NULL){
        root->data+=root->left->data;
        }
    if(root->right!=NULL){
        root->data+=root->right->data;
        }
}

void preorder(Node* root){
    if(root==NULL){return;}
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

int main(){
    Node* root=new Node(1);  //root node
    root->left=new Node(2);
    root->right=new Node(3);

    root->left->left=new Node(4);
    root->left->right=new Node(5);

    root->right->left=new Node(6);
    root->right->right=new Node(7);

    //sum replacement
    preorder(root);
    cout<<"\n";
    sumReplace(root);
    preorder(root);
    cout<<"\n";

    return 0;
}
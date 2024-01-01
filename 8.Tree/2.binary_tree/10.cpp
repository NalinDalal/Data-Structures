/*
Balanced Height in Binary Tree

Balanced tree->
difference b/w height of left subtree & right subtree<=1

mod(left ht-right ht)<=1
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

int height(Node* root){
    if(root==NULL){return 0;}
    int lh=height(root->left);
    int rh=height(root->right);
    return max(lh,rh)+1;
}

bool isBalanced(Node* root){
    if(root==NULL){return true;}
    if(isBalanced(root->left)==false){
        return false;
    }
    if(isBalanced(root->right)==false){return false;}

    int lh=height(root->left);
    int rh=height(root->right);
    if(abs(lh-rh)<=1){return true;}
    else{return false;}
}

int main(){
    //Height Balanced Tree
    Node* root1=new Node(1);  //root node
    root1->left=new Node(2);
    root1->right=new Node(3);

    root1->left->left=new Node(4);
    root1->left->right=new Node(5);

    root1->right->left=new Node(6);
    root1->right->right=new Node(7);

    //Not Balanced Tree
    /*
            1
           /
          2
         /
        3*/
    Node* root2=new Node(1);  //root node
    root2->left=new Node(2);
    root2->left=new Node(3);

    root2->left->left=new Node(4);

    if(isBalanced(root1)){cout<<"balanced Tree"<<'\n';}
    else{cout<<"Unbalanced Tree"<<'\n';}

    if(isBalanced(root2)){cout<<"balanced Tree"<<'\n';}
    else{cout<<"Unbalanced Tree"<<'\n';}

    return 0;
}
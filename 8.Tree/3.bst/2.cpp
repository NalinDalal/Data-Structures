//Search in Binary Search Tree
//Time Complexity:O(log n)

/*
key=5
        3
      /  \
     2    7
    /    / \
   1    5   8
       / \
      4   6

      Worst Case T(n)=height of tree

      Level     Time Complexity
      0         n
      1         n/2
      2         n/4
      3         n/8

    Nodes=n,height=h
    1+2+2^2+...+2^h-1=n
    2^h-1=n
    h=log(n+1)
    time complexity=O(log n)
*/

#include <iostream>

using namespace std;

struct Node{
    int data;
    Node *left,*right;
    Node(int val){
        data=val;
        left=NULL;
        right=NULL;
    }
};

/*
binary Search Tree
        4
       / \
      2   5
     / \   \
    1   3   6
*/

//function for searching
Node* searchInBST(Node* root,int key){
    if(root==NULL){return NULL;}
    if(root->data==key){return root;}
    //data>key
    if(root->data>key){return searchInBST(root->left,key);}

    //data<key
    return searchInBST(root->right,key);
}

int main(){
    Node *root=new Node(4);
    root->left=new Node(2);
    root->right=new Node(5);
    root->left->left=new Node(1);
    root->left->right=new Node(3);
    root->right->left=new Node(6);

    if(searchInBST(root,5)==NULL){cout<<"Key doesn't exist";}
    else{
        cout<<"key exist";
    }
    
    cin.get();
}
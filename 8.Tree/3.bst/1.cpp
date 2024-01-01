/*
Search Complexity:O(log n)

Rule 1:The left subtree of a node contains only nodes with keys lesser than the node's key
Rule 2:The right subtree of a node contains only nodes with keys greater than node's key
Rule 3:The left & right tree must also be a BST

Ex:
        3
       / \
      2   7
     /   / \
    1   5   8
       / \
      4   6

ex:
arr=[5,1,3,4,2,7]

        [5]
       /   \
      [1]   [7]
        \
        [3]
        / \
      [2]  [4]
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

//insertion
Node* insertBST(Node *root,int val){
    if(root==NULL){return new Node(val);}
    if(val<root->data){
        root->left=insertBST(root->left,val);
    }
    else{
        //val>root->data
        root->right=insertBST(root->right,val);
    }
    return root;
}

void inorder(Node *root){
    if(root==NULL){return;}
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

int main(){
    Node *root=NULL;
    root=insertBST(root,5);
    insertBST(root,1);
    insertBST(root,3);
    insertBST(root,4);
    insertBST(root,2);
    insertBST(root,7);

    //check if tree contruct is correct or not
    //print inorder-gives sorted array
    inorder(root);
    //output:1 2 3 4 5 7 
    cout<<endl;
    return 0;
}
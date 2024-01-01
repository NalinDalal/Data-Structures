//Delete in Binary Search Tree
//the properties must sty intact even if deleted from b/w
/*
1.Delete the Node
         5
       /  \
      1    7
       \
        3
       / \
      2   4

            5
          /  \
         1    7
          \
           3
          / 
         2   

2.Node has one child
        5
       / \
      1   7
       \
        3
       / \
      2   4 

        5
       / \
      3   7
    / \
   2   4

Steps:
1.Find inorder successor
2.Replace node with inorder successor
3.Delete the Node

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


Node* inorderSucc(Node* root){
    Node* curr=root;
    while(curr && curr->left!=NULL){
        curr=curr->left;
    }
    return curr;
}
//Deletion
Node* deleteInBST(Node* root,int key){
    //searching b/f deletion
    if(key<root->data){
        root->left=deleteInBST(root->left,key);
    }
    else if(key>root->data){
        root->right=deleteInBST(root->right,key);
    }
    else{
        if(root->left==NULL){
            Node* temp=root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL){
            Node* temp=root->left;
            free(root);
            return temp;
        }

        //case 3
        Node* temp=inorderSucc(root->right);
        root->data=temp->data;
        root->right=deleteInBST(root->right,temp->data);
    }
    return root;
}

void inorder(Node* root){
    if(root==NULL){return;}
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

int main(){
    Node *root=new Node(4);
    root->left=new Node(2);
    root->right=new Node(5);
    root->left->left=new Node(1);
    root->left->right=new Node(3);
    root->right->left=new Node(6);

    // if(searchInBST(root,5)==NULL){cout<<"Key doesn't exist";}
    // else{
    //     cout<<"key exist";
    // }

    inorder(root);
    cout<<endl;
    root=deleteInBST(root,5);
    inorder(root);
    cout<<endl;
    cin.get();
}
//Build Balanced BST from sorted array
/*
Strategy:
1.Make middle element the root
2.Recursively do the same for subtrees
    a.start to mid-1 for left subtree
    b.mid+1 to end for right subtree

[10,20,30,40,50]
        30
        / \
       10  40
       \    \
        20   50    
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

Node* sortedArraayToBST(int arr[],int start,int end){
    if(start>end){return NULL;}
    int mid=(start+end)/2;
    Node* root=new Node(arr[mid]);

    root->left=sortedArraayToBST(arr,start,mid-1);
    root->right=sortedArraayToBST(arr,mid+1,end);

    return root;
}

void preorderPrint(Node* root){
    if(root==NULL){return;}
    cout<<root->data<<" ";
    preorderPrint(root->left);
    preorderPrint(root->right);
}

int main(){
    int arr[]={10,20,30,40,50};
    Node* root=sortedArraayToBST(arr,0,4);
    preorderPrint(root);
    cout<<endl;

    return 0;
}
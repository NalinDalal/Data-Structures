/*
//Print All nodes at distance k
(s)          (k)
<------k----->

*root,*node,k

            1
           / \
          5   2
        /    / \
       6    3   4
       \
        7
       / \
      8   9

Node=5,k=3
    Ans={8,9,3,4}  


Case 1:Node's subtree
           5    k=3
          /
         6      k=2
          \
           7    k=1
          / \
         8   9  k=0
    distance covered
    ans={8,9}

Case 2:Node's Ancestors-for all ancestors search other subtree nodes at (K-d)
          1
         / \
        5   2
           / \
          3   4 
    distance to go(dtg)=3-1=2
    d=1

    node(left subtree)->search right
    node(right subtree)->search left
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

//case 1
void printSubtreeNodes(Node *root,int k){
    if(root==NULL||k<0){return;}
    if(k==0){
        cout<<root->data<<" ";
        return;
    }

    printSubtreeNodes(root->left,k-1);
    printSubtreeNodes(root->right,k-1);
}

//case 2
int printNodesAtk(Node *root,Node *target,int k){
    if(root==NULL){return -1;}
    if(root==target){printSubtreeNodes(root,k);
    return 0;
    }

    int dl=printNodesAtk(root->left,target,k);
    if(dl!=-1){
        if(dl+1==k){
            cout<<root->data<<" ";
        }else{printSubtreeNodes(root->right,k-dl-2);}
        return 1+dl;
    }
    int dr=printNodesAtk(root->right,target,k);
    if(dr!=-1){
        if(dr+1==k){
            cout<<root->data<<" ";
        }else{printSubtreeNodes(root->right,k-dr-2);}
        return 1+dr;
    }

    return -1;
}

int main(){
    struct Node* root=new Node(1);  //root node
    root->left=new Node(2);
    root->right=new Node(3);

    root->left->left=new Node(4);
    root->left->right=new Node(5);

    printNodesAtk(root,root->left,1);
    cin.get();
}
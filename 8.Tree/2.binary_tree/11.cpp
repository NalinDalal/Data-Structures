/*
Right View of tree-nodes visible from right side

            (1)
           /   \ 
          (2)   (3)
         /     /  \
        (4)   (5)  (6)
              /
             (7)

Right View:1,3,6,7
Level Order Traversal-Use Queue
*/

//#include <bits/stdc++>
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
       / \
      2    3
     / \  / \
    4   5 6   7
*/

void rightView(Node* root){
    if(root==NULL){return;}

    queue<Node*> q;
    q.push(root);

    while(!q.empty()){
        int n=q.size();
        for(int i=0;i<n;i++){
            Node* curr=q.front();
            q.pop();

            if(i==n-1){cout<<curr->data<<" ";}
            if(curr->left!=NULL){q.push(curr->left);}
            if(curr->right!=NULL){q.push(curr->right);}
        }
    }
}

int main(){
    struct Node* root=new Node(1);  //root node
    root->left=new Node(2);
    root->right=new Node(3);

    root->left->left=new Node(4);
    root->left->right=new Node(5);

    //right view
    rightView(root);
    cin.get();
}
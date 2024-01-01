/*
Sum of nodes at Kth Level
                5
            6       3
        9      1  2     1
            2       6
         3     5        7   

let k=3
nodes at 3rd level-2,6;sum=8    

well the tree is
        1
       /  \
     2      3
    / \    / \
    4  5  6   7   

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

//make queue and keep track of sum of nodes
int sumAtK(Node* root,int k){
    if(root==NULL){return -1;}
    queue<Node*> q;
    q.push(root);
    q.push(NULL);
    int level=0;
    int sum=0;

    while(!q.empty()){
        Node* node=q.front();
        q.pop();

        if(node!=NULL){
            if(level==k){sum+=node->data;}
            if(node->left){q.push(node->left);}
            if(node->right){q.push(node->right);}
        }
        else if(!q.empty()){
            q.push(NULL);
            level++;
        }
    }
    return sum;
}

int main(){
    Node *root=new Node(1);  //root node
    root->left=new Node(2);
    root->right=new Node(3);

    root->left->left=new Node(4);
    root->left->right=new Node(5);

    root->right->left=new Node(6);
    root->right->right=new Node(7);

    //printLevelOrder(root);

    cout<<sumAtK(root,2);

    cin.get();
}
/*
Maximum Path Sum
Maximum possible sum of a path in binary tree,starting & ending at any node

Algorithm->
for each node compute:
1.Node val
2.Max path through left child+node val
3.Max path through right child+node val
4.max path through left child+max path through right child+node val 
*/

#include <iostream>
#include <vector>
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

bool getPath(Node *root,int key,vector<int> &path){
    if(root==NULL){return false;}

    path.push_back(root->data);
    if(root->data==key){return true;}
    if(getPath(root->left,key,path)|| getPath(root->right,key,path)){return true;}

    path.pop_back();
    return false;
}

int LCA(Node* root,int n1,int n2){
    vector<int> path1,path2;

    if(!getPath(root,n1,path1) || !getPath(root,n2,path2)){ return -1;}

    int pc;
    for(pc=0;pc<path1.size() && path2.size();pc++){
        if(path1[pc]!=path2[pc]){break;}
    }
    return path1[pc-1];
}

int maxPathSumUtil(Node *root,int &ans){
    if(root==NULL){return 0;}

    int left=maxPathSumUtil(root->left,ans);
    int right=maxPathSumUtil(root->right,ans);

    int nodeMax=max(max(root->data,root->data+left+right),
                max(root->data+left,root->data+right));
    ans=max(ans,nodeMax);
    int singlePathSum=max(root->data,max(root->data+left,root->data+right));
    return singlePathSum;
}

int maxPathSum(Node *root){
    int ans=INT_MIN;
    maxPathSumUtil(root,ans);
    return ans;
}

int main(){
    /*
            1
           / \
          2   3
         /   / \
        4   5   6
           /
          7
    */

    Node *root=new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->right->left = new Node (5);
    root->right->right = new Node(6);
    root->right->left->left = new Node(7);

    int n1=7;
    int n2=6;
    int lca=LCA(root,n1,n2);

    if(lca==-1){cout<<"LCA doesn't exist"<<endl;}
    else{cout<<"LCA: "<<lca<<endl;}

    // int n3=7;
    // int n4=6;
    // Node* lcaa=LCA(root,n3,n4);

    // if(lcaa==-1){cout<<"LCA doesn't exist"<<endl;}
    // else{cout<<"LCA: "<<lcaa->data<<endl;}

    cout<<maxPathSum(root);

    cin.get();
}
/*
Height of Binary tree
-It's depth of the tree's deepest node

Diameter
- Number of nodes in longest path b/w any 2 leaves

Intuition
    @
   /        \
left dia    right dia
left height    right height

Intuition:
MAX{
    Left Height+Right Height+1,Left Diameter,Right Diameter
}
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

int calcDiameter2(Node* root,int* height){
    if(root==NULL){*height=0;return 0;}
    int lh=0,rh=0;
    int lDiameter=calcDiameter2(root->left,&lh);
    int rDiameter=calcDiameter2(root->right,&rh);

    int currDiameter=lh+rh+1;
    *height=max(lh,rh)+1;

    return max(currDiameter, max(lDiameter,rDiameter));
}

int calcHeight(Node* root){
    if(root==NULL){return 0;}
    int lHeight=calcHeight(root->left);
    int rHeight=calcHeight(root->right);
    return max(lHeight,rHeight)+1;
}

int calcHeight2(Node* root){
    if(root==NULL){return 0;}
    return max(calcHeight(root->left),calcHeight(root->right))+1;
}
//T(n)=O(n)

int calcDiameter(Node* root){
    //base condition
    if(root==NULL){return 0;}

    int lHeight=calcHeight(root->left);
    int rHeight=calcHeight(root->right);
    int currDiameter=lHeight+rHeight+1;

    int lDiameter=calcDiameter(root->left);
    int rDiameter=calcDiameter(root->right);

    return max(currDiameter,max(lDiameter,rDiameter));
}
//T(n)=O(n^2)
//hmm height ki O(n) thi then dia ki apni O(n) so pure function ki O(n^2)

int main(){
    Node* root=new Node(1);  //root node
    root->left=new Node(2);
    root->right=new Node(3);

    root->left->left=new Node(4);
    root->left->right=new Node(5);

    root->right->left=new Node(6);
    root->right->right=new Node(7);

    //Height of Binary Tree
    cout<<"Height of tree is:"<<calcHeight(root)<<"\n";

    //diameter of Binary Tree
    cout<<"Diameter of tree is:"<<calcDiameter(root)<<"\n";

    //optimized diameter of binary tree
    int height=0;
    cout<<calcDiameter2(root,&height)<<"\n";

    cin.get();
}
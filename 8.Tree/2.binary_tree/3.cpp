/*
Build tree from PreOrder,InOrder
    PreOrder:1,2,3
    InOrder:2,1,3
Algorithm
1. Pick element from preorder & create a node
2. Increment preorder idx
3. Search for picked element's pos in inorder
4. Call to build left subtree from inorder's 0 to pos-1
5. Call to build right subtree from inorder pos+1 to n
6. Return the node


Preorder:1 2 3 4 5
Inorder:4 2 1 5 3

Divide into 2 sub array and then use it to create tree
*/

#include <iostream>

using namespace std;

struct Node {
  int data;
  struct Node *left;
  struct Node *right;

  Node(int val) {
    data = val;
    left = NULL;
    right = NULL;
  }
};

int search(int inorder[], int start, int end, int curr) {
  for (int i = start; i <= end; i++) {
    if (inorder[i] == curr) {
      return i;
    }
  }
  return -1;
}
Node *buildTree(int preorder[], int inorder[], int start, int end) {
  static int idx = 0;
  // piar of invalid ptr;start>end
  if (start > end) {
    return NULL;
  }
  int curr = preorder[idx];
  idx++;
  Node *node = new Node(curr);
  if (start == end) { // no child only 1 node
    return node;
  }
  int pos = search(inorder, start, end, curr);
  node->left = buildTree(preorder, inorder, start, pos - 1);
  node->right = buildTree(preorder, inorder, pos + 1, end);
  // exist only for element>1
  return node;
}

void inorderPrint(Node *root) {
  if (root == NULL) {
    return;
  }

  inorderPrint(root->left);
  cout << root->data << " ";
  inorderPrint(root->right);
}

int main() {
  int preorder[] = {1, 2, 4, 3, 5}; // array made man for preorder
  int inorder[] = {4, 2, 1, 5, 3};  // array made for inorder

  // build tree
  Node *root = buildTree(preorder, inorder, 0, 4);
  inorderPrint(root);
  return 0;
}

/*
Tree from PostOrder & InOrder
Root ka left subtree then right subtree
then at last root node
so it's just opposite of PreOrder & Inorder

Algorithm:
1. Start from the end of postorder & pick an element to create a node
2. Decrement postorder idx
3. Search for picked element's pos in inorder
4. Call to build right subtree from inorder's pos+1 to n
5. Call to build left subtree from inorder 0 to pos-1
6. Return the node
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

int search(int inorder[], int start, int end, int val) {
  for (int i = start; i <= end; i++) {
    if (inorder[i] == val) {
      return i;
    }
  }
  return -1;
}

Node *buildTree(int postorder[], int inorder[], int start, int end) {
  static int idx = 4;

  // basecase
  if (start > end) {
    return NULL;
  }

  int val = postorder[idx]; // value stored
  idx--;
  Node *curr = new Node(val);
  // no need to create left,right subtree
  if (start == end) {
    return curr;
  }

  int pos = search(inorder, start, end, val);

  // construction of tree
  curr->right = buildTree(postorder, inorder, pos + 1, end);  // right subtree
  curr->left = buildTree(postorder, inorder, start, pos - 1); // left subtree

  return curr;
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
  int postorder[] = {4, 2, 5, 3, 1};
  int inorder[] = {4, 2, 1, 5, 3};

  // build tree
  Node *root = buildTree(postorder, inorder, 0, 4);
  inorderPrint(root);
  cout << "\n";

  cin.get();
}

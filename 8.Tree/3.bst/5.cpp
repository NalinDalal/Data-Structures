// Check for BST
/*
Approach 1:
node>left child
node<right child

Approach 2:
Max of left subtree(maxL)
Min of right subtree(minR)

node>maxL,node<minR

Approach 3(traverse nodes once):
min,max allowed
min allowed<node
max allowed>node

    node(min,max)
    /           \
 left           right
 (min,node)     (node,max)
*/

#include <iostream>
using namespace std;

struct Node {
  int data;
  Node *left, *right;
  Node(int val) {
    data = val;
    left = NULL;
    right = NULL;
  }
};

// check for BST
bool isBST(Node *root, Node *min = NULL, Node *max = NULL) {
  if (root == NULL) {
    return true;
  }
  if (min != NULL && root->data <= min->data) {
    return false;
  }
  if (max != NULL && root->data >= max->data) {
    return false;
  }
  bool leftValid = isBST(root->left, min, root);
  bool rightValid = isBST(root->right, root, max);
  return leftValid and rightValid;
}

int main() {
  Node *root1 = new Node(1);
  root1->left = new Node(2);
  root1->right = new Node(5);
  /*  Tree 1
          1
         / \
        2   3
  */
  if (isBST(root1, NULL, NULL)) {
    cout << "valid BST" << endl;
  } else {
    cout << "Invalid BST" << endl;
  }

  cin.get();
}

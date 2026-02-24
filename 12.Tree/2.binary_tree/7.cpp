/*
Count all nodes in a Binary Tree

well the tree is
        1
       /  \
     2      3
    / \    / \
    4  5  6   7
*/

#include <iostream>
#include <queue>

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

int sumAtK(Node *root, int k) {
  if (root == NULL) {
    return -1;
  }
  queue<Node *> q;
  q.push(root);
  q.push(NULL);
  int level = 0;
  int sum = 0;

  while (!q.empty()) {
    Node *node = q.front();
    q.pop();

    if (node != NULL) {
      if (level == k) {
        sum += node->data;
      }
      if (node->left) {
        q.push(node->left);
      }
      if (node->right) {
        q.push(node->right);
      }
    } else if (!q.empty()) {
      q.push(NULL);
      level++;
    }
  }
  return sum;
}

int countNodes(Node *root) {
  if (root == NULL) {
    return 0;
  }
  return countNodes(root->left) + countNodes(root->right) + 1;
}

int sumNodes(Node *root) {
  // left subtree sum+right subtree sum+node value
  if (root == NULL) {
    return 0;
  }
  return sumNodes(root->left) + sumNodes(root->right) + root->data;
}

int main() {
  Node *root = new Node(1); // root node
  root->left = new Node(2);
  root->right = new Node(3);

  root->left->left = new Node(4);
  root->left->right = new Node(5);

  root->right->left = new Node(6);
  root->right->right = new Node(7);

  // count of nodes
  cout << "The no of nodes:" << endl;
  cout << countNodes(root) << endl;
  // sum of nodes
  cout << "Sum of Nodes:" << endl;
  cout << sumNodes(root) << endl;

  cin.get();
}

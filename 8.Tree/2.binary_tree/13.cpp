// Find distance b/w 2 nodes in binary tree.distance b/w 2 nodes is min num of
// edges to be traversed to reach one node from another
/*
1.Find LCA(lowest common ancestor)
2.Find distance of n1(d1) & n2(d2) from LCA
3.Return (d1+d2)

        1
       / \
      2   3
     /   / \
    4   5   6(d2=1)
       / \
      7   8
    d1=2
distance =d1+d2
=2+1
=3
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

Node *LCA(Node *root, int n1, int n2) {
  if (root == NULL) {
    return NULL;
  }
  if (root->data == n1 || root->data == n2) {
    return root;
  }

  Node *left = LCA(root->left, n1, n2);
  Node *right = LCA(root->right, n1, n2);

  if (left != NULL && right != NULL) {
    return root;
  }
  if (left == NULL && right == NULL) {
    return NULL;
  }

  if (left != NULL) {
    return LCA(root->left, n1, n2);
  }
  return LCA(root->right, n1, n2);
}

int findDist(Node *root, int k, int dist) {
  if (root == NULL) {
    return -1;
  }
  if (root->data == k) {
    return dist;
  }

  int left = findDist(root->left, k, dist + 1);
  if (left != -1) {
    return left;
  }
  return findDist(root->right, k, dist + 1);
}

int distBtwNodes(Node *root, int n1, int n2) {
  Node *lca = LCA(root, n1, n2);

  int d1 = findDist(lca, n1, 0);
  int d2 = findDist(lca, n2, 0);

  return d1 + d2;
}

int main() {
  struct Node *root = new Node(1); // root node
  root->left = new Node(2);
  root->right = new Node(3);

  root->left->left = new Node(4);
  root->left->right = new Node(5);

  // test
  cout << distBtwNodes(root, 4, 5) << endl;

  cin.get();
}

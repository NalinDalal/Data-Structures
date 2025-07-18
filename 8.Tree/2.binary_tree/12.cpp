/*
Left View of tree-nodes visible from left side

            (1)
           /   \
          (2)   (3)
         /     /  \
        (4)   (5)  (6)
              /
             (7)

Left View:1,2,4
Level Order Traversal-Use Queue
*/

#include <iostream>
#include <queue>

using namespace std;

struct Node {
  int data;
  // struct Node* left;
  // struct Node* right;
  Node *left, *right;

  Node(int val) {
    data = val;
    left = NULL;
    right = NULL;
  }
};

/*
        1
       / \
      2    3
     / \  / \
    4   5 6   7
*/

void leftView(Node *root) {
  if (root == NULL) {
    return;
  }

  queue<Node *> q;
  q.push(root);

  while (!q.empty()) {
    int n = q.size();
    for (int i = 0; i < n; i++) {
      // Node* curr=q.front();
      Node *temp = q.front();
      q.pop();

      // if(i==n-1){cout<<curr->data<<" ";}
      // if(curr->left!=NULL){q.push(curr->left);}
      // if(curr->right!=NULL){q.push(curr->right);}

      if (i == 1) {
        cout << temp->data << " ";
      }

      if (temp->left != NULL) {
        q.push(temp->left);
      }
      if (temp->right != NULL) {
        q.push(temp->right);
      }
    }
  }
}

int main() {
  struct Node *root = new Node(1); // root node
  root->left = new Node(2);
  root->right = new Node(3);

  root->left->left = new Node(4);
  root->left->right = new Node(5);

  // right view
  leftView(root);
  cin.get();
}

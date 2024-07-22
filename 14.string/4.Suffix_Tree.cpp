/*
* Suffix trees are efficient for various string operations. Suffix arrays
provide a space-efficient way of achieving similar results. A suffix tree is a
compressed trie of all suffixes of a given text. It's a powerful data structure
that allows for efficient search, substring, and many other string operations. A
suffix array is an array of integers giving the starting positions of suffixes
of a string in lexicographical order.


*/

// suffix tree
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct SuffixTreeNode {
  unordered_map<char, SuffixTreeNode *> children;
  int index;
  SuffixTreeNode() : index(-1) {}
};

void build_suffix_tree(SuffixTreeNode *root, const string &text) {
  int n = text.length();
  for (int i = 0; i < n; ++i) {
    SuffixTreeNode *node = root;
    for (int j = i; j < n; ++j) {
      if (node->children.find(text[j]) == node->children.end()) {
        node->children[text[j]] = new SuffixTreeNode();
      }
      node = node->children[text[j]];
    }
    node->index = i;
  }
}

void search_suffix_tree(SuffixTreeNode *node, const string &pattern) {
  SuffixTreeNode *current = node;
  for (size_t i = 0; i < pattern.length(); ++i) {
    char c = pattern[i];
    if (current->children.find(c) == current->children.end()) {
      cout << "Pattern not found" << endl;
      return;
    }
    current = current->children[c];
  }

  // Collect all indices in the subtree.
  vector<int> indices;
  vector<SuffixTreeNode *> stack;
  stack.push_back(current);

  while (!stack.empty()) {
    SuffixTreeNode *n = stack.back();
    stack.pop_back();

    if (n->index != -1) {
      indices.push_back(n->index);
    }
    for (unordered_map<char, SuffixTreeNode *>::iterator it =
             n->children.begin();
         it != n->children.end(); ++it) {
      stack.push_back(it->second);
    }
  }

  cout << "Pattern found at indexes: ";
  for (size_t i = 0; i < indices.size(); ++i) {
    cout << indices[i] << " ";
  }
  cout << endl;
}

int main() {
  string text = "banana";
  string pattern = "ana";
  SuffixTreeNode *root = new SuffixTreeNode();
  build_suffix_tree(root, text);
  search_suffix_tree(root, pattern);
  return 0;
}

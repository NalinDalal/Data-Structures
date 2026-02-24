## Binary Tree

### What is a Binary Tree?

A **Binary Tree** is a **special type of tree** where **each node has at most two children** — usually called:

- **Left child**
- **Right child**

It’s the foundation for many powerful structures like **Binary Search Tree**, **Heap**, **AVL Tree**, and even **Expression Trees**.

---

### Structure Example

```
       1
     /   \
    2     3
   / \     \
  4   5     6
```

- Root: `1`
- Children of `2`: `4` and `5`
- `3` has only a right child `6`
- Leaf nodes: `4`, `5`, `6`

---

### Properties

| Property             | Description                            |
| -------------------- | -------------------------------------- |
| Nodes per level      | Level `i` can have at most `2^i` nodes |
| Max nodes (height h) | `2^(h+1) - 1` nodes                    |
| Min height (n nodes) | `log₂(n + 1) - 1`                      |

---

### Why Use Binary Trees?

- Easy to implement
- Good for **hierarchical data**
- Forms the **basis for search trees and heaps**
- Optimized insert/search/traverse operations (in BST, AVL, etc.)

---

### Operations on Binary Tree

#### Insertion

- Usually done level-by-level (like a complete tree)

#### Traversal (very important)

| Type            | Order                     |
| --------------- | ------------------------- |
| **Inorder**     | Left → Root → Right       |
| **Preorder**    | Root → Left → Right       |
| **Postorder**   | Left → Right → Root       |
| **Level Order** | Breadth-first (via queue) |

• pre-order: first process the root, then traverse the left subtree, then
traverse the right subtree
• in-order: first traverse the left subtree, then process the root, then traverse
the right subtree
• post-order: first traverse the left subtree, then traverse the right subtree,
then process the root

#### Deletion

- Needs pointer adjustment based on the position

---

### Common Applications

- Expression parsing (`(a + b) * c`)
- Syntax tree in compilers
- Decision trees in ML
- Balanced trees (BST, AVL) for fast searching
- Huffman coding trees (compression)

---

### Types of Binary Trees

| Type                    | Description                                |
| ----------------------- | ------------------------------------------ |
| **Full**                | Every node has 0 or 2 children             |
| **Perfect**             | Full and all leaf nodes at same level      |
| **Complete**            | All levels filled except possibly last     |
| **Skewed (left/right)** | All nodes have only one child (left/right) |

---

### C++ Node Structure Example

```cpp
struct Node {
    int data;
    Node* left;
    Node* right;
};
```

or 

```cpp
typedef struct nodeT{
  struct nodeT *left;
  struct nodeT *right;
  int value;
} node;
```

---

### Summary

- **Binary Tree** = Each node has ≤ 2 children
- Easy to build and extend into **BST**, **Heaps**, etc.
- Mastering binary trees is crucial for **interviews**, **compilers**, and **system-level data structures**

# 🌳 Binary Search Tree (BST) – README

### 📌 What is a Binary Search Tree?

A **Binary Search Tree (BST)** is a special kind of **binary tree** where:

- **Left child < Parent**
- **Right child > Parent**

This rule applies **recursively** to all nodes in the tree.

---

### 📈 Real-life Example:

Let's say you insert these numbers into a BST:

`50, 30, 70, 20, 40, 60, 80`

The BST would look like:

```
       50
     /    \
   30      70
  /  \    /  \
20   40  60  80
```

---

### 💡 Key Properties

| Property          | Description                                            |
| ----------------- | ------------------------------------------------------ |
| Search Time       | O(log n) average, O(n) worst                           |
| Insert/Delete     | O(log n) average, O(n) worst                           |
| Inorder Traversal | Yields elements in **sorted order**                    |
| Balanced BST      | Ensures height is O(log n) (e.g. AVL, Red-Black Trees) |

---

### 🛠️ Common Operations

#### 🔍 Search

Search starts from the root:

- Go **left** if the target is smaller
- Go **right** if it's larger

```pgsql
Worst-case = height of the tree
If perfectly balanced, height = log₂(n)
Time Complexity = O(log n)
```

```python-repl
Level     Nodes
0         n
1         n/2
2         n/4
...
Total levels = log(n+1)
```

Algo:

```cpp
if (key == node->val) → found
else if (key < node->val) → go left
else → go right

```

#### ➕ Insertion

Insert like a binary tree, but maintain the **BST property**:

```cpp
if (root == NULL) → create node
if (val < root->val) → insert left
else → insert right

```

#### ❌ Deletion

Three cases:

1. **Leaf Node** – Just delete
2. **One Child** – Replace node with child
3. **Two Children** – Replace with **inorder successor** or **predecessor**

#### 📚 Traversal

| Type       | Order                   | Output (BST)            |
| ---------- | ----------------------- | ----------------------- |
| Inorder    | Left → Root → Right     | Sorted ascending order  |
| Preorder   | Root → Left → Right     | Used for copying tree   |
| Postorder  | Left → Right → Root     | Used for deleting tree  |
| LevelOrder | Level-wise (uses queue) | Breadth-first traversal |

---

### 👨‍💻 C++ Structure

```cpp
struct Node {
    int data;
    Node* left;
    Node* right;
};
```

### 🚀 Insertion Example

```cpp
Node* insert(Node* root, int val) {
    if (root == nullptr)
        return new Node{val, nullptr, nullptr};
    if (val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}
```

---

### 🧠 Why Use BST?

- Efficient **search, insert, delete**
- Used in **databases**, **map/set in STL**, **file systems**
- Basis for self-balancing trees (AVL, Red-Black Trees)

---

### ❗ Limitations

- **Can become skewed** like a linked list if not balanced
- Worst-case time = O(n)

To avoid this → Use **Balanced BSTs** (e.g., AVL, Red-Black Tree)

---

### 📂 Applications

- **Dynamic sets**
- **Symbol table** in compilers
- **Autocomplete** suggestions
- **Sorted datasets** management
- **Range queries**

---

### ✅ Summary

- **BST = Binary Tree + Ordered Rule**
- Every operation is guided by: `left < root < right`
- Great for **sorted data, fast search, insertion**
- Balance is key → Consider **AVL/Red-Black** for production use

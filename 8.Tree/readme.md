## 🌳 Tree – Basic README

### 📌 What is a Tree?

A **tree** is a **non-linear hierarchical data structure** used to store data in a **parent-child** relationship.

Unlike arrays or linked lists (which are linear), **trees branch out** like an actual tree — starting from a single **root** and growing through **nodes** connected by **edges**.

---

### 📂 Real-life Examples

- Folder structure in your computer
- Family tree
- Organization chart (CEO → Manager → Employees)

---

### 🧱 Basic Terminology

| Term        | Meaning                                     |
| ----------- | ------------------------------------------- |
| **Node**    | A single element of the tree (stores data). |
| **Root**    | Topmost node (entry point).                 |
| **Child**   | Node directly connected below another node. |
| **Parent**  | Node directly above another node.           |
| **Leaf**    | Node with **no children** (end node).       |
| **Edge**    | The connection between parent and child.    |
| **Subtree** | A smaller tree within the main tree.        |
| **Height**  | Length of longest path from root to a leaf. |
| **Depth**   | Number of edges from root to the node.      |

---

### 🛠️ Common Operations

- **Insertion**: Add a new node under a parent.
- **Traversal**: Visit all nodes in some order.

  - **Preorder** (Root → Left → Right)
  - **Inorder** (Left → Root → Right)
  - **Postorder** (Left → Right → Root)
  - **Level Order** (Breadth First)

- **Searching**: Find if a node exists.
- **Deletion**: Remove a node and restructure children if needed.

---

### ✅ Example (Simple Tree)

```
        A
       / \
      B   C
     / \
    D   E
```

- Root: A
- Children of A: B, C
- Parent of D: B
- Leaf nodes: D, E, C

---

### 🧠 Why Use Trees?

- Fast hierarchical lookups
- Efficient insertion and deletion in sorted structure (like BSTs)
- Ideal for structured data: file systems, compilers, etc.

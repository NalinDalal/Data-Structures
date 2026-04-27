# Binary Search Tree (BST)

A **Binary Search Tree (BST)** is a special kind of **binary tree** where:

- **Left child < Parent**
- **Right child > Parent**

This rule applies **recursively** to all nodes in the tree.

---

### Real-life Example:

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

### Key Properties

All values in left subtree < node.val < all values in right subtree


| Property          | Description                                            |
| ----------------- | ------------------------------------------------------ |
| Search Time       | O(log n) average, O(n) worst                           |
| Insert/Delete     | O(log n) average, O(n) worst                           |
| Inorder Traversal | Yields elements in **sorted order**                    |
| Balanced BST      | Ensures height is O(log n) (e.g. AVL, Red-Black Trees) |

---

### Common Operations

#### Search

Search starts from the root:

- Go **left** if the target is smaller
- Go **right** if it's larger

algortihm:

```
Start at the root node
Loop while current node isn't NULL
    If the current node's value is equal to your value
        Return the current node
    If the current node's value is less than your value
        Make the left node your current node
    If the current node's value is greater than your value
        Make the right node your current node
End loop
```

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

```
//recursive
TREE-SEARCH(x, k):
    if x =NIL or k=key[x]
        return x
    if k < key[x]
        return TREE-SEARCH(left[x], k)
    else
        return TREE-SEARCH(right[x], k)
```

```
//iterative
iterativeTreeSearch(x,k):
    while x ̸!=NIL and k !=key[x]
        do if k < key[x]
            then x ←left[x]
            else x ←right[x]
    return x
```

#### Insertion

Insert like a binary tree, but maintain the **BST property**:

```
TREE-INSERT(T, z):
    y ←NIL
    x ←root[T ]
    while x ̸!=NIL:
        do y ←x
            if key[z] < key[x]
                x ←left[x]
            else
                x ←right[x]
    p[z] ←y
    if y=NIL
        root[T ] ←z
    else if key[z] < key[y]
        left[y] ←z
    else right[y] ←z
```

begins at the root of the
tree and traces a path downward. The pointer x traces the path, and the pointer y
is maintained as the parent of x.

```cpp
if (root == NULL) → create node
if (val < root->val) → insert left
else → insert right

```

Time: O(h) where h is height of tree

#### Deletion

Three cases:

1. **Leaf Node/No Child** –> Just delete
2. **One Child** –> Replace node with child
3. **Two Children** –> Replace with **inorder successor** or **predecessor**

```
TREE-DELETE(T, z):
    if left[z]=NIL or right[z]=NIL
        then y ←z
    else y ←TREE-SUCCESSOR(z)
    if left[y] ̸!=NIL
        x ←left[y]
    else x ←right[y]
    if x ̸!=NIL
        p[x] ←p[y]
    if p[y]=NIL
        root[T ] ←x
    else if y=left[p[y]]
        left[p[y]] ←x
    else
        right[p[y]] ←x
    if y!=z
        key[z] ←key[y]
        copy y’s satellite data into z
    return y
```

Time: O(h) where h is height of tree

#### Traversal

| Type       | Order                   | Output (BST)            |
| ---------- | ----------------------- | ----------------------- |
| Inorder    | Left → Root → Right     | Sorted ascending order  |
| Preorder   | Root → Left → Right     | Used for copying tree   |
| Postorder  | Left → Right → Root     | Used for deleting tree  |
| LevelOrder | Level-wise (uses queue) | Breadth-first traversal |

```
INORDER-TREE-WALK(x){       //Takes linear time; O(n)
    if (x ̸=NIL){
        INORDER-TREE-WALK(left[x])
        print key[x]
        INORDER-TREE-WALK(right[x])
    }
}
```

---

### C++ Structure

```cpp
struct Node {
    int data;
    Node* left;
    Node* right;
};
```

### Insertion Example

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

### Why Use BST?

- Efficient **search, insert, delete**
- Used in **databases**, **map/set in STL**, **file systems**
- Basis for self-balancing trees (AVL, Red-Black Trees)

---

# Ordered Operations

This is missing from your notes but critical.

## lower_bound(k)

```
Find smallest value ≥ k
```

Algorithm:

```
res = NULL
node = root

while node:
    if node.val ≥ k:
        res = node
        node = node.left
    else:
        node = node.right

return res
```

Time: `O(h)`

---

## upper_bound(k)

```
Find smallest value > k
```

Same logic, just strict comparison.

---

# Range Queries on BST

Add this section explicitly.

## Range Sum / Range Count

```
sum(l, r) = sum of all values in [l, r]
```

### Key pruning logic:

```
if node.val < l:
    ignore left subtree → go right

if node.val > r:
    ignore right subtree → go left

if node.val in [l, r]:
    include node
    explore both sides
```

Time:

```
O(h + k)
k = number of nodes in range
```

---

## Important Optimization 

```
Augment node with subtree_sum
```

Then:

```
If entire subtree ∈ [l, r] → take sum directly
```

This converts many problems from linear to logarithmic.

---

### Limitations

- **Can become skewed** like a linked list if not balanced
- Worst-case time = O(n)

To guarantee O(log n):

Use self-balancing BSTs:
- AVL Tree
- Red-Black Tree


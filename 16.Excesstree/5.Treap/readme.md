# Treap (Tree + Heap) / Cartesian Tree

A **Treap** is a randomized BST that simultaneously satisfies:

- **BST property on x**: For every node, all keys in the left subtree are `< node.x`, and all keys in the right subtree are `> node.x`.
- **Max-Heap property on y**: Every node's `y` value (priority) is **greater than or equal to** its children's `y` values.

Each node stores a pair `(x, y)` where `x` is the actual key (determines BST order) and `y = rand()` is a randomly assigned priority (determines heap order). Because priorities are random, the expected height of the tree is **O(log n)**.

> Also called a **Cartesian Tree** when used in its general form.

## Key Properties

- **Two invariants at once**: BST on keys, max-heap on priorities.
- **Randomized balance**: `y = rand()` ensures expected height O(log n) without explicit rotations like AVL/Red-Black trees.
- **Expected height**: `E(H) = O(log n)`
- **Core operations**: `split` and `merge` — everything else (insert, delete, get) is built on top of these two.

**Visual: What a Treap looks like (x on x-axis, y on y-axis)**

```
        (root — max y)
           ●
          / \
         ●   ●
        / \   \
       ●   ●   ●
                \
                 ●
```

> If you project each node onto the x-axis (by key) and y-axis (by priority), the tree is exactly the heap-ordered structure over a scatter plot of points.

---

## Node Structure

Each node holds:

| Field | Meaning |
|-------|---------|
| `x` | Key (BST ordering) |
| `y` | Priority — assigned as `rand()` |
| `left` | Left child pointer |
| `right` | Right child pointer |

```
struct Node {
    int x, y;
    Node* left;
    Node* right;
    Node(int x) : x(x), y(rand()), left(nullptr), right(nullptr) {}
};
```

---

## Core Operations

### 1. Split — O(log n) expected

`split(node, x)` splits the treap rooted at `node` into two treaps:
- **First**: all nodes with key `< x`
- **Second**: all nodes with key `≥ x`

**Pseudocode:**

```
split(node, x) → {first, second}
  if node = null
    return {null, null}

  if node.x < x
    p = split(node.right, x)
    node.right = p.first
    return {node, p.second}

  else
    p = split(node.left, x)
    node.left = p.second
    return {p.first, node}
```

**Diagram — split at value x:**

```
graph TD
    subgraph Before["Before split(node, x)"]
        direction TB
        R["node (root)"]
        R --> L["subtree < x"]
        R --> Ri["subtree ≥ x"]
    end

    subgraph After["After split"]
        direction LR
        T1["Tree 1 — all keys < x"]
        T2["Tree 2 — all keys ≥ x"]
    end

    Before --> After

    style T1 fill:#22c55e,color:#fff
    style T2 fill:#3b82f6,color:#fff
```

**How it works:**
- If `node.x < x`: the current node and its left subtree go to the **left part**. Recurse on `node.right` to split the right subtree, and reattach `p.first` as `node.right`.
- If `node.x ≥ x`: the current node and its right subtree go to the **right part**. Recurse on `node.left`, reattach `p.second` as `node.left`.

---

### 2. Merge — O(log n) expected

`merge(A, B)` merges two treaps into one, assuming **all keys in A < all keys in B** (i.e., this is a structural merge, not a general union). The heap property on `y` is restored by always picking the root with the higher priority.

**Pseudocode:**

```
merge(A, B) → node
  if A = null  →  return B
  if B = null  →  return A

  if A.y > B.y
    A.right = merge(A.right, B)
    return A
  else
    B.left = merge(A, B.left)
    return B
```

**Diagram — merge(A, B):**

```
graph TD
    subgraph Input["Input: two treaps A and B (all keys in A < all keys in B)"]
        direction LR
        TA["A (root has higher y?)"]
        TB["B"]
    end

    subgraph Case3["Case: A.y > B.y → A becomes root"]
        A2["A (root)"]
        A2 --> AL["A.left (unchanged)"]
        A2 --> MR["merge(A.right, B)"]
    end

    subgraph Case4["Case: B.y ≥ A.y → B becomes root"]
        B2["B (root)"]
        B2 --> ML["merge(A, B.left)"]
        B2 --> BR["B.right (unchanged)"]
    end

    Input --> Case3
    Input --> Case4

    style A2 fill:#22c55e,color:#fff
    style B2 fill:#3b82f6,color:#fff
```

**Why this works:** At each step the node with the larger `y` becomes the root (maintaining heap order). Since all keys of A < all keys of B, BST order is automatically maintained.

---

## Higher-Level Operations (built on split + merge)

### 3. Insert — O(log n) expected

To insert a new node `newNode` with key `newNode.x` and random priority `newNode.y`:

```
add(node, newNode) → node
  if newNode.y > node.y
    p = split(node, newNode.x)
    newNode.left  = p.first
    newNode.right = p.second
    return newNode

  if newNode.x < node.x
    node.left = add(node.left, newNode)
  else
    node.right = add(node.right, newNode)

  return node
```

**Logic:** If `newNode.y` is larger than the current root's `y`, `newNode` must become an ancestor — so split the current tree at `newNode.x` and attach both halves as children of `newNode`. Otherwise, recurse down the BST like a normal insertion.

---

### 4. Delete — O(log n) expected

To delete a node with key `k`:
1. `split` the treap into L (keys < k), M (keys = k), R (keys > k).
2. Discard M (the node to delete).
3. `merge(L, R)` to reunite.

```
// delete key k from treap rooted at root
{L, tmp} = split(root, k)        // L: keys < k,  tmp: keys ≥ k
{M, R}   = split(tmp, k + 1)     // M: key = k,   R: keys > k
root = merge(L, R)                // discard M
```

---

### 5. Get (k-th element) — O(log n) expected

`get(k)` retrieves the k-th smallest element (1-indexed). Requires storing **subtree sizes** in each node.

```
get(node, k) → node
  leftSize = (node.left != null) ? node.left.size : 0

  if k == leftSize + 1
    return node           // current node is the k-th element

  if k <= leftSize
    return get(node.left, k)
  else
    return get(node.right, k - leftSize - 1)
```

---

## Treap as an Implicit/Order-Statistic Structure

The real power of a treap comes from using it with **array-like indexing** instead of key-based ordering. This is the **implicit treap** (indexed by position).

**Idea:** Instead of storing keys, each node's "key" is its **position** in an implicit sorted sequence. Subtree sizes replace explicit keys.

Operations on a sequence (like a balanced array):

| Operation | How |
|-----------|-----|
| `merge(A, B)` | Concatenate sequences A and B |
| `split(A, k)` | Split sequence A into first k elements + rest |
| `get(k)` | Get k-th element |

**Example — sequence operations:**

```
[Q, Y, P, K] + [W, N, B]
       ↓ merge
[Q Y P K W N B]
       ↓ split(5)
[Q Y P K W] + [N B]
```

This makes the treap function like a **dynamic array** with O(log n) split, merge, get, insert, and delete — useful for problems requiring range operations.

---

## Complexity Summary

| Operation | Time Complexity |
|-----------|----------------|
| `split` | O(log n) expected |
| `merge` | O(log n) expected |
| `insert` | O(log n) expected |
| `delete` | O(log n) expected |
| `get(k)` | O(log n) expected |
| Build from n elements | O(n log n) expected |

> All bounds are **expected** (due to random priorities). Worst case is O(n) but astronomically unlikely with `y = rand()`.

---

## Treap vs Other Balanced BSTs

| Feature | AVL Tree | Red-Black Tree | **Treap** |
|---------|----------|----------------|-----------|
| Balance guarantee | Strict (height ≤ 1.44 log n) | Guaranteed O(log n) | Expected O(log n) |
| Balancing mechanism | Rotations on insert/delete | Color flips + rotations | Random priorities |
| Implementation complexity | High | Very high | **Low** |
| Split / Merge | Hard to implement | Hard | **Natural and simple** |
| Persistent variant | Possible but complex | Complex | **Easy** |
| Use case | General balanced BST | General (used in std::map) | **Competitive programming, order-statistics** |

---

## Practice Problems

- [CSES — Dynamic Range Minimum Queries](https://cses.fi/problemset/task/1649) (Segment tree / treap)
- [Codeforces — Ynoi problems](https://codeforces.com/problemset?tags=data+structures) (implicit treap heavy)
- [CSES — Josephus Problem II](https://cses.fi/problemset/task/2163) (classic implicit treap)
- [CF 702F — T-Shirts](https://codeforces.com/contest/702/problem/F)
- Any problem requiring **order-statistic tree** or **rope** (sequence with split/merge)

# Scapegoat Tree & List Order Maintenance

---

## Scapegoat Tree

**Core idea:** Balance a BST *without rotations* — instead, rebuild subtrees when they get too unbalanced.

### Balance Condition

For a parameter α where `1/2 < α < 1` (typically `α = 0.7`):

A node `x` with parent `p` is **α-weight-balanced** if:

```
size(x) ≤ α · size(p)
```

If this is violated after an insertion, `x` is the **scapegoat** — we rebuild the subtree rooted at `p` from scratch into a perfectly balanced BST.

### Height Bound

The tree height `H` satisfies:

```
H ≤ log_{1/α}(n)
```

**Proof sketch:**
- Root has size n
- Each level down, size shrinks by factor α
- At depth H: size ≤ α^H · n
- Since size ≥ 1: α^H · n ≥ 1 → H ≤ log_{1/α}(n)

For α = 0.7, H ≤ log_{1/0.7}(n) ≈ 2.07 · log₂(n)

### Rebuild (Reconstruct) Operation

When a scapegoat node `v` is found:

1. Flatten the subtree rooted at `v` into a sorted array (in-order traversal)
2. Rebuild it as a perfectly balanced BST

```
T(reconstruct(v)) where size(v) = X
→ O(X)  time
```

After rebuilding, the subtree is perfectly balanced. Before the *next* rebalance at this node, you must add at least `(αX - X/2)` elements — this amortizes the cost.

### Amortized Analysis

Let `T̃` = amortized cost per operation.

```
T̃ = T / N_op = X / ((α - 1/2) · X) = 1 / (α - 1/2) = Const
```

So:
- **T̃(add) = O(log n)**  (amortized)
- Each insert: walk down the tree O(log n), check balance condition, rebuild if needed

### Complexity Summary

| Operation   | Worst Case | Amortized |
|-------------|-----------|-----------|
| Insert      | O(n)      | O(log n)  |
| Search      | O(log n)  | O(log n)  |
| Delete      | O(log n)  | O(log n)  |
| Reconstruct | O(X)      | O(1) per insert |

> **Construct:** O(n log n)  
> **Query:** O(log² n)  
> **Change:** O(log² n)

### Key Insight: No Rotations Needed

Unlike AVL or Red-Black trees, scapegoat trees:
- Store **no balance info** per node (just subtree sizes)
- Use **full subtree rebuilds** instead of local rotations
- Trade constant factors for implementation simplicity

### Deletion

Uses a "lazy deletion" trick:
- Mark nodes as **invalid** (don't actually remove)
- Keep a counter of invalid nodes
- When too many invalids exist relative to tree size, rebuild the whole tree

Rebuild triggered when:
```
(X/2 + k) > α · (X + k)
```
where X = size before inserts, k = number of new inserts since last rebuild.

---

## List Order Maintenance

**Problem:** Maintain an ordered list supporting:
- `addAfter(x, y)` — insert element `y` immediately after `x`
- `isBefore(x, y)` — return true if `x` comes before `y` in the list

### Naive Approach

Assign each element an integer label from `[0..M-1]`.  
- `isBefore(x, y)` ↔ `label(x) < label(y)` → O(1)
- `addAfter(x, y)`: assign `y` the midpoint between `x` and its successor → can run out of integers!

```
Integers ≤ [0..M-1] → supports ≤ log M elements before relabeling
```

### Idea 1: Tree-Based Labels (Binary Trie)

Represent the list as a **balanced BST** where in-order traversal gives list order.  
Assign each element a **bitstring label** based on its path in the tree.

```
addAfter(x, y):
  → y gets label = midpoint(x.label, successor(x).label)
```

Example: If x = 10 (binary: `00001010`) and successor = 26 (binary: `00011010`):

```
midpoint = (10 + 26) / 2 = 18  →  y gets label 18
```

`isBefore(x, y)` = compare integer labels → **O(1)**

#### Height Bound

With labels of bit-length `h`:
- Supports up to `2^h` distinct labels
- For n elements: need `h ≥ log₂ n`
- So label length `h ≤ 2 log₂ n` → labels fit in O(log n) bits

### BST + List Order Comparison

| Structure      | addAfter  | isBefore |
|----------------|-----------|----------|
| BST            | O(log n)  | O(log n) |
| Numbers (≤lgM) | 1         | 1        |
| Scapegoat Tree | O(log n)  | 1        |
| ST + Numbers   | 1         | 1        |

### Scapegoat Tree + List Order Maintenance

Use a scapegoat tree as the backbone of the ordered list:

- **addAfter is O(1) amortized** — insert into the list, relabel only on rebuild
- **isBefore is O(1)** — compare integer labels

#### Amortized Cost of addAfter

When a rebuild (split) of a node with `> log n` children occurs:

```
T̃(add) = log n / (log n / 2) = Const = O(1) amortized
```

Before the next split at a node, at least `(log n)/2` operations must happen → amortized O(1) per add.

#### Split Strategy (Idea 2)

When a node accumulates `> log n` children:
- Split into two nodes each with `≤ log n / 2` children
- Reassign labels across subtrees

```
ln/2 operations before next split
→ T̃(add) = ln / (ln/2) = Const
```

### Final Complexity (ST + Numbers)

| Operation | Cost |
|-----------|------|
| addAfter  | O(1) amortized |
| isBefore  | O(1) |

---

## Important Notes

- Scapegoat trees are **simpler to implement** than AVL/RB trees but have worse constants
- The parameter α controls the balance–rebuild tradeoff: smaller α = more balanced, more rebuilds
- List Order Maintenance is a building block for **link-cut trees**, **order-statistic structures**, and **dynamic graph algorithms**
- The bitstring labeling scheme is essentially assigning a **path in a complete binary tree** as a label

## References

- [CSES Problem Set](https://cses.fi/problemset)

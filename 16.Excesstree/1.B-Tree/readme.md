# B Tree

B-trees differ from red-black trees in that B-tree nodes may have many children, from a handful to thousands.

similar to red-black trees in that every n-node B-tree has height O(lg n),

although the height of a B-tree can be considerably less than that of a red-black tree because its branching factor can be much larger.

Therefore, B-trees can also be used to implement many dynamic-set operations in time O(lg n).

If an internal B-tree node x contains `n[x]` keys, then `x` has `n[x] +1` children

While searching for a key in a B-tree, we make an (`n[x] +1`)-way decision based on comparisons with the `n[x]` keys stored at node `x`

**Properties:**

1. **Sorted keys in each node** — Each node stores multiple keys in sorted order and has children between key ranges.

2. **Range separation** — For any internal node, all keys in the i-th child lie between keyᵢ₋₁ and keyᵢ.

3. **Balanced tree** — All leaves are at the same depth.

4. **Degree constraints (t ≥ 2)** —
   - Except root: at least **t−1** keys, at most **2t−1** keys.
   - So internal nodes have between **t and 2t** children.

If `n ≥1`, then for any n-key B-tree T of height `h` and minimum degree `t ≥2`

$$
h \le \log_t \left(\frac{n+1}{2}\right)
$$

height of the tree grows as O(lg n)

# Basic Operations

## Search

### Idea

Searching in a B-tree is similar to searching in a binary search tree, except that each node can have multiple keys and up to ( n[x] + 1 ) children.
At each internal node, we make an ( (n[x] + 1) )-way branching decision instead of a binary decision.

### Procedure: `B-TREE-SEARCH(x, k)`

- Input:
  - Pointer to root of subtree `x`
  - Key `k`

- Output:
  - `(y, i)` if `key_i[y] = k`
  - `NIL` if `k` is not in the tree

### Algorithm Logic

1. Start with index `i = 1`.

2. Linearly scan keys in node `x` to find the smallest `i` such that:
   [
   k \le key_i[x]
   ]
   If no such key exists, set ( i = n[x] + 1 ).

3. If ( i \le n[x] ) and ( k = key_i[x] ), return `(x, i)`.

4. If `x` is a leaf, return `NIL`.

5. Otherwise:
   - Perform `DISK-READ(c_i[x])`
   - Recursively search in child `c_i[x]`

```
B-TREE-SEARCH(x, k)

1.  i ← 1

2.  while i ≤ n[x] and k > key_i[x]
3.      do i ← i + 1

4.  if i ≤ n[x] and k = key_i[x]
5.      then return (x, i)

6.  if leaf[x] = TRUE
7.      then return NIL

8.  DISK-READ(c_i[x])

9.  return B-TREE-SEARCH(c_i[x], k)
```

### Search Path Property

- The recursion follows a single path from the root down to a leaf.
- Therefore, the number of nodes accessed equals the height ( h ) of the tree.

### Time Complexity

#### Disk I/O Cost

- One disk page per level.
- Total disk accesses:
  [
  \Theta(h) = \Theta(\log_t n)
  ]

#### CPU Cost

- Each node has at most ( 2t - 1 ) keys.

- Linear scan per node takes:
  [
  O(t)
  ]

- Total CPU time:
  [
  O(th) = O(t \log_t n)
  ]

### Key Observations

- Search cost grows logarithmically with number of keys.
- Larger ( t ) reduces tree height.
- B-trees are optimized for minimizing disk accesses rather than CPU comparisons.

## Creating Empty B-Tree

To create a B-tree:

- Allocate a new node.
- Make it a leaf.
- Set number of keys to 0.
- Make it the root.

No keys are inserted at this stage.

### Required Auxiliary Procedure

**ALLOCATE-NODE()**

- Allocates one disk page for a new node.
- Runs in `O(1)` time.
- Does not require `DISK-READ`.

### Algorithm

```text
B-TREE-CREATE(T)

1.  x ← ALLOCATE-NODE()
2.  leaf[x] ← TRUE
3.  n[x] ← 0
4.  DISK-WRITE(x)
5.  root[T] ← x
```

### Complexity

- Disk operations: `O(1)`
- CPU time: `O(1)`

## Insertion in B-Tree

- Insert always happens at a **leaf**.
- If a node is full (`2t − 1` keys), it must be **split** before insertion.
- Splitting moves the **median key up** to the parent.
- We split **while going down**, so we never recurse into a full node.
- Tree height increases only when the **root splits**.

## Splitting a Full Node

### Before Split (y is full)

```
Parent x:
        [ ...  N   W  ... ]
                 |
                 y

y (2t−1 keys):
    [ P  Q  R  S  T  U  V ]
```

Median key = **S**

### After Split

```
Parent x:
        [ ...  N   S   W  ... ]
               /         \
              y           z

y: [ P  Q  R ]
z: [ T  U  V ]
```

- Median `S` moves up to parent.
- Left node keeps first `t−1` keys.
- Right node gets last `t−1` keys.

### Algorithm: B-TREE-SPLIT-CHILD

```text
B-TREE-SPLIT-CHILD(x, i, y)

1.  z ← ALLOCATE-NODE()
2.  leaf[z] ← leaf[y]
3.  n[z] ← t − 1

4.  for j ← 1 to t − 1
5.      key_j[z] ← key_{j+t}[y]

6.  if not leaf[y]
7.      for j ← 1 to t
8.          c_j[z] ← c_{j+t}[y]

9.  n[y] ← t − 1

10. for j ← n[x] + 1 downto i + 1
11.     c_{j+1}[x] ← c_j[x]

12. c_{i+1}[x] ← z

13. for j ← n[x] downto i
14.     key_{j+1}[x] ← key_j[x]

15. key_i[x] ← key_t[y]

16. n[x] ← n[x] + 1

17. DISK-WRITE(y)
18. DISK-WRITE(z)
19. DISK-WRITE(x)
```

**Time Complexity of Split**

- CPU time: `Θ(t)`
- Disk operations: `O(1)`

### Inserting a Key

- If root is full → split root → height increases.
- Then insert into a **nonfull node**.
- While descending:
  - If child is full → split it first.
  - Continue down.

### Algorithm: B-TREE-INSERT

```text
B-TREE-INSERT(T, k)

1.  r ← root[T]

2.  if n[r] = 2t − 1
3.      s ← ALLOCATE-NODE()
4.      root[T] ← s
5.      leaf[s] ← FALSE
6.      n[s] ← 0
7.      c_1[s] ← r
8.      B-TREE-SPLIT-CHILD(s, 1, r)
9.      B-TREE-INSERT-NONFULL(s, k)
10. else
11.     B-TREE-INSERT-NONFULL(r, k)
```

### Algorithm: B-TREE-INSERT-NONFULL

```text
B-TREE-INSERT-NONFULL(x, k)

1.  i ← n[x]

2.  if leaf[x]
3.      while i ≥ 1 and k < key_i[x]
4.          key_{i+1}[x] ← key_i[x]
5.          i ← i − 1
6.      key_{i+1}[x] ← k
7.      n[x] ← n[x] + 1
8.      DISK-WRITE(x)

9.  else
10.     while i ≥ 1 and k < key_i[x]
11.         i ← i − 1
12.     i ← i + 1
13.     DISK-READ(c_i[x])

14.     if n[c_i[x]] = 2t − 1
15.         B-TREE-SPLIT-CHILD(x, i, c_i[x])
16.         if k > key_i[x]
17.             i ← i + 1

18.     B-TREE-INSERT-NONFULL(c_i[x], k)
```

**Complexity**

- Disk accesses: `O(h) = O(log_t n)`
- CPU time: `O(t log_t n)`
- Height increases only when root splits.

## Deletion in B-Tree

Deletion is analogous to insertion but more complex, since a key may be deleted from any node — not just a leaf. We must ensure no node falls below the minimum number of keys `t − 1` (except the root, which may have fewer).

The procedure `B-TREE-DELETE` is structured so that whenever it is called recursively on a node `x`, the number of keys in `x` is at least `t` (one more than the minimum). This allows deletion in a single downward pass without backing up.

If the root becomes an internal node with no keys (cases 2c or 3b), it is deleted and its only child becomes the new root, decreasing the tree height by one.

### Cases for Deletion

**Case 1 — Key k is in node x and x is a leaf:**
Delete k directly from x.

**Case 2 — Key k is in node x and x is an internal node:**

- **Case 2a:** The child y that precedes k has at least t keys. Find the predecessor k′ of k in the subtree rooted at y. Recursively delete k′, and replace k with k′ in x. (Single downward pass.)
- **Case 2b:** Symmetrically, if the child z that follows k has at least t keys, find the successor k′ in the subtree rooted at z. Recursively delete k′ and replace k with k′ in x.
- **Case 2c:** Both y and z have only t − 1 keys. Merge k and all of z into y, so y now has 2t − 1 keys. Free z and recursively delete k from y.

**Case 3 — Key k is not present in internal node x:**

Determine the root c_i[x] of the appropriate subtree. If c_i[x] has only t − 1 keys, execute step 3a or 3b to guarantee we descend into a node with at least t keys. Then recurse on the appropriate child.

- **Case 3a:** c_i[x] has only t − 1 keys but has an immediate sibling with at least t keys. Give c_i[x] an extra key by moving a key from x down into c_i[x], moving a key from the immediate left or right sibling up into x, and moving the appropriate child pointer from the sibling into c_i[x].
- **Case 3b:** c_i[x] and both of its immediate siblings have t − 1 keys. Merge c_i[x] with one sibling, moving a key from x down into the merged node to become the median key.

```
B-TREE-DELETE(x, k)
1.  i ← 1
2.  while i ≤ n[x] and k > key_i[x]
3.      i ← i + 1

4.  if leaf[x]
        // Case 1: key is in a leaf — delete directly
5.      if i ≤ n[x] and k = key_i[x]
6.          for j ← i to n[x] − 1
7.              key_j[x] ← key_{j+1}[x]
8.          n[x] ← n[x] − 1
9.          DISK-WRITE(x)

10. else if i ≤ n[x] and k = key_i[x]
        // Case 2: key is in this internal node x
11.     y ← c_i[x]       // left child
12.     z ← c_{i+1}[x]   // right child
13.     if n[y] ≥ t
            // Case 2a: predecessor
14.         k' ← FIND-PREDECESSOR(y)
15.         key_i[x] ← k'
16.         B-TREE-DELETE(y, k')
17.     else if n[z] ≥ t
            // Case 2b: successor
18.         k' ← FIND-SUCCESSOR(z)
19.         key_i[x] ← k'
20.         B-TREE-DELETE(z, k')
21.     else
            // Case 2c: merge y, k, z → recurse
22.         MERGE(x, i, y, z)
23.         B-TREE-DELETE(y, k)

24. else
        // Case 3: key not in this node, go to child c_i[x]
25.     DISK-READ(c_i[x])
26.     if n[c_i[x]] = t − 1
27.         if i > 1 and n[c_{i−1}[x]] ≥ t
                // Case 3a: borrow from left sibling
28.             BORROW-FROM-LEFT(x, i)
29.         else if i ≤ n[x] and n[c_{i+1}[x]] ≥ t
                // Case 3a: borrow from right sibling
30.             BORROW-FROM-RIGHT(x, i)
31.         else
                // Case 3b: merge with a sibling
32.             if i > 1
33.                 MERGE(x, i−1, c_{i−1}[x], c_i[x])
34.                 i ← i − 1
35.             else
36.                 MERGE(x, i, c_i[x], c_{i+1}[x])
37.     B-TREE-DELETE(c_i[x], k)
```

### Example (t = 3, minimum 2 keys per non-root node)

```
(a) Initial tree:
                    [ P ]
           /                  \
      [C G M]               [T X]
    /   |   |   \           /  |  \
 [AB] [DEF] [JKL] [NO]  [QRS] [UV] [YZ]

(b) Delete F — Case 1 (leaf deletion):
                    [ P ]
           /                  \
      [C G M]               [T X]
    /   |   |   \           /  |  \
 [AB]  [DE] [JKL] [NO]  [QRS] [UV] [YZ]

(c) Delete M — Case 2a (replace with predecessor L):
                    [ P ]
           /                  \
      [C G L]               [T X]
    /   |   |   \           /  |  \
 [AB]  [DE]  [JK] [NO]  [QRS] [UV] [YZ]

(d) Delete G — Case 2c (G pushed down, merge DEJK):
                    [ P ]
           /                  \
        [C L]               [T X]
       /  |   \             /  |  \
    [AB] [DEJK] [NO]  [QRS] [UV] [YZ]

(e) Delete D — Case 3b (P pushed down, merge CL + TX → CLPTX):
         [ CLPTX ]
    /   /   |   \   \
 [AB] [EJK] [NO] [QRS] [UV] [YZ]

(e') Tree shrinks in height — CLPTX becomes new root.

(f) Delete B — Case 3a (C moves to fill B's position, E fills C's):
         [ ELPTX ]
    /   /   |   \   \
  [AC] [JK] [NO] [QRS] [UV] [YZ]
```

### Complexity

- Disk accesses: `O(h) = O(log_t n)`
- CPU time: `O(t log_t n)`
- Most deletions occur at leaves; internal node deletions require at most one downward pass, with a possible return to replace the key with its predecessor or successor (cases 2a and 2b).

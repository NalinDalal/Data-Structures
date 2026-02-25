# Height Balanced Binary Search Tree/AVL Tree

one of two common ways to balance a tree: AVL Tree

An AVL tree stores in each node the height of the subtrees rooted at this node.
Then, for any node, we can check if it is height balanced:
height of the left subtree and the height of the right subtree differ by no more than one.
This prevents situations where the tree gets too lopsided.

balance(n) = n.left.height-n.right.height
-1 <= balance(n) <= 1

## Insertion

while inserting nodes into an height balanced tree, it may happen the the height balance get disturbed
might change to -2 or 2
hence we recursively balance each node after each insertion by rotations
rotations: left or right

```mermaid
graph TD

subgraph Before
    A[30]
    B[20]
    C[35]
    D[10]
    E[25]

    A --> B
    A --> C
    B --> D
    B --> E
end

subgraph After
    F[20]
    G[10]
    H[30]
    I[25]
    J[35]

    F --> G
    F --> H
    H --> I
    H --> J
end
```

There are only 2 cases: when balance is 2 or -2

### **Case 1: Balance = +2 (Left Heavy)**

**Left-Right (LR) Case → Left Rotation + Right Rotation**

```mermaid
graph TD
    subgraph LEFT_RIGHT_SHAPE
        A[30]
        B[10]
        C[35]
        D[5]
        E[20]
        F[15]
        G[25]

        A --> B
        A --> C
        B --> D
        B --> E
        E --> F
        E --> G
    end

    subgraph AFTER_LEFT_ROTATION
        H[30]
        I[20]
        J[35]
        K[10]
        L[25]
        M[5]
        N[15]

        H --> I
        H --> J
        I --> K
        I --> L
        K --> M
        K --> N
    end

    subgraph BALANCED
        O[20]
        P[10]
        Q[30]
        R[5]
        S[15]
        T[25]
        U[35]

        O --> P
        O --> Q
        P --> R
        P --> S
        Q --> T
        Q --> U
    end
```

Steps:

1. Left rotation on left child.
2. Right rotation on root.
3. Tree becomes balanced.

---

**Left-Left (LL) Case → Single Right Rotation**

```mermaid
graph TD
    subgraph LEFT_LEFT_SHAPE
        A[30]
        B[20]
        C[35]
        D[10]
        E[25]
        F[5]
        G[15]

        A --> B
        A --> C
        B --> D
        B --> E
        D --> F
        D --> G
    end

    subgraph BALANCED
        H[20]
        I[10]
        J[30]
        K[5]
        L[15]
        M[25]
        N[35]

        H --> I
        H --> J
        I --> K
        I --> L
        J --> M
        J --> N
    end
```

**Step:**

- Single right rotation on root.

### Case 2: Balance = -2 (Right Heavy)

**Right-Left (RL) Case → Right Rotation + Left Rotation**

```mermaid
graph TD
    subgraph RIGHT_LEFT_SHAPE
        A[10]
        B[5]
        C[30]
        D[20]
        E[35]
        F[15]
        G[25]

        A --> B
        A --> C
        C --> D
        C --> E
        D --> F
        D --> G
    end

    subgraph AFTER_RIGHT_ROTATION
        H[10]
        I[5]
        J[20]
        K[15]
        L[30]
        M[25]
        N[35]

        H --> I
        H --> J
        J --> K
        J --> L
        L --> M
        L --> N
    end

    subgraph BALANCED
        O[20]
        P[10]
        Q[30]
        R[5]
        S[15]
        T[25]
        U[35]

        O --> P
        O --> Q
        P --> R
        P --> S
        Q --> T
        Q --> U
    end
```

Steps:

1. Right rotation on right child.
2. Left rotation on root.
3. Tree becomes balanced.

---

**Right-Right (RR) Case → Single Left Rotation**

```mermaid
graph TD
    subgraph RIGHT_RIGHT_SHAPE
        A[10]
        B[5]
        C[20]
        D[15]
        E[30]
        F[25]
        G[35]

        A --> B
        A --> C
        C --> D
        C --> E
        E --> F
        E --> G
    end

    subgraph BALANCED
        H[20]
        I[10]
        J[30]
        K[5]
        L[15]
        M[25]
        N[35]

        H --> I
        H --> J
        I --> K
        I --> L
        J --> M
        J --> N
    end
```

Step:

- Single left rotation on root.

---

# Important Notes (AVL Rule)

- Balance Factor = height(left) − height(right)
- Valid range: **−1, 0, +1**
- If +2 → Left heavy
- If −2 → Right heavy
- Fix locally, then recurse upward.

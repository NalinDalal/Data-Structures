# Longest Common Subsequence (LCS)

## Problem Definition

Given two sequences:
- X = (x1, x2, ..., xm)
- Y = (y1, y2, ..., yn)

A **subsequence** is a sequence derived by deleting zero or more elements **without changing order**.

A **Longest Common Subsequence (LCS)** is the longest sequence that is a subsequence of **both X and Y**.

### Example

X = (A, B, C, B, D, A, B)
Y = (B, D, C, A, B, A)

**Possible common subsequences:**
- (B, C, A)
- (B, D, A)
- (B, C, B, A)

**LCS:**
- (B, C, B, A) — length = 4

---

## Why LCS Matters

**Applications:**
- DNA sequence similarity
- Diff tools (Git)
- Plagiarism detection
- Version control merging
- Bioinformatics
- Spell correction
- Text comparison

---

## Key Observations

### Optimal Substructure

If:
- xm = yn  
  then LCS(X, Y) = LCS(Xm-1, Yn-1) + xm

- xm != yn  
  then LCS(X, Y) = max(
      LCS(Xm-1, Y),
      LCS(X, Yn-1)
    )

---

## Recurrence Relation

Let:

`c[i][j]` = length of LCS of X1..i and Y1..j

$$
dp[i][j]=
\begin{cases}
dp[i-1][j-1]+1 & x_i=y_j \\
\max(dp[i-1][j],dp[i][j-1]) & x_i\ne y_j
\end{cases}
$$

---

## Dynamic Programming Approach

### Table Meaning

`c[i][j]` represents:

LCS length of:
- prefix of X of length i
- prefix of Y of length j

**Matrix size:** (m+1) x (n+1)

**Base condition:**
- `c[i][0] = 0`
- `c[0][j] = 0`

---

## Algorithm

### Compute LCS Length

```pseudo
LCS-LENGTH(X, Y):
    m = length(X)
    n = length(Y)

    create table c[0..m][0..n]
    create table b[1..m][1..n]

    for i = 0 to m
        c[i][0] = 0

    for j = 0 to n
        c[0][j] = 0

    for i = 1 to m
        for j = 1 to n

            if X[i] == Y[j]
                c[i][j] = c[i-1][j-1] + 1
                b[i][j] = "diag"

            else if c[i-1][j] >= c[i][j-1]
                c[i][j] = c[i-1][j]
                b[i][j] = "up"

            else
                c[i][j] = c[i][j-1]
                b[i][j] = "left"

    return c, b
```

**Time Complexity:** O(mn)
**Space Complexity:** O(mn)

---

## Constructing the LCS Sequence

Backtrack using table b:

```pseudo
PRINT-LCS(b, X, i, j):
    if i == 0 or j == 0
        return

    if b[i][j] == "diag"
        PRINT-LCS(b, X, i-1, j-1)
        print X[i]

    else if b[i][j] == "up"
        PRINT-LCS(b, X, i-1, j)

    else
        PRINT-LCS(b, X, i, j-1)
```

**Time Complexity:** O(m + n)

---

## Example

X = (A, B, C, B, D, A, B)
Y = (B, D, C, A, B, A)

**Final LCS length:** 4
**One LCS:** BCBA

---

## Space Optimization

### Observation

Each entry depends only on:
- `c[i-1][j]`
- `c[i][j-1]`
- `c[i-1][j-1]`

### Optimization

We only need **2 rows** instead of full table.

**Space complexity improves:** O(mn) -> O(min(m,n))

**Limitation:** Cannot reconstruct sequence easily (only length).

---

## Key Patterns to Recognize LCS Problems

**Indicators:**
- "longest subsequence"
- "keep order"
- "minimum insertions/deletions"
- "similarity score"
- "diff between strings"
- "DNA comparison"
- "common pattern"

---

## Complexity Summary

| Step                  | Complexity  |
| -------------------- | ----------- |
| DP table computation | O(mn)       |
| LCS reconstruction   | O(m+n)      |
| Space                | O(mn)       |
| Optimized space      | O(min(m,n)) |

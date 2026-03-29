# Paths in a Grid

To find a path from the upper-left corner to the lower-right corner of an *n x n* grid, such that we only move down and right.

Each square contains a positive integer, and the path should be constructed so that the sum of the values along the path is as large as possible.

---

## Problem Setup

Let rows and columns of the grid be numbered from 1 to n:
- `value[y][x]` = value of square (y, x)
- `sum(y, x)` = maximum sum on a path from the upper-left corner to square (y, x)

`sum(n, n)` tells us the maximum sum from the upper-left corner to the lower-right corner.

---

## Key Insight

When you move to a specific square, you actually reduce the size of the problem, so the subproblems overlap with each other.

```
sum[i][j] = max sum path from (i,j) to (n-1,m-1)
```

---

## Recurrence Relation

Calculate sum recursively as follows:

```
sum(y, x) = max(sum(y, x-1), sum(y-1, x)) + value[y][x]
```

The solution for square (y, x) can come from either:
- Square (y, x-1) — coming from the left
- Square (y-1, x) — coming from above

Select the direction that maximizes the sum.

---

## Algorithm

```cpp
int sum[N][N];

for (int y = 1; y <= n; y++) {
    for (int x = 1; x <= n; x++) {
        sum[y][x] = max(sum[y][x-1], sum[y-1][x]) + value[y][x];
    }
}
```

**Base Case:** `sum[n-1][n-1] = weight of [n-1][n-1]`

---

## Complexity

| Metric | Complexity |
| ------ | ---------- |
| Time   | O(n^2)     |
| Space  | O(n^2)     |

---

## Applications

- Finding maximum sum path in matrix
- Robot movement problems
- Game scoring paths
- Resource allocation problems

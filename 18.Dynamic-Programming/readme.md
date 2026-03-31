# Dynamic Programming

Dynamic programming optimizes a problem solution by breaking it down into sub-problems so that it remembers past computations to avoid recomputing for tough sub-problems.

Instead of solving the same subproblem repeatedly (like naive recursion does), DP *caches* the answer the first time and looks it up later.

A dynamic-programming algorithm solves every subproblem just once and then saves its answer in a table, thereby avoiding the work of recomputing the answer every time the subproblem is is encountered.

---

## Four Steps to Dynamic Programming

1. Characterize the structure of an optimal solution.
2. Recursively define the value of an optimal solution.
3. Compute the value of an optimal solution in a bottom-up fashion.
4. Construct an optimal solution from computed information.

---

## Standard Topics

- [Assembly Line Scheduling](./AssemblyLineSchedule.md)
- [Foundation](./Foundation.md)
- [Longest Increasing Subsequence](./LIS.md)
- [Path in a Grid](./path-grid.md)
- [Edit Distance](./EditDist.md)
- [Longest Common Subsequence](./LCS.md)
- [Matrix Chain Multiplication](./matrix-chain-mul.md)
- [Optimal Binary Search Tree](./optimal-bst.md)
- [DP on Tree](./dp-tree.md)
- [Coin Problems](./coin.md)
- [Knapsack Problems](./knapsack.md)
- [Counting Tiles](./count-tiles.md)

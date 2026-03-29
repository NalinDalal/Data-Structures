# Reference Materials

## Cormen
- Chapter 15: Dynamic Programming (pages 344-390)
- 15.2 Matrix-chain multiplication
- 15.5 Optimal binary search trees

## Algorithms (Jeff Erickson)
- Chapter 3 (pages 115-141)
- 3.2: Even Faster Fibonacci Numbers
- 3.3: Interpunctio Verborum Redux
- 3.4: The Pattern: Smart Recursion
- 3.5: Warning: Greed is Stupid
- 3.8: Subset Sum
- 3.9: Optimal Binary Search Trees
- 3.10: Dynamic Programming on Trees

## CP Handbook
- Pages 75-86 (PDF)

## Topics
- 7 Dynamic programming (page 65)
- 7.1 Coin problem
- 7.4 Knapsack problems
- 7.6 Counting tilings

---

## Day-wise Plan

### Day 6 — Interval DP (Hard but important)

#### Study (2 hrs)
- Cormen 15.2 Matrix chain multiplication
- Programming Challenges 11.6.5 Cutting sticks

#### Core Concept

```
dp[i][j] = min_{i <= k < j}(dp[i][k] + dp[k+1][j] + cost(i,j))
```

#### Practice
- Matrix chain multiplication
- Burst balloons
- Cutting sticks

#### Pattern Learned
Solve **range problems**

---

### Day 7 — Advanced DP (Tree + OBST + mixed)

#### Study (2 hrs)
- Cormen 15.5 Optimal BST
- Algorithms 3.10 DP on trees
- Programming Challenges
  - 11.6.4 Unidirectional TSP
  - 11.6.6 Ferry Loading

#### Core Concept

```
E[i,j] = min_{r=i}^{j}(E[i,r-1] + E[r+1,j] + W[i,j])
```

#### Practice
- Optimal BST understanding
- TSP grid variant
- Tree DP example

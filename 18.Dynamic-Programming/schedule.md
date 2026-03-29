cormen: chap 15(344-390)
15 Dynamic Programming 323
15.2 Matrix-chain multiplication 331
15.5 Optimal binary search trees 356

algorithms: chap 3(115-141)
3.2 nAside: Even Faster Fibonacci Numbers . . . . . . . . . . . . . . . 103
3.3 Interpunctio Verborum Redux . . . . . . . . . . . . . . . . . . . . . . 105
3.4 The Pattern: Smart Recursion . . . . . . . . . . . . . . . . . . . . . 105
3.5 Warning: Greed is Stupid . . . . . . . . . . . . . . . . . . . . . . . . 107
3.8 Subset Sum . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 116
3.9 Optimal Binary Search Trees . . . . . . . . . . . . . . . . . . . . . . 117
3.10 Dynamic Programming on Trees . . . . . . . . . . . . . . . . . . . . 120

CP Handbook: 75-86(pdf)

7 Dynamic programming 65
7.1 Coin problem . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 65
7.4 Knapsack problems . . . . . . . . . . . . . . . . . . . . . . . . . . . . 72
7.6 Counting tilings . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 75

---

# Day-wise Plan

## Day 6 — Interval DP (Hard but important)

### Study (2 hrs)

* Cormen 15.2 Matrix chain multiplication
* Programming Challenges 11.6.5 Cutting sticks

### Core concept

dp[i][j]=\min_{i\le k<j}(dp[i][k]+dp[k+1][j]+cost(i,j))

### Practice

* Matrix chain multiplication
* Burst balloons
* Cutting sticks

### Pattern learned

Solve **range problems**

---

## Day 7 — Advanced DP (Tree + OBST + mixed)

### Study (2 hrs)

* Cormen 15.5 Optimal BST
* Algorithms 3.10 DP on trees
* Programming Challenges

  * 11.6.4 Unidirectional TSP
  * 11.6.6 Ferry Loading

### Core concept

E[i,j]=\min_{r=i}^{j}(E[i,r-1]+E[r+1,j]+W[i,j])

### Practice

* Optimal BST understanding
* TSP grid variant
* Tree DP example

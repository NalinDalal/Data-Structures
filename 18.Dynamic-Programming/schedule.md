cormen: chap 15(344-390)
15 Dynamic Programming 323
15.1 Assembly-line scheduling 324
15.2 Matrix-chain multiplication 331
15.3 Elements of dynamic programming 339
15.4 Longest common subsequence 350
15.5 Optimal binary search trees 356

programming challenges: 265-288

11.1 Don’t Be Greedy . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 245
11.2 Edit Distance . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 246
11.3 Reconstructing the Path . . . . . . . . . . . . . . . . . . . . . . . . . 250
11.4 Varieties of Edit Distance . . . . . . . . . . . . . . . . . . . . . . . . 251
11.5 Program Design Example: Elevator Optimization . . . . . . . . . . . 253
11.6 Problems . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 257
    11.6.1 Is Bigger Smarter? . . . . . . . . . . . . . . . . . . . . . . . . 257
    11.6.2 Distinct Subsequences . . . . . . . . . . . . . . . . . . . . . . 258
    11.6.3 Weights and Measures . . . . . . . . . . . . . . . . . . . . . . 259
    11.6.4 Unidirectional TSP . . . . . . . . . . . . . . . . . . . . . . . . 260
    11.6.5 Cutting Sticks . . . . . . . . . . . . . . . . . . . . . . . . . . . 262
    11.6.6 Ferry Loading . . . . . . . . . . . . . . . . . . . . . . . . . . . 263
    11.6.7 Chopsticks . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 265
    11.6.8 Adventures in Moving: Part IV . . . . . . . . . . . . . . . . . 266
11.7 Hints . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 267
11.8 Notes . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 267


algorithms: chap 3(115-141)
3.1 Matrtta . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 97
Backtracking Can Be Slow• Memo(r)ization: Remember Everything• 
Dynamic Programming: Fill Deliberately• Don’t Remember Everything After All
3.2 nAside: Even Faster Fibonacci Numbers . . . . . . . . . . . . . . . 103
Whoa! Not so fast!
3.3 Interpunctio Verborum Redux . . . . . . . . . . . . . . . . . . . . . . 105
3.4 The Pattern: Smart Recursion . . . . . . . . . . . . . . . . . . . . . 105
3.5 Warning: Greed is Stupid . . . . . . . . . . . . . . . . . . . . . . . . 107
3.6 Longest Increasing Subsequence . . . . . . . . . . . . . . . . . . . . 109
First Recurrence: Is This Next? • Second Recurrence: What’s Next?
3.7 Edit Distance. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 111
Recursive Structure • Recurrence • Dynamic Programming
3.8 Subset Sum . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 116
3.9 Optimal Binary Search Trees . . . . . . . . . . . . . . . . . . . . . . 117
3.10 Dynamic Programming on Trees . . . . . . . . . . . . . . . . . . . . 120

CP Handbook: 75-86(pdf)

7 Dynamic programming 65
7.1 Coin problem . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 65
7.2 Longest increasing subsequence . . . . . . . . . . . . . . . . . . . . . 70
7.3 Paths in a grid . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 71
7.4 Knapsack problems . . . . . . . . . . . . . . . . . . . . . . . . . . . . 72
7.5 Edit distance . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 74
7.6 Counting tilings . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 75


-----

# Overall Dependency Graph (read in this order)

1. DP mindset → memoization → recurrence thinking
2. 1D DP patterns (Fibonacci, coin, LIS)
3. 2D DP patterns (grid paths, edit distance, LCS)
4. Interval DP (matrix chain, cutting sticks)
5. Tree DP / advanced patterns
6. Reconstruction techniques
7. Hard classical problems (OBST, TSP variant)

---

# Day-wise Plan

## Day 2 — 1D DP Patterns (LIS + Subset)

### Study (2 hrs)

* Algorithms 3.6 Longest Increasing Subsequence
* CP Handbook 7.2 LIS
* Algorithms 3.8 Subset Sum

### Core concept

dp[i]=\max(dp[j]+1)\text{ for }j<i\text{ and }a_j<a_i

### Practice (1.5 hr)

* LIS (O(n²) version)
* Subset sum
* Partition equal subset sum

### Pattern learned

State depends on **previous elements**

---

## Day 3 — 2D Grid DP

### Study (2 hrs)

* CP Handbook 7.3 Paths in grid
* Algorithms 3.3 Interpunctio Verborum Redux

### Core concept

dp[i][j]=dp[i-1][j]+dp[i][j-1]

### Practice

* Unique paths
* Minimum path sum
* Grid with obstacles

### Pattern learned

State depends on **2 dimensions**

---

## Day 4 — Edit Distance + String DP

### Study (2 hrs)

* Algorithms 3.7 Edit Distance
* Programming Challenges 11.2, 11.4
* CP Handbook 7.5 Edit distance

### Core concept

dp[i][j]=\min\begin{cases}dp[i-1][j]+1\dp[i][j-1]+1\dp[i-1][j-1]+cost\end{cases}

### Practice

* Edit distance
* Delete operations
* Distinct subsequences (11.6.2)

---

## Day 5 — LCS + Reconstruction

### Study (2 hrs)

* Cormen 15.4 LCS
* Programming Challenges 11.3 Reconstructing path

### Core concept

dp[i][j]=\begin{cases}dp[i-1][j-1]+1 & x_i=y_j\\max(dp[i-1][j],dp[i][j-1]) & x_i\ne y_j\end{cases}

### Practice

* LCS
* Print LCS string
* Longest palindromic subsequence

### Pattern learned

Store **decision path**

---

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

---

# Daily Time Split

| Activity           | Time     |
| ------------------ | -------- |
| Concept reading    | 1.5 hr   |
| Implement examples | 1 hr     |
| Solve problems     | 1–1.5 hr |

---

# Order of Programming Challenges problems

Do in this order:

1. Distinct Subsequences
2. Weights and Measures
3. Unidirectional TSP
4. Cutting Sticks
5. Ferry Loading
6. Chopsticks
7. Adventures in Moving

---

# Weekly repetition strategy

Week 1 → understand patterns
Week 2 → re-solve without notes
Week 3 → solve 20 random DP problems




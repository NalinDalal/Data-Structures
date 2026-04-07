# Greedy Strategy

Key properties, design steps, and theoretical foundations of greedy algorithms.

## Design Steps

A greedy algorithm builds a solution by making locally optimal choices at each step.

Typical development process:

1. Determine optimal substructure of the problem
2. Develop a recursive solution
3. Prove that the greedy choice is always one of the optimal choices
4. Show that all but one subproblem induced by the greedy choice are empty
5. Develop a recursive algorithm implementing the greedy strategy
6. Convert the recursive algorithm to an iterative one

Streamlined version (used in practice):

1. Cast the problem as: make one choice, left with one subproblem
2. Prove there is always an optimal solution that makes the greedy choice
3. Show that greedy choice + optimal solution to subproblem = optimal overall

## Greedy-Choice Property

A globally optimal solution can be reached by making locally optimal (greedy) choices.

- The choice is made based on the current state, without consulting subproblems
- Differs from dynamic programming: DP choices depend on subproblem solutions
- Greedy progresses **top-down**; DP typically progresses bottom-up
- Preprocessing or a priority queue often enables efficient greedy choices

## Optimal Substructure

A problem has **optimal substructure** if an optimal solution contains optimal solutions to subproblems.

Required for both greedy algorithms and dynamic programming.

For greedy: it suffices to show that optimal solution to subproblem + greedy choice already made = optimal solution to original problem.

## Greedy vs Dynamic Programming

Both exploit optimal substructure, but differ in how choices are made.

### 0-1 Knapsack Problem

- $n$ items, item $i$ has value $v_i$ and weight $w_i$, knapsack capacity $W$
- Each item must be taken whole or left behind (binary choice)
- Greedy does **not** work — taking highest value-per-pound item may leave wasted capacity
- Requires dynamic programming (overlapping subproblems)

### Fractional Knapsack Problem

- Same setup, but fractions of items can be taken
- Greedy **works**: sort by $v_i / w_i$ descending, take as much as possible of each
- Running time: $O(n \log n)$

| Property | 0-1 Knapsack | Fractional Knapsack |
|---|---|---|
| Greedy works | No | Yes |
| Optimal substructure | Yes | Yes |
| Solution method | DP | Greedy |

## Matroids (§16.4)

A **matroid** is an ordered pair $M = (S, \mathcal{I})$ satisfying:

1. $S$ is a finite nonempty set
2. $\mathcal{I}$ is a nonempty hereditary family of subsets of $S$: if $B \in \mathcal{I}$ and $A \subseteq B$, then $A \in \mathcal{I}$
3. **Exchange property**: if $A, B \in \mathcal{I}$ and $|A| < |B|$, then $\exists\, x \in B - A$ such that $A \cup \{x\} \in \mathcal{I}$

### Graphic Matroid

For undirected graph $G = (V, E)$, define $M_G = (S_G, \mathcal{I}_G)$ where:

- $S_G = E$ (set of all edges)
- $A \in \mathcal{I}_G$ iff $A$ is acyclic (i.e., $(V, A)$ is a forest)

**Theorem 16.5**: If $G = (V, E)$ is an undirected graph, then $M_G$ is a matroid.

**Proof sketch**: $\mathcal{I}_G$ is hereditary (subset of forest = forest). Exchange property: if $|B| > |A|$, forest $G_B$ has fewer trees than $G_A$, so some tree in $G_B$ spans two trees in $G_A$ — the connecting edge can be added to $A$ without creating a cycle. $\blacksquare$

### Definitions

- **Extension** of $A$: element $x \notin A$ such that $A \cup \{x\} \in \mathcal{I}$
- **Maximal** independent set: has no extensions (not contained in any larger independent set)
- **Theorem 16.6**: All maximal independent subsets of a matroid have the same size

For graphic matroid: every maximal independent subset is a **spanning tree** of $G$ with exactly $|V| - 1$ edges.

### Weighted Matroid

A matroid $M = (S, \mathcal{I})$ is **weighted** if there is a weight function $w : S \to \mathbb{R}^+$.

$$w(A) = \sum_{x \in A} w(x)$$

Goal: find a **maximum-weight independent subset** $A \in \mathcal{I}$.

## Greedy Algorithm on Weighted Matroid

```
GREEDY(M, w)
1  A ← ∅
2  sort S[M] in monotonically decreasing order by weight w
3  for each x ∈ S[M] in decreasing weight order:
4      if A ∪ {x} ∈ I[M]:
5          A ← A ∪ {x}
6  return A
```

Running time: $O(n \log n + nf(n))$ where $f(n)$ = time to check independence.

### Correctness

**Lemma 16.7** (Greedy-choice property): Let $x$ be the first element of $S$ such that $\{x\}$ is independent. Then there exists an optimal subset containing $x$.

**Proof sketch**: Let $B$ be any optimal subset. If $x \notin B$, use exchange property to build $A$ starting from $\{x\}$, swap out some $y \in B$ with $w(y) \leq w(x)$, yielding $w(A) \geq w(B)$. $\blacksquare$

**Lemma 16.8**: If $x$ is an extension of some independent subset $A$, then $x$ is also an extension of $\emptyset$.

**Corollary 16.9**: If $x$ is not an extension of $\emptyset$, it is not an extension of any independent set — GREEDY can safely skip it.

**Lemma 16.10** (Optimal substructure): After GREEDY picks $x$ first, the remaining problem reduces to finding a max-weight independent subset in the **contraction** $M' = (S', \mathcal{I}')$:

$$S' = \{y \in S : \{x, y\} \in \mathcal{I}\}$$
$$\mathcal{I}' = \{B \subseteq S - \{x\} : B \cup \{x\} \in \mathcal{I}\}$$

**Theorem 16.11** (Correctness): If $M = (S, \mathcal{I})$ is a weighted matroid with weight function $w$, then GREEDY$(M, w)$ returns an optimal subset.

**Proof**: Corollary 16.9 → skipped elements can never be used. Lemma 16.7 → adding $x$ is safe. Lemma 16.10 → remaining problem is optimal substructure in $M'$. By induction, GREEDY finds the max-weight independent subset. $\blacksquare$

### Connection to MST

For the minimum-spanning-tree problem, define weighted matroid $M_G$ with:

$$w'(e) = w_0 - w(e), \quad w_0 > \max_e w(e)$$

Then maximizing $w'(A)$ minimizes $w(A)$. Any max-weight independent subset = minimum spanning tree.


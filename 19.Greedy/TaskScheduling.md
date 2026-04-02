# Task Scheduling Problem

Optimally scheduling unit-time tasks on a single processor, where each task has a deadline and a penalty paid if the deadline is missed.

A **unit-time task** is a job that requires exactly 1 unit of time to complete.

Given a set S of unit-time tasks, a **schedule** is a permutation of S.

## Input

- Set $S = \{a_1, a_2, \ldots, a_n\}$ of $n$ unit-time tasks
- Deadlines $\{d_1, d_2, \ldots, d_n\}$ where $1 \leq d_i \leq n$; task $a_i$ must be done by time $d_i$
- Penalties $\{w_1, w_2, \ldots, w_n\}$; incur penalty $w_i$ if task $a_i$ is not done by time $d_i$

A task is **late** if finished after its deadline, otherwise it is **early**.

## Canonical (Early-First) Form

A schedule can be put into **early-first form** where early tasks precede late tasks.

```
if task a[i] follows a[j] and d[i] < d[j]:
    swap(a[i], a[j])
    // a[i] will still be early after the swap
```

More generally, an arbitrary schedule can be put into **canonical form** where:
- Early tasks precede late tasks
- Early tasks are ordered by monotonically increasing deadline

If two tasks $a_i$, $a_j$ finish at times $k$ and $k+1$ with $d_i < d_j$, swapping them keeps $a_i$ early (since $k+1 \leq d_j$).

## Theorem: (S, l) is a Matroid

If $S$ is a set of unit-time tasks with deadlines and $\mathcal{l}$ is the set of all independent sets of tasks, then the system $(S, \mathcal{l})$ is a **matroid**.

A set $A$ of tasks is **independent** if there exists a schedule with no late tasks — i.e., $N_t(A) \leq t$ for all $t$, where $N_t(A)$ is the number of tasks in $A$ with deadline $\leq t$.

### Proof of Exchange Property

Let $B$ and $A$ be independent sets with $|B| > |A|$.

Let $k$ be the largest $t$ such that $N_t(B) \leq N_t(A)$.

- Such a $k$ exists since $N_0(A) = N_0(B) = 0$
- Since $N_n(B) = |B| > |A| = N_n(A)$, we must have $k < n$
- Therefore $N_j(B) > N_j(A)$ for all $j$ in the range $k+1 \leq j \leq n$

So $B$ contains more tasks with deadline $k+1$ than $A$ does. Let $a_i$ be a task in $B - A$ with deadline $k+1$, and let $A' = A \cup \{a_i\}$.

**Showing $A'$ is independent** (using Lemma 16.12, property 2):

- For $0 \leq t \leq k$: $N_t(A') = N_t(A) \leq t$ (since $A$ is independent)
- For $k < t \leq n$: $N_t(A') \leq N_t(B) \leq t$ (since $B$ is independent)

Therefore $A'$ is independent, completing the proof that $(S, \mathcal{l})$ is a matroid. $\blacksquare$

## Greedy Algorithm

By Theorem 16.11, a greedy algorithm finds a **maximum-weight independent set** $A$. The tasks in $A$ become the early tasks in the optimal schedule.

- Running time: $O(n^2)$ using GREEDY — each of the $O(n)$ independence checks takes $O(n)$ time
- A faster $O(n \log n)$ implementation exists (Problem 16-4)

## Example

| $a_i$ | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|--------|---|---|---|---|---|---|---|
| $d_i$ | 4 | 2 | 4 | 3 | 1 | 4 | 6 |
| $w_i$ | 70 | 60 | 50 | 40 | 30 | 20 | 10 |

Greedy selects $a_1, a_2, a_3, a_4$, then rejects $a_5$ and $a_6$, and finally accepts $a_7$.

Optimal schedule: $\langle a_2, a_4, a_1, a_3, a_7, a_5, a_6 \rangle$

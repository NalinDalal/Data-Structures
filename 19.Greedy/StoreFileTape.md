# Storing Files on Tape

Minimizing expected access cost when storing $n$ files on magnetic tape.

Reading file $k$ requires scanning all earlier files first — cost is cumulative.

## Input

- Set of $n$ files, each file $i$ has length $L[i]$
- Files stored in some order (permutation $\pi$)
- $\pi(i)$ = index of file at position $i$
- Each file is equally likely to be accessed

## Cost Function

Cost of accessing the $k$-th file:

$$cost(k) = \sum_{i=1}^{k} L[i]$$

Expected cost over all files:

$$E[cost] = \frac{1}{n} \sum_{k=1}^{n} \sum_{i=1}^{k} L[i]$$

For a permutation $\pi$:

$$E[cost(\pi)] = \frac{1}{n} \sum_{k=1}^{n} \sum_{i=1}^{k} L[\pi(i)]$$

## Lemma 4.1

$E[cost(\pi)]$ is minimized when $L[\pi(i)] \leq L[\pi(i+1)]$ for all $i$.

### Proof (Exchange Argument)

Suppose $L[\pi(i)] > L[\pi(i+1)]$ for some $i$. Let $a = \pi(i)$, $b = \pi(i+1)$.

Swapping $a$ and $b$:
- Cost of accessing $a$ increases by $L[b]$
- Cost of accessing $b$ decreases by $L[a]$
- Net change = $(L[b] - L[a]) / n < 0$ since $L[b] < L[a]$

Any out-of-order pair can be improved by swapping → sorted order is optimal. $\blacksquare$

## Greedy Algorithm

Sort files by **increasing length** $L[i]$. No backtracking needed.

```
sort files by L[i] ascending
write files to tape in sorted order
```

Running time: $O(n \log n)$

## Generalization: Non-Uniform Access Frequencies

Given access frequency array $F[1..n]$, total cost is:

$$\Sigma cost(\pi) = \sum_{k=1}^{n} \sum_{i=1}^{k} F[\pi(k)] \cdot L[\pi(i)]$$

| Condition | Optimal order |
|---|---|
| All $F[i]$ equal | Sort by increasing $L[i]$ |
| All $L[i]$ equal | Sort by decreasing $F[i]$ |
| Both vary | Sort by increasing ratio $L[i] / F[i]$ |

## Lemma 4.2

$\Sigma cost(\pi)$ is minimized when $\frac{L[\pi(i)]}{F[\pi(i)]} \leq \frac{L[\pi(i+1)]}{F[\pi(i+1)]}$ for all $i$.

### Proof (Exchange Argument)

Suppose $L[a]/F[a] > L[b]/F[b]$ for adjacent tasks $a$, $b$.

Swapping changes total cost by $L[b]F[a] - L[a]F[b]$.

Since $L[a]/F[a] > L[b]/F[b]$ implies $L[a]F[b] > L[b]F[a]$, the change is negative → improvement.

Any out-of-order pair improves on swap → ratio-sorted order is optimal. $\blacksquare$

## Key Insight

This is the **greedy paradigm**: prove any other solution can be improved
by a local exchange → globally optimal = locally optimal order.


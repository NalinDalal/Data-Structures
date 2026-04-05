# Minimizing Sums

Given `n` numbers `[a₁, a₂, a₃, ..., aₙ]`, find a value `x` that minimizes:

$$|a_1 - x|^c + |a_2 - x|^c + \dots + |a_n - x|^c$$

We'll focus on the cases where **c = 1** and **c = 2**.

---

## Case 1: c = 1

We minimize the sum of absolute deviations:

$$|a_1 - x| + |a_2 - x| + \dots + |a_n - x|$$

### Example

Given numbers `{1, 2, 9, 2, 6}`:

- Best solution: `x = 2`
- Sum: `|1-2| + |2-2| + |9-2| + |2-2| + |6-2| = 12`

### Key Insight

The optimal choice for `x` is the **median** of the numbers (the middle element after sorting).

$$ \{1, 2, 9, 2, 6\} \rightarrow \{1, 2, 2, 6, 9\} \rightarrow x = 2 $$

### Why Median?

- If `x < median`: increasing `x` reduces the sum
- If `x > median`: decreasing `x` reduces the sum

> **Optimal Solution:** `x` is the median of the set.

- If `n` is odd → one median, unique optimal value
- If `n` is even → two medians, any value between them is optimal

---

## Case 2: c = 2

We minimize the sum of squared deviations:

$$(a_1 - x)^2 + (a_2 - x)^2 + \dots + (a_n - x)^2$$

### Example

Given numbers `{1, 2, 9, 2, 6}`:

- Best solution: `x = 4` (the average)
- Sum: `(1-4)² + (2-4)² + (9-4)² + (2-4)² + (6-4)² = 46`

### Key Insight

The optimal choice for `x` is the **mean (average)** of the numbers:

$$x = \frac{a_1 + a_2 + \dots + a_n}{n}$$

### Derivation

Expanding the sum:

$$(a_1 - x)^2 + (a_2 - x)^2 + \dots + (a_n - x)^2$$

$$= n x^2 - 2x(a_1 + a_2 + \dots + a_n) + (a_1^2 + a_2^2 + \dots + a_n^2)$$

Since the last term doesn't depend on `x`, we can minimize:

$$n x^2 - 2xS \quad \text{where } S = a_1 + a_2 + \dots + a_n$$

This is a parabola opening upwards. The minimum occurs at:

$$x = \frac{S}{n} = \text{average}$$

> **Optimal Solution:** `x` is the arithmetic mean of the set.

---

## Summary

| Case | Minimized Sum | Optimal `x` |
|------|---------------|-------------|
| c = 1 | Σ \|aᵢ - x\| | Median |
| c = 2 | Σ (aᵢ - x)² | Mean (Average) |

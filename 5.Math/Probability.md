# Probability & Randomized Algorithms

Probability theory studies random events and their likelihoods. In competitive
programming, it appears in expected-value problems, randomized algorithms, and
Markov chain simulations.

A **probability** is a real number in [0, 1] that indicates how likely an event
is. P(certain event) = 1, P(impossible event) = 0.

---

## Core Concepts

### Events as Sets
An event A is a subset of the outcome space X.  
P(A) = Σ p(x) for x ∈ A, and P(X) = 1 always holds.

### Key Formulas

| Operation | Formula |
|-----------|---------|
| Complement | P(Ā) = 1 − P(A) |
| Union | P(A ∪ B) = P(A) + P(B) − P(A ∩ B) |
| Disjoint union | P(A ∪ B) = P(A) + P(B) |
| Intersection | P(A ∩ B) = P(A) · P(B\|A) |
| Independent intersection | P(A ∩ B) = P(A) · P(B) |
| Conditional | P(A\|B) = P(A ∩ B) / P(B) |

---

## Random Variables & Expected Value

A **random variable** X is a value produced by a random process.

**Expected value:** E[X] = Σ P(X = x) · x

**Linearity of expectation:** E[X₁ + X₂ + … + Xₙ] = E[X₁] + E[X₂] + … + E[Xₙ]  
*(holds even when variables are dependent)*

---

## Distributions

| Distribution | Description | P(X = x) | E[X] |
|---|---|---|---|
| Uniform | n equally likely values a…b | 1/n | (a+b)/2 |
| Binomial | n attempts, success prob p | pˣ(1−p)ⁿ⁻ˣ · C(n,x) | pn |
| Geometric | repeat until first success | (1−p)ˣ⁻¹ · p | 1/p |

---

## Standard Topics

- [Probability Basics](./1.basics.cpp)
- [Expected Value & Distributions](./2.expected_value.cpp)
- [Markov Chain Simulation](./3.markov_chain.cpp)
- [Quickselect — Las Vegas Algorithm](./4.quickselect.cpp)
- [Freivalds' Algorithm — Monte Carlo](./5.freivalds.cpp)

---

## Markov Chains

A **Markov chain** is a random process with states and transitions.  
The probability distribution is a vector [p₁, p₂, …, pₙ] where pₖ = P(current state is k).

- Simulate a walk of m steps in **O(n²m)** using DP on the distribution vector.
- Or use matrix exponentiation to compute the distribution after m steps in **O(n³ log m)**.

---

## Randomized Algorithms

| Type | Description |
|---|---|
| **Monte Carlo** | May give wrong answer; probability of error must be small |
| **Las Vegas** | Always correct; running time varies randomly |

### Example Algorithms
- **Quickselect** — finds kth order statistic in O(n) expected, O(n²) worst
- **Freivalds'** — verifies AB = C in O(n²) using a random vector (Monte Carlo)
- **Random graph coloring** — finds a 2-coloring where ≥ m/2 edges are bichromatic (Las Vegas)



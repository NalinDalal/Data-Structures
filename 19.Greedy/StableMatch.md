# Stable Matching

n doctors + n hospitals. Each ranks all members of the other side. A **matching** is unstable if there's a pair (α, B) where both prefer each other over their current match. Goal: find a **stable matching** — one with no unstable pairs.


## Why naive approaches failGreedily fixing instabilities can loop forever (discovered by Knuth). The multi-round greedy protocol (unmatched hospitals offer to favourite unmatched doctor each round) also fails — it can terminate in an unstable matching.

---

## Gale-Shapley algorithm

**Hospital-proposing variant** (originally Boston Pool, 1952). Each round:
1. An unmatched hospital offers to the best doctor it hasn't already been rejected by.
2. Doctor tentatively accepts if unmatched, or swaps if she prefers the new offer. Otherwise rejects.

Repeat until all matched.**Key invariant:** once a doctor receives any offer, she is never unmatched again — she only ever trades up.

---

## Complexity

| Aspect | Bound |
|---|---|
| Max offers made | n² (each hospital offers each doctor at most once) |
| Overall running time | **O(n²)** |
| Lower bound | Ω(n²) inputs exist → tight |

Representation: doctors/hospitals as integers 1..n, preferences as `Dpref[i,r]` and `Hpref[j,r]`. Each offer processed in O(1) after preprocessing.

---

## Correctness proof sketch

**Termination + completeness:** Once a doctor gets an offer she stays matched. If any doctor were unmatched at the end, the hospital that hasn't offered her yet would have exhausted nobody — impossible. So the algorithm always produces a **perfect matching**.

**Stability:** Suppose α is matched to A but prefers B. Since doctors only accept the best offer received, α never got an offer from B. But B makes offers in preference order — so B already found someone it prefers to α. Hence (α, B) is not an unstable pair. ∎

---

## Optimality (the surprise result)**Lemma 4.7:** A hospital is rejected only by doctors infeasible for it (proved by induction — if α rejects A for B, everyone B prefers over α already rejected B and is infeasible for B).

**Corollary 4.8:** GS matches A with best(A) for every hospital.

**Corollary 4.9:** GS matches α with worst(α) for every doctor.

Crucially, **the result is the same regardless of which hospital proposes in each round** — the algorithm always produces the unique hospital-optimal stable matching.

---

## The flip side (NRMP 1998 change)

Dubins & Freedman (1981): doctors can improve their outcome by lying about preferences; hospitals cannot. This is a structural property of who proposes. In 1998, NRMP switched to **doctor-proposing** GS — now doctors get best(α) and hospitals get worst(A). In practice, fewer than 1% of matches changed.

---

## Cheat sheet

```
feasible(α, A)  = ∃ stable matching assigning α to A
best(A)         = highest-ranked feasible doctor for A
worst(α)        = lowest-ranked feasible hospital for α

Hospital-GS → best for hospitals, worst for doctors
Doctor-GS   → best for doctors, worst for hospitals
```

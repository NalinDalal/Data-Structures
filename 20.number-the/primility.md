# Primality Testing

## Density of Primes

The **prime distribution function** $\pi(n)$ = number of primes $\leq n$.

**Prime Number Theorem:**

$$\lim_{n \to \infty} \frac{\pi(n)}{n / \ln n} = 1$$

So a random integer near $n$ is prime with probability $\approx 1/\ln n$.  
To find a random 512-bit prime: test $\approx \ln 2^{512} \approx 355$ candidates on average.

**Trial division** — naive approach, divide $n$ by $2, 3, \ldots, \lfloor\sqrt{n}\rfloor$.  
Worst-case: $\Theta(\sqrt{n}) = \Theta(2^{\beta/2})$ — **exponential** in the bit-length. Impractical for large $n$.

---

## Pseudoprimality Testing

Let $\mathbb{Z}_n^+ = \{1, 2, \ldots, n-1\}$. If $n$ is prime, $\mathbb{Z}_n^+ = \mathbb{Z}_n^*$.

$n$ is a **base-$a$ pseudoprime** if $n$ is composite but:

$$a^{n-1} \equiv 1 \pmod{n}$$

By Fermat's theorem, every prime satisfies this for all $a \in \mathbb{Z}_n^+$. So if we find any $a$ that violates it, $n$ is definitely composite.

```
PSEUDOPRIME(n):
  if MODULAR-EXPONENTIATION(2, n-1, n) ≢ 1 (mod n):
    return COMPOSITE   // definitely
  else:
    return PRIME       // probably (could be base-2 pseudoprime)
```

**Error:** Only one type — it can falsely say PRIME, never falsely say COMPOSITE.

**Weakness — Carmichael numbers:** Composite $n$ that satisfy $a^{n-1} \equiv 1 \pmod{n}$ for **all** $a \in \mathbb{Z}_n^*$. First few: 561, 1105, 1729. The pseudoprime test cannot detect these. Miller-Rabin can.

---

## Miller-Rabin Randomized Primality Test

Two improvements over PSEUDOPRIME:
1. Tests **multiple random bases** $a$ instead of just $a = 2$
2. Detects **nontrivial square roots of 1** mod $n$ during squaring steps (Corollary 31.35 — if such a root exists, $n$ is composite)

### Setup

Write $n - 1 = 2^t u$ where $t \geq 1$ and $u$ is odd.

For a given base $a$, WITNESS computes the sequence:

$$X = \langle a^u,\ a^{2u},\ a^{2^2 u},\ \ldots,\ a^{2^t u} \rangle \pmod{n}$$

```
WITNESS(a, n):
  let n-1 = 2^t * u  (u odd, t ≥ 1)
  x₀ ← MODULAR-EXPONENTIATION(a, u, n)
  for i = 1 to t:
    xᵢ ← xᵢ₋₁² mod n
    if xᵢ = 1 and xᵢ₋₁ ≠ 1 and xᵢ₋₁ ≠ n-1:
      return TRUE   // nontrivial square root found → composite
  if xₜ ≠ 1:
    return TRUE     // Fermat witness → composite
  return FALSE      // a is not a witness
```

WITNESS$(a, n)$ returns TRUE iff $a$ **proves** $n$ is composite.

### Four cases for sequence $X = \langle x_0, \ldots, x_t \rangle$

| Sequence ends in... | Last non-1 is... | Result |
|---|---|---|
| $d \neq 1$ | — | TRUE — Fermat witness |
| all 1's | — | FALSE — not a witness |
| $\ldots, -1, 1, \ldots, 1$ | $-1$ | FALSE — trivial square root |
| $\ldots, d, 1, \ldots, 1$ where $d \neq \pm 1$ | $d$ | TRUE — nontrivial square root |

```
MILLER-RABIN(n, s):
  for j = 1 to s:
    a ← RANDOM(1, n-1)
    if WITNESS(a, n):
      return COMPOSITE   // definitely
  return PRIME           // almost surely
```

**Complexity:** $O(s\beta)$ arithmetic operations, $O(s\beta^3)$ bit operations.

---

## Error Rate

**Theorem:** If $n$ is an odd composite, at least $(n-1)/2$ values of $a \in \mathbb{Z}_n^+$ are witnesses to the compositeness of $n$.

**Theorem:** The probability that MILLER-RABIN$(n, s)$ errs is at most $2^{-s}$.

**Proof sketch:** Each iteration has probability $\geq 1/2$ of finding a witness. Missing all $s$ iterations has probability $\leq (1/2)^s = 2^{-s}$. $\blacksquare$

> $s = 50$ suffices for virtually any application — error probability $\leq 2^{-50} \approx 10^{-15}$.

**Key distinction from PSEUDOPRIME:** The error rate of Miller-Rabin does **not** depend on $n$ — there are no "bad inputs." The error probability is purely a function of $s$.

---

## Summary: Comparison of Primality Tests

| Test | Handles Carmichael? | Error type | Error bound |
|---|---|---|---|
| Trial division | ✓ (exact) | None | — |
| PSEUDOPRIME | ✗ | False PRIME | Depends on $n$ |
| MILLER-RABIN | ✓ | False PRIME | $\leq 2^{-s}$ |

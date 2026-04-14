# Chinese Remainder Theorem 

## Core Idea

Given $n = n_1 n_2 \cdots n_k$ where $n_i$ are **pairwise coprime**, there is a bijection:

$$a \leftrightarrow (a_1, a_2, \dots, a_k) \quad \text{where } a_i = a \bmod n_i$$

This maps $\mathbb{Z}_n$ to $\mathbb{Z}_{n_1} \times \mathbb{Z}_{n_2} \times \cdots \times \mathbb{Z}_{n_k}$.  
Operations $(+, -, \times)$ mod $n$ can be done **component-wise**.

---

## Two Directions

| Direction | What | Cost |
|---|---|---|
| $a \to (a_1, \dots, a_k)$ | Compute $a_i = a \bmod n_i$ | Easy — $k$ divisions |
| $(a_1, \dots, a_k) \to a$ | Use basis elements $c_i$ | Harder — needs modular inverses |

---

## Reconstruction

**Step 1.** Define $m_i = n / n_i$ (product of all $n_j$ except $n_i$).

**Step 2.** Compute the basis elements:

$$c_i = m_i \cdot (m_i^{-1} \bmod n_i)$$

> Since $\gcd(m_i, n_i) = 1$, the inverse always exists (Corollary 31.26).

Each $c_i$ acts as a "basis vector" — it is $1$ in component $i$ and $0$ everywhere else:

$$c_i \leftrightarrow (0, \dots, 0, 1, 0, \dots, 0)$$

**Step 3.** Reconstruct $a$:

$$a \equiv (a_1 c_1 + a_2 c_2 + \cdots + a_k c_k) \pmod{n}$$

---

## Worked Example ($n_1 = 5,\ n_2 = 13,\ n = 65$)

Solve: $a \equiv 2 \pmod{5}$ and $a \equiv 3 \pmod{13}$

$$13^{-1} \equiv 2 \pmod{5} \implies c_1 = 13 \cdot 2 = 26$$
$$5^{-1} \equiv 8 \pmod{13} \implies c_2 = 5 \cdot 8 = 40$$
$$a \equiv 2 \cdot 26 + 3 \cdot 40 = 52 + 120 = 172 \equiv \boxed{42} \pmod{65}$$

**Check:** $42 \bmod 5 = 2\ ✓$, $\quad 42 \bmod 13 = 3\ ✓$

---

## Corollaries

**Uniqueness** 
If $n_1, \dots, n_k$ are pairwise coprime, the system $x \equiv a_i \pmod{n_i}$ has a **unique solution** mod $n$.

**Equivalence** 
$$x \equiv a \pmod{n_i}\ \forall i \quad \iff \quad x \equiv a \pmod{n}$$

---

## Why It Matters

1. **Structure theorem** — describes $\mathbb{Z}_n$ as a Cartesian product; powerful algebraic insight.
2. **Efficient computation** — working in smaller moduli $n_i$ can need fewer bit operations than working mod $n$ directly (e.g. RSA with CRT is ~4× faster).

---

## Related Results

**Euler's Theorem**

$$a^{\phi(n)} \equiv 1 \pmod{n} \quad \forall a \in \mathbb{Z}_n^*$$

**Fermat's Little Theorem**

$$a^{p-1} \equiv 1 \pmod{p} \quad \text{for prime } p,\ a \in \mathbb{Z}_p^*$$

**Nontrivial square roots of 1**  
If $x^2 \equiv 1 \pmod{n}$ has a solution other than $x \equiv \pm 1$, then $n$ is **composite**.  
> Used directly in the **Miller–Rabin primality test** (§31.8).

---

## Modular Exponentiation — Repeated Squaring

Compute $a^b \bmod n$ efficiently. Let $b = \langle b_k, b_{k-1}, \dots, b_0 \rangle$ in binary.

```
MODULAR-EXPONENTIATION(a, b, n)
  c ← 0, d ← 1
  for i = k downto 0:
    c ← 2c
    d ← (d · d) mod n
    if b_i = 1:
      c ← c + 1
      d ← (d · a) mod n
  return d
```

**Loop invariant:** $d = a^c \bmod n$ throughout.

**Complexity:** $O(\beta)$ multiplications, $O(\beta^3)$ bit operations where $\beta$ = number of bits in inputs.

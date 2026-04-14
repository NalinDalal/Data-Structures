# **INTEGER FACTORISATION — DIRECT NOTES (CLRS + Pollard Rho focus)**

---

### 1. Problem definition

* Given integer ( n ), find non-trivial factors ( p, q ) such that:
  [
  n = p \cdot q
  ]
* Hard in general → foundation of cryptography (RSA).
* Complexity depends heavily on **size of smallest prime factor**.

---

### 2. Baselines

* **Trial division**

  * Check up to ( \sqrt{n} )
  * Time: ( O(\sqrt{n}) )
  * Too slow for large ( n )

---

### 3. Key idea behind modern methods

* Work in modular arithmetic
* Use structure of ( \mathbb{Z}_n )
* Try to detect **non-trivial gcd**
  [
  \gcd(x - y, n) \neq 1, n
  ]

---

### 4. Pollard Rho — Core idea

* Generate pseudo-random sequence:
  [
  x_{i+1} = f(x_i) \mod n
  ]
  typically:
  [
  f(x) = x^2 + c \mod n
  ]

* Use **cycle detection (Floyd’s algorithm)**:

  * tortoise: ( x )
  * hare: ( y = f(f(y)) )

* At each step:
  [
  d = \gcd(|x - y|, n)
  ]

---

### 5. Algorithm (clean)

```
x = random
y = x
d = 1

while d == 1:
    x = f(x)
    y = f(f(y))
    d = gcd(|x - y|, n)

if d == n:
    retry with different params
else:
    return d
```

---

### 6. Why it works

* Sequence behaves “random-like”
* By **birthday paradox**, collisions happen fast
* When:
  [
  x_i \equiv x_j \ (\text{mod } p)
  ]
  but NOT mod ( n )

→ then:
[
p \mid (x_i - x_j)
]

→ so:
[
\gcd(x_i - x_j, n) = p
]

---

### 7. Key intuition (CLRS-level)

* Instead of searching factors directly
* Search for **collision mod p**
* Hidden factor emerges via gcd

---

### 8. Complexity

* Expected:
  [
  O(\sqrt{p})
  ]
  where ( p ) = smallest prime factor ([Wikipedia][1])

* Very fast when:

  * one factor is small

* Bad when:

  * both factors large and similar

---

### 9. Practical behavior

* Probabilistic algorithm

* May fail → retry with:

  * different ( x )
  * different constant ( c )

* Very low memory usage

---

### 10. Important implementation details

* Use:

  * fast modular multiplication
  * overflow-safe arithmetic
* Avoid bad polynomials:

  * ( x^2 ) → poor randomness
* Common choice:

  * ( x^2 + 1 )

---

### 11. Full factorization strategy

Pollard Rho gives **one factor**, not all.

To factor completely:

```
factor(n):
    if n is prime → return n
    d = pollard_rho(n)
    return factor(d) + factor(n/d)
```

---

### 12. Relation to CLRS explanation

* Sequence ( x_i ) forms cycle (rho shape)

* Define:

  * tail length = ( t )
  * cycle length = ( u )

* Expected:
  [
  t, u = \Theta(\sqrt{p})
  ]

* Factor found when:
  [
  x_i \equiv x_j \ (\text{mod } p)
  ]

---

### 13. Failure cases

* ( d = 1 ) → continue
* ( d = n ) → bad cycle → restart

---

### 14. Comparison with other methods

| Method          | Use case                |
| --------------- | ----------------------- |
| Trial division  | very small n            |
| Pollard Rho     | medium n, small factors |
| Pollard p−1     | when ( p-1 ) smooth     |
| Quadratic Sieve | large n                 |
| GNFS            | very large n            |

---

### 15. Key takeaways

* Converts factorization → cycle detection problem
* Uses randomness + number theory
* Extremely effective for competitive programming / mid-size integers
* Core primitive: **gcd reveals hidden factor**

---

### 16. Mental model

* You’re not “finding factors”
* You’re forcing:

  * two numbers to collide modulo a hidden factor
* Then extracting that factor via gcd



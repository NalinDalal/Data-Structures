# Hash Tables


## Table of Contents

1. [Theory — What and Why](#1-theory--what-and-why)
2. [Proofs — The Math Behind O(1)](#2-proofs--the-math-behind-o1)
3. [Implementation — How to Build It](#3-implementation--how-to-build-it)
4. [Intuition — Why O(1) Isn't Magic](#4-intuition--why-o1-isnt-magic)
5. [Perfect Hashing (FKS Scheme)](#5-perfect-hashing-fks-scheme)
6. [Cuckoo Hashing](#6-cuckoo-hashing)
7. [Bloom Filters](#7-bloom-filters)
8. [Cuckoo Filters](#8-cuckoo-filters)
9. [Tradeoff Summary](#9-tradeoff-summary)
10. [API Reference](#10-api-reference)

---

## 1. Theory — What and Why

### Goal of Hashing

We want these operations in **O(1)** time:

- Insert: O(1)
- Search: O(1)
- Delete: O(1)

### Direct Addressing

Store element with key `k` at slot `k` of a table size `|U|`.

- **Pros**: Worst-case O(1)
- **Cons**: Space = **O(|U|)** — too large if universe is big

### Hash Tables

Reduce space to **O(n)** where `n = number of keys`:

```
h : U → {0, 1, ..., m-1}
index = h(k)
```

**Tradeoff**: Average-case O(1), but not worst-case.

---

## 2. Proofs — The Math Behind O(1)

### Universal Hashing

Hash function randomly chosen from a family H:

```
h(k) = ((k · A) mod p) mod m
```

Where:
- `p` = large prime
- `A` = random in `[1, p-1]`
- `m` = table size

**Definition**: H is *universal* if for any x ≠ y:

```
P(h(x) = h(y)) ≤ 1/m
```

### Collision Probability Proof

Collision means:
```
((xA mod p) mod m) = ((yA mod p) mod m)
⟹ ((x - y)A mod p) ≡ 0 mod m
```

Only ~p/m values of A satisfy this out of p total choices.

Therefore: `P(collision) ≈ (p/m) / p = 1/m` ✓

### Expected Search Time

**Theorem**:
```
E[T(get)] = O(1 + α)
```
where `α = n/m` (load factor)

**Proof**:

For each x ≠ k, P(h(x) = h(k)) = 1/m
```
E[collisions] = (n - 1) · (1/m) ≈ n/m = α
```

If m ≈ n, then α ≈ 1, so `E[T] = O(1)` ✓

### Open Addressing Analysis

| Load factor α | Unsuccessful search | Successful search |
|--------------|--------------------|--------------------|
| 0.50         | 2.0                | 1.39               |
| 0.75         | 4.0                | 1.85               |
| 0.90         | 10.0               | 2.56               |
| 0.95         | 20.0               | 3.15               |

- **Unsuccessful search**: `E[probes] ≤ 1/(1-α)`
- **Successful search**: `E[probes] ≤ (1/α) · ln(1/(1-α))`

---

## 3. Implementation — How to Build It

### Hash Functions

**Division Method** (for integers):
```
h(k) = k mod m
```
Choose m = prime not close to a power of 2.

**Multiplication Method**:
```
h(k) = floor(m · (kA mod 1))
```
Knuth's A ≈ (√5 - 1)/2 = 0.618...

**For strings**:
```cpp
int hash(string key) {
    int h = 0;
    for (char c : key)
        h = 31 * h + c;
    return h % m;
}
```

### Collision Handling

#### Separate Chaining

Each bucket holds a linked list.

```
table[i] → [key|value] → [key|value] → ...
```

- Insert: prepend → O(1)
- Search: scan list → O(1 + α)

#### Open Addressing

All elements stored in the array itself.

**Linear Probing**:
```
h(k,i) = (h'(k) + i) mod m
```
Problem: **Primary clustering**

**Quadratic Probing**:
```
h(k,i) = (h'(k) + c1·i + c2·i²) mod m
```
Problem: **Secondary clustering**

**Double Hashing** (best):
```
h(k,i) = (h1(k) + i·h2(k)) mod m
```
Avoids clustering, near-uniform probing.

### Pseudocode

#### Insert (Open Addressing)
```
put(k, v):
    i = h(k)
    while table[i] occupied:
        i = (i + 1) mod m
    table[i] = (k, v)
```

#### Search (Open Addressing)
```
get(k):
    i = h(k)
    while table[i] not empty:
        if table[i].key == k:
            return value
        i = (i + 1) mod m
    return null
```

### Resizing

- Load factor > 0.75 → **rehash** with doubled capacity
- Re-insert all elements with the new hash function

---

## 4. Intuition — Why O(1) Isn't Magic

### Key Insights

1. **O(1) is expected, not guaranteed** — depends on random hashing
2. **Load factor matters** — keep α < 0.75
3. **Worst case = O(n)** — if hash function is poor or adversarial input

### What Interviewers Care About

- **Why collisions happen** → pigeonhole principle (|U| > m)
- **Why O(1)** → expectation over a random hash function
- **Role of load factor** → controls probes, triggers resizing
- **Chaining vs Open Addressing** → memory vs cache performance tradeoff
- **When worst case happens** → all keys hash to the same slot

### Complexity Summary

| Operation | Average | Worst |
|-----------|---------|-------|
| Insert    | O(1)    | O(n)  |
| Delete    | O(1)    | O(n)  |
| Search    | O(1)    | O(n)  |
| Space     | O(n)    | O(n)  |

---

## 5. Perfect Hashing (FKS Scheme)

**Goal**: O(1) *worst-case* lookup for a static set of keys.

### Structure

```
Level 1: hash n keys into m = n slots using h ∈ H
Level 2: for each slot i, build a secondary table a[i]
         size of a[i] = n_i²   (n_i = number of keys hashing to slot i)
         use a secondary hash g_i ∈ H with no collisions
```

### Space Analysis

**Key insight**: Size = Σ nᵢ²

```
E(Σ nᵢ²) = E(number of pairs (x,y): h(x)=h(y))
          = n + E(|{(x,y): x≠y, h(x)=h(y)}|)
          = n + n(n-1)/2 · (1/n)
          = n + (n-1)/2
          = O(n)
```

### Collision Bound

For a secondary table of size nᵢ²:
```
E(collisions in a[i]) = n_i(n_i-1)/2 · (1/n_i²) ≈ 1/2

P(collision ≥ 1) ≤ 1/2
```

Retry with a new hash if collision occurs — expected 2 tries.

### Result

| Property | Value |
|----------|-------|
| Lookup   | O(1) worst-case |
| Space    | O(n) expected |
| Build time | O(n) expected |

> **Trade-off**: Only works for *static* key sets (known in advance). Cannot support insertions efficiently.

---

## 6. Cuckoo Hashing

**Goal**: O(1) worst-case *lookup*, O(1) amortized insert.

### Structure

Two arrays `a₁` and `a₂`, each of size ~0.5n.  
Two hash functions `h₁(k)` and `h₂(k)`.

**Invariant**: Key `k` is always in `a₁[h₁(k)]` OR `a₂[h₂(k)]`.

```
a₁  [ ][ ][ ][ ][ ][ ][ ][ ]    ← size 0.5n
a₂  [ ][ ][ ][ ][ ][ ][ ][ ]    ← size 0.5n
```

### Operations

**get(k)** — O(1) worst-case:
```
look in a₁[h₁(k)]
look in a₂[h₂(k)]
```
Only ever checks 2 slots.

**put(k, v)** — insert with eviction:
```
place k at a₁[h₁(k)]
if occupied, evict existing key x → try a₂[h₂(x)]
if that's occupied, evict again → try a₁[h₁(...)]
repeat until empty slot found (or cycle detected → rehash)
```

**Visualization** (inserting B):
```
Before: a₁[...X...] a₂[...D...]
Insert B → evicts X → X evicts A → A settles → B placed
```

### Guarantees

- Lookup: **O(1) worst-case** (always checks exactly 2 locations)
- Insert: **O(1) amortized** expected (with O(log n) expected eviction chain)
- Requires load factor α < 0.5

### k-Universal Hashing (Generalization)

A family H is *k-universal* if for any k distinct keys x₁,...,xₖ and any y₁,...,yₖ:

```
P(h(x₁)=y₁, h(x₂)=y₂, ..., h(xₖ)=yₖ) ≈ 1/mᵏ
```

Used to prove correctness of cuckoo hashing.

---

## 7. Bloom Filters

**Goal**: Space-efficient probabilistic set membership. No false negatives; small false positive rate ε.

### Structure

- Bit array `a` of size `m`, initialized to 0
- `k` independent hash functions `h₁, h₂, ..., hₖ`

```
a  [0|0|1|0|1|1|0|0|1|0|0|1|...]   ← m bits
        ↑       ↑ ↑     ↑
        hashing positions set to 1
```

### Operations

**insert(x)**:
```
for i = 1..k:
    a[hᵢ(x)] = 1
```

**contains(x)**:
```
for i = 1..k:
    if a[hᵢ(x)] == 0:
        return false   // definitely not in set
return true            // probably in set
```

### False Positive Analysis

Probability a single bit is still 0 after n insertions:
```
P(bit = 0) ≈ (1 - 1/m)^(kn) ≈ e^(-kn/m)
```

False positive probability:
```
ε ≈ (1 - e^(-kn/m))^k ≈ (1/2)^k
```

### Optimal Parameters

```
k ≈ log₂(1/ε)                  ← number of hash functions
m ≈ 2kn / load_factor ≈ 1.44kn ← bits needed
```

**Example**: n = 10⁶, ε ≈ 10⁻¹⁸
```
k ≈ 60
m ≈ 6 × 10⁷ bits = 7.5 MB
```

### Key Properties

| Property | Value |
|----------|-------|
| False negatives | Never |
| False positives | Rate ≤ ε |
| Space | O(n log(1/ε)) bits |
| Lookup | O(k) = O(log(1/ε)) |
| Deletions | Not supported |

---

## 8. Cuckoo Filters

**Goal**: Like a Bloom filter, but supports **deletions** and achieves better space efficiency.

### Core Idea

Instead of storing full keys, store **fingerprints** — short `f`-bit hashes of keys.

```
x' = h(x)   // x' is the f-bit fingerprint of x
```

### Structure

Two arrays `a₁`, `a₂` (like cuckoo hashing), but each slot stores a fingerprint, not the full key.

**Invariant**: If `x` is in the set, then  
- `a₁[h₁(x)]` contains `x'`, OR  
- `a₁[h₂(x)]` contains `x'`

### Hash Function Trick

To enable deletion without knowing the original key:
```
h₁(x) = hash(x)
h₂(x) = h₁(x) ⊕ hash(x')    // XOR with hash of fingerprint
```

This means you can compute `h₂` from `h₁` and the fingerprint alone — no need to store `x`.

**Displacement**: If fingerprint `A'` is at position `i`:
```
alternate position = i ⊕ hash(A')
```

### Comparison: Bloom vs Cuckoo Filter

| Feature            | Bloom Filter | Cuckoo Filter |
|--------------------|-------------|---------------|
| False negatives    | Never       | Never         |
| False positives    | Rate ε      | Rate ε        |
| Deletions          | No          | Yes           |
| Space efficiency   | ~1.44x      | ~1.05x (better) |
| Lookup time        | O(k)        | O(1)          |

### Space

```
Size ≈ (k · n) / load_factor
```
where k ≈ log₂(1/ε) + 1

---

## 9. Tradeoff Summary

| Structure        | Lookup         | Insert        | Delete | Space      | Notes                         |
|-----------------|----------------|---------------|--------|------------|-------------------------------|
| Chaining        | O(1+α) avg     | O(1) avg      | Yes    | O(n)       | Simple, flexible              |
| Open Addressing | O(1/(1-α)) avg | O(1/(1-α))    | Yes*   | O(n)       | Cache-friendly, tricky delete |
| Perfect Hashing | O(1) worst     | No (static)   | No     | O(n) exp.  | Static keys only              |
| Cuckoo Hashing  | O(1) worst     | O(1) amort.   | Yes    | O(n)       | α < 0.5                       |
| Bloom Filter    | O(k) prob.     | O(k)          | No     | O(n log 1/ε) bits | False positives only     |
| Cuckoo Filter   | O(1) prob.     | O(1) amort.   | Yes    | O(n log 1/ε) bits | Better than Bloom         |

\* Open addressing deletion requires tombstone markers or Robin Hood rehashing.

---

## 10. API Reference

### Features

- Template-based generic key-value support
- Open addressing with linear/quadratic/double hashing
- Dynamic resizing (rehashing at α > 0.75)
- Operator overloading for `[]`

### Methods

| Method          | Description                     |
|----------------|---------------------------------|
| `insert(k, v)` | Insert key-value pair           |
| `remove(k)`    | Remove key                      |
| `contains(k)`  | Check if key exists             |
| `operator[]`   | Access or insert                |
| `size()`       | Return number of items          |
| `empty()`      | Check if empty                  |
| `clear()`      | Clear all elements              |

### Example

```cpp
HashMap<string, int> map;

map["apple"] = 5;
map["banana"] = 8;

cout << map["apple"];       // 5
map.remove("banana");
cout << map.contains("banana");  // false
```

---

## Limitations

- Not thread-safe
- Worst-case O(n) with poor hash function
- Custom keys require `==` and `hash()` to be defined
- Bloom/Cuckoo filters are probabilistic — not suitable when exact answers are required

# Hash Tables

A clean, organized guide covering theory, proofs, implementation, and intuition.

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

Hash function randomly chosen from a family:

```
h(k) = ((k · A) mod p) mod m
```

Where:
- `p` = large prime
- `A` = random in `[1, p-1]`
- `m` = table size

### Collision Probability

**Theorem**: For x ≠ y:

```
P(h(x) = h(y)) ≈ 1/m
```

**Proof**:

Collision means:
```
((xA mod p) mod m) = ((yA mod p) mod m)
```
```
((x - y)A mod p) ≡ 0 mod m
```

Only ~p/m values of A satisfy this out of p total choices.

Therefore: P(collision) ≈ (p/m)/p = 1/m

### Expected Search Time

**Theorem**:

```
E[T(get)] = O(1 + α)
```

where `α = n/m` (load factor)

**Proof**:

For each x ≠ k, P(h(x) = h(k)) = 1/m

```
E[collisions] = (n - 1) * (1/m) ≈ n/m = α
```

If m ≈ n, then α ≈ 1, so E[T] = O(1)

### Open Addressing Analysis

| Load factor α | Unsuccessful search | Successful search |
|------------|-------------------|------------------|
| 0.50       | 2.0               | 1.39            |
| 0.75       | 4.0               | 1.85            |
| 0.90       | 10.0              | 2.56            |
| 0.95       | 20.0              | 3.15            |

**Unsuccessful search**: E[probes] ≤ 1/(1-α)

**Successful search**: E[probes] ≤ (1/α) · ln(1/(1-α))

---

## 3. Implementation — How to Build It

### Hash Functions

**Division Method** (for integers):
```
h(k) = k mod m
```
- Choose m = prime not close to power of 2

**Multiplication Method**:
```
h(k) = floor(m * (kA mod 1))
```
- Knuth's A ≈ (√5 - 1)/2 = 0.618...

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

All elements in the array.

**Linear Probing**:
```
h(k,i) = (h'(k) + i) mod m
```
- **Problem**: Primary clustering

**Quadratic Probing**:
```
h(k,i) = (h'(k) + c1·i + c2·i²) mod m
```
- **Problem**: Secondary clustering

**Double Hashing** (best):
```
h(k,i) = (h1(k) + i·h2(k)) mod m
```
- Avoids clustering, near-uniform probing

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
- Re-insert all elements with new hash function

---

## 4. Intuition — Why O(1) Isn't Magic

### Key Insights

1. **O(1) is expected, not guaranteed** — depends on random hashing
2. **Load factor matters** — keep α < 0.75
3. **Worst case = O(n)** — if hash function is poor or adversarial input

### What Interviewers Care About

- **Why collisions happen** → pigeonhole principle (|U| > m)
- **Why O(1)** → expectation over random hash function
- **Role of load factor** → controls probes, triggers resizing
- **Chaining vs Open Addressing** → tradeoff: memory vs cache performance
- **When worst case happens** → all keys hash to same slot

### Perfect Hashing (Static Keys)

When keys are known in advance:

- **Level 1**: hash n keys into m = n slots
- **Level 2**: each slot j has table of size m_j = n_j²
- **Result**: O(1) worst-case lookup, O(n) space

---

## Complexity Summary

| Operation | Average | Worst |
|-----------|---------|-------|
| Insert    | O(1)    | O(n)  |
| Delete    | O(1)    | O(n)  |
| Search    | O(1)    | O(n)  |
| Space     | O(n)    | O(n)  |

---

## Features

- Template-based generic key-value support
- Open addressing with linear/quadratic/double hashing
- Dynamic resizing (rehashing)
- Operator overloading for `[]`

## API

| Method          | Description                    |
|----------------|-------------------------------|
| `insert(k, v)` | Insert key-value pair          |
| `remove(k)`    | Remove key                    |
| `contains(k)`  | Check if key exists          |
| `operator[]`   | Access or insert               |
| `size()`       | Return number of items        |
| `empty()`      | Check if empty               |
| `clear()`      | Clear all elements           |

## Example

```cpp
HashMap<string, int> map;

map["apple"] = 5;
map["banana"] = 8;

cout << map["apple"];  // 5
map.remove("banana");
cout << map.contains("banana");  // false
```

---

## Limitations

- Not thread-safe
- Worst-case O(n) with poor hash
- Custom keys need `==` and `hash()` defined
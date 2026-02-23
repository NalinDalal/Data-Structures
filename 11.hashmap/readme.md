## Table of Contents

1. [What is a HashMap?](#what-is-a-hashmap)
2. [How HashMap Works](#how-hashmap-works)
3. [Hashing Function](#hashing-function)
4. [Collision Resolution](#collision-resolution)
5. [Resizing & Load Factor](#resizing--load-factor)
6. [Features](#features)
7. [Usage](#usage)
8. [Complexity](#complexity)
9. [Limitations](#limitations)
10. [Future Enhancements](#future-enhancements)

---

##  What is a HashMap?

A **HashMap** (also known as an unordered map or dictionary) allows you to store and retrieve values using keys.
A **HashMap** is a key-value data structure that provides **average-case constant time complexity** (`O(1)`) for insertion, deletion, and lookup operations.

### Direct Addressing vs Hashing

The simplest approach is **direct addressing**: store an element with key `k` in slot `k` of a table `T` of size `|U|` (the universe of keys). This gives **worst-case O(1)** lookup, insert, and delete.

The problem: if the universe `U` is large, storing a table of size `|U|` may be impractical or impossible. Furthermore, if the set `K` of keys actually stored is much smaller than `U`, most of the allocated space is wasted.

**Hash tables** solve this. When `|K| << |U|`, a hash table requires only `Θ(|K|)` storage while still achieving **O(1) average-case** search time. The trade-off: this bound is for the *average* time, whereas direct addressing guarantees it in the *worst case*.

Unlike arrays or lists, keys can be:

- Strings
- Integers
- Custom objects (if hashable and comparable)

Example:

```cpp
map["apple"] = 3;
map["banana"] = 5;
cout << map["banana"]; // Output: 5
```

This project implements a custom `HashMap` in C++ using:

- **Open addressing** (or optionally separate chaining)
- **Linear probing** or **quadratic probing**
- **Dynamic resizing** (rehashing)
- **Generic templates** for supporting any key-value types
---

##  How HashMap Works

With direct addressing, an element with key `k` is stored in slot `k`. With hashing, the element is stored in slot `h(k)` — we use a **hash function** `h` to compute the slot from the key `k`. The function `h` maps the universe `U` of keys into the slots of a hash table `T[0 .. m-1]`:

```
h : U → {0, 1, ..., m-1}
```

We say that an element with key `k` **hashes to** slot `h(k)`; `h(k)` is the **hash value** of key `k`. The point of the hash function is to reduce the range of array indices — instead of `|U|` values, we handle only `m` values, and storage requirements are correspondingly reduced.

Step by step:

- Every key is passed to a **hash function**.
- The hash function returns an index (`0` to `capacity - 1`).
- The value is stored in the **bucket** at that index.
- If another key hashes to the same index, a **collision** occurs.

---

##  Hashing Function

A good hash function: each key is equally likely to hash to any of the m slots, independently of
where any other key has hashed to.

A **hash function** maps a key to an integer (bucket index):

```cpp
int hash(string key) {
    int hash = 0;
    for (char c : key)
        hash = 31 * hash + c;
    return hash % capacity;
}
```

One idea is to make `h` appear to be "random", thus avoiding collisions or at least minimizing their number. The term "to hash" — evoking images of random mixing and chopping — captures the spirit of this approach. Of course, `h` must be **deterministic**: a given input `k` must always produce the same output `h(k)`.

$$h(k)= \lfloor km \rfloor$$

Since `|U| > m`, there must be at least two keys that have the same hash value; **avoiding collisions altogether is therefore impossible**. A well-designed, "random"-looking hash function can minimize the number of collisions, but we still need a method for resolving those that do occur.

Good hash functions aim to:

- Distribute keys uniformly
- Be fast to compute
- Avoid clustering (minimize collisions)

### 1. The Division Method

Map key `k` into one of `m` slots by taking the remainder:

$$h(k) = k \mod m$$

- **Fast**: requires only a single division operation.
- **Example**: `m = 12`, `k = 100` → `h(k) = 4`.
- **Avoid** `m = 2^p` — then `h(k)` is just the `p` lowest-order bits of `k`, ignoring the rest.
- **Avoid** `m = 2^p - 1` for radix-`2^p` character strings — permuting characters doesn't change the hash.
- **Good choice**: a **prime not close to a power of 2**.
  - Example: `n ≈ 2000` strings, want load factor `α ≈ 3` → choose `m = 701` (prime near `2000/3`, not near any power of 2). Then `h(k) = k mod 701`.

### 2. The Multiplication Method

Two steps — multiply, then extract:

$$h(k) = \lfloor m \cdot (kA \mod 1) \rfloor$$

where `kA mod 1` means the fractional part of `kA` (i.e., `kA − ⌊kA⌋`), and `0 < A < 1`.

- **Value of `m` is not critical** — typically choose `m = 2^p`.
- **Implementation** (word size `w` bits): let `s = A · 2^w` (an integer). Multiply `k × s` to get a `2w`-bit result `r₁ · 2^w + r₀`. The `p` most significant bits of `r₀` give the hash value.
- **Knuth's suggestion**: $A \approx (\sqrt{5} - 1)/2 = 0.6180339887\ldots$
- **Example**: `k = 123456`, `p = 14`, `m = 2^14 = 16384`, `w = 32`, `A = 2654435769/2^32` → `h(k) = 67`.

### 11.3.3 Universal Hashing

Any **fixed** hash function is vulnerable: an adversary can choose `n` keys that all hash to the same slot, giving `Θ(n)` retrieval time.

**Solution**: choose the hash function **randomly** from a carefully designed class `H` at the beginning of execution.

A collection `H` of hash functions is **universal** if: for each pair of distinct keys `k, l ∈ U`, at most `|H|/m` functions in `H` satisfy `h(k) = h(l)`. That is, the collision probability is at most `1/m`.

**Theorem 11.3**: With a universal hash function, chaining, `n` keys, table size `m`:
- Key `k ∉ T`: expected list length ≤ `α = n/m`
- Key `k ∈ T`: expected list length ≤ `1 + α`

This guarantees good **expected** performance for *any* input — the adversary cannot force worst-case behavior.

---

##  Collision Resolution

Two keys may hash to the same slot — this is called a **collision**. Since collisions are unavoidable (pigeonhole principle: `|U| > m`), we need techniques to resolve them.

### 1. **Separate Chaining**

- The simplest collision resolution technique.
- Each bucket holds a **linked list** of all elements that hash to that slot.
- To insert: hash the key, prepend to the list at that slot — **O(1)**.
- To search: hash the key, scan the list at that slot — **O(1 + α)** on average, where `α = n/m` is the **load factor**.
- To delete: search, then remove from the list — **O(1 + α)** on average.
- Pros: Simple, handles any number of collisions gracefully
- Cons: Extra memory for linked list pointers

```
CHAINED-HASH-INSERT(T, x):      //Time=O(1)
    insert x at the head of list T [h(key[x])]
CHAINED-HASH-SEARCH(T, k):  //Time=O(1)
    search for an element with key k in list T [h(k)]
CHAINED-HASH-DELETE(T, x):
    delete x from the list T [h(key[x])]
```

### 2. **Open Addressing** (default)

- All elements are stored directly in the hash table (no linked lists).
- If slot `h(k)` is occupied, **probe** subsequent slots using a probe sequence until an empty slot is found.
- Common probe strategies:
  - **Linear probing**: `h(k, i) = (h(k) + i) mod m` — simple, but causes **primary clustering**
  - **Quadratic probing**: `h(k, i) = (h(k) + c₁·i + c₂·i²) mod m` — reduces clustering
  - **Double hashing**: `h(k, i) = (h₁(k) + i·h₂(k)) mod m` — best distribution
- At most one element per slot, so `n ≤ m` and `α ≤ 1`.
- Pros: Memory efficient (no extra data structures), better cache performance
- Cons: Clustering can happen; deletion is trickier (requires tombstones)

```
HASH-INSERT(T, k)
1 i ←0
2 repeat j ←h(k, i)
3   if T [ j]=NIL
4       then T [ j] ←k
5           return j
6   else i ←i +1
7 until i=m
8 error “hash table overflow”
```

```
HASH-INSERT(T, k){
    while(i!=m){
    i ←0
    repeat j ←h(k, i){
        if (T [ j]=NIL){
            T [ j] ←k
                return j
        }
        else 
            i ←i +1
    }
    }
    error “hash table overflow”
}
```

```
HASH-SEARCH(T, k)
1 i ←0
2 repeat j ←h(k, i)
3   if T [ j]=k
4       then return j
5   i ←i +1
6 until T [ j]=NIL or i=m
7 return NIL
```

```
hashSearch(T, k){
    i = 0
    do {
        j = h(k, i)
        if (T[j] == k) return j
        i = i + 1
    } while (T[j] != NULL and i != m)
    return NULL
}
```


#### Linear Probing

$$h(k, i) = (h'(k) + i) \mod m$$

- Given auxiliary hash function `h'`, first probe `T[h'(k)]`, then `T[h'(k)+1]`, ..., wrap around to `T[0]`, ..., up to `T[h'(k)-1]`.
- Initial probe determines the entire sequence → only `m` distinct probe sequences.
- **Easy to implement**, but suffers from **primary clustering**: long runs of occupied slots build up. An empty slot preceded by `i` full slots gets filled next with probability `(i+1)/m`, so long runs tend to get longer and average search time increases.

#### Quadratic Probing

$$h(k, i) = (h'(k) + c_1 i + c_2 i^2) \mod m, \quad c_2 \neq 0$$

- Offsets depend quadratically on probe number `i` — spreads probes more than linear.
- Works much better than linear probing, but `c₁`, `c₂`, and `m` must be chosen carefully for full table coverage.
- Still only `m` distinct probe sequences (initial probe determines all).
- Suffers from **secondary clustering**: keys with same initial probe follow the same sequence.

#### Double Hashing

$$h(k, i) = (h_1(k) + i \cdot h_2(k)) \mod m$$

- Uses two auxiliary hash functions. Initial probe at `h₁(k)`, then offset by `h₂(k)` each step.
- Probe sequence depends on `k` in **two ways** (position and offset) → `Θ(m²)` distinct probe sequences, vs `Θ(m)` for linear/quadratic.
- **`h₂(k)` must be relatively prime to `m`** for full table coverage.
  - Option 1: `m = 2^p`, make `h₂` always return an odd number.
  - Option 2: `m` prime, `h₁(k) = k mod m`, `h₂(k) = 1 + (k mod m')` where `m' = m - 1`.
- **Example**: `k = 123456`, `m = 701`, `m' = 700` → `h₁(k) = 80`, `h₂(k) = 257`. Probe slots 80, 337, 594, 150, ... (every 257th slot mod 701).
- Performance close to ideal uniform hashing.

#### Analysis of Open Addressing

Under **uniform hashing** (each probe sequence equally likely to be any permutation of `⟨0, 1, ..., m-1⟩`), with load factor `α = n/m < 1`:

**Theorem 11.6** (unsuccessful search): expected probes ≤

$$\frac{1}{1 - \alpha}$$

**Theorem 11.8** (successful search): expected probes ≤

$$\frac{1}{\alpha} \ln \frac{1}{1 - \alpha}$$

| Load factor `α` | Unsuccessful search | Successful search |
|------------------|--------------------:|------------------:|
| 0.50             | 2.0                 | 1.39              |
| 0.75             | 4.0                 | 1.85              |
| 0.90             | 10.0                | 2.56              |
| 0.95             | 20.0                | 3.15              |

### 3. **Perfect Hashing**

When the set of keys is **static** (never changes after insertion), we can achieve **worst-case O(1)** search — this is called **perfect hashing**. Examples: reserved words in a programming language, filenames on a CD-ROM.

**Idea**: use a **two-level hashing** scheme with universal hashing at each level.

1. **Level 1**: hash `n` keys into `m = n` slots using a universal hash function `h`. Keys that collide at slot `j` form a group of size `nⱼ`.
2. **Level 2**: instead of chaining, each slot `j` has a **secondary hash table** `Sⱼ` of size `mⱼ = nⱼ²`, with its own universal hash function `hⱼ`. The quadratic size guarantees **no collisions** at the secondary level.

**Key results:**

- **Theorem 11.9**: Hashing `n` keys into a table of size `m = n²` with a random universal hash function → probability of *any* collision is less than `1/2`. (This is why `mⱼ = nⱼ²` works for each secondary table.)

- **Theorem 11.10**: With `m = n` and universal hashing, the expected sum $\sum_{j=0}^{m-1} n_j^2 < 2n$. So the total secondary storage is linear in expectation.

- **Corollary 11.11**: Setting each secondary table size `mⱼ = nⱼ²`, the **expected total storage** for all secondary tables is less than `2n` → overall space is `O(n)`.

- **Corollary 11.12**: The probability that total secondary storage exceeds `4n` is less than `1/2`. So we can retry the level-1 hash function until we get a good one.

**Summary**: perfect hashing gives **O(1) worst-case search** with **O(n) space**, at the cost of requiring the key set to be known in advance.

---

##  Resizing & Load Factor

To keep performance `O(1)`, we must **rehash** when table gets too full.

- **Load Factor** = `size / capacity`
- If load factor > 0.75 → **rehash** (double capacity)
- All entries are reinserted using the new hash function

---

##  Features

- Template-based generic key-value support
-  Efficient hashing and collision resolution
-  Automatic resizing
-  Insert, remove, update, search
-  Operator overloading for `[]`

---

###  Example

```cpp
#include "HashMap.h"

int main() {
    HashMap<string, int> map;

    map.insert("apple", 5);
    map["banana"] = 8;
    map["orange"] = 10;

    cout << map["apple"] << endl;   // Output: 5
    map.remove("banana");
    cout << map.contains("banana"); // Output: 0 (false)
}
```

###  API

| Method         | Description                       |
| -------------- | --------------------------------- |
| `insert(k, v)` | Inserts key `k` with value `v`    |
| `remove(k)`    | Removes key `k` from map          |
| `contains(k)`  | Returns true if key exists        |
| `operator[]`   | Access or insert a key-value pair |
| `size()`       | Returns number of items in map    |
| `empty()`      | Returns true if map is empty      |
| `clear()`      | Clears all elements               |

---

##  Time & Space Complexity

| Operation | Average Case | Worst Case (with poor hash) |
| --------- | ------------ | --------------------------- |
| Insert    | O(1)         | O(n)                        |
| Delete    | O(1)         | O(n)                        |
| Search    | O(1)         | O(n)                        |
| Space     | O(n)         | O(n)                        |

---

##  Limitations

- Not thread-safe
- Worst-case linear time if hash collisions dominate
- Custom keys need `==` and `hash()` properly defined

---

##  Future Enhancements

- Add thread-safety with mutex locks
- Support custom hash functions
- Add iterators for range-based for loop
- Use Robin Hood hashing or Cuckoo hashing
- Export/Import map to/from file
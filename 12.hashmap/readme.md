chap 11- cormen(221-253)
page 658- cracking coding interview


# HashMap (Custom Implementation)

### Overview

A **HashMap** is a key-value data structure that provides **average-case constant time complexity** (`O(1)`) for insertion, deletion, and lookup operations.

This project implements a custom `HashMap` in C++ using:

- **Open addressing** (or optionally separate chaining)
- **Linear probing** or **quadratic probing**
- **Dynamic resizing** (rehashing)
- **Generic templates** for supporting any key-value types

---

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

---

##  How HashMap Works

- Every key is passed to a **hash function**.
- The hash function returns an index (`0` to `capacity - 1`).
- The value is stored in the **bucket** at that index.
- If another key hashes to the same index, a **collision** occurs.

---

##  Hashing Function

A **hash function** maps a key to an integer (bucket index):

```cpp
int hash(string key) {
    int hash = 0;
    for (char c : key)
        hash = 31 * hash + c;
    return hash % capacity;
}
```

Good hash functions aim to:

- Distribute keys uniformly
- Be fast to compute
- Avoid clustering (minimize collisions)

---

##  Collision Resolution

When two keys hash to the same bucket, we resolve the conflict using one of:

### 1. **Open Addressing** (default)

- If slot is occupied, probe the next slot (linear or quadratic).
- Pros: Memory efficient (no extra data structures)
- Cons: Clustering can happen

### 2. **Separate Chaining**

- Each bucket holds a linked list of entries.
- Pros: Simple, avoids clustering
- Cons: More memory usage

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

##  Usage

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

# Order-Statistic Tree (Policy-Based)

An order-statistic tree is a BST augmented to support two additional operations:
- **Select(i)**: Find the i-th smallest element (0-indexed)
- **Rank(x)**: Count elements less than x

In C++, GCC provides this as a policy-based data structure.

---

## Header and Setup

```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update> ordered_set;
```

---

## Operations

```cpp
ordered_set os;

// Insert
os.insert(5);
os.insert(3);
os.insert(7);
os.insert(1);

// Find k-th smallest (0-indexed)
auto it = os.find_by_order(2); // iterator to 3rd element (7)
int val = *it; // 7

// Count elements less than x
int lessThanX = os.order_of_key(10); // number of elements < 10

// Delete
os.erase(5);

// Check existence
bool exists = (os.find(3) != os.end());

// Size
int n = os.size();

// Lower bound / Upper bound
auto lb = os.lower_bound(4); // first element >= 4
auto ub = os.upper_bound(4); // first element > 4
```

---

## Pair-Based Order Statistics

For problems requiring unique keys with secondary data:

```cpp
typedef tree<pair<int,int>, null_type, less<pair<int,int>>,
             rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ordered_set os;
os.insert({5, 0});
os.insert({3, 1});
os.insert({5, 2}); // allows duplicate keys with different second values

int kth = os.find_by_order(1)->first; // 2nd smallest key
```

---

## Supported Operations

| Operation | Method | Time |
|-----------|--------|------|
| Insert | `os.insert(x)` | O(log n) |
| Delete | `os.erase(x)` | O(log n) |
| k-th smallest | `os.find_by_order(k)` | O(log n) |
| Rank of x | `os.order_of_key(x)` | O(log n) |
| Lower bound | `os.lower_bound(x)` | O(log n) |
| Upper bound | `os.upper_bound(x)` | O(log n) |
| Size | `os.size()` | O(1) |
| Count | `os.order_of_key(x+1) - os.order_of_key(x)` | O(log n) |

---

## Applications

### 1. K-th Smallest in Sliding Window

```cpp
ordered_set window;
for (int i = 0; i < n; i++) {
    window.insert(arr[i]);
    if (window.size() > k)
        window.erase(arr[i - k]);
    if (window.size() == k)
        cout << *window.find_by_order(k/2) << " "; // median
}
```

### 2. Count Inversions (Online)

```cpp
ordered_set os;
long long inversions = 0;
for (int i = 0; i < n; i++) {
    inversions += os.size() - os.order_of_key(arr[i]);
    os.insert(arr[i]);
}
```

### 3. Dynamic Rank Queries

Given a stream of numbers, answer "how many elements ≤ x" after each insertion.

### 4. Merge Two Sorted Arrays

```cpp
ordered_set merged;
for (int x : a) merged.insert(x);
for (int x : b) merged.insert(x);
// merged now contains sorted unique elements
```

### 5. Find Closest Element to x

```cpp
auto lb = os.lower_bound(x);
auto ub = os.upper_bound(x);
int closest = INT_MAX;
if (lb != os.end()) closest = min(closest, abs(*lb - x));
if (lb != os.begin()) closest = min(closest, abs(*prev(lb) - x));
```

---

## Important Notes

- **Not STL**: This is a GCC extension, not standard C++. Works on Codeforces/AtCoder but not MSVC.
- **No duplicates by default**: Use `pair<T,int>` as key to allow duplicates.
- **Based on Red-Black Tree**: Guarantees O(log n) for all operations.
- **Memory overhead**: Higher than `set` due to augmentation.

---

## Alternative: Fenwick Tree for Order Statistics

If you only need order statistics (not a full BST), use Fenwick tree:

```cpp
// For values in range [1, N]
int bit[MAXN];

void update(int i, int delta) {
    for (; i < MAXN; i += i & -i) bit[i] += delta;
}

int query(int i) { // prefix sum
    int sum = 0;
    for (; i > 0; i -= i & -i) sum += bit[i];
    return sum;
}

// Find k-th smallest (binary search on BIT)
int kth(int k) {
    int pos = 0;
    for (int pw = LOGN; pw >= 0; pw--) {
        int next = pos + (1 << pw);
        if (next < MAXN && bit[next] < k) {
            k -= bit[next];
            pos = next;
        }
    }
    return pos + 1;
}
```

---

## When to Use

| Problem | Structure |
|---------|-----------|
| K-th smallest (dynamic) | Ordered Set |
| Count elements < x | Ordered Set |
| Inversions (online) | Ordered Set |
| Range k-th smallest | Merge Sort Tree or Mo's |
| Static array, k-th smallest | Sort or Quickselect |

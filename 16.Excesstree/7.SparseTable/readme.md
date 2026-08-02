# Sparse Table

A data structure for answering **range queries** on static arrays (no updates) in O(1) after O(n log n) preprocessing. Best suited for **idempotent** operations (min, max, gcd) where overlapping sub-intervals are fine.

---

## Core Idea

Precompute answers for all intervals of length 2^k for every starting position.

```
st[i][k] = answer for range [i, i + 2^k - 1]
```

Any range [l, r] is covered by two overlapping intervals of length 2^k:
- [l, l + 2^k - 1]
- [r - 2^k + 1, r]

where k = floor(log2(r - l + 1)).

---

## Preprocessing — O(n log n)

```cpp
int st[MAXN][LOGMAXN]; // LOGMAXN = ceil(log2(MAXN)) + 1
int lg[MAXN]; // lg[i] = floor(log2(i))

void build(vector<int>& arr, int n) {
    // Precompute logarithms
    lg[1] = 0;
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i / 2] + 1;
    
    // Base case: intervals of length 1
    for (int i = 0; i < n; i++)
        st[i][0] = arr[i];
    
    // Fill table
    for (int k = 1; (1 << k) <= n; k++) {
        for (int i = 0; i + (1 << k) - 1 < n; i++) {
            st[i][k] = min(st[i][k-1], st[i + (1 << (k-1))][k-1]);
        }
    }
}
```

---

## Query — O(1) for Min/Max

```cpp
int query(int l, int r) {
    int len = r - l + 1;
    int k = lg[len];
    return min(st[l][k], st[r - (1 << k) + 1][k]);
}
```

**Why two intervals overlap**: For min/max, overlapping doesn't matter — the minimum of overlapping regions is still the minimum. This is called **idempotency**: f(x, x) = x.

---

## Range GCD Query

GCD is also idempotent: gcd(x, x) = x.

```cpp
// Preprocessing same structure, but with gcd
for (int i = 0; i < n; i++)
    st[i][0] = arr[i];

for (int k = 1; (1 << k) <= n; k++) {
    for (int i = 0; i + (1 << k) - 1 < n; i++) {
        st[i][k] = __gcd(st[i][k-1], st[i + (1 << (k-1))][k-1]);
    }
}

// Query same as min/max
int query(int l, int r) {
    int k = lg[r - l + 1];
    return __gcd(st[l][k], st[r - (1 << k) + 1][k]);
}
```

---

## Range Sum Query (Non-idempotent)

Sum is NOT idempotent, so overlapping intervals would double-count. Use a different approach:

```cpp
// Precompute prefix sums
// Or use sparse table differently:
// st[i][k] = sum of arr[i..i+2^k-1]
// Decompose [l,r] into disjoint intervals of powers of 2

int querySum(int l, int r) {
    int sum = 0;
    for (int k = lg[r - l + 1]; l <= r; k = lg[r - l]) {
        if (l + (1 << k) - 1 <= r) {
            sum += st[l][k];
            l += (1 << k);
        }
    }
    return sum;
}
```

This is O(log n) for sum queries.

---

## Second Minimum Sparse Table

To find the second minimum in a range (useful for problems requiring the two smallest values):

```cpp
int stMin[MAXN][LOGMAXN];
int stSecMin[MAXN][LOGMAXN];

void buildSecondMin(vector<int>& arr, int n) {
    for (int i = 0; i < n; i++) {
        stMin[i][0] = arr[i];
        stSecMin[i][0] = INT_MAX;
    }
    
    for (int k = 1; (1 << k) <= n; k++) {
        for (int i = 0; i + (1 << k) - 1 < n; i++) {
            int a = stMin[i][k-1], b = stSecMin[i][k-1];
            int c = stMin[i + (1 << (k-1))][k-1];
            int d = stSecMin[i + (1 << (k-1))][k-1];
            
            // Merge two sorted pairs
            vector<int> v = {a, b, c, d};
            sort(v.begin(), v.end());
            stMin[i][k] = v[0];
            stSecMin[i][k] = v[1];
        }
    }
}
```

---

## Comparison with Other Structures

| Structure | Preprocessing | Query | Updates | Use Case |
|-----------|--------------|-------|---------|----------|
| Sparse Table | O(n log n) | O(1) | None | Static min/max/gcd |
| Segment Tree | O(n) | O(log n) | O(log n) | Dynamic range queries |
| Fenwick Tree | O(n) | O(log n) | O(log n) | Dynamic prefix sums |
| Sqrt Decomposition | O(n) | O(sqrt(n)) | O(sqrt(n)) | General range queries |

---

## Limitations

- **Static only**: Cannot handle point updates or range updates
- **Idempotent operations only** for O(1) query: min, max, gcd, and, or
- **Memory**: O(n log n) — can be an issue for very large arrays
- For non-idempotent operations (sum, product), query becomes O(log n)

---

## When to Use

| Scenario | Recommended |
|----------|-------------|
| Static array, range min/max | Sparse Table |
| Dynamic array, range min/max | Segment Tree |
| Range sum, static | Prefix Sums |
| Range sum, dynamic | Fenwick / Segment Tree |
| Range gcd, static | Sparse Table |
| Range gcd, dynamic | Segment Tree |

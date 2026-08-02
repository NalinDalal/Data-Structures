# Mo's Algorithm (Offline Range Queries)

Mo's algorithm answers range queries offline by reordering them to minimize pointer movement. Ideal for problems where adding/removing one element from a range is O(1).

---

## Core Idea

Sort queries in blocks of size sqrt(n). Within each block, sort by right endpoint. Process queries in this order to get O((n + q) * sqrt(n)) total complexity.

---

## Complexity

| Component | Complexity |
|-----------|-----------|
| Add/Remove element | O(1) |
| Total add/remove | O((n + q) * sqrt(n)) |
| Sorting queries | O(q log q) |
| **Overall** | **O((n + q) * sqrt(n))** |

---

## Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int BLOCK = 350; // ~sqrt(MAXN)

int arr[MAXN], ans[MAXN];
int freq[MAXN]; // frequency map for current range
int currentAns = 0;

struct Query {
    int l, r, idx;
};

bool cmp(Query a, Query b) {
    if (a.l / BLOCK != b.l / BLOCK)
        return a.l / BLOCK < b.l / BLOCK;
    return a.r < b.r;
}

void add(int pos) {
    freq[arr[pos]]++;
    // Update currentAns based on problem
    // Example: count distinct elements
    if (freq[arr[pos]] == 1) currentAns++;
}

void remove(int pos) {
    freq[arr[pos]]--;
    if (freq[arr[pos]] == 0) currentAns--;
}

void solve(vector<Query>& queries, int n) {
    sort(queries.begin(), queries.end(), cmp);
    
    int curL = 0, curR = -1;
    for (auto& q : queries) {
        while (curL > q.l) add(--curL);
        while (curR < q.r) add(++curR);
        while (curL < q.l) remove(curL++);
        while (curR > q.r) remove(curR--);
        
        ans[q.idx] = currentAns;
    }
}
```

---

## Example: Count Distinct in Range

```cpp
int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> arr[i];
    
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--; queries[i].r--; // 0-indexed
        queries[i].idx = i;
    }
    
    solve(queries, n);
    
    for (int i = 0; i < q; i++)
        cout << ans[i] << "\n";
}
```

---

## Example: Range Frequency Query

Count how many times a specific value appears in [l, r].

```cpp
void add(int pos) {
    freq[arr[pos]]++;
}

void remove(int pos) {
    freq[arr[pos]]--;
}

// For query asking frequency of value v:
// ans[q.idx] = freq[v];
```

---

## Mo's Algorithm with Updates (Mo's on Trees variant)

For problems with point updates + range queries:

```cpp
struct Query {
    int l, r, idx, time; // time = update index
};

// Three pointers: l, r, t (time)
// Sort: (l/BLOCK, r/BLOCK, t)
// Add/remove updates as time pointer moves

void addUpdate(int pos, int& curAns) {
    // Apply update at position pos
}

void removeUpdate(int pos, int& curAns) {
    // Undo update at position pos
}
```

Complexity: O((n + q) * n^(2/3))

---

## Template: Range XOR Query

```cpp
int xorPrefix[MAXN];

void add(int pos) {
    currentAns ^= arr[pos];
}

void remove(int pos) {
    currentAns ^= arr[pos]; // XOR is its own inverse
}

// For query [l, r]: ans = currentAns
```

---

## Template: Range Majority Element

Maintain a frequency map and track the majority candidate.

```cpp
int majorityCandidate = -1, majorityCount = 0;

void add(int pos) {
    freq[arr[pos]]++;
    if (freq[arr[pos]] > majorityCount) {
        majorityCount = freq[arr[pos]];
        majorityCandidate = arr[pos];
    }
}

// After processing query, verify majorityCandidate actually has > (r-l+1)/2 frequency
```

---

## Why Square Root Block Size?

- Number of blocks = n / B
- Within a block, right pointer moves O(n) total
- Between blocks, right pointer moves O(n) per block = O(n * n/B)
- Left pointer moves O(B) per query = O(q * B)
- Total: O(n * n/B + q * B)
- Minimized when B = sqrt(n), giving O((n + q) * sqrt(n))

---

## Comparison with Segment Tree

| Feature | Mo's Algorithm | Segment Tree |
|---------|---------------|--------------|
| Online/Offline | Offline | Online |
| Updates | Harder (Mo's with updates) | Natural |
| Complexity | O((n+q)*sqrt(n)) | O((n+q)*log(n)) |
| Implementation | Simple for basic queries | Moderate |
| Flexibility | Any "add/remove" query | Specific merge operations |

---

## When to Use

| Problem | Use Mo's? |
|---------|----------|
| Range count distinct | Yes |
| Range frequency queries | Yes |
| Range XOR/sum queries | Use Fenwick instead |
| Need online answers | No (use Segment Tree) |
| Have point updates | Mo's with updates |
| Range majority element | Yes |

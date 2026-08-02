# Suffix Array (Construction)

A suffix array is a sorted array of all suffixes of a string. Combined with an LCP array, it solves many string problems efficiently.

---

## Definition

For string `S = "banana"`:

| Index | Suffix | Rank |
|-------|--------|------|
| 0 | banana | 5 |
| 1 | anana | 1 |
| 2 | nana | 4 |
| 3 | ana | 0 |
| 4 | na | 3 |
| 5 | a | 2 |

**Suffix Array (SA):** [5, 3, 1, 4, 2, 0] (indices sorted by suffix)
**Rank array:** [3, 2, 5, 1, 4, 0] (rank of suffix starting at i)

---

## Naive Construction — O(n^2 log n)

Sort suffixes by direct comparison.

```cpp
vector<int> buildSA_naive(string& s) {
    int n = s.size();
    vector<int> sa(n);
    iota(sa.begin(), sa.end(), 0);
    sort(sa.begin(), sa.end(), [&](int a, int b) {
        return s.substr(a) < s.substr(b);
    });
    return sa;
}
```

---

## O(n log n) Construction (Prefix Doubling)

Sort by first 1 char, then 2, then 4, then 8, ... Each step doubles the prefix length.

```cpp
vector<int> buildSA(string& s) {
    int n = s.size();
    vector<int> sa(n), rank(n), tmp(n);
    
    // Initial: sort by single character
    iota(sa.begin(), sa.end(), 0);
    for (int i = 0; i < n; i++) rank[i] = s[i];
    
    for (int k = 1; k < n; k *= 2) {
        // Comparator: sort by (rank[i], rank[i+k])
        auto cmp = [&](int a, int b) {
            if (rank[a] != rank[b]) return rank[a] < rank[b];
            int ra = (a + k < n) ? rank[a + k] : -1;
            int rb = (b + k < n) ? rank[b + k] : -1;
            return ra < rb;
        };
        
        sort(sa.begin(), sa.end(), cmp);
        
        // Recompute ranks
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i-1]] + (cmp(sa[i-1], sa[i]) ? 1 : 0);
        
        rank = tmp;
        if (rank[sa[n-1]] == n - 1) break; // all ranks unique
    }
    
    return sa;
}
```

---

## O(n) Construction (SA-IS)

Linear-time suffix array construction using induced sorting. Complex but optimal.

```cpp
// Simplified outline (full implementation ~100 lines)
vector<int> buildSA_SAIS(string& s) {
    // 1. Classify characters as L-type or S-type
    // 2. Find LMS (Left-Most S) positions
    // 3. Recursively sort LMS characters
    // 4. Induce full order from sorted LMS positions
    // ...
}
```

Most CP solutions use O(n log n) which is sufficient.

---

## LCP Array (Kasai's Algorithm) — O(n)

The LCP array stores the longest common prefix between consecutive suffixes in SA order.

```cpp
vector<int> buildLCP(string& s, vector<int>& sa) {
    int n = s.size();
    vector<int> rank(n), lcp(n);
    
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (rank[i] == 0) { lcp[0] = 0; continue; }
        int j = sa[rank[i] - 1];
        while (i + h < n && j + h < n && s[i+h] == s[j+h]) h++;
        lcp[rank[i]] = h;
        if (h > 0) h--;
    }
    
    return lcp;
}
```

---

## Applications

### 1. Longest Repeated Substring

```cpp
int longestRepeatedSubstring(string& s) {
    auto sa = buildSA(s);
    auto lcp = buildLCP(s, sa);
    return *max_element(lcp.begin(), lcp.end());
}
```

### 2. Number of Distinct Substrings

```cpp
long long countDistinct(string& s) {
    int n = s.size();
    auto sa = buildSA(s);
    auto lcp = buildLCP(s, sa);
    long long total = (long long)n * (n + 1) / 2;
    for (int i = 0; i < n; i++) total -= lcp[i];
    return total;
}
```

### 3. Longest Common Substring of Two Strings

```cpp
int lcs(string& a, string& b) {
    string combined = a + "#" + b + "$";
    auto sa = buildSA(combined);
    auto lcp = buildLCP(combined, sa);
    
    int alen = a.size(), blen = b.size();
    int ans = 0;
    for (int i = 1; i < combined.size(); i++) {
        bool across = (sa[i] < alen) != (sa[i-1] < alen);
        if (across) ans = max(ans, lcp[i]);
    }
    return ans;
}
```

### 4. Pattern Matching — O(m log n)

Binary search on the suffix array.

```cpp
pair<int,int> search(string& s, vector<int>& sa, string& pat) {
    int n = s.size(), m = pat.size();
    int lo = 0, hi = n - 1;
    
    // Find lower bound
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (s.substr(sa[mid], min(m, n - sa[mid])) >= pat) hi = mid;
        else lo = mid + 1;
    }
    if (s.substr(sa[lo], min(m, n - sa[lo])) != pat) return {-1, -1};
    
    int lb = lo;
    lo = 0; hi = n - 1;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (s.substr(sa[mid], min(m, n - sa[mid])) <= pat) lo = mid;
        else hi = mid - 1;
    }
    
    return {lb, lo};
}
```

### 5. Lexicographically K-th Suffix

Simply return `sa[k]`.

### 6. Minimum Lexicographic Rotation

Duplicate the string and find the lexicographically smallest suffix of length >= n.

```cpp
int minRotation(string s) {
    s += s;
    int n = s.size() / 2;
    auto sa = buildSA(s);
    for (int i = 0; i < sa.size(); i++) {
        if (sa[i] < n) return sa[i];
    }
    return -1;
}
```

---

## Comparison: Suffix Array vs Suffix Tree vs Suffix Automaton

| Feature | Suffix Array | Suffix Tree | Suffix Automaton |
|---------|-------------|-------------|-----------------|
| Build | O(n log n) | O(n) | O(n) |
| Space | O(n) | O(n) | O(n) |
| Pattern matching | O(m log n) | O(m) | O(m) |
| Distinct substrings | O(n) with LCP | O(n) | O(n) |
| LCP queries | O(1) with RMQ | O(1) | O(n) |
| Implementation | Simple | Moderate | Complex |
| Cache friendly | Yes | No | Moderate |

---

## When to Use

| Problem | Best Structure |
|---------|---------------|
| Lexicographic ordering | Suffix Array |
| Pattern matching | Suffix Array or KMP |
| Longest repeated substring | SA + LCP |
| Distinct substrings | SA + LCP or SAM |
| All substrings of a string | Suffix Array |
| Dynamic string updates | Suffix Automaton |

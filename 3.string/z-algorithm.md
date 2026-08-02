# Z-Algorithm

For a string s of length n, the Z-array z[i] is the length of the longest substring starting at position i that is also a prefix of s.

z[i] = length of longest common prefix between s and s[i..n-1]

z[0] is defined as 0 (or n, but conventionally 0).

---

## Example

```
s = "aabxaabxcaab"
z = [0, 1, 0, 0, 3, 1, 0, 0, 2, 1, 0, 0]
```

At i=4: s[4..] = "aabxcaab", prefix match = "aab" → z[4] = 3

---

## Construction — O(n)

```cpp
vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    
    for (int i = 1; i < n; i++) {
        if (i < r)
            z[i] = min(r - i, z[i - l]);
        
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;
        
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    
    return z;
}
```

---

## How It Works

Maintain a window [l, r] that is the rightmost match with the prefix.

For each position i:
1. If i is inside [l, r], use previously computed values: z[i] = min(r-i, z[i-l])
2. Extend naively from that point
3. Update [l, r] if the match extends past r

**Why O(n)?** The r pointer only moves forward. Total character comparisons = O(n).

---

## Pattern Matching — O(n + m)

Find all occurrences of pattern p in text t.

```cpp
vector<int> search(string& text, string& pattern) {
    string combined = pattern + "#" + text;
    vector<int> z = z_function(combined);
    int m = pattern.size();
    
    vector<int> occurrences;
    for (int i = m + 1; i < combined.size(); i++) {
        if (z[i] == m)
            occurrences.push_back(i - m - 1);
    }
    return occurrences;
}
```

---

## Applications

### 1. Longest Common Prefix of All Suffixes

The Z-array directly gives the LCP of each suffix with the whole string.

### 2. Count Distinct Substrings

```cpp
long long countDistinct(string s) {
    int n = s.size();
    auto z = z_function(s);
    long long ans = n; // all single characters
    for (int i = 1; i < n; i++)
        ans += n - i - z[i]; // suffix minus prefix match
    return ans;
}
```

### 3. String Period

A string has period p if s[i] = s[i+p] for all valid i. Check if z[i] + i == n for any i where i is a divisor of n.

```cpp
vector<int> getPeriods(string s) {
    auto z = z_function(s);
    int n = s.size();
    vector<int> periods;
    for (int i = 1; i < n; i++) {
        if (z[i] + i == n)
            periods.push_back(i);
    }
    return periods;
}
```

### 4. Concatenation of a String with Itself

Find the longest suffix of s that is also a prefix. This is max(z[i]) for i > 0 where i + z[i] == n.

### 5. Longest Repeated Substring (Non-overlapping)

```cpp
int longestRepeated(string s) {
    int n = s.size();
    auto z = z_function(s);
    int ans = 0;
    for (int i = 1; i < n; i++)
        ans = max(ans, z[i]);
    return ans;
}
```

---

## Comparison

| Algorithm | Time | Space | Use Case |
|-----------|------|-------|----------|
| Z-Algorithm | O(n) | O(n) | Pattern matching, prefix analysis |
| KMP | O(n+m) | O(m) | Pattern matching |
| Rabin-Karp | O(n+m) expected | O(1) | Multiple pattern matching |
| Naive | O(n*m) | O(1) | Simple cases |

---

## When to Use

| Problem | Use Z? |
|---------|--------|
| Pattern matching | Yes (simpler than KMP) |
| Prefix-suffix overlap | Yes |
| String period | Yes |
| Count distinct substrings | Yes or SAM |
| Longest common prefix | Yes |

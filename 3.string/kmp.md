# KMP (Knuth-Morris-Pratt) Algorithm

Pattern matching in O(n + m) time using preprocessing of the pattern. Never backtracks in the text.

---

## Key Idea: Prefix Function (π)

For pattern P[1..m], the prefix function π[q] is the length of the longest proper prefix of P[1..q] that is also a suffix.

```
π[q] = max { k : k < q and P[1..k] is a suffix of P[1..q] }
```

---

## Compute Prefix Function — O(m)

```cpp
vector<int> computePrefix(string& P) {
    int m = P.size();
    vector<int> pi(m, 0);
    pi[0] = 0;
    int k = 0;
    
    for (int q = 1; q < m; q++) {
        while (k > 0 && P[k] != P[q])
            k = pi[k - 1];
        if (P[k] == P[q])
            k++;
        pi[q] = k;
    }
    
    return pi;
}
```

---

## KMP Matcher — O(n + m)

```cpp
vector<int> kmpSearch(string& T, string& P) {
    int n = T.size(), m = P.size();
    vector<int> pi = computePrefix(P);
    vector<int> matches;
    
    int q = 0; // number of characters matched
    for (int i = 0; i < n; i++) {
        while (q > 0 && P[q] != T[i])
            q = pi[q - 1];
        if (P[q] == T[i])
            q++;
        if (q == m) {
            matches.push_back(i - m + 1); // match at position i-m+1
            q = pi[q - 1];
        }
    }
    
    return matches;
}
```

---

## How It Works

1. Preprocess pattern to build π array
2. Scan text left to right with pointer q on pattern
3. On mismatch at P[q], instead of restarting from 0, jump to π[q-1]
4. This skips characters that are guaranteed to match

**Why O(n)?** Each time q increases, i also increases. Each time q decreases (via π), q was previously increased. Total q increases ≤ n, so total decreases ≤ n.

---

## Example

```
Text:    A B A C D A B A B
Pattern: A B A B

π for "ABAB": [0, 0, 1, 2]

i=0: T=A, P[0]=A, q=1
i=1: T=B, P[1]=B, q=2
i=2: T=A, P[2]=A, q=3
i=3: T=C, P[3]=B ≠ C, q=π[2]=1
i=3: T=C, P[1]=B ≠ C, q=π[0]=0
i=3: T=C, P[0]=A ≠ C, q=0
i=4: T=D, q=0
i=5: T=A, P[0]=A, q=1
i=6: T=B, P[1]=B, q=2
i=7: T=A, P[2]=A, q=3
i=8: T=B, P[3]=B, q=4 → MATCH at position 5
```

---

## Counting Occurrences

```cpp
int countOccurrences(string& T, string& P) {
    int n = T.size(), m = P.size();
    vector<int> pi = computePrefix(P);
    int count = 0, q = 0;
    
    for (int i = 0; i < n; i++) {
        while (q > 0 && P[q] != T[i])
            q = pi[q - 1];
        if (P[q] == T[i]) q++;
        if (q == m) { count++; q = pi[q - 1]; }
    }
    
    return count;
}
```

---

## Applications

### 1. Pattern Matching

The basic use case — find all occurrences of pattern in text.

### 2. String Period

A string s has period p if s[i] = s[i+p] for all valid i. The minimum period is:
```
period = n - pi[n-1]  (if n % period == 0)
```

```cpp
int period(string s) {
    auto pi = computePrefix(s);
    int n = s.size();
    int per = n - pi[n-1];
    return (n % per == 0) ? per : n;
}
```

### 3. Count Distinct Substrings

```cpp
long long countDistinct(string s) {
    long long ans = 0;
    for (int i = 0; i < s.size(); i++) {
        string sub = s.substr(0, i + 1);
        auto pi = computePrefix(sub);
        int maxLen = pi.back();
        ans += (i + 1) - maxLen;
    }
    return ans;
}
```

### 4. Find All Border Lengths

Borders of a string are prefixes that are also suffixes.

```cpp
vector<int> getBorders(string s) {
    auto pi = computePrefix(s);
    vector<int> borders;
    int k = pi.back();
    while (k > 0) {
        borders.push_back(k);
        k = pi[k - 1];
    }
    return borders;
}
```

### 5. Build Prefix Function for Pattern + "#" + Text

For finding all occurrences where pattern is a substring of text using only the π array.

---

## KMP vs Other Algorithms

| Algorithm | Preprocessing | Matching | Backtracks? |
|-----------|--------------|----------|-------------|
| Naive | 0 | O(nm) | Yes |
| Rabin-Karp | O(m) | O(n) expected | No |
| **KMP** | **O(m)** | **O(n)** | **No** |
| Z-Algorithm | O(n+m) | O(n+m) | No |
| Boyer-Moore | O(m+k) | O(n) best | Yes |

---

## When to Use

| Problem | Use KMP? |
|---------|---------|
| Single pattern matching | Yes |
| Count occurrences | Yes |
| String period/borders | Yes |
| Multiple patterns | Use Aho-Corasick |
| Simple implementation needed | Z-algorithm |
| Pattern matching with wildcards | No |

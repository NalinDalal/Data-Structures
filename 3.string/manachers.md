# Manacher's Algorithm

Finds the longest palindromic substring in O(n) time. Handles both odd-length and even-length palindromes.

---

## Core Idea

For each center position, expand as far as possible while maintaining symmetry. Use previously computed palindrome information to skip redundant work.

---

## Preprocessing

Insert sentinel characters between every pair of characters to handle even-length palindromes uniformly:

```
"abba" → "^#a#b#b#a#$"
```

Now every palindrome has an odd length in the transformed string.

---

## Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

string longestPalindrome(string s) {
    int n = s.size();
    if (n == 0) return "";
    
    // Transform: "^#a#b#b#a#$"
    string t = "^#";
    for (char c : s) {
        t += c;
        t += '#';
    }
    t += '$';
    
    int m = t.size();
    vector<int> p(m, 0); // p[i] = radius of palindrome centered at i
    int center = 0, right = 0;
    
    for (int i = 1; i < m - 1; i++) {
        int mirror = 2 * center - i;
        
        if (i < right)
            p[i] = min(right - i, p[mirror]);
        
        // Expand
        while (t[i + p[i] + 1] == t[i - p[i] - 1])
            p[i]++;
        
        // Update center and right boundary
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
    }
    
    // Find maximum palindrome
    int maxLen = 0, maxCenter = 0;
    for (int i = 1; i < m - 1; i++) {
        if (p[i] > maxLen) {
            maxLen = p[i];
            maxCenter = i;
        }
    }
    
    int start = (maxCenter - maxLen - 2) / 2;
    return s.substr(start, maxLen);
}
```

---

## How It Works

1. Transform string to handle even/odd uniformly
2. For each center i:
   - If i is within the current right boundary, mirror = 2*center - i
   - Initialize p[i] = min(right - i, p[mirror])
   - Expand outward while characters match
   - Update center/right if palindrome extends past right
3. Find the maximum radius

**Why O(n)?** Right boundary moves forward at most n times. Each comparison either extends right or is skipped. Total comparisons = O(n).

---

## Even-Length Palindromes (Separate Approach)

Without transformation, handle even and odd separately:

```cpp
vector<int> d1, d2; // d1[i] = radius of odd palindrome at i
                     // d2[i] = radius of even palindrome at i

void manachers(string& s) {
    int n = s.size();
    d1.resize(n); d2.resize(n);
    
    // Odd-length palindromes
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        d1[i] = (i <= r) ? min(r - i + 1, d1[l + r - i]) : 1;
        while (i - d1[i] >= 0 && i + d1[i] < n && s[i - d1[i]] == s[i + d1[i]])
            d1[i]++;
        if (i + d1[i] - 1 > r) { l = i - d1[i] + 1; r = i + d1[i] - 1; }
    }
    
    // Even-length palindromes
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        d2[i] = (i <= r) ? min(r - i + 1, d2[l + r - i + 1]) : 0;
        while (i - d2[i] - 1 >= 0 && i + d2[i] < n && s[i - d2[i] - 1] == s[i + d2[i]])
            d2[i]++;
        if (i + d2[i] - 1 > r) { l = i - d2[i]; r = i + d2[i] - 1; }
    }
}

// Longest odd palindrome: max(d1[i]) centered at i, length = 2*d1[i]-1
// Longest even palindrome: max(d2[i]) centered between i-1 and i, length = 2*d2[i]
```

---

## Applications

### 1. Longest Palindromic Substring

Already shown above. Direct result of Manacher's.

### 2. Count All Palindromic Substrings

Each d1[i] gives the count of odd palindromes centered at i. Each d2[i] gives even.

```cpp
long long countPalindromes(string& s) {
    manachers(s);
    long long count = 0;
    for (int x : d1) count += x; // odd
    for (int x : d2) count += x; // even
    return count;
}
```

### 3. Longest Palindromic Subsequence

This is a DP problem (not Manacher's), but often confused:
- Substring = contiguous
- Subsequence = not necessarily contiguous

### 4. Palindrome Partitioning

Minimum cuts to partition a string into palindromes — use Manacher's to precompute which substrings are palindromes, then DP.

```cpp
int minCuts(string s) {
    int n = s.size();
    manachers(s);
    
    // isPalin[i][j] = true if s[i..j] is palindrome
    vector<bool> isPalin(n * n, false);
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int len = j - i + 1;
            int center = i + j; // in transformed coordinates
            // Check using Manacher's data
        }
    }
    
    vector<int> cuts(n, INT_MAX);
    for (int i = 0; i < n; i++) {
        if (isPalin[0 * n + i]) { cuts[i] = 0; continue; }
        for (int j = 1; j <= i; j++) {
            if (isPalin[j * n + i])
                cuts[i] = min(cuts[i], cuts[j-1] + 1);
        }
    }
    return cuts[n-1];
}
```

---

## Complexity

| Operation | Time | Space |
|-----------|------|-------|
| Build d1/d2 | O(n) | O(n) |
| Longest palindrome | O(n) | O(n) |
| Count palindromes | O(n) | O(n) |

---

## Comparison with Other Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Brute force | O(n^3) | O(1) | Check all substrings |
| DP | O(n^2) | O(n^2) | isPalin[i][j] table |
| Expand around center | O(n^2) | O(1) | Simple |
| **Manacher's** | **O(n)** | **O(n)** | **Optimal** |

---

## When to Use

| Problem | Use Manacher's? |
|---------|----------------|
| Longest palindromic substring | Yes |
| Count palindromic substrings | Yes |
| Palindrome partitioning | Precompute with Manacher's |
| Longest palindromic subsequence | No (use DP) |

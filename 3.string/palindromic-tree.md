# Palindromic Tree (Eertree)

A data structure that stores all distinct palindromic substrings of a string in O(n) time. Each node represents a distinct palindrome.

---

## Structure

Two root nodes:
- **Node 0**: represents length -1 (odd root)
- **Node 1**: represents length 0 (even root)

Each node stores:
- `len`: length of the palindrome
- `link`: suffix link to the longest proper palindromic suffix
- `next[c]`: transition on character c
- `occ`: number of occurrences (propagated at end)

```
"ababa"
Nodes:
0: len=-1, link=0 (odd root)
1: len=0, link=0 (even root)
2: len=1, "a", link=1
3: len=1, "b", link=1
4: len=3, "aba", link=2
5: len=3, "bab", link=3
6: len=5, "ababa", link=4
```

---

## Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int ALPHA = 26;

struct Node {
    int len, link;
    int next[ALPHA];
    long long occ;
};

struct PalindromicTree {
    Node st[MAXN];
    int sz, last;
    string s;
    
    void init() {
        st[0].len = -1; st[0].link = 0;
        st[1].len = 0;  st[1].link = 0;
        sz = 2; last = 1;
        memset(st[0].next, 0, sizeof(st[0].next));
        memset(st[1].next, 0, sizeof(st[1].next));
        s = "";
    }
    
    int getLink(int v) {
        while (true) {
            int curlen = st[v].len;
            if (s.size() - 2 - curlen >= 0 && s[s.size() - 2 - curlen] == s.back())
                break;
            v = st[v].link;
        }
        return v;
    }
    
    void extend(char c) {
        s += c;
        int cur = getLink(last);
        
        if (!st[cur].next[c - 'a']) {
            int now = sz++;
            st[now].len = st[cur].len + 2;
            st[now].link = st[getLink(st[cur].link)].next[c - 'a'];
            memset(st[now].next, 0, sizeof(st[now].next));
            st[cur].next[c - 'a'] = now;
        }
        
        last = st[cur].next[c - 'a'];
        st[last].occ++;
    }
    
    long long countDistinct() {
        return sz - 2; // minus two roots
    }
    
    // Must call after all extend() to propagate occurrences
    long long totalPalindromes() {
        long long ans = 0;
        for (int i = sz - 1; i >= 2; i--)
            st[st[i].link].occ += st[i].occ;
        for (int i = 2; i < sz; i++)
            ans += st[i].occ;
        return ans;
    }
};
```

---

## Usage

```cpp
int main() {
    string s;
    cin >> s;
    
    PalindromicTree pt;
    pt.init();
    for (char c : s)
        pt.extend(c);
    
    cout << "Distinct palindromes: " << pt.countDistinct() << "\n";
    cout << "Total palindrome occurrences: " << pt.totalPalindromes() << "\n";
}
```

---

## How It Works

### Adding Character s[i]

1. Find the longest palindrome that can be extended: follow suffix links from `last` until we find a palindrome where s[i] matches the character before it
2. If a transition on s[i] exists from that node, move there
3. Otherwise, create a new node:
   - Length = current node's length + 2
   - Suffix link = follow suffix link from current node, then check transition on s[i]
4. Update `last` and increment occurrence count

### Suffix Links

Suffix link from node v points to the longest proper palindromic suffix of the palindrome represented by v. This is analogous to suffix links in Aho-Corasick.

---

## Complexity

| Operation | Time |
|-----------|------|
| Build | O(n) |
| Each extend() | O(1) amortized |
| Count distinct | O(1) |
| Total palindromes | O(n) |
| Space | O(n * ALPHA) |

---

## Applications

### 1. Count Distinct Palindromic Substrings

```
distinct = sz - 2 (excluding the two roots)
```

### 2. Count Total Occurrences of All Palindromes

Propagate occurrence counts through suffix links.

### 3. Longest Palindromic Substring

Track the node with maximum `len` during construction.

### 4. Most Frequent Palindrome

Track the node with maximum `occ` after propagation.

### 5. Each Palindrome's Occurrence Count

After propagation, `st[i].occ` gives the count for each distinct palindrome.

---

## Comparison with Manacher's

| Feature | Palindromic Tree | Manacher's |
|---------|-----------------|------------|
| Time | O(n) | O(n) |
| Space | O(n * ALPHA) | O(n) |
| Distinct palindromes | Yes (lists them) | No |
| Occurrence counts | Yes | No |
| Longest palindrome | Yes | Yes |
| Implementation | Moderate | Simple |

---

## When to Use

| Problem | Use Palindromic Tree? |
|---------|---------------------|
| Count distinct palindromic substrings | Yes |
| Count all palindrome occurrences | Yes |
| Longest palindromic substring | Yes or Manacher's |
| Palindrome frequency queries | Yes |
| Find all distinct palindromes | Yes |

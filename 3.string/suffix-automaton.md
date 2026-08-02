# Suffix Automaton (SAM)

A suffix automaton is a compact DFA (deterministic finite automaton) that recognizes all suffixes of a given string. It's the most powerful string data structure — it can solve problems that suffix arrays and suffix trees solve, often more elegantly.

---

## Key Properties

For a string of length n:
- At most **2n - 1** states
- At most **3n - 4** transitions
- Built in **O(n)** time
- Accepts exactly the set of suffixes of the string

---

## Structure

Each state represents an **equivalence class** of substrings that share the same set of end positions (endpos set).

```
State: {endpos set, length, link, transitions}
```

- **len**: length of the longest string in this state's equivalence class
- **link**: suffix link — points to the state representing the longest proper suffix
- **next[c]**: transition on character c

---

## Node Structure

```cpp
struct State {
    int len;        // length of longest string in this state
    int link;       // suffix link
    int next[26];   // transitions
};

State st[2 * MAXN];
int sz, last;
```

---

## Construction — O(n)

```cpp
void sam_init() {
    st[0].len = 0;
    st[0].link = -1;
    memset(st[0].next, -1, sizeof(st[0].next));
    sz = 1;
    last = 0;
}

void sam_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    memset(st[cur].next, -1, sizeof(st[cur].next));
    
    int p = last;
    while (p != -1 && st[p].next[c] == -1) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].link = st[q].link;
            memcpy(st[clone].next, st[q].next, sizeof(st[q].next));
            
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            
            st[q].link = st[cur].link = clone;
        }
    }
    
    last = cur;
}
```

---

## Building from a String

```cpp
string s;
cin >> s;
sam_init();
for (char c : s)
    sam_extend(c - 'a');
```

---

## Applications

### 1. Count Distinct Substrings

Number of distinct substrings = sum of (st[i].len - st[st[i].link].len) for all states i > 0.

```cpp
long long countDistinctSubstrings() {
    long long ans = 0;
    for (int i = 1; i < sz; i++)
        ans += st[i].len - st[st[i].link].len;
    return ans;
}
```

### 2. Longest Common Substring of Two Strings

Build SAM for string A, then run string B through it.

```cpp
int lcs(string& a, string& b) {
    sam_init();
    for (char c : a) sam_extend(c - 'a');
    
    int v = 0, l = 0, best = 0;
    for (char c : b) {
        int ch = c - 'a';
        while (v != 0 && st[v].next[ch] == -1) {
            v = st[v].link;
            l = st[v].len;
        }
        if (st[v].next[ch] != -1) {
            v = st[v].next[ch];
            l++;
        }
        best = max(best, l);
    }
    return best;
}
```

### 3. Count Occurrences of Each Substring

First, compute `occ[i]` = number of times state i's strings appear:

```cpp
// After building SAM, mark terminal states
vector<int> order; // topological order by len
// ... build order ...

// Initialize: each state that was 'last' during construction gets occ = 1
for (int i = sz - 1; i > 0; i--) {
    int v = order[i];
    occ[st[v].link] += occ[v];
}
```

### 4. Find All Occurrences of a Pattern

```cpp
vector<int> findAllOccurrences(string& pattern) {
    int v = 0;
    for (char c : pattern) {
        int ch = c - 'a';
        if (st[v].next[ch] == -1) return {};
        v = st[v].next[ch];
    }
    // v now represents the pattern
    // Use endpos set to find all starting positions
    // (requires additional DFS on suffix links)
    // Returns end positions
}
```

### 5. Minimum Period of a String

```cpp
int minPeriod(string& s) {
    sam_init();
    for (char c : s) sam_extend(c - 'a');
    int v = last; // state representing the whole string
    int fullLen = st[v].len;
    int linkLen = st[st[v].link].len;
    int period = fullLen - linkLen;
    return (fullLen % period == 0) ? period : fullLen;
}
```

---

## Comparison with Other String Structures

| Structure | Build | Pattern Match | Distinct Substrings | LCP |
|-----------|-------|---------------|--------------------|----|
| Suffix Array + LCP | O(n log n) | O(m log n) | O(n log n) | O(n) |
| Suffix Tree | O(n) | O(m) | O(n) | O(n) |
| Suffix Automaton | O(n) | O(m) | O(n) | O(n) |
| Z-Algorithm | O(n) | O(n + m) | — | — |
| KMP | O(n) | O(n + m) | — | — |

---

## When to Use

| Problem | Best Structure |
|---------|---------------|
| Count distinct substrings | SAM or SA + LCP |
| Longest common substring | SAM |
| Occurrence counting | SAM |
| Pattern matching (single) | KMP / Z |
| Pattern matching (multiple) | SA or SAM |
| Palindromes | Palindromic Tree |

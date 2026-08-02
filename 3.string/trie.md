# Trie (Prefix Tree)

A Trie is a tree-like data structure used for efficient storage and retrieval of strings over a given alphabet. Each node represents a character, and paths from root to marked nodes form stored strings.

---

## Structure

```
root
├── c
│   └── a
│       ├── t  (word: "cat")
│       └── r  (word: "car")
├── d
│   └── o
│       └── g  (word: "dog")
```

**Key properties:**
- Each edge is labeled with a character
- Each node stores a flag: `isEnd` (marks end of a word)
- Root is empty (contains no character)
- Sibling nodes share a common prefix

---

## Node Structure

```cpp
struct TrieNode {
    TrieNode* children[26]; // for lowercase a-z
    bool isEnd;
    
    TrieNode() {
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
        isEnd = false;
    }
};
```

---

## Operations

### Insert — O(m)

Insert a string of length m into the trie.

```cpp
void insert(TrieNode* root, string word) {
    TrieNode* node = root;
    for (char c : word) {
        int idx = c - 'a';
        if (!node->children[idx])
            node->children[idx] = new TrieNode();
        node = node->children[idx];
    }
    node->isEnd = true;
}
```

### Search — O(m)

Check if a word exists in the trie.

```cpp
bool search(TrieNode* root, string word) {
    TrieNode* node = root;
    for (char c : word) {
        int idx = c - 'a';
        if (!node->children[idx])
            return false;
        node = node->children[idx];
    }
    return node->isEnd;
}
```

### StartsWith (Prefix Check) — O(m)

Check if any word in the trie starts with the given prefix.

```cpp
bool startsWith(TrieNode* root, string prefix) {
    TrieNode* node = root;
    for (char c : prefix) {
        int idx = c - 'a';
        if (!node->children[idx])
            return false;
        node = node->children[idx];
    }
    return true;
}
```

### Delete — O(m)

Delete a word from the trie (recursive approach).

```cpp
TrieNode* remove(TrieNode* node, string& word, int depth) {
    if (!node) return nullptr;
    
    if (depth == word.size()) {
        node->isEnd = false;
        // If node has no children, delete it
        bool hasChildren = false;
        for (int i = 0; i < 26; i++) {
            if (node->children[i]) { hasChildren = true; break; }
        }
        if (!hasChildren) { delete node; return nullptr; }
        return node;
    }
    
    int idx = word[depth] - 'a';
    node->children[idx] = remove(node->children[idx], word, depth + 1);
    
    // If node is not end of another word and has no children, delete it
    bool hasChildren = false;
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) { hasChildren = true; break; }
    }
    if (!node->isEnd && !hasChildren) { delete node; return nullptr; }
    return node;
}
```

---

## Applications

### 1. Autocomplete / Prefix Search

Find all words that start with a given prefix.

```cpp
void findAllWords(TrieNode* node, string& prefix, vector<string>& results) {
    if (node->isEnd)
        results.push_back(prefix);
    
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            prefix.push_back('a' + i);
            findAllWords(node->children[i], prefix, results);
            prefix.pop_back();
        }
    }
}

vector<string> autocomplete(TrieNode* root, string prefix) {
    TrieNode* node = root;
    for (char c : prefix) {
        int idx = c - 'a';
        if (!node->children[idx]) return {};
        node = node->children[idx];
    }
    vector<string> results;
    findAllWords(node, prefix, results);
    return results;
}
```

### 2. Word Matching in Grid (Boggle)

Use a trie to store dictionary words, then DFS from each cell in the grid to find valid words.

### 3. Longest Common Prefix

The longest common prefix of all strings in a set is the deepest node from which all paths to marked nodes exist.

### 4. String Sorting (Trie Sort)

Insert all strings, then do a DFS traversal — characters are output in lexicographic order. O(total characters).

### 5. Bitwise Trie (XOR problems)

For integer XOR problems, store numbers as binary strings (32 bits) in a trie, then greedily find the number that maximizes XOR with a query.

```cpp
struct BitTrieNode {
    BitTrieNode* children[2];
    BitTrieNode() { children[0] = children[1] = nullptr; }
};

void insertBitTrie(BitTrieNode* root, int num) {
    BitTrieNode* node = root;
    for (int i = 31; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (!node->children[bit])
            node->children[bit] = new BitTrieNode();
        node = node->children[bit];
    }
}

int maxXOR(BitTrieNode* root, int num) {
    BitTrieNode* node = root;
    int result = 0;
    for (int i = 31; i >= 0; i--) {
        int bit = (num >> i) & 1;
        int desired = 1 - bit; // want opposite bit for max XOR
        if (node->children[desired]) {
            result |= (1 << i);
            node = node->children[desired];
        } else {
            node = node->children[bit];
        }
    }
    return result;
}
```

---

## Complexity

| Operation   | Time    | Space   |
|-------------|---------|---------|
| Insert      | O(m)    | O(m)    |
| Search      | O(m)    | O(1)    |
| Delete      | O(m)    | O(m)    |
| Prefix Search | O(m + k) | —     |

m = length of string, k = number of results

---

## Compressed Trie (Radix Tree)

Merge chains of single-child nodes into one edge labeled with a substring.

```
Before:  root -> b -> a -> t (word: "bat")
After:   root -> "bat" (word: "bat")
```

Reduces space and improves cache performance.

---

## Patricie Trie (Radix Trie for bit strings)

Each edge is labeled by a bit position. Used in routing tables and IP address lookups.

---

## When to Use

| Problem | Use Trie? |
|---------|-----------|
| Autocomplete | Yes |
| Spell checker | Yes |
| Word search in grid | Yes |
| XOR maximization | Bitwise Trie |
| Simple prefix check | Yes |
| Frequency counting | Use HashMap instead |

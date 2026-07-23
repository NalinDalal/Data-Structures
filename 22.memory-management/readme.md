# Memory Management

## External Memory Algorithms

External memory algorithms handle data that doesn't fit in RAM, using disk storage.

### I/O Model

- RAM size M, disk block size B
- Cost measured in block transfers (I/Os)
- Goal: minimize disk reads/writes

### B-Tree

- Balanced tree with high branching factor (order B)
- Height O(log_B n) - few disk accesses
- Used in databases, file systems

```cpp
struct BTreeNode {
    int keys[2*B-1];
    BTreeNode* children[2*B];
    int n;
    bool leaf;
};

void insert(BTreeNode* root, int key) {
    if (root->n == 2*B-1) {
        BTreeNode* s = new BTreeNode();
        s->children[0] = root;
        splitChild(s, 0);
        insertNonFull(s, key);
        root = s;
    } else {
        insertNonFull(root, key);
    }
}
```

### External Sorting

Sort n records with M memory:

1. Load M records, sort in memory, write back
2. Merge sorted runs

**I/O Complexity:** O((n/B) * log_{M/B}(n/B))

```cpp
void externalSort(string input, string output, int M) {
    // Phase 1: Create sorted runs
    vector<int> buffer(M);
    while (readBlock(input, buffer)) {
        sort(buffer.begin(), buffer.end());
        writeBlock(output, buffer);
    }
    
    // Phase 2: Merge runs
    mergeRuns(output, M/B);
}
```

### Buffer Tree

- Batch processing structure
- Supports insert/delete in O(log_B n) I/Os amortized
- Used for offline algorithms

### Cache-Oblivious Algorithms

- No knowledge of B or M needed
- Optimal for all cache levels automatically
- Example: Van Emde Boas layout for binary trees

## Cache Efficiency

| Operation | RAM Only | External Memory |
|-----------|----------|-----------------|
| Search | O(log n) | O(log_B n) |
| Sort | O(n log n) | O((n/B) log_{M/B}(n/B)) |
| Range Query | O(log n + k) | O(log_B n + k/B) |

## Applications

- Database systems
- File systems
- Large-scale data processing
- Geographic information systems

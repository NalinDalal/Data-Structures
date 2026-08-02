# LRU Cache (Least Recently Used)

An LRU cache evicts the least recently accessed item when it reaches capacity. O(1) for both get and put operations.

---

## Data Structure

Combine a **HashMap** (for O(1) lookup) with a **Doubly Linked List** (for O(1) removal/reordering).

```
HashMap: key → node pointer
Doubly Linked List: most recently used → ... → least recently used
```

---

## Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key, value;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    unordered_map<int, Node*> cache;
    Node* head; // dummy head (most recent)
    Node* tail; // dummy tail (least recent)
    
    void remove(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    void addToFront(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
    
    void moveToFront(Node* node) {
        remove(node);
        addToFront(node);
    }
    
    Node* evictLast() {
        Node* last = tail->prev;
        remove(last);
        return last;
    }
    
public:
    LRUCache(int cap) : capacity(cap) {
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (cache.find(key) == cache.end())
            return -1;
        
        Node* node = cache[key];
        moveToFront(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            node->value = value;
            moveToFront(node);
            return;
        }
        
        if ((int)cache.size() == capacity) {
            Node* last = evictLast();
            cache.erase(last->key);
            delete last;
        }
        
        Node* newNode = new Node(key, value);
        cache[key] = newNode;
        addToFront(newNode);
    }
    
    ~LRUCache() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};
```

---

## Usage

```cpp
LRUCache lru(2); // capacity 2
lru.put(1, 1);
lru.put(2, 2);
lru.get(1);      // returns 1 (now 1 is most recent)
lru.put(3, 3);   // evicts key 2
lru.get(2);      // returns -1
lru.put(4, 4);   // evicts key 1
lru.get(1);      // returns -1
lru.get(3);      // returns 3
lru.get(4);      // returns 4
```

---

## Complexity

| Operation | Time | Space |
|-----------|------|-------|
| Get | O(1) | O(capacity) |
| Put | O(1) | O(capacity) |

---

## LFU Cache (Least Frequently Used)

Evicts the least frequently accessed item. On ties, evict least recently used.

```cpp
class LFUCache {
private:
    int capacity, minFreq;
    unordered_map<int, pair<int,int>> keyToVal; // key → {value, freq}
    unordered_map<int, list<int>> freqToKeys;   // freq → list of keys
    unordered_map<int, list<int>::iterator> keyToIter; // key → iterator in freqToKeys
    
public:
    LFUCache(int cap) : capacity(cap), minFreq(0) {}
    
    int get(int key) {
        if (keyToVal.find(key) == keyToVal.end()) return -1;
        
        int freq = keyToVal[key].second;
        int val = keyToVal[key].first;
        
        // Remove from current freq list
        freqToKeys[freq].erase(keyToIter[key]);
        if (freqToKeys[freq].empty()) {
            freqToKeys.erase(freq);
            if (minFreq == freq) minFreq++;
        }
        
        // Add to freq+1 list
        freq++;
        freqToKeys[freq].push_front(key);
        keyToIter[key] = freqToKeys[freq].begin();
        keyToVal[key].second = freq;
        
        return val;
    }
    
    void put(int key, int value) {
        if (capacity == 0) return;
        
        if (get(key) != -1) {
            keyToVal[key].first = value;
            return;
        }
        
        if ((int)keyToVal.size() == capacity) {
            // Evict LFM from minFreq
            int evictKey = freqToKeys[minFreq].back();
            freqToKeys[minFreq].pop_back();
            if (freqToKeys[minFreq].empty()) freqToKeys.erase(minFreq);
            keyToVal.erase(evictKey);
            keyToIter.erase(evictKey);
        }
        
        // Insert new key
        keyToVal[key] = {value, 1};
        freqToKeys[1].push_front(key);
        keyToIter[key] = freqToKeys[1].begin();
        minFreq = 1;
    }
};
```

---

## LRU vs LFU

| Feature | LRU | LFU |
|---------|-----|-----|
| Eviction policy | Least recently used | Least frequently used |
| Recency bias | High | Low |
| Implementation | Simpler | More complex |
| Use case | Browser cache, OS page replacement | Music streaming, CDN |

---

## Applications

| Application | Cache Type |
|-------------|-----------|
| Browser history | LRU |
| CPU cache | LRU |
| Database buffer pool | LRU |
| Web page cache | LRU |
| Music playlist | LFU |
| CDN cache | LFU or LRU |
| OS page replacement | LRU (approximation) |

---

## When to Use

| Problem | Structure |
|---------|-----------|
| Evict oldest access | LRU |
| Evict least popular | LFU |
| Time-based expiry | LRU + timestamp |
| Bounded cache | LRU |

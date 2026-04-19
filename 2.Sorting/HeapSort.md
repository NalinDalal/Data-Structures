# Heap Sort

**Idea**: Build a max-heap and repeatedly extract the maximum element.

Heap is like a binary search tree, but the root node will always have element of max value
hence as you traverse raw array, you put the elements in binary search tree

- All levels full except possibly last
- Last level filled from left to right

**Max Heap**: `A[parent(i)] >= A[i]`;Root always contains maximum element
**Min-Heap**: `A[parent(i)] <= A[i]`;Root always contains minimum element

**Algo:**

1. Build max heap
2. Swap root (max) with last
3. Reduce heap size
4. Heapify root again
5. Repeat

**Time Complexity**: O(n log n)
**Space**: O(1)

```cpp
void heapify(vector<int> &a, int n, int i) {
    int largest = i, l = 2*i + 1, r = 2*i + 2;
    if (l < n && a[l] > a[largest]) largest = l;
    if (r < n && a[r] > a[largest]) largest = r;
    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(vector<int> &a) {
    int n = a.size();
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(a, n, i);
    for (int i = n-1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}
```

Using an efficient priority queue to maintain the unsorted portion of the array suddenly turns O(n2) selection sort into O(n lg n) heapsort!



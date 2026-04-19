# Selection Sort

**Idea**: Repeatedly select the minimum element from unsorted part and put it at the beginning.

**Time Complexity**: O(n²)
**Space**: O(1)

```cpp
void selectionSort(vector<int> &a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minIdx])
                minIdx = j;
        swap(a[i], a[minIdx]);
    }
}
```


## 2. Selection Sort

**Idea**: Repeatedly select the minimum element from unsorted part and put it at the beginning.

**Time Complexity**: O(n²)
**Space**: O(1)

```cpp
void selectionSort(vector<int> &a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minIdx])
                minIdx = j;
        swap(a[i], a[minIdx]);
    }
}
```



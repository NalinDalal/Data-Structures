# Merge Sort

based on recursion

**Idea**: Divide the array into halves, sort each half, and merge them. each of those halves has the same sorting algorithm applied to it.
operates by copying all the elements from the target array segment into a helper array,
keeping track of where the start of the left and right halves should be

**Algorithm:**
to sort a subarray `array[a...b]`

1. if(a==b){ already sorted}
2. find k
   k=floor((a+b)/2)

3. recursively sort subarray `array[a...k]`
4. recursively sort subarray `array[k+1...b]`
5. merge `array[a...k]` and `array[k+1...b]` into sorted array `array[a...b]`

**Time Complexity**: O(n log n)
**Space**: O(n)

```cpp
void merge(vector<int> &a, int l, int m, int r) {
    vector<int> L(a.begin() + l, a.begin() + m + 1);
    vector<int> R(a.begin() + m + 1, a.begin() + r + 1);
    int i = 0, j = 0, k = l;

    while (i < L.size() && j < R.size())
        a[k++] = (L[i] < R[j]) ? L[i++] : R[j++];
    while (i < L.size()) a[k++] = L[i++];
    while (j < R.size()) a[k++] = R[j++];
}

void mergeSort(vector<int> &a, int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    merge(a, l, m, r);
}
```




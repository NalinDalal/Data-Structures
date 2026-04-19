# Insertion Sort

**Idea**: Pick elements one by one and insert them at the correct position in the already sorted part of the array.

maintains sorted and unsorted regions of the array.
In each iteration, the next unsorted element moves up to its appropriate
position in the sorted region:

```
insertion_sort(int s[], int n){
    int i,j; /* counters */
    for (i=1; i<n; i++) {
        j=i;
        while ((j>0) && (s[j] < s[j-1])) {
            swap(&s[j],&s[j-1]);
            j = j-1;
        }
    }
}
```

**Time Complexity**:

- Best: O(n)
- Average/Worst: O(n²)

```cpp
void insertionSort(vector<int> &a) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}
```

- significant as it minimises the movement of data
- no of swap=no of moves




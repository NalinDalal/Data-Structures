# Shell Sort

**Idea**: Generalized version of insertion sort, improves performance using a gap sequence.

**Time Complexity**: Varies based on gap. Average ~ O(n^(3/2)) to O(n log² n)

```cpp
void shellSort(vector<int> &a) {
    int n = a.size();
    for (int gap = n / 2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++) {
            int temp = a[i];
            int j;
            for (j = i; j >= gap && a[j - gap] > temp; j -= gap)
                a[j] = a[j - gap];
            a[j] = temp;
        }
}
```



## Shell Sort

**Idea**: Generalized version of insertion sort, improves performance using a gap sequence.

**Time Complexity**: Varies based on gap. Average \~ O(n^(3/2)) to O(n log² n)

```cpp
void shellSort(vector<int> &a) {
    int n = a.size();
    for (int gap = n / 2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++) {
            int temp = a[i];
            int j;
            for (j = i; j >= gap && a[j - gap] > temp; j -= gap)
                a[j] = a[j - gap];
            a[j] = temp;
        }
}
```



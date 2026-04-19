# Bubble Sort

**Idea**: Repeatedly swap adjacent elements if they are in the wrong order.

n rounds

we start at the beginning of the array and swap the first two elements if the first is greater
than the second. Then, we go to the next pair, and so on, continuously making sweeps of the array until it is
sorted, tn doing so, the smaller items slowly "bubble" up to the beginning of the list.

```
for each round:
    iterate thru array
    2 consecutive element no in order
        swap them
```

**Time Complexity**: O(n²)
**Best Case**: O(n) if already sorted

```cpp
void bubbleSort(vector<int> &a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
    }
}
```

- `n-1` swaps are performed in worst case


----


## 1. Bubble Sort

**Idea**: Repeatedly swap adjacent elements if they are in the wrong order.

n rounds

we start at the beginning of the array and swap the first two elements if the first is greater
than the second. Then, we go to the next pair, and so on, continuously making sweeps of the array until it is
sorted, tn doing so, the smaller items slowly "bubble" up to the beginning of the list.

```
for each round:
    iterate thru array
    2 consecutive element no in order
        swap them
```

**Time Complexity**: O(n²)
**Best Case**: O(n) if already sorted

```cpp
void bubbleSort(vector<int> &a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
    }
}
```

- `n-1` swaps are performed in worst case



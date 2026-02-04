# Sorting Algorithms in C++

This document provides implementations and explanations for the following sorting algorithms:

- [x] Insertion Sort
- [x] Selection Sort
- [x] Bubble Sort
- [x] Shell Sort
- [x] Heap Sort
- [x] Quick Sort
- [x] Merge Sort
- [x] Radix Sort (for non-negative integers)

---

## Insertion Sort

**Idea**: Pick elements one by one and insert them at the correct position in the already sorted part of the array.

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

---

## Selection Sort

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

---

## Bubble Sort

**Idea**: Repeatedly swap adjacent elements if they are in the wrong order.

**Time Complexity**: O(n²)
**Best Case**: O(n) if already sorted

```cpp
void bubbleSort(vector<int> &a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        if (!swapped) break;
    }
}
```

---

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

---

## Heap Sort

**Idea**: Build a max-heap and repeatedly extract the maximum element.

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

---

## Quick Sort

**Idea**: Choose a pivot, partition the array around it, and recurse.

**Time Complexity**:

- Best/Average: O(n log n)
- Worst: O(n²) (rare with randomization)

```cpp
int partition(vector<int> &a, int low, int high) {
    int pivot = a[high], i = low - 1;
    for (int j = low; j < high; j++)
        if (a[j] < pivot)
            swap(a[++i], a[j]);
    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(vector<int> &a, int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}
```

---

## Merge Sort

**Idea**: Divide the array into halves, sort each half, and merge them.

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

---

## Radix Sort

**Idea**: Sort numbers digit by digit using counting sort as subroutine.

**Time Complexity**: O(nk), where k = number of digits

```cpp
void countingSort(vector<int> &a, int exp) {
    int n = a.size();
    vector<int> output(n), count(10, 0);

    for (int i = 0; i < n; i++)
        count[(a[i]/exp)%10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i-1];
    for (int i = n-1; i >= 0; i--) {
        output[count[(a[i]/exp)%10]-1] = a[i];
        count[(a[i]/exp)%10]--;
    }
    a = output;
}

void radixSort(vector<int> &a) {
    int maxNum = *max_element(a.begin(), a.end());
    for (int exp = 1; maxNum / exp > 0; exp *= 10)
        countingSort(a, exp);
}
```

---

## Summary Table

| Algorithm      | Best       | Average    | Worst      | Space    |
| -------------- | ---------- | ---------- | ---------- | -------- |
| Insertion Sort | O(n)       | O(n²)      | O(n²)      | O(1)     |
| Selection Sort | O(n²)      | O(n²)      | O(n²)      | O(1)     |
| Bubble Sort    | O(n)       | O(n²)      | O(n²)      | O(1)     |
| Shell Sort     | O(n log n) | \~O(n^1.5) | O(n²)      | O(1)     |
| Heap Sort      | O(n log n) | O(n log n) | O(n log n) | O(1)     |
| Quick Sort     | O(n log n) | O(n log n) | O(n²)      | O(log n) |
| Merge Sort     | O(n log n) | O(n log n) | O(n log n) | O(n)     |
| Radix Sort     | O(nk)      | O(nk)      | O(nk)      | O(n+k)   |

---

## Sample Usage

```cpp
int main() {
    vector<int> arr = {64, 25, 12, 22, 11};
    quickSort(arr, 0, arr.size() - 1);
    for (int x : arr) cout << x << " ";
    return 0;
}
```

---

## Tip:

Use:

- Insertion/Selection/Bubble for small or almost sorted arrays
- Merge/Heap for stable sorting
- QuickSort for average fast sorting
- Radix for non-comparative digit-based sort

# 📚 Array Data Structures (C++ Revision Guide)

## 1. 📘 Introduction to Arrays

Arrays are contiguous memory blocks holding elements of the same type. Each element is accessed using an index starting from 0.

```cpp
int arr[5] = {1, 2, 3, 4, 5};  // Static array
```

---

## 2. 📂 Array Types

### 2.1 Static Arrays

- Fixed size, defined at compile-time.

```cpp
int arr[100];  // Max 100 integers
```

### 2.2 Dynamic Arrays (`vector`)

- Resizable, part of STL.

```cpp
#include <vector>
std::vector<int> vec = {1, 2, 3};
vec.push_back(4);
```

### 2.3 Multidimensional Arrays

```cpp
int mat[3][3];  // 3x3 matrix
```

### 2.4 Jagged Arrays (using vector of vectors)

```cpp
std::vector<std::vector<int>> jagged = {{1}, {2, 3}, {4, 5, 6}};
```

### 2.5 Circular Arrays

Used in circular queue or buffer implementations.

```cpp
int next = (i + 1) % size;
```

### 2.6 Sparse Arrays

Efficient storage for mostly-zero data. Use hash maps or custom classes.

```cpp
std::unordered_map<int, int> sparseArr;
sparseArr[1000000] = 5;  // Efficient storage
```

---

## 3. 🔧 Basic Operations (C++)

```cpp
// Traverse
for (int i = 0; i < n; i++) std::cout << arr[i];

// Insert at end
vec.push_back(10);

// Delete last
vec.pop_back();

// Update
arr[2] = 99;

// Search
bool found = (std::find(vec.begin(), vec.end(), 10) != vec.end());
```

---

## 4. ⚙️ Common Array Algorithms

### 4.1 Searching

#### Linear Search – O(n)

**`💡 Algorithm Steps`**

1. Start from index 0.

2. Compare each element with the key.

3. If found, return index.

4. If not found till end, return -1.

```cpp
int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) if (arr[i] == key) return i;
    return -1;
}
```

#### Binary Search – O(log n) (sorted only)

**`💡 Algorithm Steps`**

1. Set low = 0, high = n - 1.

2. Repeat while low <= high:

   - Find mid = (low + high) / 2.
   - If arr[mid] == key, return mid.
   - If arr[mid] > key, search left half.
   - Else, search right half.

3. Return -1 if not found.

```cpp
int binarySearch(int arr[], int l, int r, int key) {
    while (l <= r) {
        int mid = (l + r) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}
```

---

### 4.2 Sorting

#### Bubble Sort – O(n²)

**`Algorithm Steps`**

1. Repeat n - 1 times:

2. For each pair of adjacent elements:

   - If arr[j] > arr[j+1], swap them.

3. Each pass pushes largest element to end.

```cpp
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) std::swap(arr[j], arr[j + 1]);
}
```

#### STL Sort – O(n log n)

```cpp
std::sort(arr, arr + n);       // For arrays
std::sort(vec.begin(), vec.end());  // For vector
```

---

### 4.3 Prefix Sum – O(n)

**`Algorithm`**

1. Initialize prefix[0] = arr[0].

2. For i = 1 to n-1:

   - prefix[i] = prefix[i-1] + arr[i]

3. To find sum of subarray [l, r]:

   - If l == 0: sum = prefix[r]

   - Else: sum = prefix[r] - prefix[l-1]

```cpp
std::vector<int> prefix(n);
prefix[0] = arr[0];
for (int i = 1; i < n; i++)
    prefix[i] = prefix[i - 1] + arr[i];
```

### 4.4 Sliding Window – O(n)

**Max sum of subarray of size k**

**`Algorithm`**

1. Compute initial window sum of first k elements.

2. Slide window by 1 element each time:

   - Subtract arr[i-k], add arr[i].

   - Update max.

```cpp
int maxSumK(int arr[], int n, int k) {
    int sum = 0, maxSum = 0;
    for (int i = 0; i < k; i++) sum += arr[i];
    maxSum = sum;
    for (int i = k; i < n; i++) {
        sum += arr[i] - arr[i - k];
        maxSum = std::max(maxSum, sum);
    }
    return maxSum;
}
```

### 4.5 Two Pointer – O(n)

**Check if pair with given sum exists in sorted array**

**`Algortihm`**

1. Set two pointers: `i = 0`, `j = n-1`.

2. While `i < j`:
   - If arr[i] + arr[j] == sum, return `true`.
   - If < sum, {`i++`}.
   - Else{ `j--`}.

```cpp
bool hasPair(int arr[], int n, int sum) {
    int l = 0, r = n - 1;
    while (l < r) {
        int s = arr[l] + arr[r];
        if (s == sum) return true;
        else if (s < sum) l++;
        else r--;
    }
    return false;
}
```

---

### 4.6 Kadane’s Algorithm – O(n)

**Max subarray sum**

**`Algortihm`**

1. Initialize: `currMax = arr[0]`, `maxSoFar = arr[0]`

2. For i = 1 to n-1:
   - `currMax = max(arr[i], currMax + arr[i])`
   - `maxSoFar = max(maxSoFar, currMax)`

```cpp
int maxSubArraySum(int arr[], int n) {
    int maxSoFar = arr[0], currMax = arr[0];
    for (int i = 1; i < n; i++) {
        currMax = std::max(arr[i], currMax + arr[i]);
        maxSoFar = std::max(maxSoFar, currMax);
    }
    return maxSoFar;
}
```

---

### 4.7 Binary Search Variants

- Lower bound: first element ≥ target
- Upper bound: first element > target

```cpp
int lb = std::lower_bound(arr, arr + n, target) - arr;
int ub = std::upper_bound(arr, arr + n, target) - arr;
```

---

## 5. 💡 Advanced Problems (Patterns)

| Pattern                 | Example Problem                 |
| ----------------------- | ------------------------------- |
| Two Sum                 | Use two-pointer in sorted array |
| Subarray with Given Sum | Sliding window or hash map      |
| Move Zeros to End       | In-place rearrangement          |
| Trapping Rain Water     | Two pointer                     |
| Product Except Self     | Prefix + Suffix                 |
| Rotate Array            | Reverse algorithm               |

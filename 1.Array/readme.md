# 1. Introduction to Arrays

An array is a contiguous block of memory storing elements of the same type. Elements
are accessed by a zero-based index. Access by index is O(1); searching for a value is O(n).

Example (static array):

```cpp
int arr[5] = {1, 2, 3, 4, 5}; // static array
// access 2nd element: arr[1]
```

Key properties:

- Fixed-size (static) arrays: size known at compile time.
- Dynamic arrays (`std::vector`): resizable, part of the C++ STL.

### Dynamic arrays (std::vector)

```cpp
#include <vector>
std::vector<int> vec = {1, 2, 3};   //vector declared
vec.push_back(4);   //add a element to end of vector; [1,2,3,4]
//average time complexity of push_back is O(1).

cout << v[0] << "\n"; // access elements, 1


// size 10, initial value 0
vector<int> v(10);

//create empty vector
vector<int> v;

//size 10, initial value 5
vector<int> v(10,5);
```

### 2.3 Multidimensional Arrays

```cpp
int mat[3][3];  // 3x3 2D matrix
```
vector is a one-dimensional array of numbers.
matrix is a rectangular array of numbers

**Diagonal Matrix**
diag(a11, a22, . . . , ann )=
[
    [a11, 0,......0],
    [0, a12, ......],
    [..............],
    [..............],
    [0, 0, 0.......ann]
]

**identity matrix** In is a diagonal matrix with 1’s along the diagonal

An **upper-triangular matrix** U is one for which uij =0 if i > j

[
[u11 u12. . . u1n],
[0 u22. . . u2n],
.  .   .  .   .
.  .   .  .   .
.  .   .  .  .
[0 0. . . unn]
]

same for lower triangular matrix

A **permutation matrix** P has exactly one 1 in each row or column, and 0’s elsewhere

**symmetric matrix** A satisfies the condition A=$$pow(A,T)$$

**Matrix Operations**
If A and B are 2 matrix, and u apply addition on them such that C=A+B
then cij =aij +bij

A +0= A
= 0 +A 

\{lambda}
λ is a number and A= (aij ) is a matrix, then λ A= (λaij ) is the scalar
multiple of A obtained by multiplying each of its elements by λ.

A +(−A)= 0
= (−A) +A .


If A=(aij ) is an m ×n
matrix and B=(bjk) is an n ×p matrix, then their matrix product C=AB is the
m ×p matrix C=(cik ), where
cik =
n
aij bjk (28.3)
j=1
for i= 1, 2, . . . , m and k= 1, 2, . . . , p.


A(BC)=( AB)C

A(B +C)= AB +AC ,
(B +C)D= B D +C D. 

AB != BA

**Inverse of Matrix**
AA−1 =In =A−1 A.


If A and B are nonsingular
n ×n matrices, then (B A)−1=A−1 B−1.

( A−1)T
=( AT)−1
.


The determinant of an n ×n
matrix A can be defined recursively in terms of its minors by
det( A)=
    
a11 if n =1 ,
n
(28.7)
(−1)1+j a1 j det( A[1 j]) if n > 1 .
j=1
The term (−1)i+j det( A[ij]) is known as the cofactor of the element aij.


An n ×n matrix A is singular if and only if det( A)=0.

For any matrix A with full column rank, the matrix AT A is positive-definite.

#### Strassen's Algo for Multiplication
Strassen's algorithm applies divide-and-conquer to multiply two n×n matrices.

Assume n is a power of two. Partition A and B into four n/2×n/2 blocks:

$$
A=\begin{pmatrix}a & b\\ c & d\end{pmatrix},\qquad
B=\begin{pmatrix}e & f\\ g & h\end{pmatrix},\qquad
C=AB=\begin{pmatrix}r & s\\ t & u\end{pmatrix}.
$$

The naive divide-and-conquer uses the equalities
$$
r = ae + bg,\qquad s = af + bh,\qquad t = ce + dg,\qquad u = cf + dh,
$$
which yields the recurrence $T(n)=8T(n/2)+\Theta(n^2)$ and therefore $T(n)=\Theta(n^3)$.

Strassen discovered a scheme that computes the same result with only seven
recursive multiplications, giving $T(n)=7T(n/2)+\Theta(n^2)=\Theta(n^{\log_2 7})\approx\Theta(n^{2.81})$.

Define the seven products (each is an n/2×n/2 multiplication):

$$
\begin{aligned}
P_1 &= a\cdot(f-h),\\
P_2 &= (a+b)\cdot h,\\
P_3 &= (c+d)\cdot e,\\
P_4 &= d\cdot(g-e),\\
P_5 &= (a+d)\cdot(e+h),\\
P_6 &= (b-d)\cdot(g+h),\\
P_7 &= (a-c)\cdot(e+f).
\end{aligned}
$$

Then the blocks of the product matrix are recovered from these as:

$$
\begin{aligned}
r &= P_5 + P_4 - P_2 + P_6,\\
s &= P_1 + P_2,\\
t &= P_3 + P_4,\\
u &= P_5 + P_1 - P_3 - P_7.
\end{aligned}
$$

These combinations use only additions/subtractions of n/2×n/2 matrices (\Theta(n^2)
work) plus the seven recursive multiplications. Recursing yields the asymptotic
improvement; note that Strassen's method increases constant factors and has
numerical/stability considerations, so it's mainly useful for large dense matrices.



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

## 3. Basic Operations (C++)

```cpp
// Traverse
for (int i = 0; i < n; i++)
    std::cout << arr[i];

//vector traverse
for (int i = 0; i < v.size(); i++) {
cout << v[i] << "\n";
}

//shorter way to access
for (auto x : v) {
cout << x << "\n";
}

// Insert at end
vec.push_back(10);  //T.C. - O(1)

//returns last element in vector
vec.back();

// Delete last element
vec.pop_back();

// Update
arr[2] = 99;

// Search
bool found = (std::find(vec.begin(), vec.end(), 10) != vec.end());
```

---

## 4. Common Array Algorithms

### 4.1 Searching

#### Linear Search – O(n)

General method is to use a for loop that iterates through the elements of the array.

1. Start from index 0.

2. Compare each element with the key.

3. If found, return index.

4. If not found till end, return -1.

```cpp
int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++)
        if (arr[i] == key) return i;
    return -1;
}
```

#### Binary Search – O(log n)

When array is sorted,
possible to perform the search much faster, because the order of the elements in the array guides the search

**Method 1:**
resembles looking for a word in dictionary
search maintains an active region in the array(initially has all elements)
as no of steps increase, size of region halves

at each step look for middle element of active region, check with target, then eliminate search
otherwise search recursively continues to the left or right half of the region

1. Set low = 0, high = n - 1.

2. Repeat while low <= high:
   - Find mid = (low + high) / 2.
   - If `arr[mid] == key`, return mid.
   - If `arr[mid] > key`, search left half.
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

//recursive algo
int binarySearchRecursive(int[] a, int x, Int low, int high) {
    if (low > high) return -1; // Error
    int mid = (low + high) / 2;
    if (a[mid] < x) 
        return binarySearchRecursive(a, mid + 1, high);
    else if (a[mid] > x)
        return binarySearchRecursive(a, x, low, mid - 1);
    else 
        return mid;
}
```

**Method 2:**

idea is to make jumps and slow
the speed when we get closer to the target element.

goes from left to right, initial jump is n/2
then n/4, then n/8 till jump length is 1
After the jumps, either the target element
has been found or we know that it does not appear in the array.

```cpp
int k = 0;
for (int b = n/2; b >= 1; b /= 2) {
    while (k+b < n && array[k+b] <= x)
        k += b;
}
if (array[k] == x) {
    // x found at index k
}
```

#### Built-in Functions

• lower_bound returns a pointer to the first array element whose value is at least x.
• upper_bound returns a pointer to the first array element whose value is larger than x.
• equal_range returns both above pointers.

functions assume that the array is sorted. If there is no such element, the pointer points to the element after the last array element.

```cpp
auto k = lower_bound(array,array+n,x)-array;
if (k < n && array[k] == x) {
// x found at index k
}
```

no of elements whose value is `x`

```cpp
auto a = lower_bound(array, array+n, x);
auto b = upper_bound(array, array+n, x);
cout << b-a << "\n";
```

more short code:

```cpp
auto r = equal_range(array, array+n, x);
cout << r.second-r.first << "\n";
```

find the position where the value of a function changes.

we wish to find `k` that is valid solution for problem
`ok(x)` returns `true` if `x` is solution
else `false`

```cpp
if(x<k){
    ok(x)=false;
}
else if(x>=k){
    ok(x)=false;
}
```

hence find `k` via binary search:

```cpp
int x = -1;
for (int b = z; b >= 1; b /= 2) {
while (!ok(x+b)) x += b;
}
int k = x+1;
```

search finds the largest value of x for which ok(x) is false

the next
value k= x + 1 is the smallest possible value for which ok(k) is true.

algo calls `ok()` `O(log z)` times
so total time complexity depends on `ok()`

like if `ok()` works in `O(n)` time
total time complexity=`O(nlogz)`

#### finding max value

find the maximum value for a function that is
first increasing and then decreasing.

find a `k` such that:

```
• f (x) < f (x + 1) when x < k, and
• f (x) > f (x + 1) when x ≥ k.
```

use binary search to find max(x) such that: `f (x) < f (x+1)`

```
int x = -1;
for (int b = z; b >= 1; b /= 2) {
while (f(x+b) < f(x+b+1)) x += b;
}
int k = x+1;
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
   - Subtract `arr[i-k]`, add `arr[i]`.
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
   - If `arr[i] + arr[j] == sum`, return `true`.
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

## 5. Advanced Problems (Patterns)

| Pattern                 | Example Problem                 |
| ----------------------- | ------------------------------- |
| Two Sum                 | Use two-pointer in sorted array |
| Subarray with Given Sum | Sliding window or hash map      |
| Move Zeros to End       | In-place rearrangement          |
| Trapping Rain Water     | Two pointer                     |
| Product Except Self     | Prefix + Suffix                 |
| Rotate Array            | Reverse algorithm               |

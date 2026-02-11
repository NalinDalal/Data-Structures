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

minimum possible number of steps in a sorting algorithm in the worst case is at least nlogn.

---

## Insertion Sort

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

---

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

---

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

---

## 4. Quick Sort

Based on Divide-Conquer paradigm

**Idea**: Choose a pivot(random), partition the array around it, and recurse. Algo reduces job of sorting 1 big array into job of 2 small array by partition
partition separates the array into those elements that are less than the pivot/divider element,
and those which are strictly greater than this pivot/divider element.
repeatedly partition the array (and its sub-arrays) around an element, the array will eventually become sorted.



**Divide**: Partition (rearrange) the array `A[p. . r]` into two (possibly empty) subarrays `A[p. . q−1]` and `A[q +1 . . r]` such that each element of `A[p. . q−1]<=A[q]`, which is, in turn, less than or equal to each element of `A[q +1 . . r]`.
Compute the index `q` as part of this partitioning procedure.

**Conquer**: Sort the two subarrays `A[p. . q−1]` and `A[q +1 . . r]` by recursive calls to quicksort.
**Combine**: Since the subarrays are sorted in place, no work is needed to combine them: the entire array `A[p. . r]` is now sorted.

```
QUICKSORT( A, p, r){
    if (p < r){
    q ←PARTITION( A, p, r)
     QUICKSORT( A, p, q−1)
     QUICKSORT( A, q +1, r)
}}

PARTITION( A, p, r){
x ←A[r]
 i ← p−1
 for j ←p to r−1{
 do if A[ j] ≤x{
 then i ←i +1{
 exchange A[i] ↔A[ j]}}}

 exchange A[i +1] ↔A[r]
 return i +1
}
```

for any array index `k`

```
If p ≤k ≤i, then A[k] ≤x.
 If i +1 ≤k ≤ j−1, then A[k] > x.
 If k=r, then A[k]=x.
```

To sort an entire array A, the initial call is QUICKSORT( A, 1, length[A]).

**Algo:**

```
quicksort(int s[], int l, int h){
    int p; /* index of partition */
    if ((h-l)>0) {
        p = partition(s,l,h);
        quicksort(s,l,p-1);
        quicksort(s,p+1,h);
    }
}

int partition(int s[], int l, int h){
    int i; /* counter */
    int p; int firsthigh; /* pivot element index */

    /* divider position for pivot */
    p = h;
    firsthigh = l;

    for (i=l; i<h; i++){
        if (s[i] < s[p]) {
            swap(&s[i],&s[firsthigh]);
            firsthigh ++;
        }
    }
    swap(&s[p],&s[firsthigh]);
    return(firsthigh);
}
```

**Time Complexity**:

- Best/Average: O(n log n)
- Worst: O(n²) (rare with randomization)

**Space Complexity**: O(log n)

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

## 5. Quick Sort(Randomised Version)

In exploring the average-case behavior of quicksort, we have made an assumption
that all permutations of the input numbers are equally likely.
But engineering asks for worst case

randomise the algorithm by explicitly permuting the input.
Instead of always using `A[r]` as the pivot, we will use a randomly chosen element from the subarray `A[p. . r]`
exchange `A[r]` with random element from `A[p..r]`

In the new partition procedure, we simply implement the swap before actually partitioning:

```
randomPartition(A,p,r){
    i ←RANDOM( p, r)
    exchange A[r] ↔A[i]
    return PARTITION( A, p, r)
}

randomQuickSort(A,p,r){
    if(p<r){
        //q is randomly taken b/w p and r
        randomQuickSort(A,p,q-1)
        randomQuickSort(A,q+1,r)
    }
}
```

---

## 3. Merge Sort

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

---

## 6. Radix Sort

**Idea**: Sort numbers digit by digit using counting sort as subroutine.
iterate through each digit of the number, grouping numbers by each digit.
Then, we sort each of these groupings by the next digit. 
We repeat this process sorting by each subsequent digit, until finally the whole array is sorted.


```
RADIX-SORT( A, d){
 for (i ←1 to d){
 do use a stable sort to sort array A on digit i
}
}
```

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

Radix Sort does what is apply sorting on the least significant digit first
process continues until the cards have
been sorted on all d digits

Given n d-digit numbers in which each digit can take on up to k possible values,
RADIX-SORT correctly sorts these numbers in Omega(d(n +k)) time.

Given n b-bit numbers and any positive integer r ≤ b, RADIX-SORT correctly
sorts these numbers in Omega((b/r)(n +2r )) time.

---

## Counting Sort

**Idea**: Sorts the array in O(n) assuming every element is in b/w 0 and c.

**Algorithn**:
algorithm creates a bookkeeping array, whose indices are elements of the original array.
iterate thriugh the original array and calculate how many times each array appear

example: [1,3,6,9,9,3,5,9]

book-keeping array:
[1, 2, 3, 4, 5, 6, 7, 8, 9]
[1, 0, 2, 0, 1, 1, 0, 0, 3]

construction takes O(n) time
new sorted array will take O(n) time because the number of occurrences of each
element can be retrieved from the bookkeeping array.

**Time Complexity**: O(n)

Input Array A:[1...n]
length[A]=n
Array B: [1..n]{sorted}
array C[0. . k] provides temporary working storage

```
COUNTING-SORT( A, B, k)
1 for i ←0 to k
2   do C[i] ←0
3 for j ←1 to length[A]
4   do C[A[ j]] ←C[A[ j]] +1
5 ✄ C[i] now contains the number of elements equal to i.
6 for i ←1 to k
7   do C[i] ←C[i] +C[i−1]
8 ✄ C[i] now contains the number of elements less than or equal to i.
9 for j ←length[A] downto 1
10  do B[C[A[ j]]] ←A[ j]
11      C[A[ j]] ←C[A[ j]]−1
```

The for loop of lines 1–2 takes
time Omega(k), the for loop of lines 3–4 takes time Omega(n), the for loop of lines 6–7
takes time Omega(k), and the for loop of lines 9–11 takes time Omega(n). Thus, the overall
time is Omega(k+n). In practice, we usually use counting sort when we have k=O(n),
in which case the running time is Omega(n).

---

## Bucket sort

runs in linear time when the input is drawn from a uniform distribution.

idea of bucket sort:

- divide the interval [0, 1) into n equal-sized subintervals/bucket
- distribute the n input numbers into the buckets.

**Algo:**

```
BUCKET-SORT( A)
1 n ←length[A]
2 for i ←1 to n
3   do insert A[i] into list B[⌊n A[i]⌋]
4 for i ←0 to n−1
5   do sort list B[i] with insertion sort
6 concatenate the lists B[0], B[1], . . . , B[n−1] together in order
```

## Time: Omega(n) +n·O(2−1/n)= Omega(n)

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

## Tip:

Use:

- Insertion/Selection/Bubble for small or almost sorted arrays
- Merge/Heap for stable sorting
- QuickSort for average fast sorting
- Radix for non-comparative digit-based sort

---

## InBuilt Functions

many benefits in using a library function.

1. It saves time because there is no need to implement the function.
2. The library implementation is certainly correct and efficient: it is not probable that a home-made sorting function would be better.

```cpp
vector<int> v = {4,2,5,3,5,8,3};
sort(v.begin(),v.end());    //[2,3,3,4,5,5,8]
```

reverse order:

```cpp
vector<int> v = {4,2,5,3,5,8,3};
sort(v.rbegin(),v.rend());  //[8,5,5,4,3,3,2]
```

sorting an ordinary array:

```cpp
int n = 7; // array size
int a[] = {4,2,5,3,5,8,3};
sort(a,a+n);
```

sorting a string:

```cpp
string s = "monkey";
sort(s.begin(), s.end());   //ekmnoy
```

---

## Comparison Operator

Used to find order of two elements while sorting.

ex: numbers are sorted according to their values and strings are sorted in alphabetical order.

Pairs (pair) are sorted primarily according to their first elements (first).
However, if the first elements of two pairs are equal, they are sorted according to their second elements (second):

```cpp
vector<pair<int,int>> v;
v.push_back({1,5});
v.push_back({2,3});
v.push_back({1,2});
sort(v.begin(), v.end());   //(1,2), (1,5) and (2,3)
```

Tuple are sorted primarily by the first element,
secondarily by the second element, etc.

```cpp
vector<tuple<int,int,int>> v;
v.push_back({2,1,4});
v.push_back({1,5,3});
v.push_back({2,1,3});
sort(v.begin(), v.end());   //(1,5,3), (2,1,3) and (2,1,4)
```

## Comparison Functions

give an external comparison function to the sort function as a callback function.
sorts strings primarily by length and secondarily by alphabetical order:

```cpp
bool comp(string a, string b) {
if (a.size() != b.size()) return a.size() < b.size();
return a < b;
}
```

sort vector of strings:

```cpp
sort(v.begin(), v.end(), comp);
```

## User Defined Structs

don't have comparison operator automatically.
operator should be defined inside the struct as a function operator<, whose parameter is another element of the same type.
operator return true if element<parameter, false otherwise

```
if(element<parameter){
return true;
}else{return false;}
```

```cpp
struct P {
    int x, y;
    bool operator<(const P &p) {
        if (x != p.x) return x < p.x;
        else return y < p.y;
    }
};
```

---

## Sorting in Linear Time

Comparison sorts can be viewed abstractly in terms of decision trees. A decision
tree is a full binary tree that represents the comparisons between elements that
are performed by a particular sorting algorithm operating on an input of a given
size.

### Lower Bound for Worst Case

Any comparison sort algorithm requires Omega(n lg n) comparisons in the worst case.

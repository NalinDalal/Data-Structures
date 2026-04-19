# Quick Sort

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

# Quick Sort (Randomised Version)

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

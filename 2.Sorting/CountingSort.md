# Counting Sort

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
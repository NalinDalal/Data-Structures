# Bucket Sort

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
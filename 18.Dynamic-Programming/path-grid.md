# Paths in a grid

To find a path from the upper-left corner to the lower-right corner of an *n×n* grid, such that we only move down and right.
Each square contains a positive integer, and the path should be constructed so that the sum of the values along the path is as large as possible.

let rows and columns of the grid are numbered from 1 to n, and `value[y][x]` equals the value of square (y, x).
`sum(y, x)` denote the maximum sum on a path from the upper-left corner to `square (y, x)`

`sum(n,n)` tells us the maximum sum from the upper-left corner to the lower-right corner

when you move to a specififc square, you actually reduce the size of the problem

so the subproblems overlap with each other

`sum[i][j]=max sum path from (i,j) to (n-1,m-1)`

calculate sum recursively as follows:
`sum(y, x)= max(sum(y, x− 1),sum(y− 1, x))+ value[y][x]`

solution for square(y,x) can come from either square (y, x− 1) or square (y− 1, x)
select the direction that maximizes the sum

```
int sum[N][N];
for (int y = 1; y <= n; y++) {
    for (int x = 1; x <= n; x++) {
        sum[y][x] = max(sum[y][x-1],sum[y-1][x])+value[y][x];
    }
}
```

Base Case: `sum[n-1][n-1]=weight of [n-1][n-1]`

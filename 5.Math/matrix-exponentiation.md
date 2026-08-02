# Matrix Exponentiation

Compute A^n in O(k^3 log n) time where k is the matrix dimension. Used to solve linear recurrences (like Fibonacci) in O(k^3 log n) instead of O(n).

---

## Key Idea

If a recurrence can be expressed as:

```
f(n) = c1*f(n-1) + c2*f(n-2) + ... + ck*f(n-k)
```

Then we can write it as a matrix equation:

```
| f(n)   |       | f(n-1) |
| f(n-1) | = M * | f(n-2) |
| ...    |       | ...    |
| f(n-k+1)|      | f(n-k) |
```

And compute M^n using binary exponentiation.

---

## Matrix Multiplication

```cpp
const int MOD = 1e9 + 7;
typedef vector<vector<long long>> Matrix;

Matrix multiply(Matrix& A, Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++) {
            if (A[i][k] == 0) continue;
            for (int j = 0; j < n; j++)
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
        }
    return C;
}
```

---

## Matrix Power

```cpp
Matrix matPow(Matrix M, long long p) {
    int n = M.size();
    Matrix result(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) result[i][i] = 1; // identity
    
    while (p > 0) {
        if (p & 1)
            result = multiply(result, M);
        M = multiply(M, M);
        p >>= 1;
    }
    return result;
}
```

---

## Example 1: Fibonacci

```
F(0) = 0, F(1) = 1
F(n) = F(n-1) + F(n-2)
```

Transformation matrix:

```
| F(n)   |   | 1  1 |   | F(n-1) |
| F(n-1) | = | 1  0 | * | F(n-2) |
```

So:

```
| F(n)   |   | 1  1 |^(n-1)   | F(1) |
| F(n-1) | = | 1  0 |       * | F(0) |
```

```cpp
long long fibonacci(long long n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    Matrix M = {{1, 1}, {1, 0}};
    Matrix result = matPow(M, n - 1);
    
    return result[0][0]; // F(n)
}
```

Time: O(log n) vs O(n) with DP.

---

## Example 2: Linear Recurrence

Solve: `a(n) = a(n-1) + 2*a(n-2) + 3*a(n-3)`

```cpp
long long solve(vector<long long> base, vector<long long> coeff, long long n) {
    int k = coeff.size();
    if (n < k) return base[n];
    
    Matrix M(k, vector<long long>(k, 0));
    for (int i = 0; i < k; i++)
        M[0][i] = coeff[i];
    for (int i = 1; i < k; i++)
        M[i][i-1] = 1;
    
    Matrix result = matPow(M, n - k + 1);
    
    long long ans = 0;
    for (int i = 0; i < k; i++)
        ans = (ans + result[0][i] * base[k - 1 - i]) % MOD;
    return ans;
}

// Usage: base = {a(2), a(1), a(0)}, coeff = {1, 2, 3}
```

---

## Example 3: Grid Path Counting

Count number of ways to reach cell (r, c) in a grid, moving only right or down.

This is a 2D recurrence:
```
dp[i][j] = dp[i-1][j] + dp[i][j-1]
```

Represent as matrix exponentiation on a flattened state vector.

---

## Modular Arithmetic

Always take mod to prevent overflow:

```cpp
const long long MOD = 1e9 + 7;

Matrix multiply(Matrix& A, Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < n; j++)
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    return C;
}
```

---

## Complexity

| Operation | Time | Space |
|-----------|------|-------|
| Matrix multiply (k x k) | O(k^3) | O(k^2) |
| Matrix power k^k^n | O(k^3 log n) | O(k^2) |

---

## Common Recurrences and Their Matrices

| Recurrence | Matrix | Base |
|------------|--------|------|
| Fibonacci: F(n)=F(n-1)+F(n-2) | [[1,1],[1,0]] | [1, 0] |
| Tribonacci: T(n)=T(n-1)+T(n-2)+T(n-3) | [[1,1,1],[1,0,0],[0,1,0]] | [1, 1, 0] |
| a(n)=2a(n-1)+3a(n-2) | [[2,3],[1,0]] | [a(1), a(0)] |
| a(n)=a(n-1)+n (arithmetic) | [[1,1,0],[0,1,1],[0,0,1]] | [a(0), 1, 1] |

---

## Applications

| Problem | Use Matrix Expo? |
|---------|-----------------|
| Fibonacci(n) for large n | Yes |
| Linear recurrences | Yes |
| Count paths in DAG | Yes |
| DP with constant coefficients | Yes |
| Fibonacci modulo m | Yes |
| 0/1 Knapsack | No |
| Graph shortest paths | Use Floyd-Warshall |

---

## When to Use

| Scenario | Technique |
|----------|-----------|
| f(n) = linear combination of previous k terms | Matrix exponentiation |
| n up to 10^18 | Matrix exponentiation |
| Modulo arithmetic needed | Matrix exponentiation with mod |
| Small n (≤ 10^6) | Simple DP is easier |

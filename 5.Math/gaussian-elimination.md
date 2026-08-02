# Gaussian Elimination & XOR Basis

Gaussian elimination solves systems of linear equations in O(n^3). XOR basis finds a minimal set of vectors that span a space over GF(2).

---

## Gaussian Elimination (System of Linear Equations)

Solve: Ax = b where A is n x n, x and b are n x 1.

### Forward Elimination — O(n^3)

```cpp
const double EPS = 1e-9;

int gauss(vector<vector<double>>& a, vector<double>& ans) {
    int n = a.size(); // n equations, n+1 columns (augmented matrix)
    
    for (int col = 0, row = 0; col < n && row < n; col++) {
        // Find pivot
        int pivot = row;
        for (int i = row + 1; i < n; i++)
            if (abs(a[i][col]) > abs(a[pivot][col]))
                pivot = i;
        
        swap(a[row], a[pivot]);
        
        if (abs(a[row][col]) < EPS) continue; // skip zero column
        
        // Eliminate below
        for (int i = row + 1; i < n; i++) {
            double factor = a[i][col] / a[row][col];
            for (int j = col; j <= n; j++)
                a[i][j] -= factor * a[row][j];
        }
        
        row++;
    }
    
    // Back substitution
    ans.assign(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        if (abs(a[i][i]) < EPS) return 0; // no unique solution
        ans[i] = a[i][n];
        for (int j = i + 1; j < n; j++)
            ans[i] -= a[i][j] * ans[j];
        ans[i] /= a[i][i];
    }
    
    return 1; // unique solution found
}
```

---

## Gaussian Elimination (Modular, for CP)

Solve Ax = b over GF(p) where p is prime.

```cpp
const int MOD = 1e9 + 7;

long long modpow(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int gaussMod(vector<vector<long long>>& a, vector<long long>& ans) {
    int n = a.size();
    
    for (int col = 0, row = 0; col < n && row < n; col++) {
        int pivot = row;
        for (int i = row + 1; i < n; i++)
            if (abs(a[i][col]) > abs(a[pivot][col]))
                pivot = i;
        
        swap(a[row], a[pivot]);
        
        if (a[row][col] == 0) continue;
        
        long long inv = modpow(a[row][col], MOD - 2);
        
        for (int i = row + 1; i < n; i++) {
            long long factor = a[i][col] * inv % MOD;
            for (int j = col; j <= n; j++) {
                a[i][j] = (a[i][j] - factor * a[row][j] % MOD + MOD) % MOD;
            }
        }
        
        row++;
    }
    
    ans.assign(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        if (a[i][i] == 0) return 0;
        ans[i] = a[i][n];
        for (int j = i + 1; j < n; j++)
            ans[i] = (ans[i] - a[i][j] * ans[j] % MOD + MOD) % MOD;
        ans[i] = ans[i] * modpow(a[i][i], MOD - 2) % MOD;
    }
    
    return 1;
}
```

---

## XOR Basis

Find a minimal set of basis vectors for the XOR space spanned by a set of numbers.

### Insert into Basis

```cpp
const int BITS = 30; // for numbers up to 2^30

struct XorBasis {
    int basis[BITS]; // basis[i] has the i-th basis vector
    
    XorBasis() { memset(basis, 0, sizeof(basis)); }
    
    void insert(int x) {
        for (int i = BITS - 1; i >= 0; i--) {
            if (!(x & (1 << i))) continue;
            if (!basis[i]) { basis[i] = x; return; }
            x ^= basis[i];
        }
    }
    
    bool canRepresent(int x) {
        for (int i = BITS - 1; i >= 0; i--) {
            if (!(x & (1 << i))) continue;
            if (!basis[i]) return false;
            x ^= basis[i];
        }
        return true;
    }
    
    int maxXor() {
        int result = 0;
        for (int i = BITS - 1; i >= 0; i--)
            result = max(result, result ^ basis[i]);
        return result;
    }
    
    int minXor() {
        for (int i = 0; i < BITS; i++)
            if (basis[i]) return basis[i];
        return 0;
    }
    
    int size() {
        int cnt = 0;
        for (int i = 0; i < BITS; i++)
            if (basis[i]) cnt++;
        return cnt;
    }
    
    // K-th smallest XOR (0-indexed)
    int kth(int k) {
        vector<int> b;
        for (int i = 0; i < BITS; i++)
            if (basis[i]) b.push_back(basis[i]);
        
        if (k >= (1 << b.size())) return -1;
        
        int result = 0;
        for (int i = 0; i < b.size(); i++)
            if (k & (1 << i)) result ^= b[i];
        return result;
    }
};
```

---

## XOR Basis Applications

### 1. Maximum XOR Subset

```cpp
XorBasis basis;
for (int x : arr) basis.insert(x);
cout << basis.maxXor() << "\n";
```

### 2. Check if XOR of subset can equal K

```cpp
XorBasis basis;
for (int x : arr) basis.insert(x);
cout << (basis.canRepresent(k) ? "YES" : "NO") << "\n";
```

### 3. Count Subsets with XOR = K

If K is representable, answer = 2^(n - rank) where rank = basis size.

### 4. Maximum XOR with a Given Number

```cpp
XorBasis basis;
for (int x : arr) basis.insert(x);

int maxXorWith(int x) {
    int result = x;
    for (int i = BITS - 1; i >= 0; i--) {
        if (!basis[i]) continue;
        result = max(result, result ^ basis[i]);
    }
    return result;
}
```

### 5. Basis of Union of Two Sets

```cpp
XorBasis combined;
for (int i = 0; i < BITS; i++) {
    if (a.basis[i]) combined.insert(a.basis[i]);
    if (b.basis[i]) combined.insert(b.basis[i]);
}
```

---

## Complexity

| Operation | Time |
|-----------|------|
| Gaussian Elimination | O(n^3) |
| XOR Basis Insert | O(BITS) = O(30) |
| XOR Basis Max | O(BITS) |
| XOR Basis K-th | O(BITS^2) |

---

## When to Use

| Problem | Technique |
|---------|-----------|
| Solve linear equations | Gaussian Elimination |
| Maximum XOR subset | XOR Basis |
| Check XOR representability | XOR Basis |
| Count XOR subsets | XOR Basis |
| Linear independence check | Gaussian Elimination or XOR Basis |
| System of modular equations | Gaussian Elimination (mod p) |

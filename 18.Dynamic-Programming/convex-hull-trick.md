# Convex Hull Trick (CHT)

An optimization technique for DP problems where the transition is of the form:

```
dp[i] = min/max over j < i of: (m[j] * x[i] + b[j])
```

Each previous state j defines a line y = m[j]*x + b[j]. The DP picks the line with min/max value at x[i].

---

## When to Use

DP of the form:
```
dp[i] = min(dp[j] + cost(j, i))  for all j < i
```
where `cost(j, i)` can be written as `m[j] * x[i] + b[j]`.

Common pattern: the cost function is linear in some parameter x[i] that depends on i.

---

## Simple CHT (Lines added in order of slope, queries monotonic)

```cpp
struct Line {
    long long m, b; // y = m*x + b
    long long eval(long long x) { return m * x + b; }
};

deque<Line> hull;

// Check if line l2 is unnecessary between l1 and l3
bool bad(Line l1, Line l2, Line l3) {
    // l2 is unnecessary if intersection(l1,l3) <= intersection(l1,l2)
    // (for min hull with increasing slopes)
    return (__int128)(l3.b - l1.b) * (l1.m - l2.m) <= 
           (__int128)(l2.b - l1.b) * (l1.m - l3.m);
}

void addLine(long long m, long long b) {
    Line l = {m, b};
    while (hull.size() >= 2 && bad(hull[hull.size()-2], hull[hull.size()-1], l))
        hull.pop_back();
    hull.push_back(l);
}

long long query(long long x) {
    // Binary search for best line at x
    int lo = 0, hi = hull.size() - 1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (hull[mid].eval(x) <= hull[mid+1].eval(x))
            hi = mid;
        else
            lo = mid + 1;
    }
    return hull[lo].eval(x);
}
```

---

## Li Chao Segment Tree (Dynamic CHT)

For arbitrary x-coordinates and insertions in any order. O(log C) per operation where C is coordinate range.

```cpp
const long long INF = 1e18;
const long long MINX = -1e9, MAXX = 1e9;

struct LiChao {
    struct Node {
        Line line;
        Node *left, *right;
        Node(Line l) : line(l), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    
    LiChao() : root(nullptr) {}
    
    void addLine(Line newLine, Node*& node, long long l, long long r) {
        if (!node) { node = new Node(newLine); return; }
        
        long long mid = (l + r) / 2;
        bool leftBetter = newLine.eval(l) < node->line.eval(l);
        bool midBetter = newLine.eval(mid) < node->line.eval(mid);
        
        if (midBetter) swap(node->line, newLine);
        
        if (r - l == 1) return;
        
        if (leftBetter != midBetter)
            addLine(newLine, node->left, l, mid);
        else
            addLine(newLine, node->right, mid, r);
    }
    
    void addLine(long long m, long long b) {
        addLine({m, b}, root, MINX, MAXX);
    }
    
    long long query(long long x, Node* node, long long l, long long r) {
        if (!node) return INF;
        long long mid = (l + r) / 2;
        long long result = node->line.eval(x);
        
        if (r - l == 1) return result;
        
        if (x < mid)
            return min(result, query(x, node->left, l, mid));
        else
            return min(result, query(x, node->right, mid, r));
    }
    
    long long query(long long x) {
        return query(x, root, MINX, MAXX);
    }
};
```

---

## Example 1: Classic DP

```
dp[i] = min(dp[j] + (x[i] - x[j])^2)
      = min(dp[j] + x[i]^2 - 2*x[i]*x[j] + x[j]^2)
      = x[i]^2 + min(dp[j] + x[j]^2 - 2*x[i]*x[j])
      
Line for each j: y = (-2*x[j]) * x + (dp[j] + x[j]^2)
Query at x = x[i]
```

```cpp
long long solve(vector<long long>& x) {
    int n = x.size();
    vector<long long> dp(n, INF);
    
    LiChao cht;
    dp[0] = 0;
    cht.addLine(-2 * x[0], x[0] * x[0]);
    
    for (int i = 1; i < n; i++) {
        dp[i] = x[i] * x[i] + cht.query(x[i]);
        cht.addLine(-2 * x[i], dp[i] + x[i] * x[i]);
    }
    
    return dp[n - 1];
}
```

---

## Example 2: Divide and Conquer DP Optimization

For DP of the form:
```
dp[i] = min(dp[j] + C(j, i))  where opt[i] <= opt[i+1]
```

```cpp
void compute(int l, int r, int optL, int optR) {
    if (l > r) return;
    
    int mid = (l + r) / 2;
    pair<long long, int> best = {INF, -1};
    
    for (int k = optL; k <= min(mid - 1, optR); k++)
        best = min(best, {dp[k] + C(k, mid), k});
    
    dp[mid] = best.first;
    
    compute(l, mid - 1, optL, best.second);
    compute(mid + 1, r, best.second, optR);
}
```

---

## Example 3: Knuth's Optimization

For DP with quadrangle inequality:
```
dp[i][j] = min(dp[i][k] + dp[k+1][j]) + C(i, j)
```

Knuth's adds: `opt[i][j-1] <= opt[i][j] <= opt[i+1][j]`

```cpp
for (int len = 1; len < n; len++) {
    for (int i = 0; i + len < n; i++) {
        int j = i + len;
        for (int k = opt[i][j-1]; k <= opt[i+1][j]; k++)
            dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + C(i, j));
    }
}
```

---

## Comparison

| Method | Insert | Query | Constraints |
|--------|--------|-------|-------------|
| Simple deque | O(1) amortized | O(1) | Monotonic slopes + queries |
| Binary search on deque | O(1) | O(log n) | Ordered slopes |
| Li Chao Tree | O(log C) | O(log C) | Any order |
| Dynamic CHT (set) | O(log n) | O(log n) | Any order |

---

## When to Use

| Problem Type | Technique |
|-------------|-----------|
| dp[i] = min(dp[j] + linear cost) | CHT |
| Quadrangle inequality | Divide & Conquer DP |
| Opt[i] is monotonic | D&C or Knuth |
| Non-monotonic queries | Li Chao Tree |
| dp[i] = min(j*cost + value) | CHT |

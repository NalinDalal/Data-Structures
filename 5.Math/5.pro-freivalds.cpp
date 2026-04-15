// 5.freivalds.cpp
// Monte Carlo + Las Vegas algorithm examples
//
// ── Part 1: Freivalds' Algorithm ──────────────────────────────────────────
// Problem: Verify if A*B == C for n×n matrices in O(n^2) instead of O(n^3)
// Idea:    Pick random vector x. Check if A*(B*x) == C*x.
//          If AB ≠ C, a random x detects this with probability >= 1/2.
//          Run k times to reduce error probability to (1/2)^k.
//
// ── Part 2: Random Graph 2-Coloring ───────────────────────────────────────
// Problem: Color n nodes with 2 colors so that >= m/2 edges are bichromatic.
// Idea:    Assign each node a random color (0 or 1).
//          E[bichromatic edges] = m/2, so repeat until condition is satisfied.

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(42);

// ── Matrix-vector multiply: result = M * v (mod arithmetic avoided; use int)
vector<long long> matVec(const vector<vector<long long>> &M,
                         const vector<long long> &v) {
  int n = M.size();
  vector<long long> res(n, 0);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      res[i] += M[i][j] * v[j];
  return res;
}

// ── Freivalds' Algorithm ───────────────────────────────────────────────────
// Returns true if AB == C (with error probability <= (1/2)^iterations)
bool freivalds(const vector<vector<long long>> &A,
               const vector<vector<long long>> &B,
               const vector<vector<long long>> &C, int iterations = 20) {
  int n = A.size();
  for (int iter = 0; iter < iterations; iter++) {
    // Random 0/1 vector x
    vector<long long> x(n);
    for (auto &xi : x)
      xi = rng() % 2;

    // Compute Bx, then A(Bx), and Cx
    vector<long long> Bx = matVec(B, x);
    vector<long long> ABx = matVec(A, Bx);
    vector<long long> Cx = matVec(C, x);

    if (ABx != Cx)
      return false; // definitely AB ≠ C
  }
  return true; // AB == C with high probability
}

// ── Random Graph 2-Coloring (Las Vegas) ───────────────────────────────────
// Returns a coloring vector (0 or 1 per node) where >= m/2 edges are
// bichromatic
vector<int> randomColoring(int n, const vector<pair<int, int>> &edges) {
  int m = edges.size();
  int target = m / 2; // we need at least this many bichromatic edges

  while (true) {
    vector<int> color(n);
    for (auto &c : color)
      c = rng() % 2;

    int bichromatic = 0;
    for (auto [u, v] : edges)
      if (color[u] != color[v])
        bichromatic++;

    if (bichromatic >= target)
      return color;
  }
}

int main() {
  cout << "=== Freivalds' Algorithm ===\n";

  // Example from the book: [6 8; 1 3] * [3; 6] vs [8 7; 3 2] * [3; 6]
  // These matrices are NOT equal
  vector<vector<long long>> A = {{6, 8}, {1, 3}};
  vector<vector<long long>> B = {{3, 0}, {6, 0}}; // column vector as matrix
  vector<vector<long long>> C = {{8, 7}, {3, 2}};

  // Case 1: Check A == C (they are NOT equal)
  cout << "A == C? "
       << (freivalds(A, {{1, 0}, {0, 1}}, C) ? "YES (probable)"
                                             : "NO (certain)")
       << "\n";

  // Case 2: Check A == A (they ARE equal)
  cout << "A == A? "
       << (freivalds(A, {{1, 0}, {0, 1}}, A) ? "YES (probable)"
                                             : "NO (certain)")
       << "\n";

  // Proper AB == C test
  // Let A = [1 2; 3 4], B = [5 6; 7 8], C = A*B = [19 22; 43 50]
  vector<vector<long long>> M1 = {{1, 2}, {3, 4}};
  vector<vector<long long>> M2 = {{5, 6}, {7, 8}};
  vector<vector<long long>> M3 = {{19, 22}, {43, 50}};       // correct
  vector<vector<long long>> M3_wrong = {{19, 22}, {43, 51}}; // wrong
  cout << "\nM1*M2 == M3 (correct)?  " << (freivalds(M1, M2, M3) ? "YES" : "NO")
       << "\n";
  cout << "M1*M2 == M3_wrong?      "
       << (freivalds(M1, M2, M3_wrong) ? "YES" : "NO") << "\n";

  cout << "\n=== Random Graph 2-Coloring ===\n";
  // Graph from the book: 5 nodes, 7 edges
  int n = 5;
  vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {0, 3}, {1, 2},
                                  {1, 4}, {2, 3}, {3, 4}};
  // 0-indexed: matches nodes 1-5 in the book

  vector<int> coloring = randomColoring(n, edges);

  int bichromatic = 0;
  for (auto [u, v] : edges)
    if (coloring[u] != coloring[v])
      bichromatic++;

  cout << "Coloring: ";
  for (int i = 0; i < n; i++)
    cout << "node" << i + 1 << "=" << coloring[i] << " ";
  cout << "\nBichromatic edges: " << bichromatic << " / " << edges.size()
       << " (target >= " << edges.size() / 2 << ")\n";

  return 0;
}

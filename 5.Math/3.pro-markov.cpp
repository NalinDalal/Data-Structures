// 3.markov_chain.cpp
// Markov Chain simulation
//
// Problem: n-floor building, start at floor 1.
//   At each step: move up or down with prob 1/2.
//   Floor 1 → always go up.  Floor n → always go down.
// Q: What is P(being at floor m after k steps)?
//
// Method 1: DP on probability distribution — O(n^2 * m)
// Method 2: Matrix exponentiation         — O(n^3 * log m)

#include <bits/stdc++.h>
using namespace std;

typedef vector<double> Vec;
typedef vector<Vec> Mat;

// ── Method 1: DP simulation ────────────────────────────────────────────────
// dist[i] = probability of being at floor i (1-indexed, stored at index i-1)
Vec markovDP(int n, int steps) {
  Vec dist(n, 0.0);
  dist[0] = 1.0; // start at floor 1

  for (int s = 0; s < steps; s++) {
    Vec next(n, 0.0);
    for (int i = 0; i < n; i++) {
      if (dist[i] == 0.0)
        continue;
      if (i == 0) {
        // floor 1: always go up
        next[1] += dist[i];
      } else if (i == n - 1) {
        // floor n: always go down
        next[n - 2] += dist[i];
      } else {
        next[i - 1] += dist[i] * 0.5;
        next[i + 1] += dist[i] * 0.5;
      }
    }
    dist = next;
  }
  return dist;
}

// ── Method 2: Matrix exponentiation ───────────────────────────────────────
Mat matMul(const Mat &A, const Mat &B) {
  int n = A.size();
  Mat C(n, Vec(n, 0.0));
  for (int i = 0; i < n; i++)
    for (int k = 0; k < n; k++)
      if (A[i][k] != 0)
        for (int j = 0; j < n; j++)
          C[i][j] += A[i][k] * B[k][j];
  return C;
}

Mat matPow(Mat M, int p) {
  int n = M.size();
  Mat result(n, Vec(n, 0.0));
  for (int i = 0; i < n; i++)
    result[i][i] = 1.0; // identity
  while (p > 0) {
    if (p & 1)
      result = matMul(result, M);
    M = matMul(M, M);
    p >>= 1;
  }
  return result;
}

Vec markovMatrix(int n, int steps) {
  // Build transition matrix T where T[j][i] = P(go from i to j)
  Mat T(n, Vec(n, 0.0));
  for (int i = 0; i < n; i++) {
    if (i == 0) {
      T[1][0] = 1.0;
    } else if (i == n - 1) {
      T[n - 2][n - 1] = 1.0;
    } else {
      T[i - 1][i] = 0.5;
      T[i + 1][i] = 0.5;
    }
  }
  Mat Tk = matPow(T, steps);

  // initial dist: floor 1 (index 0) has prob 1
  Vec result(n, 0.0);
  for (int j = 0; j < n; j++)
    result[j] = Tk[j][0];
  return result;
}

int main() {
  cout << fixed << setprecision(4);

  int n = 5, steps = 6;
  cout << "n=" << n << " floors, " << steps
       << " steps, starting at floor 1\n\n";

  Vec dp = markovDP(n, steps);
  Vec mat = markovMatrix(n, steps);

  cout << "Floor | DP Method | Matrix Exp\n";
  cout << "------+-----------+-----------\n";
  for (int i = 0; i < n; i++)
    printf("  %d   |  %.4f   |  %.4f\n", i + 1, dp[i], mat[i]);

  return 0;
}

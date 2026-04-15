// 2.expected_value.cpp
// Expected value, linearity of expectation, and common distributions
//
// Covers:
//   - E[X] = sum of P(X=x)*x
//   - Linearity: E[X1+X2+...+Xn] = E[X1]+...+E[Xn]
//   - Empty boxes problem
//   - Uniform, Binomial, Geometric distributions

#include <bits/stdc++.h>
using namespace std;

// ── Expected value of a dice roll ──────────────────────────────────────────
double diceExpected() {
  // E[X] = 1/6*1 + 1/6*2 + ... + 1/6*6 = 7/2
  double e = 0;
  for (int x = 1; x <= 6; x++)
    e += (1.0 / 6) * x;
  return e; // 3.5
}

// ── Linearity: expected sum of two dice ────────────────────────────────────
// E[X1+X2] = E[X1] + E[X2] = 3.5 + 3.5 = 7
double twoDiceExpected() { return 2 * diceExpected(); }

// ── Empty boxes problem ────────────────────────────────────────────────────
// n balls placed uniformly at random into n boxes.
// P(single box empty) = ((n-1)/n)^n
// E[empty boxes] = n * ((n-1)/n)^n
double expectedEmptyBoxes(int n) {
  double p_empty = pow((double)(n - 1) / n, n);
  return n * p_empty;
}

// ── Uniform distribution ───────────────────────────────────────────────────
// Values a, a+1, ..., b each with prob 1/n, n = b-a+1
// E[X] = (a+b)/2
double uniformExpected(int a, int b) { return (a + b) / 2.0; }

// ── Binomial distribution ──────────────────────────────────────────────────
// n attempts, each succeeds with prob p
// E[X] = n*p
// P(X=x) = C(n,x) * p^x * (1-p)^(n-x)
double binomialProb(int n, int x, double p) {
  // C(n,x)
  double comb = 1;
  for (int i = 0; i < x; i++)
    comb *= (double)(n - i) / (i + 1);
  return comb * pow(p, x) * pow(1 - p, n - x);
}

double binomialExpected(int n, double p) { return n * p; }

// ── Geometric distribution ─────────────────────────────────────────────────
// Repeat until first success (prob p each attempt)
// P(X=x) = (1-p)^(x-1) * p
// E[X] = 1/p
double geometricProb(int x, double p) { return pow(1 - p, x - 1) * p; }

double geometricExpected(double p) { return 1.0 / p; }

int main() {
  cout << fixed << setprecision(4);

  cout << "=== Expected Value ===\n";
  cout << "E[dice]         = " << diceExpected() << "\n";    // 3.5
  cout << "E[sum 2 dice]   = " << twoDiceExpected() << "\n"; // 7.0

  cout << "\n=== Empty Boxes (n=10) ===\n";
  cout << "E[empty]        = " << expectedEmptyBoxes(10) << "\n";

  cout << "\n=== Uniform(1,6) ===\n";
  cout << "E[X]            = " << uniformExpected(1, 6) << "\n"; // 3.5

  cout << "\n=== Binomial(n=10, p=1/6) ===\n";
  cout << "E[X]            = " << binomialExpected(10, 1.0 / 6)
       << "\n"; // ~1.667
  cout << "P(X=3)          = " << binomialProb(10, 3, 1.0 / 6)
       << "\n"; // three 6s in 10 throws

  cout << "\n=== Geometric(p=1/6) ===\n";
  cout << "E[X]            = " << geometricExpected(1.0 / 6) << "\n"; // 6.0
  cout << "P(X=4)          = " << geometricProb(4, 1.0 / 6)
       << "\n"; // (5/6)^3 * 1/6

  return 0;
}

// 1.basics.cpp
// Probability basics: calculating P(event) using combinatorics
// Example: probability of drawing 3 cards of the same value from a 52-card deck
// Method 1: combinatorics  →  13 * C(4,3) / C(52,3) = 1/425
// Method 2: sequential     →  1 * (3/51) * (2/50) = 1/425

#include <bits/stdc++.h>
using namespace std;

// Binomial coefficient C(n, k)
long long C(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    long long num = 1, den = 1;
    for (int i = 0; i < k; i++) {
        num *= (n - i);
        den *= (i + 1);
    }
    return num / den;
}

// Method 1: combinatorics
// desired outcomes = 13 * C(4,3)  (13 values, choose 3 suits from 4)
// total outcomes   = C(52,3)
double method1() {
    double desired = 13.0 * C(4, 3);
    double total   = C(52, 3);
    return desired / total;
}

// Method 2: sequential simulation
// P = 1 * (3/51) * (2/50)
double method2() {
    return 1.0 * (3.0 / 51.0) * (2.0 / 50.0);
}

// Monte Carlo verification: simulate N draws and count matches
double monteCarlo(int N = 1000000) {
    mt19937 rng(42);
    // Represent deck as cards 0..51; card value = card/4
    int count = 0;
    for (int i = 0; i < N; i++) {
        // Draw 3 distinct cards
        int a = rng() % 52;
        int b, c;
        do { b = rng() % 52; } while (b == a);
        do { c = rng() % 52; } while (c == a || c == b);
        if (a / 4 == b / 4 && b / 4 == c / 4) count++;
    }
    return (double)count / N;
}

int main() {
    cout << fixed << setprecision(6);
    cout << "Method 1 (combinatorics): " << method1() << "\n"; // ~0.002353 = 1/425
    cout << "Method 2 (sequential):    " << method2() << "\n";
    cout << "Monte Carlo estimate:      " << monteCarlo() << "\n";
    return 0;
}

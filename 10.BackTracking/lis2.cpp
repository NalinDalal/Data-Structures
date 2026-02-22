// Longest Increasing Subsequence 2 — Backtracking (LISfirst formulation)
// Instead of "skip or take?", ask "where is the NEXT element?"
//
// LISfirst(i) = length of the longest increasing subsequence of A[i..n]
//               that BEGINS with A[i].
//
// LISfirst(i) = 1 + max{ LISfirst(j) | j > i and A[j] > A[i] }
//             = 1  if no such j exists
//
// Final answer = max{ LISfirst(i) | 1 <= i <= n }
//
// Time: O(2^n) without memoisation
//       O(n^2) with memoisation

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

vector<int> A;
int n;

// ----- Brute-force backtracking (exponential) -----

// LISfirst(i): length of LIS of A[i..n] starting with A[i]
int LISfirst(int i) {
    int best = 0;
    for (int j = i + 1; j <= n; j++) {
        if (A[j] > A[i])
            best = max(best, LISfirst(j));
    }
    return 1 + best;
}

// ----- Memoised version (O(n^2)) -----

vector<int> memo;

int LISfirstMemo(int i) {
    if (memo[i] != -1)
        return memo[i];

    int best = 0;
    for (int j = i + 1; j <= n; j++) {
        if (A[j] > A[i])
            best = max(best, LISfirstMemo(j));
    }
    return memo[i] = 1 + best;
}

// ----- Bottom-up DP (O(n^2)) -----

vector<int> dp;

void LISfirstDP() {
    dp.assign(n + 1, 1);
    // Fill right to left
    for (int i = n - 1; i >= 1; i--) {
        int best = 0;
        for (int j = i + 1; j <= n; j++) {
            if (A[j] > A[i])
                best = max(best, dp[j]);
        }
        dp[i] = 1 + best;
    }
}

// ----- Reconstruct one LIS from DP table -----

void printLIS() {
    // Find starting index with max dp value
    int start = 1;
    for (int i = 2; i <= n; i++)
        if (dp[i] > dp[start])
            start = i;

    int len = dp[start];
    cout << A[start];
    int prev = start;
    int remaining = len - 1;

    for (int j = start + 1; j <= n && remaining > 0; j++) {
        if (A[j] > A[prev] && dp[j] == remaining) {
            cout << " " << A[j];
            prev = j;
            remaining--;
        }
    }
    cout << endl;
}

// ----- Print ALL LIS starting from index i with given length -----

void printAllLIS(int i, int targetLen, vector<int>& seq) {
    seq.push_back(A[i]);
    if (targetLen == 1) {
        for (int k = 0; k < (int)seq.size(); k++) {
            if (k > 0) cout << " ";
            cout << seq[k];
        }
        cout << endl;
    } else {
        for (int j = i + 1; j <= n; j++) {
            if (A[j] > A[i] && dp[j] == targetLen - 1)
                printAllLIS(j, targetLen - 1, seq);
        }
    }
    seq.pop_back();
}

int main() {
    vector<int> input = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7};

    n = input.size();
    A.resize(n + 1);
    for (int i = 0; i < n; i++)
        A[i + 1] = input[i];

    cout << "=== Longest Increasing Subsequence 2 — LISfirst ===" << endl;
    cout << "Array: ";
    for (int i = 1; i <= n; i++) cout << A[i] << " ";
    cout << "\n" << endl;

    // Brute-force: find max LISfirst(i) over all i
    int bruteResult = 0;
    for (int i = 1; i <= n; i++)
        bruteResult = max(bruteResult, LISfirst(i));
    cout << "[Brute-force] LIS length: " << bruteResult << endl;

    // Memoised
    memo.assign(n + 1, -1);
    int memoResult = 0;
    for (int i = 1; i <= n; i++)
        memoResult = max(memoResult, LISfirstMemo(i));
    cout << "[Memoised]    LIS length: " << memoResult << endl;

    // Bottom-up DP
    LISfirstDP();
    int dpResult = *max_element(dp.begin() + 1, dp.end());
    cout << "[Bottom-up]   LIS length: " << dpResult << endl;

    // Reconstruct one LIS
    cout << "\nOne LIS: ";
    printLIS();

    // Print all LIS
    cout << "\nAll LIS of maximum length:" << endl;
    for (int i = 1; i <= n; i++) {
        if (dp[i] == dpResult) {
            vector<int> seq;
            printAllLIS(i, dpResult, seq);
        }
    }

    return 0;
}

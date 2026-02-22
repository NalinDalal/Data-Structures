// Longest Increasing Subsequence — Backtracking
// Given array A[1..n], find the length of the longest strictly increasing subsequence.
//
// Approach: For each element, decide to skip or take (if > prev).
//
// LISbigger(i, j):
//     if j > n              → return 0
//     if A[i] >= A[j]       → return LISbigger(i, j+1)     // must skip
//     else
//         skip ← LISbigger(i, j+1)
//         take ← LISbigger(j, j+1) + 1
//         return max(skip, take)
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

// i = index of last taken element (0 = sentinel with A[0] = -INF)
// j = current index under consideration
int LISbigger(int i, int j) {
    if (j > n)
        return 0;
    if (A[i] >= A[j])
        return LISbigger(i, j + 1); // A[j] not large enough, skip
    // A[j] > A[i], so we can take or skip
    int skip = LISbigger(i, j + 1);
    int take = LISbigger(j, j + 1) + 1;
    return max(skip, take);
}

// ----- Memoised version (O(n^2)) -----

vector<vector<int>> memo;

int LISbiggerMemo(int i, int j) {
    if (j > n)
        return 0;
    if (memo[i][j] != -1)
        return memo[i][j];

    if (A[i] >= A[j])
        return memo[i][j] = LISbiggerMemo(i, j + 1);

    int skip = LISbiggerMemo(i, j + 1);
    int take = LISbiggerMemo(j, j + 1) + 1;
    return memo[i][j] = max(skip, take);
}

// ----- Reconstruct one LIS -----

void printLIS(int i, int j, vector<int>& seq) {
    if (j > n) {
        for (int k = 0; k < (int)seq.size(); k++) {
            if (k > 0) cout << " ";
            cout << seq[k];
        }
        cout << endl;
        return;
    }
    if (A[i] >= A[j]) {
        printLIS(i, j + 1, seq);
        return;
    }

    int skip = LISbiggerMemo(i, j + 1);
    int take = LISbiggerMemo(j, j + 1) + 1;

    if (take >= skip) {
        // Take A[j]
        seq.push_back(A[j]);
        printLIS(j, j + 1, seq);
    } else {
        // Skip A[j]
        printLIS(i, j + 1, seq);
    }
}

int main() {
    // A[0] is a sentinel with value -INF
    // Actual array is A[1..n]
    vector<int> input = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7};

    n = input.size();
    A.resize(n + 1);
    A[0] = INT_MIN; // sentinel
    for (int i = 0; i < n; i++)
        A[i + 1] = input[i];

    cout << "=== Longest Increasing Subsequence — Backtracking ===" << endl;
    cout << "Array: ";
    for (int i = 1; i <= n; i++) cout << A[i] << " ";
    cout << "\n" << endl;

    // Brute-force
    int bruteResult = LISbigger(0, 1);
    cout << "[Brute-force] LIS length: " << bruteResult << endl;

    // Memoised
    memo.assign(n + 1, vector<int>(n + 2, -1));
    int memoResult = LISbiggerMemo(0, 1);
    cout << "[Memoised]    LIS length: " << memoResult << endl;

    // Reconstruct
    cout << "\nOne LIS: ";
    vector<int> seq;
    printLIS(0, 1, seq);

    return 0;
}

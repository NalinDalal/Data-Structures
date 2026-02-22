// Text Segmentation — Backtracking (Word Break Problem)
// Given a string with no spaces, determine if it can be broken into valid words.
// Try every possible first word; if A[1..i] is a word, recursively check A[i+1..n].
//
// Splittable(i):
//     if i > n         → return True
//     for j ← i to n
//         if IsWord(i, j) and Splittable(j + 1)
//             return True
//     return False
//
// Time: O(2^n) without memoisation
//       O(n^2) with memoisation (n subproblems, each O(n) work)

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

// Dictionary of valid words
unordered_set<string> dictionary;

// IsWord(w): returns true if w is in the dictionary
bool IsWord(const string& w) {
    return dictionary.count(w) > 0;
}

// ----- Brute-force backtracking (exponential) -----

// Splittable(A, i): can suffix A[i..n-1] be segmented into words?
bool Splittable(const string& A, int i) {
    int n = A.size();
    if (i >= n)
        return true; // entire string processed

    for (int j = i; j < n; j++) {
        string word = A.substr(i, j - i + 1);
        if (IsWord(word)) {
            if (Splittable(A, j + 1))
                return true;
        }
    }
    return false;
}

// ----- Memoised version (polynomial) -----

// memo[i] = 0 (unvisited), 1 (true), -1 (false)
vector<int> memo;

bool SplittableMemo(const string& A, int i) {
    int n = A.size();
    if (i >= n)
        return true;
    if (memo[i] != 0)
        return memo[i] == 1;

    for (int j = i; j < n; j++) {
        string word = A.substr(i, j - i + 1);
        if (IsWord(word)) {
            if (SplittableMemo(A, j + 1)) {
                memo[i] = 1;
                return true;
            }
        }
    }
    memo[i] = -1;
    return false;
}

// ----- Print one valid segmentation -----

bool PrintSegmentation(const string& A, int i, vector<string>& words) {
    int n = A.size();
    if (i >= n) {
        for (int k = 0; k < (int)words.size(); k++) {
            if (k > 0) cout << " · ";
            cout << words[k];
        }
        cout << endl;
        return true;
    }

    for (int j = i; j < n; j++) {
        string word = A.substr(i, j - i + 1);
        if (IsWord(word)) {
            words.push_back(word);
            if (PrintSegmentation(A, j + 1, words))
                return true;
            words.pop_back();
        }
    }
    return false;
}

// ----- Print ALL valid segmentations -----

void PrintAllSegmentations(const string& A, int i, vector<string>& words) {
    int n = A.size();
    if (i >= n) {
        for (int k = 0; k < (int)words.size(); k++) {
            if (k > 0) cout << " · ";
            cout << words[k];
        }
        cout << endl;
        return;
    }

    for (int j = i; j < n; j++) {
        string word = A.substr(i, j - i + 1);
        if (IsWord(word)) {
            words.push_back(word);
            PrintAllSegmentations(A, j + 1, words);
            words.pop_back();
        }
    }
}

int main() {
    // Populate dictionary
    vector<string> dict = {
        "both", "bot", "he", "hear", "heart", "hearth",
        "earth", "and", "sand", "sat", "saturn", "spin",
        "pin", "urns", "urn", "hands", "hand", "at",
        "a", "i", "in", "it", "is", "the", "to", "art"
    };
    for (const string& w : dict)
        dictionary.insert(w);

    string input = "bothearthandsaturnspin";

    cout << "=== Text Segmentation — Backtracking ===" << endl;
    cout << "Input: \"" << input << "\"" << endl;
    cout << "Dictionary: { ";
    for (const string& w : dict) cout << w << " ";
    cout << "}\n" << endl;

    // Brute-force check
    cout << "[Brute-force] Splittable? "
         << (Splittable(input, 0) ? "Yes" : "No") << endl;

    // Memoised check
    memo.assign(input.size(), 0);
    cout << "[Memoised]    Splittable? "
         << (SplittableMemo(input, 0) ? "Yes" : "No") << "\n" << endl;

    // Print one segmentation
    cout << "One valid segmentation:" << endl;
    vector<string> words;
    PrintSegmentation(input, 0, words);

    // Print all segmentations
    cout << "\nAll valid segmentations:" << endl;
    words.clear();
    PrintAllSegmentations(input, 0, words);

    return 0;
}

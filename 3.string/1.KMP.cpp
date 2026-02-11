/*
*1. Knuth-Morris-Pratt (KMP) Algorithm
Theory:
The KMP algorithm searches for occurrences of a "pattern" within a main "text"
by employing the observation that when a mismatch occurs, the pattern itself
contains sufficient information to determine where the next match could begin.
This eliminates the need for re-examining previously matched characters.

The KMP algorithm preprocesses the pattern to create a "partial match" table
(also known as the "failure function" or "prefix function") that indicates where
the next comparison should begin in case of a mismatch.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> compute_prefix_function(const string &pattern) {
  int m = pattern.length();
  vector<int> lps(m, 0);
  int j = 0;
  for (int i = 1; i < m; ++i) {
    while (j > 0 && pattern[i] != pattern[j]) {
      j = lps[j - 1];
    }
    if (pattern[i] == pattern[j]) {
      ++j;
      lps[i] = j;
    }
  }
  return lps;
}

void kmp_search(const string &text, const string &pattern) {
  int n = text.length();
  int m = pattern.length();
  vector<int> lps = compute_prefix_function(pattern);
  int i = 0, j = 0;

  while (i < n) {
    if (pattern[j] == text[i]) {
      ++i;
      ++j;
    }
    if (j == m) {
      cout << "Pattern found at index " << (i - j) << endl;
      j = lps[j - 1];
    } else if (i < n && pattern[j] != text[i]) {
      if (j != 0) {
        j = lps[j - 1];
      } else {
        ++i;
      }
    }
  }
}

int main() {
  string text = "ABABDABACDABABCABAB";
  string pattern = "ABABCABAB";
  kmp_search(text, pattern);
  return 0;
}

/*
 * Theory: Uses hashing to find patterns efficiently by comparing hash values of
 * substrings. The Rabin-Karp algorithm uses hashing to find any one of a set of
 * pattern strings in a text. It calculates a hash value for the pattern and
 * each substring of the text with the same length as the pattern. If the hash
 * values match, it checks the substring against the pattern to avoid false
 * positives due to hash collisions.
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> rabin_karp_search(const string &text, const string &pattern,
                              int d = 256, int q = 101) {
  vector<int> result;
  int n = text.length();
  int m = pattern.length();
  long long p = 0; // hash value for pattern
  long long t = 0; // hash value for text
  long long h = 1;

  for (int i = 0; i < m - 1; ++i) {
    h = (h * d) % q;
  }

  for (int i = 0; i < m; ++i) {
    p = (d * p + pattern[i]) % q;
    t = (d * t + text[i]) % q;
  }

  for (int i = 0; i <= n - m; ++i) {
    if (p == t) {
      if (text.substr(i, m) == pattern) {
        result.push_back(i);
      }
    }
    if (i < n - m) {
      t = (d * (t - text[i] * h) + text[i + m]) % q;
      if (t < 0) {
        t = t + q;
      }
    }
  }

  return result;
}

int main() {
  string text = "GEEKS FOR GEEKS";
  string pattern = "GEEK";
  vector<int> result = rabin_karp_search(text, pattern);
  cout << "Pattern found at indexes: ";
  for (int index : result) {
    cout << index << " ";
  }
  cout << endl;
  return 0;
}

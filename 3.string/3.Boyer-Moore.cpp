/*
Theory: Utilizes bad character and good suffix heuristics to skip sections of
text.

The Boyer-Moore algorithm is an efficient string searching algorithm that skips
sections of the text, allowing for faster matching. It uses two heuristics: the
bad character heuristic and the good suffix heuristic to shift the pattern more
effectively when mismatches occur.

*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> bad_char_heuristic(const string &pattern) {
  vector<int> bad_char(256, -1);
  for (int i = 0; i < pattern.length(); ++i) {
    bad_char[pattern[i]] = i;
  }
  return bad_char;
}

void boyer_moore_search(const string &text, const string &pattern) {
  int n = text.length();
  int m = pattern.length();
  vector<int> bad_char = bad_char_heuristic(pattern);
  int s = 0;

  while (s <= n - m) {
    int j = m - 1;
    while (j >= 0 && pattern[j] == text[s + j]) {
      --j;
    }
    if (j < 0) {
      cout << "Pattern found at index " << s << endl;
      s += (s + m < n) ? m - bad_char[text[s + m]] : 1;
    } else {
      s += max(1, j - bad_char[text[s + j]]);
    }
  }
}

int main() {
  string text = "ABAAABCD";
  string pattern = "ABC";
  boyer_moore_search(text, pattern);
  return 0;
}

// suffix array
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> build_suffix_array(const string &text) {
  int n = text.length();
  vector<pair<string, int> > suffixes(n);
  for (int i = 0; i < n; ++i) {
    suffixes[i] = make_pair(text.substr(i), i);
  }
  sort(suffixes.begin(), suffixes.end());
  vector<int> suffix_array(n);
  for (int i = 0; i < n; ++i) {
    suffix_array[i] = suffixes[i].second;
  }
  return suffix_array;
}

int main() {
  string text = "banana";
  vector<int> suffix_array = build_suffix_array(text);
  cout << "Suffix array: ";
  for (int index : suffix_array) {
    cout << index << " ";
  }
  cout << endl;
  return 0;
}

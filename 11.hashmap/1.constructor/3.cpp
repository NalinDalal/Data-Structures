// ListConstructor

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
  unordered_map<int, string> hashmap = {
      {1, "Value 1"}, {2, "Value 2"}, {3, "Value 3"}};
  for (const auto &pair : hashmap) {
    cout << pair.first << ": " << pair.second << endl;
  }
  return 0;
}

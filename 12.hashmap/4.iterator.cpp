#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
  unordered_map<int, string> hashmap = {
      {1, "Value 1"}, {2, "Value 2"}, {3, "Value 3"}};
  for (auto it = hashmap.begin(); it != hashmap.end(); ++it) {
    cout << "Key: " << it->first << ", Value: " << it->second << endl;
  }
  return 0;
}

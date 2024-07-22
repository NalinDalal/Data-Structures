// RangeConstructor

#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  std::pair<int, std::string> arr[] = {std::make_pair(1, "Value 1"),
                                       std::make_pair(2, "Value 2"),
                                       std::make_pair(3, "Value 3")};

  std::unordered_map<int, std::string> hashmap(arr, arr + sizeof(arr) /
                                                              sizeof(arr[0]));

  for (const auto &pair : hashmap) {
    std::cout << pair.first << ": " << pair.second << std::endl;
  }

  return 0;
}

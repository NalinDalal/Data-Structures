#include <iostream>
#include <unordered_map>

int main() {
  std::unordered_map<int, std::string> hashmap = {
      {1, "Value 1"}, {2, "Value 2"}, {3, "Value 3"}};
  std::size_t count = hashmap.count(1);
  std::cout << "Count of key 1: " << count << std::endl;
  return 0;
}

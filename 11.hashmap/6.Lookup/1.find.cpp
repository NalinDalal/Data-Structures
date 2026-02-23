#include <iostream>
#include <unordered_map>

int main() {
  std::unordered_map<int, std::string> hashmap = {
      {1, "Value 1"}, {2, "Value 2"}, {3, "Value 3"}};
  auto it = hashmap.find(1);
  if (it != hashmap.end()) {
    std::cout << "Key found: " << it->first << " -> " << it->second
              << std::endl;
  } else {
    std::cout << "Key not found" << std::endl;
  }
  return 0;
}

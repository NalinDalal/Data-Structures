#include <iostream>
#include <unordered_map>

int main() {
  std::unordered_map<int, std::string> hashmap;
  if (hashmap.empty()) {
    std::cout << "The hashmap is empty." << std::endl;
  } else {
    std::cout << "The hashmap is not empty." << std::endl;
  }
  return 0;
}

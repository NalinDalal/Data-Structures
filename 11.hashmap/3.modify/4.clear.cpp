#include <iostream>
#include <unordered_map>

int main() {
  std::unordered_map<int, std::string> hashmap = {
      {1, "Value 1"}, {2, "Value 2"}, {3, "Value 3"}};
  hashmap.clear();
  std::cout << "Cleared all elements using clear()." << std::endl;
  return 0;
}

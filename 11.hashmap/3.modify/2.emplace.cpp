#include <iostream>
#include <unordered_map>

int main() {
  std::unordered_map<int, std::string> hashmap;
  hashmap.emplace(1, "Value 1");
  hashmap.emplace(2, "Value 2");
  std::cout << "Inserted elements using emplace()." << std::endl;
  return 0;
}

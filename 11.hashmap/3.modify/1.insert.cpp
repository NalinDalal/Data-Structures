#include <iostream>
#include <unordered_map>

int main() {
  std::unordered_map<int, std::string> hashmap;
  hashmap.insert(std::make_pair(1, "Value 1"));
  hashmap.insert({2, "Value 2"});
  std::cout << "Inserted elements using insert()." << std::endl;
  return 0;
}

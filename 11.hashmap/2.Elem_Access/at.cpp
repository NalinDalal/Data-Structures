#include <iostream>
#include <unordered_map>

int main() {
  std::unordered_map<int, std::string> hashmap = {{1, "Value 1"},
                                                  {2, "Value 2"}};
  try {
    std::string value = hashmap.at(1);
    std::cout << "Element access using at(): " << value << std::endl;
  } catch (const std::out_of_range &e) {
    std::cout << "Key not found" << std::endl;
  }
  return 0;
}

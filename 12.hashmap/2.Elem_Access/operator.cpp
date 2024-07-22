#include <iostream>
#include <unordered_map>

int main() {
  std::unordered_map<int, std::string> hashmap = {{1, "Value 1"},
                                                  {2, "Value 2"}};
  std::string value = hashmap[1];
  std::cout << "Element access using operator[]: " << value << std::endl;
  return 0;
}

#include <iostream>
#include <unordered_map>

int main() {
  std::unordered_map<int, std::string> hashmap = {
      {1, "Value 1"}, {2, "Value 2"}, {3, "Value 3"}};
  hashmap.erase(2);
  std::cout << "Erased element with key 2 using erase()." << std::endl;
  return 0;
}

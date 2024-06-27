#include <bitset>
#include <iostream>
int main() {
  int a = 0b101;
  int b = 0b10110;
  b <<= 4;
  int c = a | b;
  std::cout << std::bitset<9>(c) << std::endl;
  return 0;
}

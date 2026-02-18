#include <iostream>
using namespace std;

void tailRecursivePrint(int i) {
  if (i == 0)
    return;
  cout << i << endl;
  tailRecursivePrint(i - 1); // Tail call: last action
}

int main() {
  int n = 5;

  cout << "\nRecursive version:\n";
  tailRecursivePrint(n);

  cin.get();
  return 0;
}

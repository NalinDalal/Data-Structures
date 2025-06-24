#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

#define vi vector<int>
#define rep(i, a, b) for (int i = a; i < b; i++)

void printHeapAsTree(const vi &a) {
  int n = a.size();
  int level = 0;
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (count == 0) {
      cout << "\nLevel " << level << ": ";
      level++;
      count = 1 << (level - 1); // 2^(level-1)
    }
    cout << a[i] << " ";
    count--;
  }
  cout << "\n";
}

void heapify(vi &a, int n, int i) {
  int maxIdx = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  if (l < n && a[l] > a[maxIdx])
    maxIdx = l;
  if (r < n && a[r] > a[maxIdx])
    maxIdx = r;

  if (maxIdx != i) {
    swap(a[i], a[maxIdx]);
    heapify(a, n, maxIdx);
  }
}

void buildHeap(vi &a) {
  int n = a.size();
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(a, n, i);
  }
  cout << "\n🔧 After Building Max Heap:";
  printHeapAsTree(a);
}

void heapsort(vi &a) {
  int n = a.size();
  buildHeap(a);

  for (int i = n - 1; i > 0; i--) {
    swap(a[0], a[i]);
    cout << "\n📤 Swapped root with a[" << i << "]: ";
    printHeapAsTree(a);
    heapify(a, i, 0);
    cout << "🔄 After heapify:\n";
    printHeapAsTree(a);
  }
}

signed main() {
  int n;
  cout << "Enter number of elements: ";
  cin >> n;
  vi a(n);

  cout << "Enter elements:\n";
  rep(i, 0, n) cin >> a[i];

  heapsort(a);

  cout << "\n✅ Fin[48;52;178;1768;2848tal Sorted Array:\n";
  rep(i, 0, n) cout << a[i] << " ";
  cout << "\n";

  return 0;
}

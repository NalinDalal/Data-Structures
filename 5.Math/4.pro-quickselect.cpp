// 4.quickselect.cpp
// Quickselect — Las Vegas randomized algorithm
//
// Finds the k-th smallest element (1-indexed) in an unsorted array.
// Expected time: O(n)   Worst case: O(n^2) — but astronomically rare
//
// How it works:
//   1. Pick a random pivot x
//   2. Partition: left part has elements < x, right part has elements >= x
//   3. If left has exactly k-1 elements, x is the answer
//   4. If left has >= k elements, recurse on left
//   5. Otherwise recurse on right for (k - left_size - 1)-th smallest

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// Returns the k-th smallest element in arr[l..r] (0-indexed, k is 0-indexed)
int quickselect(vector<int> &arr, int l, int r, int k) {
  if (l == r)
    return arr[l];

  // Pick random pivot and move it to end
  int pivotIdx = l + rng() % (r - l + 1);
  swap(arr[pivotIdx], arr[r]);
  int pivot = arr[r];

  // Partition into [< pivot | >= pivot]
  int i = l;
  for (int j = l; j < r; j++) {
    if (arr[j] < pivot)
      swap(arr[i++], arr[j]);
  }
  swap(arr[i], arr[r]); // place pivot at its sorted position

  int leftSize = i - l;
  if (leftSize == k)
    return arr[i];
  else if (k < leftSize)
    return quickselect(arr, l, i - 1, k);
  else
    return quickselect(arr, i + 1, r, k - leftSize - 1);
}

// Wrapper: finds 1-indexed k-th smallest
int kthSmallest(vector<int> arr, int k) {
  return quickselect(arr, 0, arr.size() - 1, k - 1);
}

int main() {
  vector<int> arr = {7, 2, 10, 1, 4, 9, 3, 8, 6, 5};
  cout << "Array: ";
  for (int x : arr)
    cout << x << " ";
  cout << "\n\n";

  for (int k = 1; k <= (int)arr.size(); k++) {
    cout << "k=" << k << " -> " << kthSmallest(arr, k) << "\n";
  }

  // Verify by sorting
  vector<int> sorted_arr = arr;
  sort(sorted_arr.begin(), sorted_arr.end());
  cout << "\nSorted: ";
  for (int x : sorted_arr)
    cout << x << " ";
  cout << "\n";

  return 0;
}

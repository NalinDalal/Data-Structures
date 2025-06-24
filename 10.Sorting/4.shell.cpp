#include <iostream>
using namespace std;

template <class T> void Shellsort(T data[], int n) {
  register int i, j, hCnt, h;
  int increments[20], k;
  //  create an appropriate number of increments h
  for (h = 1, i = 0; h < n; i++) {
    increments[i] = h;
    h = 3 * h + 1;
  }
  // loop on the number of different increments h
  for (i--; i >= 0; i--) {
    h = increments[i];
    // loop on the number of subarrays h-sorted in ith pass
    for (hCnt = h; hCnt < 2 * h; hCnt++) {
      // insertion sort for subarray containing every hth element of
      for (j = hCnt; j < n;) { // array data
        T tmp = data[j];
        k = j;
        while (k - h >= 0 && tmp < data[k - h]) {
          data[k] = data[k - h];
          k -= h;
        }
        data[k] = tmp;
        j += h;
      }
    }
  }
}

int main() {
  int arr[] = {1, 2, 367, 35, 23, 356};
  int arr_size = sizeof(arr) / sizeof(arr[0]);
  Shellsort(arr, 6);

  for (int i = 0; i < arr_size; i++) {
    cout << arr[i] << " ";
  }
  return 0;
}

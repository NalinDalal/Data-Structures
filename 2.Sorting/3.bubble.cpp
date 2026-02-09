#include <iostream>
using namespace std;

template <class T> void bubblesort(T data[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = n - 1; j > i; --j) {
      if (data[j] < data[j - 1]) {
        swap(data[j], data[j - 1]);
      }
    }
  }
}

int main() {
  int arr[] = {1, 2, 367, 35, 23, 356};
  int arr_size = sizeof(arr) / sizeof(arr[0]);
  bubblesort(arr, 6);

  for (int i = 0; i < arr_size; i++) {
    cout << arr[i] << " ";
  }
  return 0;
}

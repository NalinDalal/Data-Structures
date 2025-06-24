#include <iostream>

using namespace std;

template <class T> void insertionsort(T data[], int n) {
  for (int i = 1, j; i < n; i++) {
    T tmp = data[i];
    for (j = i; j > 0 && tmp < data[j - 1]; j--)
      data[j] = data[j - 1];
    data[j] = tmp;
  }
}

int main() {
  cout << "Hello World";
  int arr[] = {1, 2, 367, 35, 23, 356};
  int arr_size = sizeof(arr) / sizeof(arr[0]);
  insertionsort(arr, 5);

  for (int i = 0; i < arr_size; i++) {
    cout << arr[i] << " ";
  }
  return 0;
}

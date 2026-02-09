#include <iostream>
using namespace std;

template <class T> void selectionsort(T data[], int n) {
  for (int i = 0, j, least; i < n - 1; i++) {
    for (j = i + 1, least = i; j < n; j++)
      if (data[j] < data[least])
        least = j;
    swap(data[least], data[i]);
  }
}

int main() {
  int arr[] = {1, 2, 367, 35, 23, 356};
  int arr_size = sizeof(arr) / sizeof(arr[0]);
  selectionsort(arr, 6);

  for (int i = 0; i < arr_size; i++) {
    cout << arr[i] << " ";
  }
  return 0;
}

#include <iostream>
using namespace std;

template <class T> void heapify(T arr[], int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && arr[left] > arr[largest])
    largest = left;

  if (right < n && arr[right] > arr[largest])
    largest = right;

  if (largest != i) {
    swap(arr[i], arr[largest]);
    heapify(arr, n, largest);
  }
}

template <class T> void heapsort(T arr[], int n) {
  // Build heap (rearrange array)
  for (int i = n / 2 - 1; i >= 0; --i) {
    heapify(arr, n, i);
  }

  // Extract elements from the heap one by one
  for (int i = n - 1; i > 0; --i) {
    swap(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
}

int main() {
  int arr[] = {1, 2, 367, 35, 23, 356};
  int arr_size = sizeof(arr) / sizeof(arr[0]);

  heapsort(arr, arr_size);

  cout << "Sorted array: ";
  for (int i = 0; i < arr_size; i++) {
    cout << arr[i] << " ";
  }

  return 0;
}

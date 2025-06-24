#include <iostream>

int main() {
  int n;
  std::cin >> n;

  int arr[n];
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }

  int maxNo = INT_MIN;
  int minNo = INT_MAX;

  for (int i = 0; i < n; i++) {
    /*	if(arr[i]>maxNo){
                    maxNo=arr[i];
            }
            if(arr[i]<minNo){
                    minNo=arr[i];
            }*/
    maxNo = fmax(maxNo, arr[i]);
    minNo = fmin(minNo, arr[i]);
  }

  std::cout << maxNo << " " << minNo;

  return 0;
}

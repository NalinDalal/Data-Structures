#include <iostream>
using namespace std;

int main() {
  int n;
  int arr[n];
  cout << "Enter no of elements in array:";
  cin >> n;
  // cout<<"Elements are:";
  // int arr[n];
  // for(i=0;i<=n-1;i++){
  //     cin>>arr[i];
  // }

  // cout<<arr[n]<<endl;

  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }

  cin.get();
}

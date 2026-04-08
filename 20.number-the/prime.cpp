// to check if N is prime or not
// instinctively, we will would do what, check all no from 2 to N and then
// divide N by them now if N is diviible, then it is not prime.
//
// But can we optimise this?
// go from 2 to sqrt(N)
// reason:
//       if N is divisible by d => N=d*N/d
//       if N/d < d => N/d or prime factor of N/d would have divided N
//       hence d, N/d <= sqrt(N) => O(sqrt(N))

#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0)
      cout << n + 'is not prime' << endl;
  }
  cout << n << 'is prime' << endl;
  return 0;
}

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void PlaceQueens(vector<int>& Q, int r, int n) {
    if (r == n + 1) {
        for (int i = 1; i <= n; i++)
            cout << Q[i] << " ";
        cout << endl;
    } else {
        for (int j = 1; j <= n; j++) {
            bool legal = true;
            for (int i = 1; i < r; i++) {
                if (Q[i] == j || Q[i] == j + r - i || Q[i] == j - r + i)
                    legal = false;
            }
            if (legal) {
                Q[r] = j;
                PlaceQueens(Q, r + 1, n);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;
    vector<int> Q(n + 1);
    PlaceQueens(Q, 1, n);
    return 0;
}
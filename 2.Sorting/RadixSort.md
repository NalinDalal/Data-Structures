# Radix Sort

**Idea**: Sort numbers digit by digit using counting sort as subroutine.
iterate through each digit of the number, grouping numbers by each digit.
Then, we sort each of these groupings by the next digit. 
We repeat this process sorting by each subsequent digit, until finally the whole array is sorted.


```
RADIX-SORT( A, d){
 for (i ←1 to d){
 do use a stable sort to sort array A on digit i
 }
}
```

**Time Complexity**: O(nk), where k = number of digits

```cpp
void countingSort(vector<int> &a, int exp) {
    int n = a.size();
    vector<int> output(n), count(10, 0);

    for (int i = 0; i < n; i++)
        count[(a[i]/exp)%10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i-1];
    for (int i = n-1; i >= 0; i--) {
        output[count[(a[i]/exp)%10]-1] = a[i];
        count[(a[i]/exp)%10]--;
    }
    a = output;
}

void radixSort(vector<int> &a) {
    int maxNum = *max_element(a.begin(), a.end());
    for (int exp = 1; maxNum / exp > 0; exp *= 10)
        countingSort(a, exp);
}
```

Radix Sort does what is apply sorting on the least significant digit first
process continues until the cards have
been sorted on all d digits

Given n d-digit numbers in which each digit can take on up to k possible values,
RADIX-SORT correctly sorts these numbers in Omega(d(n +k)) time.

Given n b-bit numbers and any positive integer r ≤ b, RADIX-SORT correctly
sorts these numbers in Omega((b/r)(n +2r )) time.



# Sorting Algorithms 

- [Insertion Sort](./InsertionSort.md)
- [Selection Sort](./SelectionSort.md)
- [Bubble Sort](./BubbleSort.md)
- [Shell Sort](./ShellSort.md)
- [Heap Sort](./HeapSort.md)
- [Quick Sort](./QuickSort.md)
- [Merge Sort](./MergeSort.md)
- [Radix Sort (for non-negative integers)](./RadixSort.md)
- [COunting Sort](./CountingSort.md)

minimum possible number of steps in a sorting algorithm in the worst case is at least nlogn.

## Summary Table

| Algorithm      | Best       | Average    | Worst      | Space    |
| -------------- | ---------- | ---------- | ---------- | -------- |
| Insertion Sort | O(n)       | O(n²)      | O(n²)      | O(1)     |
| Selection Sort | O(n²)      | O(n²)      | O(n²)      | O(1)     |
| Bubble Sort    | O(n)       | O(n²)      | O(n²)      | O(1)     |
| Shell Sort     | O(n log n) | \~O(n^1.5) | O(n²)      | O(1)     |
| Heap Sort      | O(n log n) | O(n log n) | O(n log n) | O(1)     |
| Quick Sort     | O(n log n) | O(n log n) | O(n²)      | O(log n) |
| Merge Sort     | O(n log n) | O(n log n) | O(n log n) | O(n)     |
| Radix Sort     | O(nk)      | O(nk)      | O(nk)      | O(n+k)   |

---

## Tip:

Use:

- Insertion/Selection/Bubble for small or almost sorted arrays
- Merge/Heap for stable sorting
- QuickSort for average fast sorting
- Radix for non-comparative digit-based sort

---

## InBuilt Functions

many benefits in using a library function.

1. It saves time because there is no need to implement the function.
2. The library implementation is certainly correct and efficient: it is not probable that a home-made sorting function would be better.

```cpp
vector<int> v = {4,2,5,3,5,8,3};
sort(v.begin(),v.end());    //[2,3,3,4,5,5,8]
```

reverse order:

```cpp
vector<int> v = {4,2,5,3,5,8,3};
sort(v.rbegin(),v.rend());  //[8,5,5,4,3,3,2]
```

sorting an ordinary array:

```cpp
int n = 7; // array size
int a[] = {4,2,5,3,5,8,3};
sort(a,a+n);
```

sorting a string:

```cpp
string s = "monkey";
sort(s.begin(), s.end());   //ekmnoy
```

---

## Comparison Operator

Used to find order of two elements while sorting.

ex: numbers are sorted according to their values and strings are sorted in alphabetical order.

Pairs (pair) are sorted primarily according to their first elements (first).
However, if the first elements of two pairs are equal, they are sorted according to their second elements (second):

```cpp
vector<pair<int,int>> v;
v.push_back({1,5});
v.push_back({2,3});
v.push_back({1,2});
sort(v.begin(), v.end());   //(1,2), (1,5) and (2,3)
```

Tuple are sorted primarily by the first element,
secondarily by the second element, etc.

```cpp
vector<tuple<int,int,int>> v;
v.push_back({2,1,4});
v.push_back({1,5,3});
v.push_back({2,1,3});
sort(v.begin(), v.end());   //(1,5,3), (2,1,3) and (2,1,4)
```

## Comparison Functions

give an external comparison function to the sort function as a callback function.
sorts strings primarily by length and secondarily by alphabetical order:

```cpp
bool comp(string a, string b) {
if (a.size() != b.size()) return a.size() < b.size();
return a < b;
}
```

sort vector of strings:

```cpp
sort(v.begin(), v.end(), comp);
```

## User Defined Structs

don't have comparison operator automatically.
operator should be defined inside the struct as a function operator<, whose parameter is another element of the same type.
operator return true if element<parameter, false otherwise

```
if(element<parameter){
return true;
}else{return false;}
```

```cpp
struct P {
    int x, y;
    bool operator<(const P &p) {
        if (x != p.x) return x < p.x;
        else return y < p.y;
    }
};
```

---

## Sorting in Linear Time

Comparison sorts can be viewed abstractly in terms of decision trees. A decision
tree is a full binary tree that represents the comparisons between elements that
are performed by a particular sorting algorithm operating on an input of a given
size.

### Lower Bound for Worst Case

Any comparison sort algorithm requires Omega(n lg n) comparisons in the worst case.

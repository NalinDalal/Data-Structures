##  1. What is Recursion?

> **Recursion** is a method of solving a problem where a function calls itself.

u solve them by breaking 1 big problem into multiple small problems
then you merge them recursively to get final solution

Reducing one problem X to another problem Y means to write an algorithm
for X that uses an algorithm for Y as a black box or subroutine

powerful kind of reduction:
- if can be solved directly, solve it
- else reduce to more simpler instance of same problem

Every recursive function must have:

- **Base Case** → Stops recursion
- **Recursive Case** → Reduces problem into smaller subproblems

3 approaches:  bottom-up, top-down, and half-and-half.

Bottom Up: like for 1, then for 2, then goes to whole
build the solution for one case off of the previous case

Top Down: divide the problem for case N into subproblems.

Half-Half: like break down into half to solve

recursion is very much space inefficient
each step adds up a new memeory layer of O(n) complexity

hence efficient to implement iteratively

---


## 2. Recursive Flow – Dry Run Diagram

```mermaid
graph TD;
    Start["Start: factorial(3)"];
    Start --> F2["factorial(2)"];
    F2 --> F1["factorial(1)"];
    F1 --> Base["Base Case: return 1"];
    Base --> Back1["Return: 1 * 1 = 1"];
    Back1 --> Back2["Return: 2 * 1 = 2"];
    Back2 --> Back3["Return: 3 * 2 = 6"];

```

each node gives out 2 child, hence for n node it will be $2^n$ nodes

T (n) = r T (n/c) + f (n).
each node at depth d contains the value f (n/pow(c,d)).

---

## 3. Types of Recursion

| Type                   | Description                                  |
| ---------------------- | -------------------------------------------- |
| **Tail Recursion**     | Recursive call is the last statement         |
| **Head Recursion**     | Recursive call happens before any processing |
| **Tree Recursion**     | Function calls itself multiple times         |
| **Indirect Recursion** | Function A → B → A                           |
| **Nested Recursion**   | Recursive call within a recursive call       |

---

## 4. General Recursive Template

```cpp
returnType func(params) {
    if (base case) return base_value;

    // Processing
    result = func(smaller_input);

    // Combine and return
    return something_using(result);
}
```

---

## 5. Standard Recursive Algorithms

### 1. Factorial (n!)

**Algorithm:**

1. Base case: if n == 0 → return 1
2. Else: return n \* factorial(n - 1)

```
fact(n){
    if(n>1) fact(n-1)*n;
    else return 1;
}
```

---

### 2. Fibonacci(n)

**Algorithm:**

1. Base: 
    if n == 0 return 0
    if n == 1 return 1
2. Else: 
    fib(n - 1) + fib(n - 2)

```mermaid
graph TD;
    F5["Fib(5)"] --> F4["Fib(4)"];
    F4["Fib(4)"] --> F3a["Fib(3)"];
    F3a["Fib(3)"] --> F2a["Fib(2)"];
    F2a["Fib(2)"] --> F1a["Fib(1)"];
    F2a["Fib(2)"] --> F0a["Fib(0)"];
    F3a["Fib(3)"] --> F1b["Fib(1)"];
    F4["Fib(4)"] --> F2b["Fib(2)"];
    F5["Fib(5)"] --> F3b["Fib(3)"];
```


```
recursion(n){
    if(i==0 || i==1)return 1;
    else recursion(n-1)+recursion(n-2);
}
```

directly shoots down n depth tree
each node has 2 child, so 2n children in total
O(n) linear runtime

use bottom up dynamic programming approach
we already know `fib(1)` and `fib(0)`, hence can easily find `fib(2)`, `fib(3)` etc
```
recursionBottomUp(n){

}
```

it's like a,b

---

### 3. Power (a^b)

**Algorithm:**

1. Base: if b == 0 → return 1
2. Return a \* power(a, b - 1)

**Pingala Algorithm:**

$$
a^n = \begin{cases} 1 & \text{if } n = 0 \\ (a^{n/2})^2 & \text{if } n > 0 \text{ and } n \text{ is even} \\ (a^{\lfloor n/2 \rfloor})^2 \cdot a & \text{otherwise} \end{cases}
$$

```
PingalaPower(a, n):
    if n = 1
        return a
    else
        x ←Pi˙ ngalaPower(a, ⌊n/2⌋)
        if n is even
            return x·x
        else
            return x·x·a
```

T (n) <= T (n/2) + 2.
T (n) = O(log n)

---

### 4. Print Numbers from N to 1

**Algorithm:**

1. Base: if n == 0 return
2. Print n
3. Call function with n - 1

---

### 5. Print 1 to N

**Algorithm:**

1. Base: if n == 0 return
2. Call with n - 1
3. Then print n

---

### 6. Sum of First N Numbers

**Algorithm:**

1. Base: if n == 0 return 0
2. Return n + sum(n - 1)

---

### 7. Reverse an Array

**Algorithm:**

1. Base: if start >= end → return
2. Swap arr\[start], arr\[end]
3. Call reverse(arr, start+1, end-1)

---

### 8. Check Palindrome (String)

**Algorithm:**

1. Base: if left >= right → return true
2. If str\[left] != str\[right] → return false
3. Call with (left+1, right-1)

---

### 9. Binary Search (Recursive)

**Algorithm:**

1. Base: if low > high → not found
2. mid = (low + high)/2
3. If arr\[mid] == key → return mid
4. If key < arr\[mid] → search in left
5. Else → search in right

---

### 10. Permutations (Backtracking + Recursion)

**Algorithm:**

1. If idx == n → store current permutation
2. Loop from idx to n:

   - Swap i with idx
   - Call permute(idx+1)
   - Backtrack: swap again

---

### 11. MergeSort

1. Divide the input array into two subarrays of roughly equal size.
2. Recursively mergesort each of the subarrays.
3. Merge the newly-sorted subarrays into a single sorted array.

merge algo is also recursive:
identify the first element of the output array, and then 
recursively merge the rest of the input arrays.

```
MergeSort(A[1 .. n]):
    if n >1
        m ←⌊n/2⌋
        MergeSort(A[1 .. m]) 〈〈Recurse!〉〉
        MergeSort(A[m + 1 .. n]) 〈〈Recurse!〉〉
        Merge(A[1 .. n], m)

Merge(A[1 .. n], m):
    i ←1; j ←m + 1
    for k ←1 to n
        if j >n
            B[k] ←A[i]; i ←i + 1
        else if i >m
            B[k] ←A[ j]; j ←j + 1
        else if A[i] <A[ j]
            B[k] ←A[i]; i ←i + 1
        else
            B[k] ←A[ j]; j ←j + 1
    
    for k ←1 to n
        A[k] ←B[k]
```

Time: T(n)=T(ceil(n/2))+T(floor(n/2))+O(n)
        T(n)=2T(n/2)+O(n)
        T(n)=O(nlog n)

---

### 12. Quicksort
hard work is to split the array into smaller subarrays before recursion, so that merging the sorted subarrays is trivial.

1. Choose a pivot element from the array.
2. Partition the array into three subarrays containing the elements smaller than the pivot, the pivot element itself, and the elements larger than the pivot.
3. Recursively quicksort the first and last subarrays.

```
QuickSort(A[1 .. n]):
    if (n >1)
        Choose a pivot element A[p]
        r ←Partition(A, p)
        QuickSort(A[1 .. r−1]) 〈〈Recurse!〉〉
        QuickSort(A[r + 1 .. n]) 〈〈Recurse!〉〉

Partition(A[1 .. n], p):
    swap A[p] ↔A[n]
    ℓ←0 〈〈#items <pivot〉〉
    for i ←1 to n−1
        if A[i] <A[n]
            ℓ←ℓ+ 1
            swap A[ℓ] ↔A[i]
    swap A[n] ↔A[ℓ+ 1]
    return ℓ+ 1
```

Time: T (n) = T (r−1) + T (n−r) + O(n)

r=ceil(n/2)
T(n)=T(ceil(n/2)-1)+T(floor(n/2))+O(n)
    <=2T(n/2)+O(n)

T(n)=O(n log n)

since r can go from 1 to n

T(n)=max(T(r-1)+T(n-r)+O(n)) {1<=r<=n}
worst case: r=1 and r=n
 T (n) <=T (n−1) + O(n).

T(n)=O(n^2)


-----

## 6. Tail vs Head Recursion (Comparison)

| Feature        | Head Recursion | Tail Recursion           |
| -------------- | -------------- | ------------------------ |
| Recursive Call | First          | Last                     |
| Stack Usage    | More           | Less (can optimize)      |
| Example        | fib(n), sum(n) | print(n to 1), factorial |

---

## 7. Debugging Tips

- Always write the **base case first**
- Print before & after recursive calls
- Use call stack trace mentally or on paper

---

## 8. Tower of Hanoi
3 tower A,B,C, with n discs of different sizes
now all dics are at tower A, need to move thm to tower C
no disc maybe placed on top of a disc smaller than itself

break into sub problems:
1. Move n− 1 discs from peg A to peg B using peg C as the intermediate peg.
After this recursive step is done, we are left with disc n by itself in peg A.
2. Move disc n from peg A to peg C.
3. Move n− 1 discs from peg B to peg C using peg A as the intermediate peg.
These n− 1 discs will be on top of disc n which is now at the bottom of peg C.

```cpp
#include <cstdio>
using namespace std;
void solve(int count, char source, char destination, char intermediate) {
    if (count == 1)
        printf("Move top disc from pole %c to pole %c\n", source, destination);
    else {
        solve(count-1, source, intermediate, destination);
        solve(1, source, destination, intermediate);
        solve(count-1, intermediate, destination, source);
    }
}

int main() {
    solve(3, ’A’, ’C’, ’B’);
    return 0;
}
```

Algorithms- JeffE: 39-88
programming-interview: 104-128(pdf)

to read on 18.02

##  1. What is Recursion?

> **Recursion** is a method of solving a problem where a function calls itself.

Every recursive function must have:

- **Base Case** → Stops recursion
- **Recursive Case** → Reduces problem into smaller subproblems

u solve them by breaking 1 big problem into multiple small problems
then you merge them recursively to get final solution

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
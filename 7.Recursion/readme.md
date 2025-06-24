### 🔥 1. What is Recursion?

> **Recursion** is a method of solving a problem where a function calls itself.

Every recursive function must have:

- **Base Case** → Stops recursion
- **Recursive Case** → Reduces problem into smaller subproblems

---

### 🧠 2. Recursive Flow – Dry Run Diagram

```mermaid
graph TD
    Start[Start: factorial(3)]
    Start --> F2[factorial(2)]
    F2 --> F1[factorial(1)]
    F1 --> Base[Base Case: return 1]
    Base --> Back1[Return: 1 * 1 = 1]
    Back1 --> Back2[Return: 2 * 1 = 2]
    Back2 --> Back3[Return: 3 * 2 = 6]
```

---

### 🧩 3. Types of Recursion

| Type                   | Description                                  |
| ---------------------- | -------------------------------------------- |
| **Tail Recursion**     | Recursive call is the last statement         |
| **Head Recursion**     | Recursive call happens before any processing |
| **Tree Recursion**     | Function calls itself multiple times         |
| **Indirect Recursion** | Function A → B → A                           |
| **Nested Recursion**   | Recursive call within a recursive call       |

---

### ⚙️ 4. General Recursive Template

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

## 🔁 5. Standard Recursive Algorithms

---

### 1️⃣ Factorial (n!)

**Algorithm:**

1. Base case: if n == 0 → return 1
2. Else: return n \* factorial(n - 1)

---

### 2️⃣ Fibonacci(n)

**Algorithm:**

1. Base: if n == 0 return 0, if n == 1 return 1
2. Else: fib(n - 1) + fib(n - 2)

```mermaid
graph TD
    F5[Fib(5)] --> F4[Fib(4)] --> F3a[Fib(3)] --> F2a[Fib(2)] --> F1a[Fib(1)]
    F2a --> F0a[Fib(0)]
    F3a --> F1b[Fib(1)]
    F4 --> F2b[Fib(2)]
    F5 --> F3b[Fib(3)]
```

---

### 3️⃣ Power (a^b)

**Algorithm:**

1. Base: if b == 0 → return 1
2. Return a \* power(a, b - 1)

---

### 4️⃣ Print Numbers from N to 1

**Algorithm:**

1. Base: if n == 0 return
2. Print n
3. Call function with n - 1

---

### 5️⃣ Print 1 to N

**Algorithm:**

1. Base: if n == 0 return
2. Call with n - 1
3. Then print n

---

### 6️⃣ Sum of First N Numbers

**Algorithm:**

1. Base: if n == 0 return 0
2. Return n + sum(n - 1)

---

### 7️⃣ Reverse an Array

**Algorithm:**

1. Base: if start >= end → return
2. Swap arr\[start], arr\[end]
3. Call reverse(arr, start+1, end-1)

---

### 8️⃣ Check Palindrome (String)

**Algorithm:**

1. Base: if left >= right → return true
2. If str\[left] != str\[right] → return false
3. Call with (left+1, right-1)

---

### 9️⃣ Binary Search (Recursive)

**Algorithm:**

1. Base: if low > high → not found
2. mid = (low + high)/2
3. If arr\[mid] == key → return mid
4. If key < arr\[mid] → search in left
5. Else → search in right

---

### 🔂 10. Permutations (Backtracking + Recursion)

**Algorithm:**

1. If idx == n → store current permutation
2. Loop from idx to n:

   - Swap i with idx
   - Call permute(idx+1)
   - Backtrack: swap again

---

## 🧵 6. Tail vs Head Recursion (Comparison)

| Feature        | Head Recursion | Tail Recursion           |
| -------------- | -------------- | ------------------------ |
| Recursive Call | First          | Last                     |
| Stack Usage    | More           | Less (can optimize)      |
| Example        | fib(n), sum(n) | print(n to 1), factorial |

---

## 🔍 7. Debugging Tips

- Always write the **base case first**
- Print before & after recursive calls
- Use call stack trace mentally or on paper

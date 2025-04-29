### Binary Storage & Bit Manipulation Cheatsheet

- **RAM has a threshold**:  
  - Above threshold → stores data  
  - Below threshold → doesn’t  
- Data is stored in **binary format**

---

### Binary Representation of Integers

```
0 -> 00  
1 -> 01  
2 -> 10  
3 -> 11  
4 -> 100  
5 -> 101  
6 -> 110  
```

---

### Integer in Memory (Example)

```cpp
int a = 5;  // int is 4 bytes = 32 bits
```

Binary representation of `a` in memory:

```
0000 0101 0000 0000 0000 0000 0000 0000
```

- **LSB (Least Significant Bit)** → Leftmost part → Lower memory address  
- **MSB (Most Significant Bit)** → Rightmost part → Higher memory address  

---

### Bit Shifting

#### Left Shift (`<<`)

```cpp
0101 << 1
```

→ Shifts 1 bit to the left  
Result:
```
1010
```

Left shift multiplies by power of two:

```
a << n  →  a * 2ⁿ
```

#### Right Shift (`>>`)

```cpp
0101 >> 1
```

→ Shifts 1 bit to the right  
Result:
```
0010
```

Right shift divides by power of two:

```
a >> n  →  a / 2ⁿ
```

---

### Bitwise Operators

| Operator | Name  | Description         |
|----------|-------|---------------------|
| `&`      | AND   | Both bits must be 1 |
| `|`      | OR    | Either bit is 1     |
| `^`      | XOR   | Bits must differ    |
| `~`      | NOT   | Inverts the bits    |

#### AND (`&`)

```
0 & 0 → 0  
0 & 1 → 0  
1 & 0 → 0  
1 & 1 → 1
```

#### OR (`|`)

```
0 | 0 → 0  
0 | 1 → 1  
1 | 0 → 1  
1 | 1 → 1
```

#### XOR (`^`)

```
0 ^ 0 → 0  
0 ^ 1 → 1  
1 ^ 0 → 1  
1 ^ 1 → 0
```

#### NOT (`~`)

```
~1 → 0  
~0 → 1
```

---

### Bit Masking – Checking Specific Bit

Say you want to check the **5th bit** (from the rightmost, 0-indexed):

Given number:

```
10100101
```

Bit mask for 5th bit:

```
00010000  // Only 5th bit is 1
```

Apply AND:

```
  10100101
& 00010000
-----------
  00000000  → 5th bit is not set
```

If result ≠ 0 → bit is **set**  
If result = 0 → bit is **not set**

Another example:

| Binary      | Bit Pos | Mask       | Result (Decimal) |
|-------------|---------|------------|------------------|
| 00100101    | 5th     | 00010000   | 32               |

---

### Bit Tricks & Patterns

#### ✅ Toggle K-th Bit:
```cpp
num ^ (1 << k)
```

#### ✅ Set K-th Bit:
```cpp
num | (1 << k)
```

#### ✅ Clear K-th Bit:
```cpp
num & ~(1 << k)
```

#### ✅ Check K-th Bit:
```cpp
(num >> k) & 1  // 0-based
```
or
```cpp
(num & (1 << k)) != 0
```

---

### Power of 2 Check

```cpp
(n > 0) && ((n & (n - 1)) == 0)
```

- Works because power of 2 numbers have only **one set bit**
- `8 & 7 = 1000 & 0111 = 0000` → Valid

---

### Isolate Lowest Set Bit

```cpp
x & -x
```

Example:
```cpp
int x = 12; // 1100
x & -x = 0100 → 4
```

---

### Swapping Two Integers Using XOR

```cpp
a ^= b;
b ^= a;
a ^= b;
```

- No temp variable needed
- Works only on integer types

`x & ~1` guarantees an `even number output` for any integer x
---

### Fixed-size Arrays in C++

- **Do not resize dynamically**
- **Accessed via integer index**
- **Stored in contiguous memory**

---

### Increment - Decrement

```cpp
x++  // use then increase  
++x  // increase then use
```

`post`: use then operate  
`pre`: operate then use

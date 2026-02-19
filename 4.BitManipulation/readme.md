# Binary Storage & Bit Manipulation Cheatsheet

an n bit integer is internally stored as a binary number that
consists of n bits.

`43`:`00000000000000000000000000101011`

- **RAM has a threshold**:  
  - Above threshold → stores data  
  - Below threshold → doesn’t  
- Data is stored in **binary format**

bits in the representation are indexed from right to left (the rightmost bit is the least significant bit, index 0).

To convert a bit representation $b_k\dots b_2 b_1 b_0$ into a number, use the formula

$$
\sum_{i=0}^{k} b_i\,2^i = b_k 2^k + \dots + b_2 2^2 + b_1 2^1 + b_0 2^0.
$$

For example, the 6-bit binary number `101011` corresponds to

$$
1\cdot 2^5 + 0\cdot 2^4 + 1\cdot 2^3 + 0\cdot 2^2 + 1\cdot 2^1 + 1\cdot 2^0 = 32 + 0 + 8 + 0 + 2 + 1 = 43.
$$


---

# Binary Representation of Integers

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

# Integer in Memory (Example)

```cpp
int a = 5;  // int is 4 bytes = 32 bits
```

computers store digits in form of 2's complement of N-bit number

A positive number is represented as itself while 
a negative number is represented as the two's complement of its absolute value (with a 1 in its sign bit to indicate that a negative value)

Binary representation of `a` in memory:

```
0000 0101 0000 0000 0000 0000 0000 0000
```

- **LSB (Least Significant Bit)** → Leftmost part → Lower memory address  
- **MSB (Most Significant Bit)** → Rightmost part → Higher memory address  

the binary representation of -K (negative K) as a N-bit number is concat(l, pow(2,N)- K).

---

# Bitwise Operators

| Operator | Name  | Description         |
|----------|-------|---------------------|
| `&`      | AND   | Both bits must be 1 |
| \|      | OR    | Either bit is 1     |
| `^`      | XOR   | Bits must differ    |
| `~`      | NOT   | Inverts the bits    |

## AND (`&`)

It produces a number that has one bits in positions where both x and y have one bits.

```
0 & 0 → 0  
0 & 1 → 0  
1 & 0 → 0  
1 & 1 → 1
```

## OR (`|`)

produces a number that has one bits in positions where at least one of x and y have one bits.

```
0 | 0 → 0  
0 | 1 → 1  
1 | 0 → 1  
1 | 1 → 1
```

## XOR (`^`)

produces a number that has one bits in positions where exactly one of x and y have one bits

```
0 ^ 0 → 0  
0 ^ 1 → 1  
1 ^ 0 → 1  
1 ^ 1 → 0
```

## NOT (`~`)

produces a number where all the bits of x have been inverted.

```
~1 → 0  
~0 → 1
```
```
~x = −x− 1 
```

---

# Bit Shifting

## Left Shift (`<<`)

`x << k` appends k zero bits to the number

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

## Right Shift (`>>`)

In an arithmetic right shift, we shift values to the right but fill in the new bits with the value of the sign bit.
This has the effect of {roughly) dividing by two. It is indicated by a `>>` operator.

` x >> k` removes the k last bits from the number


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

# Bit Tricks & Patterns

##  Toggle K-th Bit:
```cpp
num ^ (1 << k)
```

##  Set K-th Bit:
```cpp
num | (1 << k)
```

##  Clear K-th Bit:

we create a number like 11101111 by creating the reverse of it (00010000) and negating it. 
Then, we perform an AND with num. This will clear the ith bit and leave the remainder unchanged.

```cpp
num & ~(1 << k)
```

##  Check K-th Bit:

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

**Alt:**

shifts 1 over by i bits
By performing an AND with num, we clear all bits other than the bit at bit i.


```cpp
(num >> k) & 1  // 0-based
```

```cpp
boolean getBit( int num, int i) {
 return ((num & (1 << i ) ) != 0 ) ;
}
```

or
```cpp
(num & (1 << k)) != 0
```

---

# Power of 2 Check

```cpp
(n > 0) && ((n & (n - 1)) == 0)
```

- Works because power of 2 numbers have only **one set bit**
- `8 & 7 = 1000 & 0111 = 0000` → Valid

---

# Isolate Lowest Set Bit

```cpp
x & -x
```

Example:
```cpp
int x = 12; // 1100
x & -x = 0100 → 4
```

---

# Swapping Two Integers Using XOR

```cpp
a ^= b;
b ^= a;
a ^= b;
```

- No temp variable needed
- Works only on integer types

`x & ~1` guarantees an `even number output` for any integer x

---

# Increment - Decrement

```cpp
x++  // use then increase  
++x  // increase then use
```

`post`: use then operate  
`pre`: operate then use

---

# To set the ith bit to a value v:
1. clear the bit at position i by using a mask that looks like 11101111,
2. we shift the intended value, v, left by i bits
3. create a number with bit i equal to v and all other bits equal to 0
4. Finally, we OR these two numbers, updating the i t h bit if v is 1 and leaving it as 0 otherwise.

```cpp
int updateBit(int num, int i, boolean bit|s| ) {
 int value = bit|s| ? 1 : 8;
 int mask = ~(1 << i ) ;
 return (num & mask) | (value << i ) ;
}
```

---

## In Built Functions
The g++ compiler provides the following functions for counting bits:
- `__builtin_clz(x)`: the number of zeros at the beginning of the number
- `__builtin_ctz(x)`: the number of zeros at the end of the number
- `__builtin_popcount(x)`: the number of ones in the number
- `__builtin_parity(x)`: the parity (even or odd) of the number of ones

---

# Operations based on Bit Manipulation
The following code goes through the subsets of {0,1,...,n− 1}:
```cpp
for (int b = 0; b < (1<<n); b++) {
  // process subset b
}
```

The following code goes through the subsets with exactly k elements:
```cpp
for (int b = 0; b < (1<<n); b++) {
  if (__builtin_popcount(b) == k) {
    // process subset b
  }
}
```

The following code goes through the subsets of a set x:
```cpp
int b = 0;
do {
  // process subset b
} while (b=(b-x)&x);
```

----

# Optimisations

## Hamming Distance
`hamming(a,b)` between two strings a and b of equal length is the number of positions where the strings differ. 
For example, 
`hamming(01101,11001)= 2.`

```cpp
int hamming(string a, string b) { //O(k*n^2)
  int d = 0;
  for (int i = 0; i < k; i++) {
    if (a[i] != b[i]) d++;
  }
  return d;
}
```

but if `k<=32`

```cpp
int hamming(int a, int b) {
  return __builtin_popcount(a^b);
}
```
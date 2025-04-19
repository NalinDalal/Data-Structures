### Binary Storage & Bit Manipulation Cheatsheet

- **RAM has a threshold**:  
  - Above threshold → stores data  
  - Below threshold → doesn’t  
- Data is stored in **binary format**

#### Binary Representation of Integers

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

| Operator | Name  | Description     |
|----------|-------|-----------------|
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
```

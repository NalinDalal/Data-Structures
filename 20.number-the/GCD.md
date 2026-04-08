# Greatest Common Divisor

Greatest Common Divisor refers to the number that divides both given arguments.

$$\text{gcd}(a,b)$$

Consider:
$$a = p_1^{e_1} \cdot p_2^{e_2} \cdot p_3^{e_3} \cdots p_r^{e_r}$$
$$b = p_1^{f_1} \cdot p_2^{f_2} \cdot p_3^{f_3} \cdots p_r^{f_r}$$

Then:
$$\text{gcd}(a,b) = p_1^{\min(e_1, f_1)} \cdot p_2^{\min(e_2, f_2)} \cdots p_r^{\min(e_r, f_r)}$$

For any non-negative integer $a$ and positive integer $b$:
$$\text{gcd}(a,b) = \text{gcd}(b, a \bmod b)$$

## Euclid's Algorithm

```
EUCLID(a, b):
    if b = 0
        return a
    else
        return EUCLID(b, a mod b)
```

Running time is proportional to number of recursive calls.

## Theorem

If $(a > b \geq 1)$, calling $\text{EUCLID}(a,b)$ performs $k \geq 1$ recursive calls, then:
$$a \geq F_{k+2} \text{ and } b \geq F_{k+1}$$

$$F_{k+1} \bmod F_k = F_{k-1}$$

$$\text{gcd}(F_{k+1}, F_k) = \text{gcd}(F_k, F_{k-1})$$

## Implementation

```cpp
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
```

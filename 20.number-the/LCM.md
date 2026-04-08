# Least Common Multiple

Least Common Multiple refers to the smallest positive integer that is divisible by both given arguments.

$$\text{lcm}(a,b)$$

Consider:
$$a = p_1^{e_1} \cdot p_2^{e_2} \cdot p_3^{e_3} \cdots p_r^{e_r}$$
$$b = p_1^{f_1} \cdot p_2^{f_2} \cdot p_3^{f_3} \cdots p_r^{f_r}$$

Then:
$$\text{lcm}(a,b) = p_1^{\max(e_1, f_1)} \cdot p_2^{\max(e_2, f_2)} \cdots p_r^{\max(e_r, f_r)}$$

## Relationship between GCD and LCM

$$\text{gcd}(a,b) \times \text{lcm}(a,b) = |a \times b|$$

For any non-negative integer $a$ and positive integer $b$:
$$\text{lcm}(a,b) = \frac{a \times b}{\text{gcd}(a,b)}$$

## Implementation

```cpp
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}
```

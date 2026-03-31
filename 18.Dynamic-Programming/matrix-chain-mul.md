# Matrix Chain Multiplication

We are given a sequence (chain) of matrices  
\<A₁, A₂, …, Aₙ\> and we want to compute the product:

A₁A₂…Aₙ

Matrix multiplication is **associative**, meaning:

(A₁A₂)A₃ = A₁(A₂A₃)

However, the **order of parenthesization affects the total number of scalar multiplications**, even though the final result matrix remains the same.

Goal:
Find the most efficient way to parenthesize the product so that the **total computation cost is minimized**.

---

## Valid Matrix Multiplication Condition

If:


A is a p × q matrix  
B is a q × r matrix  

Then:

C = A × B is a p × r matrix  

Constraint:
Number of columns of A must equal number of rows of B.

---

## Standard Matrix Multiplication Algorithm

```

matrixMultiply(A,B){
if(A.columns != B.rows)
    error("incompatible dimensions")

else
    for(i=1 to A.rows){
        for(j=1 to B.columns){
            C[i][j]=0
            for(k=1 to A.columns){
                C[i][j] = C[i][j] + (A[i][k] * B[k][j])
            }
        }
    }

}
```


Time Complexity:
O(p × q × r)

---

## Number of Ways to Parenthesize

For n matrices, the number of possible full parenthesizations is:

Catalan(n−1)

Example:

\<A₁ A₂ A₃ A₄\> can be parenthesized in 5 ways:

1. (A₁(A₂(A₃A₄)))
2. (A₁((A₂A₃)A₄))
3. ((A₁A₂)(A₃A₄))
4. ((A₁(A₂A₃))A₄)
5. (((A₁A₂)A₃)A₄)

Each order may require a different number of scalar multiplications.

---

## Matrix Chain Multiplication Problem

Given matrices A₁, A₂, …, Aₙ where matrix Aᵢ has dimension:

pᵢ₋₁ × pᵢ

Find the optimal parenthesization that minimizes:

Number of scalar multiplications.

---

## Dynamic Programming Formulation

Let:

`m[i,j]` = minimum number of multiplications needed to compute Aᵢ…Aⱼ

If i = j:

`m[i,i]` = 0

If i < j:

`m[i,j]` = min over i ≤ k < j of:

`m[i,k] + m[k+1,j] + pᵢ₋₁ pₖ pⱼ`

---

## Algorithm (Dynamic Programming)

```

MatrixChainOrder(p[], n):

for i = 1 to n:
    m[i,i] = 0

for L = 2 to n:          // chain length
    for i = 1 to n-L+1:
        j = i + L - 1
        m[i,j] = ∞

        for k = i to j-1:
            cost = m[i,k] 
                   + m[k+1,j] 
                   + p[i-1]*p[k]*p[j]

            if cost < m[i,j]:
                m[i,j] = cost

return m[1,n]
```
```

```

Time Complexity: $O(n^{3})$

Space Complexity: $O(n^{2})$

---

## Example

Matrices:

A₁ = 10×30  
A₂ = 30×5  
A₃ = 5×60  

Two possible parenthesizations:

1. (A₁A₂)A₃

Cost:
(10×30×5) + (10×5×60)
= 1500 + 3000
= 4500

2. A₁(A₂A₃)

Cost:
(30×5×60) + (10×30×60)
= 9000 + 18000
= 27000

Optimal:
(A₁A₂)A₃ with 4500 multiplications.

---

# Strassen's Algorithm for Multiplication

Strassen's algorithm applies divide-and-conquer to multiply two n×n matrices.

Assume n is a power of two. Partition A and B into four n/2×n/2 blocks:

$$
A=\begin{pmatrix}a & b\\ c & d\end{pmatrix},\qquad
B=\begin{pmatrix}e & f\\ g & h\end{pmatrix},\qquad
C=AB=\begin{pmatrix}r & s\\ t & u\end{pmatrix}.
$$

Naive divide-and-conquer:

$$
r = ae + bg,\qquad
s = af + bh,\qquad
t = ce + dg,\qquad
u = cf + dh
$$

Recurrence:

T(n) = 8T(n/2) + Θ(n²)

Complexity:

Θ(n³)

---

## Strassen Optimization (7 Multiplications)

Instead of 8 recursive multiplications, Strassen computes 7:

$$
\begin{aligned}
P_1 &= a(f-h) \\
P_2 &= (a+b)h \\
P_3 &= (c+d)e \\
P_4 &= d(g-e) \\
P_5 &= (a+d)(e+h) \\
P_6 &= (b-d)(g+h) \\
P_7 &= (a-c)(e+f)
\end{aligned}
$$

Final submatrices:

$$
\begin{aligned}
r &= P_5 + P_4 - P_2 + P_6 \\
s &= P_1 + P_2 \\
t &= P_3 + P_4 \\
u &= P_5 + P_1 - P_3 - P_7
\end{aligned}
$$

Recurrence:

T(n) = 7T(n/2) + Θ(n²)

Complexity:

Θ(n^{log₂7}) ≈ Θ(n^{2.81})

---

## Comparison

| Method | Complexity | Idea |
|-------|-----------|------|
| Standard Multiplication | O(n³) | triple nested loop |
| Divide & Conquer | O(n³) | 8 recursive multiplications |
| Strassen Algorithm | O(n^{2.81}) | reduces multiplications to 7 |
| Matrix Chain Multiplication | O(n³) | optimal parenthesization |

---

## Key Insight

Matrix Chain Multiplication:
optimizes order of multiplication.

Strassen:
optimizes how multiplication itself is computed.

Both reduce computation cost for large matrix problems.

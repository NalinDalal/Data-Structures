
# Combinatorics
the study of countable discrete structures.

## Fib No
$$fib(0) = 0, fib(1) = 1, and for n ≥ 2, f ib(n) = fib(n− 1) + fib(n− 2)$$.

dp takes O(n)

compute the n-th Fibonacci number (where n is large) in O(log n) time using the eﬃcient matrix power

there is an O(1) approximation technique to get the n-th Fibonacci number.

compute the closest integer of (φn
− (−φ)−n)/√5 (Binet’s formula) where  φ  $${/phi}$$(golden ratio)

Zeckendorf ’s theorem: Every positive integer can be written in a unique way as a sum of one or more
distinct Fibonacci numbers such that the sum does not include any two consecutive Fibonacci
numbers.

Pisano Period where the last one/last two/last three/last four
digit(s) of a Fibonacci number repeats with a period of 60/300/1500/15000, respectively.

## Binomial No

finding the coeﬃcients of the algebraic expansion of powers of a binomial

These coeﬃcients are also the number of ways that n
items can be taken k at a time, usually written as C(n, k) or nCk

$$\\binom{n}{k}$$

$$C(n, k) =\frac{n!}{(n−k)!×k!}$$

$$
C(n, 0) = C(n, n) = 1 // base cases.
C(n, k) = C(n− 1, k− 1) + C(n− 1, k) // take or ignore an item, n > k > 0.
$$

## Multinomial coefficient

$$
C(n, {k1,k2,....,km})= \frac{n!}{k1! k2! k3! .... km!}
$$

## Catalan Numbers

It is no of valid parenthesis expression that consist of n left and right parenthesis.

Cat(n) = ((2×n)Cn)/(n + 1); Cat(0) = 1. 

$$
Cat(n) = \frac{2n!}{n!×n!×(n+1)}.
$$

$$
Cat(n + 1) = \frac{(2×(n+1))!}{(n+1)!×(n+1)!×((n+1)+1)}= \frac{(2n+2)×(2n+1)×2n!}{(n+1)×n!×(n+1)×n!×(n+2)}= \frac{(2n+2)×(2n+1)×...[2n!]}{(n+2)×(n+1)×...[n!×n!×(n+1)]}.
$$

Therefore, 
$$
Cat(n + 1) = {(2n+2)×(2n+1)/
(n+2)×(n+1)} × Cat(n)
$$

Alternatively, we can set m = n + 1 so that we have: 
$$
Cat(m) = {2m×(2m−1)/(m+1)×m}× Cat(m− 1).
$$




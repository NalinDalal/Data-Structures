# Number Theory
Number Theory is widely used due to cryptographic aspects and propoerties.
Let's introudce some basic concepts of number theory, divisibility, modular equivalence, unique factors etc.

some things to keep on mind

large input doesn't refers to size, rather it's the value
large input means some input having large integer value.
hence size shall be measured in terms of bits.

# Elementary number-theoretic notions

*Z* refers to the set of integers
*N* refers to set of natural numbers.

`d|a` = a divides d; `a=kd` for some k.
i.e. a is factor of d
```
if(a>0 && d|a){
|d|<= |a|
}
```

# Prime and Composite Numbers 

If `a>1` whose divisor are only `1` and `a` => `a` is prime no.

Composite no are the natural no that are not prime.

To find if number `N` is prime or not.-> *prime.cpp*


# Divisor Theorem, Remainders & Modulos

for integers a and positive integer n, there exists q and r such that
0<=r<n ; a=nq+r 

q=floor(a/n) is quotient of division.
r=a mod n is remainder of division.

n|a is true only when a mod n=0.

# Common Divisors & Greatest Common Divisors

If `d` is divisor of `a` and `b` then `d` is common divisor of both `a` and `b`.

**properties**
- `d|a` && `d|b` => `d|(ax+by)` for `x`, `y`
- `d|a` && `d|b` => `d|(a+b)` and `d|(a-b)`

`Greatest Common Divisor` is the greatest number which divides both a, b
denoted by `gcd(a,b)`

some properties:
```

gcd(a,b)=gcd(b,a)
gcd(a,b)=gcd(-a,b)
gcd(a,b)=gcd(|a|,|b|)
gcd(a,0)=|a|
gcd(a,ka)=|a|
```

If $a$ and $b$ are any integers, then $gcd(a,b)$ is smallest positive element of set `{ax+by : x,y belongs to Z}` of linear combination of a,b. 

if `d|a` && `d|b` then `d|gcd(a,b)`


```
while(n>0){
    gcd(an,bn)=n*gcd(a,b)
}
```


```
for positive integers: n,a,b 
if(n|ab && gcd(a,n)==1)
    n|b
```


`Relatively Prime Numbers`
a,b are relatively prime if `gcd(a,b)=1`

for integers `a`, `b`, `p`
```
if(gcd(a,p)==1 && gcd(b,p)==1){
    gcd(ab,p)=1
}
```

`Unique Factorization`
for all prime no `p` and all integer `a` and `b`
```
if(p|ab){
 p|a or p|b or both   
}
```

`Prime No b/w 1 and n`
$
\pi(n) = \frac{n}{ln n}
$


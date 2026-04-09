# Primes & Factors

A number `a` is called **factor** or **divisor** of a number b if `a` divides `b`
if `a` is factor of `b`, we write `a|b`.
else `a!|b`

A number `n` >1 is **prime** only if it's positive factors are 1 and n.
ex: 7,19,41 are prime; 35 is not{5,7}

for every number n>1; there is a unique prime factorization.

n= (p1^alpha1) * (p2^alpha2) .....(pk^alphak)

where p1,p2..pk are distinct primes 
alpha1, aplha2...alphak are positive numbers.

ex: 84=2^2*3^1*7^1.

number of factors of a number n is:
tou(n)=\prod{i=1}{k}{alpha i +1}

because each prime pi, there are alpha i +1 ways to choose how many times it appears.

tou(84)=3*2*2=12
factors are: 1,2,3,4,5,6,7,12,14,21,28,42,84

sum of factors of n is 
\sigma(n)=\pi{i=1}{k}{1+pi+....+pi^alpha i}
        = \pi{i=1}{k}{\frac{pi^(alpha i +1)-1}{pi-1}}

product of factors of n is
mu(n)=\pow{n}{tou(n)/2}


number n is perfect number if
n=sigma(n)-n
ex: 28=> 28=1+2+4+7+11

----

let there be a set P of primes; P={p1,p2,....,pn}
P contains all the primes.
p1=2,p2=3,p3=5 and so on.

new prime= p1p2...pn+1.

new prime larger than all elements in P.

----

Density of Primes.

pi(n) denote no of primes b/w 1,n.

pi(n) is equivalence to \frac{n}{ln n}

----

Conjectures 

there are various conjectures( an unproven mathematical or scientific theorem.)

Goldbach Conjecture: each even integer n>2 can be represented as n=a+b where a,b are prime.
Twin Prime conjecture: infinite no of pair of form{p,p+2} where p and p+2 are primes.
Legendre Conjecture: there is always a prime b/w no n^2 and (n+1)^2.

----

if n is not prime, can n is product of a,b where a,b<=root(n)
then it has a factor b/w 2 and floor(sqrt(n))

check if prime or not, by dividing n by all number b/w 2 and floor(sqrt(n)):
```cpp
bool prime(int n){
    if(n<2) return false;
    for(int x=2;x*x<=n;x++){
        if(n%x==0)return false;
    }
    return true;
}
```

----

to return all prime factors of n in a vector:
same logic, just add to vector when true;

```cpp 
vector<int> factors(int n){
    vector<int> f;
    for(int x=2;x*x<=n;x++){
        while(n%x==0){
            f.push_back(x);
            n/=x;
        }
    }
    if(n>1) f.push_back(n);

    return f;
}
```

----

Factorial 
Factorial of n i.e. n! or fac(n) is defined as 1 if n=0/1 
else fac(n)=n*fac(n-1) if n>0.

`fac(n)=n*(n-1)*(n-2)*...*3*2*1`

-----

Finding Prime Factors with Optimized Trial Divisions

composite no can be written uniquely as multiplication of its prime factors.

prime power factorization:
N=120=2x2x2x2x3x5x5
    = 2^4 x 3 x 5^2

naive algorithm generates list and then check which prime divide N.
better algorithm:
N=PFxN'
PF=prime factor; N'=N/PF.
do this until N'=1.

to speed up, we use the fact that N can't have any divisor greater than sqrt(N).
hence repeat only till PF<=sqrt(N).

trial division: O(pi(sqrt(N)))=O(sqrt{N}/ln(sqrt{N}))

```cpp
vi primeFactor(ll N){
    vi factors;
    ll PF_idx = 0, PF = primes[PF_idx]; // primes has been populated by sieve 
    while (PF * PF <= N) { // stop at sqrt(N); N can get smaller 
        while (N % PF == 0) { N /= PF; factors.push_back(PF); } // remove PF 
        PF = primes[++PF_idx]; // only consider primes! 
    } 
    if (N != 1) factors.push_back(N); // special case if N is a prime 
    return factors; // if N does not fit in 32-bit integer and is a prime 
    // then ‘factors’ will have to be changed to vector<ll>
}

// inside int main(), assuming sieve(1000000) has been called before
vi r = primeFactors(2147483647); // slowest, 2147483647 is a prime 
for (vi::iterator i = r.begin(); i != r.end(); i++) printf("> %d\n", *i);

r = primeFactors(136117223861LL); // slow, 104729*1299709 
for (vi::iterator i = r.begin(); i != r.end(); i++) printf("# %d\n", *i);

r = primeFactors(142391208960LL); // faster, 2^10*3^4*5*7^4*11*13 
for (vi::iterator i = r.begin(); i != r.end(); i++) printf("! %d\n", *i);
```

----

# Prime Factors Functions

1. **numPF(N)** : Count no of prime factors of N 
```cpp
ll numPF(ll N){
    ll PF_idx=0,PF=primes[PF_idx],ans=0;
    while(PF*PF<=N){
        while(N%PF==0){N/=PF;ans++;}
        PF=primes[++PF_idx];
    }
    if(N!=1) ans++;
        return ans;
}
```

2. **numDiffPF(N)**: Count no of different prime factor of N 

3. **sumPF(N)**: Sum prime factors of N.

4. **numDiv(N)**: Count no of divisors of N.

```cpp
ll numDiv(ll N){
    ll PF_idx=0, PF=primes[PF_idx], ans=1;
    while(PF*PF<=N){
        ll power=0;
        while(N%PF==0){
            N/=PF;power++;
        }
        ans*=(power+1);
        PF=primes[++PF_idx];
    }
    if(N!=1)ans*=2;
    return ans;
}
```


**5. `sumDiv(N)`: Sum the divisors of N**

If $N = a^i \times b^j \times \ldots \times c^k$, the sum of divisors is:

$$\sigma(N) = \frac{a^{i+1}-1}{a-1} \times \frac{b^{j+1}-1}{b-1} \times \ldots \times \frac{c^{k+1}-1}{c-1}$$

Example: $N = 60 = 2^2 \times 3^1 \times 5^1$, so $\text{sumDiv}(60) = \frac{7 \times 8 \times 24}{1 \times 2 \times 4} = 168$.

```cpp
ll sumDiv(ll N) {
    ll PF_idx = 0, PF = primes[PF_idx], ans = 1; // start from ans = 1
    while (PF * PF <= N) {
        ll power = 0;
        while (N % PF == 0) { N /= PF; power++; }
        ans *= ((ll)pow((double)PF, power + 1.0) - 1) / (PF - 1);
        PF = primes[++PF_idx];
    }
    if (N != 1) ans *= ((ll)pow((double)N, 2.0) - 1) / (N - 1); // last factor
    return ans;
}
```


**6. `EulerPhi(N)`: Count positive integers < N that are coprime to N**

Two integers $a$ and $b$ are *relatively prime* (coprime) if $\gcd(a,b) = 1$.

The Euler's Totient function is:
$$\varphi(N) = N \times \prod_{PF} \left(1 - \frac{1}{PF}\right)$$

Example: $N = 36 = 2^2 \times 3^2$. $\varphi(36) = 36 \times (1 - \frac{1}{2}) \times (1 - \frac{1}{3}) = 12$.

```cpp
ll eulerPhi(ll N) {
    ll PF_idx = 0, PF = primes[PF_idx], ans = N; // start from ans = N
    while (PF * PF <= N) {
        if (N % PF == 0) ans -= ans / PF;     // only count unique factor
        while (N % PF == 0) N /= PF;
        PF = primes[++PF_idx];
    }
    if (N != 1) ans -= ans / N;               // last factor
    return ans;
}
```


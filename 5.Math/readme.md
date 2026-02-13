# Number Theory
to study integers
consider:

${x}^{3}+{y}^{3}+{z}^{3}=33$

$x=3$
$y={3}^{1/3}$
$z={3},{1/3}$

# Division Algoirthm

For any integer a and any positive integer n, there are unique integers q and r such
that 0 ≤r < n and a =qn +r.
The value q=⌊a/n⌋is the *quotient* of the division.

value r =a mod n is the *remainder* (or residue) of the division.

# Primes and Factors
number a is called a `factor` or a `divisor` of a number b if a divides b.
If a is a factor of b, we write a | b, and otherwise we write a | b.

- **Goldbach’s conjecture**: Each even integer n > 2 can be represented as a
sum n = a + b so that both a and b are primes.
- **Twin prime conjecture**: There is an infinite number of pairs of the form
{p, p + 2}, where both p and p + 2 are primes.
- **Legendre’s conjecture**: There is always a prime between numbers $n^2$
and $(n + 1)^2$, where n is any positive integer.

**greatest common divisor** of two integers a and b, not both zero, is the
largest of the common divisors of a and b; it is denoted gcd(a, b)

```
gcd(a,b)=gcd(b,a)
gcd(a,b)=gcd(-a,b)
gcd(a,b)=gcd(|a|,|b|)
gcd(a,0)=|a|

```

## Basic Algos

n is not prime then represented as n=a*b
then $a<=/sqrt{n}$ and $b<=/sqrt{b}$

to find if no is prime or not
divide n by all numbers between 2 and floor{/sqrt{n}}, and if none of
them divides n, then n is prime.

```
bool prime(int n) {
    if (n < 2) return false;
    for (int x = 2; x*x <= n; x++) {
        if (n%x == 0) return false;
    }
    return true;
}
```

build a vector that has allfactors of n
```
vector<int> factors(int n) {
    vector<int> f;
    for (int x = 2; x*x <= n; x++) {
        while (n%x == 0) {
            f.push_back(x);
            n /= x;
        }
    }
    if (n > 1) f.push_back(n);
    return f;
}
```

**Sieve of Eratosthenes**
preprocessing algorithm that builds an array
using which we can efficiently check if a given number between 2...n is prime
and, if it is not, find one prime factor of the number.

build an array whose position 2,3,4...n are used
sieve[k]=0 means k is prime
one of its prime factors is sieve[k]

is x is prime then multiple of x are not prime, hence we cancel them out

```
for (int x = 2; x <= n; x++) {
    if (sieve[x]) continue;
    for (int u = 2*x; u <= n; u += x) {
        sieve[u] = x;
    }
}
```

running time: O(nlogn)

**Euclid's Algorithm**

gcd(a, b)=gcd(b, a mod b) .

lcm(a,b)=a*b/gcd(a,b)

gcd(a,b)={
    a   b=0
    gcd(b,a mod b)  b!=0
}

```
int gcd(int a, int b) {
if (b == 0) return a;
return gcd(b, a%b);
}
```

overall running time of EUCLID is proportional to the number of recursive
calls it makes

Time: O(log n)

num a,b are coprime
gcd(a,b)=1


**Euler’s totient function ϕ(n)**
gives the number of coprime numbers to n between 1 and n

ϕ(n)=
k
i=1
αi−1
p
i (pi− 1).

- For any integers a and b, if d |a and d |b then d |gcd(a, b) 
- gcd(an, bn)=n gcd(a, b) .


# Modular Arithmetic
x mod m= the remainder after dividing x by m

following formulas hold:
(x + y) mod m = (x mod m + y mod m) mod m
(x− y) mod m = (x mod m− y mod m) mod m
(x· y) mod m = (x mod m· y mod m) mod m
pow(x,n) mod m = pow((x mod m),n) mod m

to calculate **pow(x,n) mod m**
in O(log n) time



```cpp
int modpow(int x, int n, int m) {
if (n == 0) return 1%m;
long long u = modpow(x,n/2,m);
u = (u*u)%m;
if (n%2 == 1) u = (u*x)%m;
return u;
}
```

**CoPrime**
gcd(a, b)= 1.

**Fermat's theorem**
if m is prime and x,m are coprime

$x^{m-1} mod m=1$

**Modular Inverse**
inverse of x modulo m is a number $x^{-1}$

$xx^{-1} mod m = 1$

If a modular inverse exists, it can be calculated using the formula

$x^{−1}= x^{ϕ(m)−1}$

if m is prime then
$x^{-1}=x^{m-2}$


---


# Solving Equations
Diophantine equation is an equation of the form
ax + by= c {a, b and c are constants and the values of x and y should be found so that ax + by= gcd(a,b)}


can be solved if c is divisible by gcd(a,b)

cosider:
39x + 15y = 12
gcd(39,15)= 3 and 3 | 12
gcd(39,15)==> gcd(39,15)= gcd(15,9)= gcd(9,6)= gcd(6,3)= gcd(3,0)= 3

39− 2· 15= 9
15− 1· 9= 6
9− 1· 6= 3

we can derive
39· 2+ 15· (−5)= 3

and by multiplying this by 4, the result is
39· 8+ 15· (−20)= 12,
so a solution to the equation is x = 8 and y = −20.

If a pair (x, y) is a solution, then also all pairs $$(x+\frac{kb}{gcd(a,b)}, y-\frac{ka}{gcd(a,b)})$$ are solution for any real k

# Chinese Remainder Theorem
 
The Chinese Remainder Theorem (CRT) describes solutions to a system of simultaneous congruences
\[\begin{aligned}
x &\equiv a_1 \pmod{m_1},\\
x &\equiv a_2 \pmod{m_2},\\
&\ \vdots \\
x &\equiv a_n \pmod{m_n},
\end{aligned}\]
where the moduli $m_1,\dots,m_n$ are pairwise coprime (i.e. $\gcd(m_i,m_j)=1$ for $i\ne j$).

Statement (pairwise-coprime case): If the moduli are pairwise coprime then there exists a unique solution $x$ modulo
$$M=\prod_{i=1}^n m_i.$$ 
One explicit construction is:

Let $M_i=M/m_i$, and let $y_i$ be the modular inverse of $M_i$ modulo $m_i$, i.e. $M_i y_i\equiv 1\pmod{m_i}$. Then
$$x \equiv \sum_{i=1}^n a_i M_i y_i \pmod{M}$$
is a solution, and every solution is congruent to this $x$ modulo $M$.

Example (from the figure):
$$x\equiv 3\pmod{5},\qquad x\equiv 4\pmod{7},\qquad x\equiv 2\pmod{3}.$$ 
Here $M=5\cdot7\cdot3=105$. Then $M_1=21$, $M_2=15$, $M_3=35$. Compute inverses:
$21\equiv1\pmod5\Rightarrow y_1=1$, $15\equiv1\pmod7\Rightarrow y_2=1$, $35\equiv2\pmod3\Rightarrow y_3=2$ (since $2\cdot2\equiv1\pmod3$). Thus
$$x=3\cdot21\cdot1+4\cdot15\cdot1+2\cdot35\cdot2=263,$$
and $x\equiv263\pmod{105}$ gives the canonical solution $x\equiv53\pmod{105}$.

Remarks:
- If moduli are not pairwise coprime, a solution exists iff each pair of congruences is consistent modulo the gcd of the moduli (or equivalently the system can be reduced pairwise); in general one can use an iterative CRT that merges two congruences at a time using the extended gcd.
- Once one solution $x_0$ is found, all solutions are $x_0 + tM$ for integer $t$.

Algorithms and code

1) Fast constructive method (requires pairwise-coprime moduli): compute each $M_i$ and its inverse modulo $m_i$ (use extended gcd to find inverses), then form the sum above.

2) Iterative CRT that also handles non-coprime moduli (returns no solution when inconsistent): merge congruences two at a time using extended gcd.

Here are compact C++ snippets — first the extended gcd / modular inverse helper, then two CRT variants.

```cpp
// extended gcd: returns g = gcd(a,b) and finds x,y with ax+by=g
long long extgcd(long long a, long long b, long long &x, long long &y) {
    if (b==0) { x= (a>=0?1:-1); y=0; return llabs(a); }
    long long x1,y1;
    long long g = extgcd(b, a%b, x1, y1);
    x = y1;
    y = x1 - (a/b)*y1;
    return g;
}

// modular inverse of a modulo m (returns -1 if inverse doesn't exist)
long long modinv(long long a, long long m) {
    long long x,y;
    long long g = extgcd(a,m,x,y);
    if (g!=1) return -1;
    x %= m; if (x<0) x += m;
    return x;

// CRT for pairwise-coprime moduli: returns (x,M) with 0<=x<M, or (0,-1) on error
pair<long long,long long> crt_pairwise(const vector<long long>& a, const vector<long long>& m) {
    int n = a.size();
    long long M = 1;
    for (auto v:m) M *= v;
    long long x = 0;
    for (int i=0;i<n;i++){
        long long Mi = M / m[i];
        long long yi = modinv(Mi % m[i], m[i]);
        if (yi==-1) return {0,-1};
        x = (x + (__int128)a[i] * Mi % M * yi) % M;
    }
    if (x<0) x+=M;
}
// General iterative CRT that handles non-coprime moduli when possible.
// Returns (x,m) representing solutions x (mod m); if no solution returns (0,-1).
pair<long long,long long> crt_general(long long a1, long long m1, long long a2, long long m2) {
    // solve x = a1 (mod m1), x = a2 (mod m2)
    long long x,y;
    long long g = extgcd(m1,m2,x,y);
    if ((a2 - a1) % g != 0) return {0,-1}; // no solution
    long long l = m1 / g * m2; // lcm
    long long t = ((__int128)(a2 - a1) / g * x) % (m2/g);
    if (t<0) t += m2/g;
    long long res = (a1 + (__int128)m1 * t) % l;
    if (res<0) res += l;
    return {res, l};
}

// Example usage (merge many congruences using crt_general):
// pair<long long,long long> cur = {a0,m0};
// for each i>0: cur = crt_general(cur.first, cur.second, a[i], m[i]);
// if cur.second == -1 -> no solution; otherwise cur.first is solution mod cur.second.
```

## Lagrange’s theorem
Lagrange’s theorem states that every positive integer can be represented as a sum of four squares, i.e., $${a}^{2} + {b}^{2} + {c}^{2} + {d}^{2}$$.

## Zeckendorf’s theorem
eve

Sketch of play: when S != 0, there exists a heap where reducing it to make the overall XOR zero is possible; the winning player always moves to a zero XOR position and can maintain that invariant.ry positive integer has a unique representation as a sum of Fibonacci numbers such that no two numbers are equal or consecutive Fibonacci numbers.

## Pythagorean Triplets
a triple (a, b, c) that satisfies the Pythagorean theorem
$${a}^{2} + {b}^{2} = {c}^{2}$$

each triplet is of form $$({n}^{2}− {m}^{2},2nm,{n}^{2} + {m}^{2})$$

0 < m < n, n and m are coprime and at least one of n and m is even

## Wilson’s theorem

n is prime exactly when
$$(n− 1)! mod n = n− 1$$

---

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

## Catalan Numbers

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

-------


# Game Theory

Game Theory models strategic situations where a player's success depends on others' choices. In programming contests many two-player problems are zero-sum: one player's win is the other's loss. Typical examples include Tic-Tac-Toe, Chess, and many impartial integer games (UVa problems such as 847, 10368, 10578, 10891, 11489, and others).

Game theory studies two-player games without random elements where a player's success depends on the opponent's choices. Our aim is to find strategies guaranteeing a win under perfect play when such strategies exist. Many contest problems are zero-sum: one player's gain is the other's loss (examples: Tic-Tac-Toe, Chess, and integer games such as UVa 847, 10368, 10578, 10891, 11489).

## Game states

Consider a heap of n sticks. Players A and B alternate moves; A starts. On each move a player removes 1, 2 or 3 sticks; the player who removes the last stick wins. States are 0,1,2,...,n where the state number equals the sticks left.

Example (n=10): A removes 2 (8 left), B removes 3 (5 left), A removes 1 (4 left), B removes 2 (2 left), A removes 2 and wins.

## Winning and losing states

A state is winning if the current player can force a win with optimal play; otherwise it is losing. State 0 is losing (no moves). States 1,2,3 are winning (can remove all sticks). State 4 is losing since any move leads to a winning state for the opponent. In general, a state is winning iff there exists a move to a losing state; otherwise it is losing.

For the 1..3 removal game the pattern repeats every 4: states divisible by 4 are losing, others winning. Optimal play: always move so the remaining sticks are divisible by 4 (if possible).

## State graph (divisor-removal game)

Now consider a variant: from state k you may remove any x<k such that x divides k. E.g. from 8 you can remove 1,2,4; from 7 only 1. The terminal state is 1 (no valid moves), which is losing. For states 1..9 the pattern is:

1 2 3 4 5 6 7 8 9
L W L W L W L W L

All even states win, all odd states lose in this rule-set.

## Decision Tree and Minimax

Represent the game as a decision (game) tree: nodes represent game states and which player's turn it is; edges represent legal moves. The root is the initial state. Leaf nodes are terminal states with known outcomes. If subproblems overlap use Dynamic Programming (memoization) to avoid exponential work.

At each internal node the current player chooses a move that maximizes their outcome assuming the opponent also plays optimally. This is the Minimax strategy (maximise your minimum gain).

Implementation notes:
- Use recursion + memoization for state spaces that fit memory.
- Encode the state compactly (bitmask, tuple, or integer) so it can be used as a key in a hash map.
- Return win/lose (or numeric score) for the current player; flip the sign or invert result when switching players.

Example (Euclid's Game, UVa 10368): states are pairs (a,b) with a>=b. A player subtracts a positive multiple of b from a provided result >=0. Explore options greedily but memoize states; depth parity determines current player.

## Mathematical insights to speed solutions

Many contest games admit number-theoretic or combinatorial shortcuts that avoid full search.

- Multiplication game (UVa 847): players multiply a running product p by a number in [2..9]; target is n. Observing small cases often reveals optimal moves (e.g. first player picks 9, second picks 2), and proofs by induction or interval analysis justify the greedy choices.

- Always look for invariants, monotone parameters, and winning thresholds that let you collapse the search to a few cases.

## Nim game

Players alternate removing any positive number of sticks from a single heap, among several heaps with sizes n1, n2, ..., nk; the player taking the last stick wins. The nim-sum $$ s = x1 \oplus x2 \oplus ... \oplus xn$$ classifies states: s=0 => losing; $$s\ne0 => winning$$

Why: final state [0,...,0] has nim-sum 0. Any legal move changes exactly one heap, so any move from a 0 nim-sum leads to nonzero nim-sum (winning for opponent). Conversely, if s\ne0 find a heap xk with a 1 bit at the leftmost 1-bit of s; set that heap to xk\oplus s < xk to make the overall nim-sum 0.

Example: [10,12,5] has $$nim-sum 10\oplus12\oplus5 = 3$$, choose heap 10 -> $$10\oplus3 = 9$$ (remove 1 stick) to reach [9,12,5] with nim-sum 0.

Sketch of play: when S != 0, there exists a heap where reducing it to make the overall XOR zero is possible; the winning player always moves to a zero XOR position and can maintain that invariant.

## Misère Nim

In misère play (last move loses) play as in normal Nim except near the end: when all heaps will contain at most one stick after the next move, switch strategy — in normal Nim you move to make the number of size-1 heaps even; in misère move to make that number odd. This adjustment handles the terminal condition difference.

## Practical tips

- When solving contest problems, first try to detect whether the game is impartial and whether a known solution (Nim, subtraction games, Euclid-style reductions) applies.
- Otherwise implement Minimax with memoization and prune symmetric or dominated moves.
- Add small worked examples in your notes to build intuition for greedy heuristics.


## Sprague–Grundy theorem

This theorem generalizes Nim: impartial games satisfying (no randomness, finite play, same moves for both players, perfect information) have Grundy numbers (or nimbers). Each state has a Grundy number g defined by
$$g = \operatorname{mex}(\{g_1,g_2,\dots,g_m\}),$$
where g_i are the Grundy numbers of positions reachable in one move, and mex returns the minimum excluded nonnegative integer. Terminal positions have Grundy 0.

If a game is a disjoint sum of subgames, the Grundy number of the sum is the nim-sum of subgame Grundy numbers; play reduces to Nim.

### Example: maze-moving game

Consider moving a token on a grid where allowed moves are left or up any positive number of steps (no walls in reachable squares). Each reachable cell has a Grundy number computed by mex over reachable positions. Example Grundy table (illustrative) shows how positions map to small nonnegative integers; a position with Grundy 2 is winning because you can move to positions with Grundy 0 or 1.

## Subgames and Grundy’s game

When a move splits the position into independent subgames, the Grundy of the move is the nim-sum of the resulting subgames. Grundy’s game: a heap of n; a move splits a heap into two heaps of different positive sizes. Let f(n) be Grundy of size-n heap; f is computed by considering all splits a+b=n with $$a\ne b$$, and taking mex of $$f(a)\oplus f(b)$$. Base: f(1)=f(2)=0. Example sequence: f(1)=0,f(2)=0,f(3)=1,f(4)=0,f(5)=2,f(6)=1,f(7)=0,f(8)=2.

## Practical summary

- Model games as state graphs and classify states via DP/minimax when feasible.
- Look for reductions to Nim using Grundy numbers; compute Grundy values with memoization.
- For standard Nim use xor (nim-sum); for misère adjust endgame.
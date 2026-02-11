# Strings
A collection of characters
unlike arrays, it's size is not defined

```cpp
string s;
cin>>s; //input


string s1="hello";
cout<<s1;   //output
```

# Terminologies
The set of characters that may appear in strings is called an **alphabet**.

**substring** is a sequence of consecutive characters in a string.
**subsequence** is a sequence of (not necessarily consecutive) characters in a string in their original order.
A string of length n has pow(2,n)− 1 subsequences.

**prefix** is a substring that starts at the beginning of a string
**suffix** is a substring that ends at the end of a string.

A **period** is a prefix of a string such that the string can be constructed by repeating the period. period of ABCABCA is ABC.

A **border** is a string that is both a prefix and a suffix of a string. borders of ABACABA are A, ABA and ABACABA
---

# String Operations

## Concatenation:
```cpp
string a="Hello",b="World";
string c=a+" "+b;

cout<<c<<endl;
```

```bin
Hello World
```

## Length:
```cpp
string s="Hi";
s.len();    //2
//or
s.size();
//or
s.length();
```

## Copying the String
to copy over the string into other string
```cpp
string b=a;
```

## Traversal
Traversal means to go over the string `char-by-char`:
```cpp
for(int i=0;i<s.length();i++){
    cout<<s[i]<<" ";
}
```

# Common String Functions

## `substr()`
**Usage:** `str.substr(a, b)`

Returns a substring starting from index `a` of the original string with a length of `b` characters.  
> **Example:**  
> ```cpp
> std::string s = "hello world";
> std::string sub = s.substr(0, 5); // returns "hello"
> ```

Note: If you want to extract up to a certain index `b`, use `str.substr(a, b - a)`.

---

## `find()`
**Usage:** `str.find(substring)` or `str.find(substring, start_pos)`

Searches the string for the first occurrence of the specified substring.  
Returns the index of the first character of the found substring or `std::string::npos` if not found.  
> **Example:**  
> ```cpp
> std::string s = "hello world";
> size_t pos = s.find("world"); // returns 6
> ```

---

## `replace()`
**Usage:** `str.replace(start_pos, length, new_substring)`

Replaces a portion of the string starting at `start_pos` and spanning `length` characters with `new_substring`.  
> **Example:**  
> ```cpp
> std::string s = "hello world";
> s.replace(6, 5, "there"); // s becomes "hello there"
> ```

---

## `erase()`
**Usage:** `str.erase(pos, len)`

Erases `len` characters from the string starting at position `pos`.  
If `len` is not provided, all characters from `pos` to the end are removed.  
> **Example:**  
> ```cpp
> std::string s = "hello world";
> s.erase(5, 1);  // removes the space, s becomes "helloworld"
> s.erase(5);     // removes all characters from index 5 onwards
> ```

---

## `stringstream`
splits the string into words.

`reverse(word.begin(), word.end())` reverses each word separately.

Print each reversed word with a space.
> ```cpp
>     string s = "hello world";
>     stringstream ss(s);
>     string word;
> 
>     while (ss >> word) {
>         reverse(word.begin(), word.end());
>         cout << word << " ";
>     }
> ```


----

# String Matching

Finding all occurrences of a pattern in a text 
assume that the text is an array T [1. . n] of length n and that the pattern is an array P[1. . m] of length m ≤ n.

elements of P and T are from set of finite alphabet.
sigma={0,1} or {a,b,c,d...,z}

say pattern P occurs with shift s in text T

if 0 ≤ s ≤ n−m and T [s +1 . . s +m]= P[1. . m] (that is, if T [s + j]= P[ j], for 1 ≤ j ≤ m).
If P occurs with shift s in T , then we call s a valid shift; otherwise, we call s an invalid shift.

```
text T -------->  a b c a b a a b c a b a c
pattern P -----s=3----> a b a a
```
| Algo | Preprocessing Time | Matching Time |
|------|--------------------|---------------|
|Naive | 0                  | O((n-m+1)m)   |
|Rabin-Karp | Omega(m)      | O((n-m+1)m)   |
|Finite automaton | O(m * length of input set) | Omega(n)|
|Knuth-Morris-Pratt | Omega(m) | Omega(n) |

sigma * = set of all finite-length strings formed using characters from the alphabet sigma

say string w is a prefix of a string x, denoted w subset of x, if x =wy for some string y ∈ sigma∗.

x,y,z are strings such that x is subset of z, and y is subset of z
if len(x)=> len(y) then y is subset of x
if len(x)=len(y) then x=y

time complexity: Omega(t+1); t= length of the longest string z such that z is subset of x and z is subset of y.

## Naive String Matching Algo

finds all valid shifts using a loop that checks the condition 
P[1. . m]=T [s +1 . . s +m] for each of the n−m +1 possible values of s.
```
NAIVE-STRING-MATCHER(T, P)
1 n ←length[T ]
2 m ←length[P]
3 for s ←0 to n−m
4   do if P[1. . m]=T [s +1 . . s +m]
5       then print“Pattern occurs with shift” s
```

```
naiveStrMatch(T,P){
    n=len(T)
    m=len(P)

    for(s=0 to n-m){
        if(P[1..m]==T[s+1...s+m])
            Patten found with shift s
    }
}
```
takes time O((n−m +1)m)

```cpp
void naiveMatching() {
    for (int i = 0; i < n; i++) { // try all potential starting indices
        bool found = true;
        for (int j = 0; j < m && found; j++) // use boolean flag ‘found’
            if (i + j >= n || P[j] != T[i + j]) // if mismatch found
                found = false; // abort this, shift the starting index i by +1
        if (found) // if P[0..m-1] == T[i..i+m-1]
            printf("P is found at index %d in T\n", i);
    }
}
```

consider a string a^n(a,aa,aaa,....) and pattern a^m
For each of the `n−m +1` possible values of the shift s,
the implicit loop on line 4 to compare corresponding characters must execute m times to validate the shift.

worst case time: Omega((n−m +1)m)
                Omega(n^2) for m=floor(n/2)

The running time of NAIVE-STRING-MATCHER is equal to its matching time, since there is no preprocessing.


----

>>> Write an efficient function to find the first non-repeated character in a string. For instance, the first non-repeated character in "total" is 'o' and the first non-repeated character in "teeter" is 'r'. Discuss the efficiency of your algorithm.

compare each char with other chars in string -> O(n^2)
there must exist more efficient algo
n^2 came because we were checking each char in str to see if it was non-repeated

n-> traverse
n^2-> search entire string to lookup for each char

easy way-> improve search by putting in a data structure that has more efficient searching.
Binary Trees(O(log n)).
Array/HashTable(O(1) for lookup)

use char as index in array or key in hashtable

store no of time each char appeared
then just traverse to find `1`

ASCII String: 256 elements
UniCode: 65000

Algo:
```
First, build the character count hashtable:
    For each character
        If no value is stored for the character, store 1
        Otherwise, increment the value

Second, scan the string:
    For each character
        Return character if count in hashtable is 1
    If no characters have count 1, return null
```

-----

## Rabin Karp Algo

uses Omega(m) pre-processing time
worst-case running time is Omega((n−m +1)m).

sigma={0,1,2...9}
a string of k consecutive characters as representing a length-k decimal number.

pattern P[1..m], p is decimal value
text T[1...n], ts is decimal value of length m substr T [s +1 . . s +m], for s =0, 1, . . . , n−m.

if (T [s +1 . . s +m]= P[1. . m]){ts=p}
s is valid shift for ts=p

compute p in time Omega(m) and ts in Omega(n-m+1)
Omega(m)+Omega(n-m+1)=Omega(n)

find p via Horner’s rule  in Omega(m)

p=P[m] +10 ( P[m−1] +10( P[m−2] +···+10(P[2] +10P[1])···)) .

t0 can be similarly computed from T [1. . m] in time (m).

t1,t2,...t(n-m) in time Omega(n-m)
t[s+1] can be found from t[s] in constant time
t[s+1] =10(t[s]−(10^m−1)T [s +1]) +T [s +m +1]. 

constant 10^m-1 is precomputed

compute p in Omega(m) time

compute t0,t1,....t[n-m] in time Omega(n-m+1)

hence Omega(m) preprocessing time and Omega(n−m +1) matching time.

what if p and ts are large,compute p and the ts modulo a suitable modulus q

p modulo q in Omega(m);ts modulo q in Omega(n-m+1)

ts=(d(ts-T[s+1]h)+T[s+m+1]) mod q
h=pow(d,m-1) mod q

`Rabin Karp Matcher`

```
rabinKarpMatcher(T, P, d, q) {
    n = T.size()
    m = P.size()

    h = (pow(d, m-1)) mod q     // d^(m-1) % q

    p = 0      // hash of pattern
    t = 0      // hash of current text window (t0)

    // ---------- Preprocessing ----------
    for (i = 0; i < m; i++) {
        p = (d*p + P[i]) % q
        t = (d*t + T[i]) % q
    }

    // ---------- Matching ----------
    for (s = 0; s <= n - m; s++) {

        // if hash matches, then check actual string (to avoid collision)
        if (p == t) {
            if (T.substr(s, m) == P) {
                print("Pattern occurs with shift ", s)
            }
        }

        // compute next window hash (rolling hash)
        if (s < n - m) {
            t = ( d*(t - T[s]*h) + T[s + m] ) % q

            // handle negative modulo
            if (t < 0) t += q
        }
    }
}

```

### **Algorithm Steps**

**Step 1: Initialize**

1. `n = length(T)`
2. `m = length(P)`
3. Compute
   **h = (d^(m-1)) mod q**
4. Set:

   * `p = 0` (hash of pattern)
   * `t = 0` (hash of first window of text)


**Step 2: Preprocessing (Compute initial hashes)**

5. For `i = 0 to m-1`:

   * `p = (d*p + P[i]) mod q`
   * `t = (d*t + T[i]) mod q`

So now:

* `p` = hash(pattern)
* `t` = hash(text[0...m-1])



**Step 3: Sliding Window Matching**

6. For `s = 0 to n-m` (shift of window):

   **(A) Hash Check**

   * If `p == t`
     → then compare actual strings:

     * If `P == T[s ... s+m-1]`
       → print `"Pattern found at shift s"`

   **(B) Rolling Hash Update**

   * If `s < n-m`:
     Update next window hash:
     $$
     t = (d*(t - T[s]*h) + T[s+m]) \mod q
     $$
     If `t < 0` → `t = t + q`


Omega(m) preprocessing
Omega((n-m+1)m) matching time
Omega((n-m+1)m) verification time


## KMP(Knuth-Morris-Pratt) Algo

matching time: Omega(n) via aux func pi[1...m], precomputed from pattern in time Omega(m)

**prefix function (π)**
Given pattern `P[1..m]`, prefix function is:

$$
\pi[q] = \max { k : k < q \text{ and } P[1..k] \text{ is a suffix of } P[1..q] }
$$

Meaning:

* `π[q]` = length of the **longest proper prefix** of `P[1..q]`
* which is also a **suffix** of `P[1..q]`

## Compute Prefix Function

Algo:

```text
Input:
    Pattern P[1..m]

Output:
    Prefix function π[1..m]

Initialize:
    π[1] = 0
    k = 0

For q = 2 to m:
    While k > 0 and P[k+1] != P[q]:
        k = π[k]

    If P[k+1] == P[q]:
        k = k + 1

    π[q] = k

Return π
```

## KMP Matcher

Algo:

```text
Input:
    Text T[1..n]
    Pattern P[1..m]

Output:
    All shifts s where P matches T

First, preprocess the pattern:
    Compute π[1..m] using COMPUTE-PREFIX-FUNCTION(P)

Initialize:
    q = 0   // number of matched characters

For i = 1 to n:
    While q > 0 and P[q+1] != T[i]:
        q = π[q]

    If P[q+1] == T[i]:
        q = q + 1

    If q == m:
        Print "Pattern occurs with shift" (i - m)
        q = π[q]
```

##  Key Idea in One Line

When mismatch happens at `q`, KMP jumps to:

$$
q = \pi[q]
$$

instead of restarting from 0 like naive.

## 2 D Grid
find pattern p in a 2d grid 
```
abcdefghigg 
hebkWaldork 
ftyawAldorm 
ftsimrLqsrc
byoarbeDeyv 
klcbqwikOmk
strebgadhRb 
yuiqlxcnbjF
```

solution: recursive backtracking
efficiency: Once the recursion depth exceeds the length of pattern P, we can immediately prune that
recursive branch. Known as Depth-Limited Search.

# String with DP

## String Alignment (Edit Distance)
Align two strings A with B with the maximum alignment score (or minimum number of edit operations):

possibilities b/w A[i] and B[i]:
1. Character A[i] and B[i] match and we do nothing (assume this worth ‘+2’ score),
2. Character A[i] and B[i] mismatch and we replace A[i] with B[i] (assume ‘-1’ score),
3. We insert a space in A[i] (also ‘-1’ score),
4. We delete a letter from A[i] (also ‘-1’ score).

Brute-Force: TLE

Also known as `Needleman-Wunsch’s (bottom-up) DP algorithm`

V(i,j): score of optimal alignment b/w prefix A[1..i] and B[1..j]
score(C1,C2): returns the score if character C1 is aligned with character C2

Base Cases:
V (0, 0) = 0 // no score for matching two empty strings
V (i, 0) = i × score(A[i], ) // delete substring A[1..i] to make the alignment, i > 0
V (0, j) = j × score( , B[j]) // insert spaces in B[1..j] to make the alignment, j > 0

Recurrences: For i > 0 and j > 0:
V (i, j) = max(option1, option2, option3), where
option1 = V (i− 1, j− 1) + score(A[i], B[j]) // score of match or mismatch
option2 = V (i− 1, j) + score(A[i], ) // delete Ai
option3 = V (i, j− 1) + score( , B[j]) // insert Bj

match: +2
mismatch, insert, delete: -1
fill values row by row, left-to-right

V(i,j) for i,j>0; need V (i− 1, j− 1), V (i− 1, j), and V (i, j− 1)

Space COmplexity: O(mn)
1 cell time: O(1)
total time complexity: O(mn)
---

## Longest Common SubSequence
Given String A,B; what is the longest common subsequence between them.

can be reduced to the String Alignment problem

cost for mismatch= -Infinity
cost for insertion, deleting= 0
cost for match=1
---

# Longest Palindrome
given a string, find max length of palindrome that can be created by deleting 0/more chars

'ADAM'-> ADA
'MADAM’ → ’MADAM’ (of length 5, delete nothing)
’NEVERODDOREVENING’ → ’NEVERODDOREVEN'

The DP solution: let len(l, r) be the length of the longest palindrome from string A[l..r].
Base cases:
If (l= r), then len(l, r) = 1. // odd-length palindrome
If (l + 1 = r), then len(l, r) = 2 if (A[l] = A[r]), or 1 otherwise. // even-length palindrome
Recurrences:
If (A[l] = A[r]), then len(l, r) = 2 + len(l + 1, r− 1). // both corner characters are the same
else len(l, r) = max(len(l, r− 1), len(l + 1, r)). // increase left side or decrease right side
This DP solution has time complexity of O(n^2).

---

# Suffix Tree/Trie/Array

## Sufix Trie
we know what is suffix; ith suffix will be s[i...n]

A Suffix Trie is a Trie (tree) that stores:
> All suffixes of all strings in a set S

Trie:
- Root is empty.
- Each edge has one character
- A path from root to a node forms a string.

If you insert all suffixes, then:
- Any substring becomes a prefix of some suffix.
- So substring search becomes easy.

CAR: CAR,AR,R

{"CAR", "CAT", "RAT"}: { CAR, AR, R, CAT, AT, T, RAT, AT, T }
remove duplicates
{ "CAR", "CAT", "RAT" }: { AR, AT, CAR, CAT, R, RAT, T }

now see like CAR and CAT, so upto CA path will be same, and then splits for R and T

2 boolean flags:
suffix-terminating: Some suffix ends exactly at this node.
word-terminating (In Dictionary): An original dictionary word ends here.

**LookUp O(m)**
Given query pattern P of length m:

Search steps:
    - Start from root
    - For each character of P:
        - follow that edge
        - if edge missing → not found

This takes O(m) because you process each character once.

why??
Because it stores all suffixes; substring search = O(m)

drawback: fast but heavy
For one string length n:
- number of suffixes = n
- total nodes can become O(n²) in worst case.

### Application

### String Matching in O(m log n)
pattern string P (of length m) in T (of length n) in O(m log n).
do two O(log n) binary searches on sorted suﬃxes and do up to O(m) suﬃx comparisons

```cpp
ii stringMatching() { // string matching in O(m log n)
    int lo = 0, hi = n-1, mid = lo; // valid matching = [0..n-1]
    
    while (lo < hi) { // find lower bound
        mid = (lo + hi) / 2; // this is round down
        int res = strncmp(T + SA[mid], P, m); // try to find P in suffix ’mid’
        if (res >= 0) hi = mid; // prune upper half (notice the >= sign)
        else lo = mid + 1; // prune lower half including mid
    } // observe ‘=’ in "res >= 0" above

    if (strncmp(T + SA[lo], P, m) != 0) return ii(-1, -1); // if not found
    
    ii ans; ans.first = lo;
    lo = 0; hi = n - 1; mid = lo;

    while (lo < hi) { // if lower bound is found, find upper bound
        mid = (lo + hi) / 2;
        int res = strncmp(T + SA[mid], P, m);
        if (res > 0) hi = mid; // prune upper half
        else lo = mid + 1; // prune lower half including mid
    } // (notice the selected branch when res == 0)

    if (strncmp(T + SA[hi], P, m) != 0) hi--; // special case
    ans.second = hi;
    return ans;
} // return lower/upperbound as first/second item of the pair, respectively

int main() {
    n = (int)strlen(gets(T)); T[n++] = ’$’; // input T as per normal, without the ‘$’

    // add terminating character
    constructSA();

    for (int i = 0; i < n; i++) printf("%2d\t%s\n", SA[i], T + SA[i]);
    
    while (m = (int)strlen(gets(P)), m) { // stop if P is an empty string
        ii pos = stringMatching();
        if (pos.first != -1 && pos.second != -1) {
            printf("%s found, SA [%d..%d] of %s\n", P, pos.first, pos.second, T);
            printf("They are:\n");
            for (int i = pos.first; i <= pos.second; i++)
                printf(" %s\n", T + SA[i]);
        } 
        else 
            printf("%s is not found in %s\n", P, T);
    } 
    return 0;
}
```

### Longest Common Prefix in O(n)
given suffix array `SA` of text `T`
compute the Longest Common Prefix (LCP) between consecutive suffixes in Suffix Array order

For `i > 0`,
`LCP[i] =` the length of common prefix between suffix `SA[i]` and suffix `SA[i-1]`.

```cpp
void computeLCP_slow() {
  LCP[0] = 0; // default value
  for (int i = 1; i < n; i++) { // compute LCP by definition
    int L = 0; // always reset L to 0
    while (T[SA[i] + L] == T[SA[i-1] + L]) L++; // same L-th char, L++
    LCP[i] = L;
  }
}
```

`O(n^2)` unfortunately

better approach: Permuted Longest-Common-Prefix (PLCP) theorem
easier to compute the LCP in the original position order of the suffixes instead of the lexicographic order of the suffixes
total number of increase (and decrease) operations is at most `O(n)`.

---

## PLCP idea

We compute an auxiliary array `Phi[i]` that stores:

`Phi[i] =` the suffix index of the previous suffix of suffix `i` in Suffix Array order.

Formally:

* `Phi[SA[0]] = -1` (there is no previous suffix before the first suffix in SA order)
* for `k = 1..n-1`:

  * `Phi[SA[k]] = SA[k-1]`

Example reasoning:
If `Phi[SA[3]] = SA[2]`, and `SA[3] = 3`, `SA[2] = 5`, then `Phi[3] = 5`.

Now, with `Phi[i]`, we compute the permuted LCP array:

`PLCP[i] = LCP between suffix i and suffix Phi[i]`

This is computed in original suffix index order `i = 0..n-1`.

---

## PLCP theorem (amortized O(n))

Let `L` be the number of currently matched characters while comparing suffix `i` with `Phi[i]`.

When we move from suffix `i` to suffix `i+1`, we know that:

* the next suffix starts one character later,
* therefore the LCP can drop by at most 1.

So we can start with:

`L = max(L - 1, 0)`

and try to extend matches further.

The PLCP theorem guarantees that across the whole algorithm:

* `L` increases at most `n` times
* `L` decreases at most `n` times

Therefore the total runtime is amortized `O(n)`.

---

## Example explanation (as described)

When `i = 0`:

* `Phi[0] = 4`
* suffix `0 = "GATAGACA$"`
* suffix `4 = "GACA$"`

The first two characters match, so:

* `PLCP[0] = 2`

When `i = 1`:

* we know at least `L - 1 = 1` character matches already
* `Phi[1] = 3`
* suffix `1 = "ATAGACA$"`
* suffix `3 = "AGACA$"`

These have at least 1 character match.
We cannot extend further, so:

* `PLCP[1] = 1`

Continue this for all `i = 0..n-1`, skipping the case `Phi[i] = -1`.

---

## Converting PLCP back to LCP

`PLCP` is indexed by suffix starting position `i`.
But the final required `LCP` is indexed by suffix array order.

So after computing `PLCP`, we rebuild `LCP` by:

`LCP[k] = PLCP[ SA[k] ]`

---

## O(n) LCP construction (Kasai-style via Phi/PLCP)

```cpp
void computeLCP_fast() {
  // Step 1: build Phi
  Phi[SA[0]] = -1;
  for (int i = 1; i < n; i++)
    Phi[SA[i]] = SA[i - 1];

  // Step 2: compute PLCP in suffix index order
  int L = 0;
  for (int i = 0; i < n; i++) {
    if (Phi[i] == -1) { // first suffix in SA order
      PLCP[i] = 0;
      continue;
    }

    while (T[i + L] == T[Phi[i] + L]) L++;
    PLCP[i] = L;

    L = max(L - 1, 0);
  }

  // Step 3: map PLCP back to LCP in SA order
  LCP[0] = 0;
  for (int i = 1; i < n; i++)
    LCP[i] = PLCP[SA[i]];
}
```

Runtime: `O(n)` amortized
Space: `O(n)` for `Phi` and `PLCP`

---

### Longest Repeated Substring in O(n)
given text T

We build:
- `SA` = suffix array (suffixes sorted lexicographically)
- `LCP[i]` = common prefix length between SA[i] and SA[i-1]

**Why??**
A substring is **repeated** iff it appears in **at least 2 suffixes**.

If a substring `X` appears in two different positions in `T`, then:

* there exist two suffixes starting at those positions
* and both suffixes start with substring `X`

So `X` becomes a **common prefix** of those two suffixes.

Now suffix array sorts suffixes.
In sorted order, suffixes with common prefix come next to each other.

So:

* the longest repeated substring must be the **maximum LCP between adjacent suffixes**
* because the best common-prefix pair will be adjacent somewhere in SA order.


Algo:

```text
Build SA of T
Build LCP array of T

bestLen = 0
bestPos = -1

For i = 1 to n-1:
    If LCP[i] > bestLen:
        bestLen = LCP[i]
        bestPos = SA[i]

Answer substring = T[bestPos .. bestPos + bestLen - 1]
```

Time: `O(n)` after SA + LCP is ready.

-------

# String Hashing
allows us to efficiently check whether two strings are equal.
idea is to compare hash values of strings instead of their individual characters.

use **polynomial hashing**
hash value of a string s of length n is
\[
(s[0]A^{n-1} + s[1]A^{n-2} + \cdots + s[n-1]A^{0}) \bmod B
\]

example: ALLEY

--------------
|A|L|L|E|Y|
|-|-|-|-|-|
|65|76|76|69|89|


if A= 3 and B= 97, the hash value of ALLEY is
(65* 3^4 + 76* 3^3 + 76* 3^2 + 69* 3^1 + 89* 3^0) mod 97= 52.


s[0],s[1],...,s[n− 1] are interpreted as the codes of the characters of s, and
A and B are pre-chosen constants.

calculate the hash value of any substring of a
string s in O(1) time after an O(n) time preprocessing.

construct an array h such that h[k] contains the hash value of the prefix s[0...k].
array values:
h[0]=s[0]
h[k]= (h[k− 1]A + s[k]) mod B

construct an array p where p[k]=pow(A,k) mod B
p[0]= 1
p[k]= (p[k− 1]A) mod B.

construction takes O(n)

hash value of any substring s[a...b] can be calculated in O(1) time using the formula

(h[b]− h[a− 1]p[b− a + 1]) mod B    {a>0}
if a=0, hash value= h[b]


----
# Z-algorithm

The Z-array `z` of a string `s` of length `n` contains for each `k = 0,1,...,n−1` the
length of the longest substring of `s` that begins at position `k` and is a prefix of `s`.

Thus, `z[k] = p` tells us that `s[0...p−1] = s[k...k+p−1]`.

Many string processing problems can be efficiently solved using the Z-array.


## Z-array of `ACBACDACBACBACDA`

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
| - | - | - | - | - | - | - | - | - | - | -- | -- | -- | -- | -- | -- |
| A | C | B | A | C | D | A | C | B | A | C  | B  | A  | C  | D  | A  |
| – | 0 | 0 | 2 | 0 | 0 | 5 | 0 | 0 | 7 | 0  | 0  | 2  | 0  | 0  | 1  |

`z[6] = 5`, because the substring `ACBAC` of length 5 is a prefix of `s`, but the substring
`ACBACB` of length 6 is not a prefix of `s`.


## Algorithm description (how Z is computed in O(n))

The Z-algorithm constructs the Z-array in `O(n)` time.

The algorithm calculates Z-values from left to right by:

* using information already stored in the Z-array
* and only comparing characters when needed

To do this efficiently, the algorithm maintains a range:

`[x, y]`

such that:

* `s[x...y]` is a prefix of `s`
* and `y` is as large as possible

Since we know that:

`s[0...y-x] = s[x...y]`

we can reuse this information when calculating `z[x+1], z[x+2], ..., z[y]`.


## Key case analysis at position k

At each position `k`, we first check `z[k-x]`.

### Case 1: k is inside the current window and fully fits

If:

`k + z[k-x] < y`

then we know:

`z[k] = z[k-x]`

(no new comparisons needed)

### Case 2: k is inside the window but may extend past y

If:

`k + z[k-x] ≥ y`

then we know:

`s[0...y-k] = s[k...y]`

and we must extend the match beyond `y` by comparing characters one by one.

Still the total runtime is `O(n)`, because:

* we start comparisons from the boundary
* `y` only moves forward
* total increases/decreases of the match length are bounded by `O(n)`


## Example walkthrough (same string)

String:

`ACBACDACBACBACDA`

After calculating `z[6] = 5`, the current range is:

`[x, y] = [6, 10]`

because:

`s[6...10] = ACBAC`
matches prefix `s[0...4] = ACBAC`

Now, since `s[0...4] = s[6...10]`, we can fill subsequent values quickly:

* `z[7] = z[1] = 0`
* `z[8] = z[2] = 0`

Then, since `z[3] = 2`, we know:

`z[9] ≥ 2`

but because we may extend past position `10`, we compare further characters.

It turns out:

`z[9] = 7`

so the new range becomes:

`[x, y] = [9, 15]`

After that, all remaining Z-values are determined using already stored values.


## Using the Z-array for pattern matching

We can solve pattern matching (find occurrences of pattern `p` in string `s`) using the Z-array.

Construct a combined string:

`p#s`

where `#` is a special character that does not occur in `p` or `s`.

Then:

* compute Z-array of `p#s`
* any position where `z[i] = |p|` means `p` occurs in `s`

Example:

`s = HATTIVATTI`
`p = ATT`

String:

`ATT#HATTIVATTI`

Z-array:

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 |
| - | - | - | - | - | - | - | - | - | - | -- | -- | -- | -- |
| A | T | T | # | H | A | T | T | I | V | A  | T  | T  | I  |
| – | 0 | 0 | 0 | 0 | 3 | 0 | 0 | 0 | 0 | 3  | 0  | 0  | 0  |

The values `3` at positions `5` and `10` mean that pattern `ATT` occurs in `HATTIVATTI`
at those positions.

The total time complexity is linear because:

* building the Z-array is `O(n)`
* scanning it is `O(n)`



## Implementation (C++)

```cpp
vector<int> z(string s) {
  int n = s.size();
  vector<int> z(n);
  int x = 0, y = 0;

  for (int i = 1; i < n; i++) {
    z[i] = max(0, min(z[i - x], y - i + 1));

    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      x = i;
      y = i + z[i];
      z[i]++;
    }
  }
  return z;
}
```

Time complexity: `O(n)`
Space complexity: `O(n)`
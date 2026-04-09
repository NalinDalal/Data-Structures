# Sieve of Eratosthenes

It is a pre-processing algorithm that builds an array using which we can efficiently check if a given number b/w 2...n is prime
if not, then find prime factor of number.

make an array `sieve[n]` where 

`sieve[k]=0=> k is prime`
`sieve[k]!=0 => k is not prime & prime factor=sieve[k]`


now when algorithm finds that `x` is prime, it automatically handle the cases for multiples of `x` i.e. `2x,3x,4x etc`.

consider when n=20 =>

 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20
[0,0,2,0,3,0,2,3,5,0,3,0,7,5,2,0,3,0,5]

code assumes that each element of sieve is 0

```cpp
for(int x=2;x<=n;x++){
    if(sieve[x]) continue;
    for(int u=x*2;u<=n;u+=x){
        sieve[u]=x;
    }
}
```

inner loop executes n/x time for each value of x.

\sum{x=2}{n}{n/x}= n/2+n/3+n/4+....+n/n 
= O(n logn)

run time is only O(n log log n), nearing about O(n)

alt:
```cpp
memset(numDiffPF,0,sizeof numDiffPF);
for(int i=2;i<MAX_N;i++)
    if(numDiffPF[i]==0)         // i is a prime number
        for(int j=i;j<MAX_N;j+=i)
            numDiffPF[j]++;     //increase value of multiples of i
```

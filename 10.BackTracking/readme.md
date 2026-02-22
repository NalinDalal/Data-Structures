# BackTracking
begins with an empty solution and extends the solution step by step. 
The search recursively goes through all different ways how a solution can be constructed.
It is a systematic method to iterate through all possible configration of a search space

so you have a pre-existing incomplete solution, you add a element, and check if it works or not
if it works, then you add it to permanent solution and move ahead for next element
if not then you delete it and try for some other element

```cpp
bool finished = FALSE; /* found all solutions yet? */
backtrack(int a[], int k, data input){
    int c[MAXCANDIDATES]; /* candidates for next position */
    int ncandidates; /* next position candidate count */
    int i; /* counter */

    if (is_a_solution(a,k,input))   //test whether 1st k element are solution or not
        process_solution(a,k,input);    //process solution once constructed
    else {
        k = k+1;
        construct_candidates(a,k,input,c,&ncandidates); //fills array c with complete set of possible candidates for the kth position of a
        for (i=0; i<ncandidates; i++) {
            a[k] = c[i];
            backtrack(a,k,input);
            if (finished) return; /* terminate early */
        }
    }
}
```

constructing all of subsets:
```cpp
is_a_solution(int a[], int k, int n)
return (k == n);

{
    /* is k == n? */
    construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
    c[0] = TRUE;
    c[1] = FALSE;
    *ncandidates = 2;
}

process_solution(int a[], int k){
    int i; /* counter */
    printf("{");
    for (i=1; i<=k; i++)
        if (a[i] == TRUE) printf(" %d",i);
    
    printf(" }\n");
}

generate_subsets(int n){
    int a[NMAX]; /* solution vector */
    backtrack(a,0,n);
}
```

constructing all permutations:
```cpp
construct_candidates(int a[], int k, int n, int c[], int *ncandidates){
    int i; /* counter */
    bool in_perm[NMAX]; /* who is in the permutation? */
    for (i=1; i<NMAX; i++) in_perm[i] = FALSE;
    for (i=0; i<k; i++) in_perm[ a[i] ] = TRUE;
    *ncandidates = 0;
    for (i=1; i<=n; i++){
        if (in_perm[i] == FALSE) {
            c[ *ncandidates] = i;
            *ncandidates = *ncandidates + 1;
        }
    }
}
```


u place queens on each square, check if they attack each other then you move back to previous safe state

```cpp
void search(int y) {
    if (y == n) {
        count++;
        return;
    }
    for (int x = 0; x < n; x++) {
        if (column[x] || diag1[x+y] || diag2[x-y+n-1]) continue;
        column[x] = diag1[x+y] = diag2[x-y+n-1] = 1;
        search(y+1);
        column[x] = diag1[x+y] = diag2[x-y+n-1] = 0;
    }
}
process_solution(int a[], int k){
    int i; /* counter */
    for (i=1; i<=k; i++) 
        printf(" %d",a[i]);
    printf("\n");
}
{
is_a_solution(int a[], int k, int n)
return (k == n);
generate_permutations(int n)
int a[NMAX]; backtrack(a,0,n);
}

construct_candidates(int a[], int k, int n, int c[], int *ncandidates){
    int i,j; /* counters */
    bool legal_move; /* might the move be legal? */
    *ncandidates = 0;
    for (i=1; i<=n; i++) {
        legal_move = TRUE;
        for (j=1; j<k; j++) {
            if (abs((k)-j) == abs(i-a[j])) /* diagonal threat */
                legal_move = FALSE;
            if (i == a[j]) /* column threat */
                legal_move = FALSE;
        }
        if (legal_move == TRUE) {
            c[*ncandidates] = i;
            *ncandidates = *ncandidates + 1;
        }
    }
}


process_solution(int a[], int k){
    int i; /* counter */
    solution_count ++;
}

is_a_solution(int a[], int k, int n){
    return (k == n);
}

nqueens(int n){
    int a[NMAX]; /* solution vector */
    solution_count = 0;
    backtrack(a,0,n);
    printf("n=%d solution_count=%d\n",n,solution_count);
}
```

q(n) denote the number of ways to place n queens on an n × n chessboard.
increases exponentially

## Pruning the Search
optimise by pruning search tree
idea: add ”intelligence” to the algorithm so that it will notice as soon as possible if a partial solution cannot be extended to a complete solution


**Basic algorithm**
• running time: 483 seconds
• number of recursive calls: 76 billion

**Optimisation 1:**
we first move one step down or right. There are always two
paths that are symmetric about the diagonal of the grid after the first step

decide that we always first move one step down (or right), and
finally multiply the number of solutions by two
• running time: 244 seconds
• number of recursive calls: 38 billion

**Optimisation 2:**
If the path reaches the lower-right square before it has visited all other squares
of the grid, it is clear that it will not be possible to complete the solution.
• running time: 119 seconds
• number of recursive calls: 20 billion

**Optimisation 3:**
If the path touches a wall and can turn either left or right, the grid splits into
two parts that contain unvisited squares.

• running time: 1.8 seconds
• number of recursive calls: 221 million

**Optimisation 4:**
if the path cannot continue
forward but can turn either left or right, the grid splits into two parts that both
contain unvisited squares
cannot visit all squares anymore, so we can terminate the
search.
• running time: 0.6 seconds
• number of recursive calls: 69 million

---

## N Queen
u are given a nxn chessboard, now you need to place n queen on it so that no queen attacks it
has 92 solutions by trial and
error in a few hours.

place queens on the board one row at a time, starting with the top row. 
To place the rth queen, we methodically try all n squares in row r from left to right in a simple for loop.
if attacks then ignore, else put a queen

Q[1...n]: position of queens
Q[i] : which square in row i contains a queen
r : index of 1st empty row,
Q[1 .. r−1]: positions of the first r−1 queens
```
PlaceQueens(Q[1 .. n], r):
    if r = n + 1
        printQ[1 .. n]
    else
        for j ←1 to n
            legal←True
            for i ←1 to r−1
                if (Q[i] = j) or (Q[i] = j + r−i) or (Q[i] = j−r + i)
                    legal←False
            if legal
                Q[r] ←j
                PlaceQueens(Q[1 .. n], r + 1) 
```

## Game Trees
- An n×n grid with a border of squares around it
- Two players: Horace (horizontal) and Vera (vertical)
- Each player has n tokens

Starting positions:
- Horace's n tokens sit in the left border, one per row — they move rightward
- Vera's n tokens sit in the top border, one per column — they move downward


Turns (alternating):

|Player	|Move|	Jump|
|-------|----|------|
|Horace	|Move a token 1 step right into an empty square|	Jump over exactly one of Vera's tokens, landing 2 steps right in an empty square|
|Vera	|Move a token 1 step down into an empty square|	Jump over exactly one of Horace's tokens, landing 2 steps down in an empty square|

If a player has no legal moves or jumps, they pass.

Winning condition: First player to move all their tokens off the opposite edge of the board wins.

following recursive backtracking algorithm to determine whether a given game state is good or bad. 
At its core, this algorithm is just a depth-first search of the game tree; 
equivalently, the game tree is the recursion tree of the algorithm
```
PlayAnyGame(X , player):
    if player has already won in state X
        return Good
    if player has already lost in state X
        return Bad
    for all legal moves X-> Y
        if PlayAnyGame(Y,~player) = Bad
            return Good 〈〈X Y is a good move〉〉
    return Bad 〈〈There are no good moves〉〉
```

## Subset Sum
Given a set X of positive integers and target integer T , is there a subset of elements in X that add up to T

X = {8, 6, 7, 5, 3, 10, 9}and T = 15,
true; {8, 7}and {7, 5, 3}and {6, 9}and {5, 10}all sum to 15

2 cases:
if (T=0) return true
else if (T<0 or (T!=0 && set X is empty)) return False

There is a subset of X that sums to T if:
- There is a subset of X that includes x and whose sum is T .
- There is a subset of X that excludes x and whose sum is T .

```cpp
//Does any subset of X sum to T ?〉〉
SubsetSum(X , T ):
    if T = 0
        return True
    else if T <0 or X = ∅
        return False
    else
        x ←any element of X
        with ←SubsetSum(X \{x}, T−x) 〈〈Recurse!〉〉
        wout←SubsetSum(X \{x}, T ) 〈〈Recurse!〉〉
        return (with∨wout)
```

T (n) ≤2T (n−1) + O(1)
T (n) = O(2n)

## Text Segmentation

Problem: Given a string of characters with no spaces, determine if it can be broken into valid words.

Input: A string `A[1..n]` and a subroutine `IsWord(w)` that returns true if `w` is a valid word.

Key insight: Process the string left to right. At each position, try every possible next word — if `A[i..j]` is a valid word, recursively check if the remaining suffix `A[j+1..n]` can also be segmented. If any choice works, return success.

Example: `BOTHEARTHANDSATURNSPIN` can be split as:
- `BOTH · EARTH · AND · SATURN · SPIN`, or
- `BOT · HEART · HANDS · AT · URNS · PIN`

Recursive structure: Only the unprocessed suffix matters — past decisions are irrelevant. Different sequences of past splits leading to the same suffix face the exact same subproblem. This makes it a natural fit for memoisation/dynamic programming.
```
Splittable(A[1..n]):
    if n = 0
        return True
    for i ← 1 to n
        if IsWord(A[1..i]) and Splittable(A[i+1..n])
            return True
    return False
```

### Index Formulation
rewrite the problem: Given an index i, find a segmentation of the suﬃx A[i .. n].

- for (i, j)(if A[i .. j] is a word){ IsWord(i, j) = True}
- if (suﬃx A[i .. n] can be split into words){Splittable(i) = True}

```
Splittable(i):
    if i >n
        return True
    for j ←i to n
        if IsWord(i, j)
            if Splittable( j + 1)
                return True
    return False
```

The recurrence for the running time is:

$$T(n) \leq \sum_{i=0}^{n-1} T(i) + O(n)$$

To solve it, let $T(n) = \sum_{i=0}^{n-1} T(i) + \alpha n$ and $T(n-1) = \sum_{i=0}^{n-2} T(i) + \alpha(n-1)$.

Subtracting: $T(n) - T(n-1) = T(n-1) + \alpha$, so $T(n) = 2T(n-1) + \alpha$.

$$\implies T(n) = O(2^n)$$

## Longest Increasing Subsequence
Given two indices i and j, where i < j, find the longest increasing
subsequence of A[ j.. n] in which every element is larger than A[i].
```
LISbigger(prev, A[1 .. n]):
    if n = 0
        return 0
    else if A[1] ≤prev
        return LISbigger(prev, A[2 .. n)
    else:
        skip←LISbigger(prev, A[2 .. n])
        take←LISbigger(A[1], A[2..n])+1
        return max{skip, take}
```
alt:
```
LISbigger(i, j):
    if j >n
        return 0
    else if A[i] ≥A[ j]
        return LISbigger(i, j + 1)
    else
        skip←LISbigger(i, j + 1)
        take←LISbigger( j, j + 1) + 1
        return max{skip, take}
```

## Longest Increasing Subsequence 2
instead of asking “Is A[i] the next element of the output sequence?”, we could
ask directly, “Where is the next element of the output sequence, if any?”

or

Given an index i, find the longest increasing subsequence of A[i .. n] that
begins with A[i].

LISfirst(i) =length of longest increasing subsequence of A[i .. n] that begins with A[i].

`LISfirst(i) = 1 + max {LISfirst( j) | j >i and A[ j] >A[i]}`

```
for(j>i){
    if (A[ j] <=A[i]){
        LISfirst(i) = 1
    }
}

LISfirst(i){
    best←0
    for (j ←i + 1 to n){
        if(A[ j] >A[i])
            best=max(best,LISFirst(j))
    return 1 + best
    }
}
```
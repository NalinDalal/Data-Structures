# BackTracking
begins with an empty solution and extends the solution step by step. 
The search recursively goes through all different ways how a solution can be constructed.
It is a systematic method to iterate through all possible configration of a search space

so you have a pre-existing incomplete solution, you add a element, and check if it works or not
if it works, then you add it to permanent solution and move ahead for next element
if not then you delete it and try for some other element
```
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
{
return (k == n); }
{
/* is k == n? */
construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
c[0] = TRUE;
c[1] = FALSE;
*ncandidates = 2;
}

process_solution(int a[], int k)
{
int i; /* counter */
printf("{");
for (i=1; i<=k; i++)
    if (a[i] == TRUE) printf(" %d",i);

printf(" }\n");
}

generate_subsets(int n)
{
int a[NMAX]; /* solution vector */
backtrack(a,0,n);
}
```


constructing all permutations:
```cpp
construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
int i; /* counter */
bool in_perm[NMAX]; /* who is in the permutation? */
for (i=1; i<NMAX; i++) in_perm[i] = FALSE;
for (i=0; i<k; i++) in_perm[ a[i] ] = TRUE;
*ncandidates = 0;
for (i=1; i<=n; i++)
if (in_perm[i] == FALSE) {
c[ *ncandidates] = i;
*ncandidates = *ncandidates + 1;
}
}
```


u place queens on each square, check if they attack each other then you move back to previous safe state

```
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
process_solution(int a[], int k)
{
int i; /* counter */
for (i=1; i<=k; i++) printf(" %d",a[i]);
printf("\n");
}
{
}
{
is_a_solution(int a[], int k, int n)
return (k == n);
generate_permutations(int n)
int a[NMAX]; backtrack(a,0,n);
}

construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
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


process_solution(int a[], int k)
{
int i; /* counter */
solution_count ++;
}

is_a_solution(int a[], int k, int n){
    return (k == n);
}

nqueens(int n)
{
int a[NMAX]; /* solution vector */
solution_count = 0;
backtrack(a,0,n);
printf("n=%d solution_count=%d\n",n,solution_count);}
```

 q(n) denote the number of ways to place n queens on an n × n chessboard.
 increases exponentially

 ## Pruning the Search
 optimise by pruning search tree
 idea: add ”intelligence” to the algorithm so that it will notice as soon as possible if a
partial solution cannot be extended to a complete solution

```cpp

```
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
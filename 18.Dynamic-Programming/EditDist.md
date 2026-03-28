# Edit Distance/Levenshtein distance
The *edit distance* between two strings is the minimum number of letter inser-
tions, letter deletions, and letter substitutions required to transform one string
into the other.

Ex: FOOD, MONEY
FOOD →MOOD →MOND →MONED →MONEY
Edit distance = 4 

> Edit distance is the minimum number of insertions, deletions, or substitutions needed to transform one string into another.

We compare prefixes of the two strings and build the answer gradually.

Let:
- `A` = string1 (length m)
- `B` = string2 (length n)

```
Edit(i, j) = edit distance between
A[1...i] and B[1...j]
```

Think:
>   At every step, we decide the best operation for the last character.

Take another example:
Ex: LOVE and MOVIE
LOVE -> MOVE(modify) -> MOVIE(insert)
cost = 2

given a string x of length n and a string y of length m, and we want to calculate the edit distance between x and y.


Relation:
$$ 
Edit(i,j)=\min\begin{cases}Edit(i-1,j)+1\Edit(i,j-1)+1\Edit(i-1,j-1)+[A_i \ne B_j]\end{cases}
$$


$$
Edit(i,j) = \min \begin{cases}
Edit(i-1,j) + 1 \\
Edit(i,j-1) + 1 \\
Edit(i-1,j-1) + [A_i \ne B_j]
\end{cases}
$$



| Case                    | Operation  | Explanation        |
| ----------------------- | ---------- | ------------------ |
| `Edit(i-1, j) + 1`      | Delete     | remove char from A(e.g. ABC→ AC) |
| `Edit(i, j-1) + 1`      | Insert     | add char to A(e.g. ABC→ ABCA)      |
| `Edit(i-1, j-1) + cost` | Substitute | change char(e.g. ABC→ ADC)        |

Where:

```
cost = 0 if A[i] == B[j]
cost = 1 otherwise
```


```
• distance(a,b− 1): insert a character at the end of x
• distance(a− 1,b): remove the last character from x
• distance(a− 1,b− 1): match or modify the last character of x
```



**Base Case:**
If one string is empty:

```
Edit(0, j) = j     (j insertions)
Edit(i, 0) = i     (i deletions)
Edit(0,0) = 0
```



We create a 2D table:

```
        ""  M  O  N  E  Y
""      0   1  2  3  4  5
F       1
O       2
O       3
D       4
```

Fill row by row using recurrence.

Final answer = bottom-right cell.


##  Algorithm (Step-by-step)

1. Create matrix `dp[m+1][n+1]`
2. Fill first row and column
3. Fill remaining cells using recurrence
4. Return `dp[m][n]`

```
function editDistance(A, B):

    m = length(A)
    n = length(B)

    create dp[m+1][n+1]

    for i in 0..m:
        dp[i][0] = i

    for j in 0..n:
        dp[0][j] = j

    for i in 1..m:
        for j in 1..n:

            if A[i] == B[j]:
                cost = 0
            else:
                cost = 1

            dp[i][j] = min(
                dp[i-1][j] + 1,      // delete
                dp[i][j-1] + 1,      // insert
                dp[i-1][j-1] + cost  // substitute
            )

    return dp[m][n]
```



| Metric          | Value       |
| --------------- | ----------- |
| Time            | O(mn)       |
| Space           | O(mn)       |
| Optimized Space | O(min(m,n)) |


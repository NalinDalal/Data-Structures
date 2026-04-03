# Scheduling Classes

So there are say multiple classes in a day scheduled for random time in day 
Now you want to take as many as classes as possible

different start time and different end time in the day.
The registration computer won't let you register for overlapping classes. 

given 2 arrays:
`S[1...n]`
`F[1...n]`

ex

|event|Start Time | End Time |
|------|----------|----------|
|A | 1 | 3 |
|B | 2 | 5 |
|C | 3 | 9 |
|D | 6 | 8 |


listing start+finish time of each class.

for each i: 0<=S[i]<=F[i]<=M {say some M}

Problem: choose largest possible subset X belongs to {1,2,....,n} so that for any {i,j} belong to X

either `S[i]>F[j]` or `S[j]>F[i]`

Recursive Solution: Either take a class or Don't . Let

B: set of classes that end before class 1 starts
A: set of classes that start after class 1 ends

`B={i | 2<=i<=n and F[i]<S[1]}`
`A={i | 2<=i<=n and S[i]>F[1]}`

Try both and then take whatever gives the better schedule.
Apply recursion and we get a dp algorithm of $O(n^{3})$ time.

Intuition says to follow a simple greedy algorithm.
Scan the classes in order of finish time: get class that doesn't interfere with current then acept it.

```
GreedySchedule(S[1...n], F[1...n]):
    sort F and permute S to match
    count=1 
    X[count]=1 
    for(i=2 to n){
        if(S[i]>F[X[count]]){
            count=count+1 
            X[count]=i
        }
    }
    return X[1...count]
```


Apply a sort, then it's a simple linear time loop; time complexity: $O(n log n)$

## Algorithm 1:

1st idea is to select as *short* events as possible.
but it's won't always work

## Algorithm 2:

To select next possible events that *begins as early* as possible.
but this also won't work, consider if there is a schedule that start early and goes throug whole; 
if you select this, you can't select any other

## Algorithm 3:

To select next possible events that ends as early as possible.

Always produces **Optimal Solution**

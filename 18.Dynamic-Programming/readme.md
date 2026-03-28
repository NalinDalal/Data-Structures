# Dynamic programming

So basically dynamic programming says to optimise a problem solution via breaking it down into sub-problems so that the it remembers past to avoid recomputing for tough sub-problems
Instead of solving the same subproblem repeatedly (like naive recursion does), DP *caches* the answer the first time and looks it up later.

A dynamic-programming algorithm solves
every subsubproblem just once and then saves its answer in a table, thereby avoiding 
the work of recomputing the answer every time the subsubproblem is encountered.

we need to optimise the solution, call it *optimal solution*
4 steps:
1. Characterize the structure of an optimal solution.
2. Recursively define the value of an optimal solution.
3. Compute the value of an optimal solution in a bottom-up fashion.
4. Construct an optimal solution from computed information.


There are multiple standard topics, let's take alook at them one-by-one:

[Assembly Line Scheduling](./AssemblyLineSchedule.md)
[Foundation](./Foundation.md)
[Longest Increasing SubSequence](./LIS.md)
[Path in a Grid](./path-grid.md)
[Edit Distance](./EditDist.md)


Problems:

* Fibonacci (top-down + bottom-up)
* Coin change (min coins)
* Dice combinations (CSES)


https://www.youtube.com/playlist?list=PLcXpkI9A-RZI-xF76L0sZq_u-k_yHz8pd

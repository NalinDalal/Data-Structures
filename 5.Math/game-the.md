
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



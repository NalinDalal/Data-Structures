// Game Tree — Backtracking / Minimax for the Horace-vs-Vera grid game
// Horace's tokens move RIGHT, Vera's tokens move DOWN.
// A token can move 1 step into an empty square, or jump over exactly one
// opponent token into an empty square 2 steps away.
// First player to move all tokens off the board wins.
//
// PlayAnyGame(X, player):
//     if player already won  → return Good
//     if player already lost → return Bad
//     for each legal move X → Y
//         if PlayAnyGame(Y, ~player) == Bad → return Good
//     return Bad

#include <iostream>
#include <vector>
#include <set>
using namespace std;

// Board size (change for experimentation; keep small — state space is huge)
const int N = 3;

// grid[r][c]:  0 = empty, 1 = Horace token, 2 = Vera token
// Horace tokens: stored as column positions for each row  (col  0 = left border)
// Vera   tokens: stored as row    positions for each col  (row  0 = top  border)
// When a token moves past column N (or row N) it is "off the board".

struct State {
    // hPos[i] = column of Horace's token in row i  (1..N grid, 0 = border)
    //           N+1 means the token has exited the board
    // vPos[j] = row    of Vera's  token in col j
    //           N+1 means the token has exited the board
    vector<int> hPos, vPos;

    bool operator<(const State& o) const {
        if (hPos != o.hPos) return hPos < o.hPos;
        return vPos < o.vPos;
    }
};

// Check if a grid cell is occupied by any token
// Returns 0 (empty), 1 (Horace), 2 (Vera)
int cellOccupant(const State& s, int r, int c) {
    // Horace token in row r at column hPos[r]
    if (r >= 0 && r < N && s.hPos[r] == c && c >= 1 && c <= N)
        return 1;
    // Vera token in column c at row vPos[c]
    if (c >= 0 && c < N && s.vPos[c] == r && r >= 1 && r <= N)
        return 2;
    return 0;
}

// Has Horace won? All his tokens are off the right edge (col > N)
bool horaceWon(const State& s) {
    for (int i = 0; i < N; i++)
        if (s.hPos[i] <= N) return false;
    return true;
}

// Has Vera won? All her tokens are off the bottom edge (row > N)
bool veraWon(const State& s) {
    for (int j = 0; j < N; j++)
        if (s.vPos[j] <= N) return false;
    return true;
}

// Generate all successor states for the current player
// player: 1 = Horace, 2 = Vera
vector<State> getLegalMoves(const State& s, int player) {
    vector<State> moves;

    if (player == 1) { // Horace — move right
        for (int i = 0; i < N; i++) {
            int c = s.hPos[i];
            if (c > N) continue; // already off the board

            // Move 1 step right
            int nc = c + 1;
            if (nc > N) {
                // token exits the board — always legal
                State ns = s;
                ns.hPos[i] = N + 1;
                moves.push_back(ns);
            } else if (cellOccupant(s, i, nc) == 0) {
                State ns = s;
                ns.hPos[i] = nc;
                moves.push_back(ns);
            }

            // Jump over a Vera token 2 steps right
            int mc = c + 1; // middle cell (must hold Vera)
            int jc = c + 2; // landing cell
            if (mc >= 1 && mc <= N && cellOccupant(s, i, mc) == 2) {
                if (jc > N) {
                    // exits board
                    State ns = s;
                    ns.hPos[i] = N + 1;
                    moves.push_back(ns);
                } else if (cellOccupant(s, i, jc) == 0) {
                    State ns = s;
                    ns.hPos[i] = jc;
                    moves.push_back(ns);
                }
            }
        }
    } else { // Vera — move down
        for (int j = 0; j < N; j++) {
            int r = s.vPos[j];
            if (r > N) continue;

            // Move 1 step down
            int nr = r + 1;
            if (nr > N) {
                State ns = s;
                ns.vPos[j] = N + 1;
                moves.push_back(ns);
            } else if (cellOccupant(s, nr, j) == 0) {
                State ns = s;
                ns.vPos[j] = nr;
                moves.push_back(ns);
            }

            // Jump over a Horace token 2 steps down
            int mr = r + 1;
            int jr = r + 2;
            if (mr >= 1 && mr <= N && cellOccupant(s, mr, j) == 1) {
                if (jr > N) {
                    State ns = s;
                    ns.vPos[j] = N + 1;
                    moves.push_back(ns);
                } else if (cellOccupant(s, jr, j) == 0) {
                    State ns = s;
                    ns.vPos[j] = jr;
                    moves.push_back(ns);
                }
            }
        }
    }
    return moves;
}

// Memoisation cache:  state+player → Good(true) / Bad(false)
#include <map>
map<pair<State, int>, bool> memo;

// PlayAnyGame: returns true if the current state is GOOD for `player`
// i.e. the current player (whose turn it is) can force a win.
// `player` is the one about to move.
bool PlayAnyGame(const State& s, int player) {
    // Terminal checks — from the perspective of the moving player
    if (player == 1) {
        if (horaceWon(s)) return true;  // Horace already won
        if (veraWon(s)) return false;   // Vera already won
    } else {
        if (veraWon(s)) return true;
        if (horaceWon(s)) return false;
    }

    auto key = make_pair(s, player);
    if (memo.count(key)) return memo[key];

    int opponent = (player == 1) ? 2 : 1;
    vector<State> moves = getLegalMoves(s, player);

    // If no legal moves, the player passes — opponent moves next
    if (moves.empty()) {
        bool result = !PlayAnyGame(s, opponent); // pass = opponent moves
        return memo[key] = result;
    }

    for (const State& next : moves) {
        // If this move leads to a BAD state for the opponent, it's GOOD for us
        if (!PlayAnyGame(next, opponent)) {
            return memo[key] = true;
        }
    }
    // All moves lead to good states for the opponent → BAD for us
    return memo[key] = false;
}

// Pretty-print the board
void printBoard(const State& s) {
    // Header: Vera tokens in top border
    cout << "  ";
    for (int j = 0; j < N; j++)
        cout << (s.vPos[j] == 0 ? 'V' : '.') << ' ';
    cout << "\n";

    for (int r = 1; r <= N; r++) {
        // Left border: Horace token?
        bool hInBorder = false;
        for (int i = 0; i < N; i++)
            if (s.hPos[i] == 0 && i == r - 1) hInBorder = true;
        cout << (hInBorder ? 'H' : '.') << ' ';

        for (int c = 1; c <= N; c++) {
            int occ = cellOccupant(s, r - 1, c); // row index for Horace is i (0-based)
            // Need to check all tokens
            char ch = '.';
            for (int i = 0; i < N; i++)
                if (s.hPos[i] == c && i == r - 1) ch = 'H';
            for (int j = 0; j < N; j++)
                if (s.vPos[j] == r && j == c - 1) ch = 'V';
            cout << ch << ' ';
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    // Initial state: Horace tokens in column 0 (left border), rows 0..N-1
    //                Vera   tokens in row    0 (top  border), cols 0..N-1
    State init;
    init.hPos.assign(N, 0);
    init.vPos.assign(N, 0);

    cout << "=== Grid Game — Game Tree (Minimax Backtracking) ===" << endl;
    cout << "Board size: " << N << " x " << N << "\n\n";
    cout << "Initial board:\n";
    printBoard(init);

    // Horace moves first (player 1)
    bool horaceCanWin = PlayAnyGame(init, 1);

    cout << "Result: ";
    if (horaceCanWin)
        cout << "Horace (first player, moves RIGHT) can FORCE A WIN." << endl;
    else
        cout << "Vera (second player, moves DOWN) can FORCE A WIN." << endl;

    cout << "States explored (memoised): " << memo.size() << endl;

    return 0;
}

/* UVa problem: 11195 - AnotherNQueenProblem
 *
 * Topic: Backtracking
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *  Classic N-Queens problem but the chessboard can be up to 14x14 large
 *  and there are some invalid spaces.
 *
 * Solution Summary:
 *  Calculate the potential moves for the next column using bitmasks 
 *  to keep track of available rows, diagonals, and invalid spaces.
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *
 * I hereby certify that I have produced the following solution myself
 * using the resources listed above in accordance with the CMPUT 403
 * collaboration policy.
 *
 * --- Tamara Bain
 *
 * Language: C++11
 */
 
#include <cstdio>
#include <cstring>

using namespace std;

int answer, N, solve_mask, x;
int board[14];

void solve(int col, int rows, int leftdiag, int rightdiag) {
    // base case
    if (rows == solve_mask) {
        ++answer;
        return;
    }
    
    // calculate the positions for this column
    int pos = solve_mask & (~(rows | leftdiag | rightdiag | board[col]));
    
    while (pos) {
        int p = pos & -pos;
        // set bit as unavailable
        pos -= p;
        solve(col+1, rows | p, (leftdiag | p) << 1, (rightdiag | p) >> 1);
    }
    
}

int main() {
    int testcase = 1;
    char in_char;
    

    while(scanf("%d", &N), N) {
        
        answer = 0;
        for(int i = 0; i < 14; ++i)
            board[i] = 0;
        
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) { 
                
                scanf("%c",  &in_char);
                if (in_char == '\n')
                    --j;
                
                // save as bitmasks
                if (in_char == '*')
                    board[i] ^= (1<<j);
            }
        }
        
        solve_mask = (1 << N) - 1;
        solve(0, 0, 0, 0);
        printf("Case %d: %d\n", testcase, answer);
        ++testcase;
    }
        
}
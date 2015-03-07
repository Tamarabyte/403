/* UVa problem: 167 - TheSultansSuccessors
 *
 * Topic: Backtracking
 *
 * Level: trivial
 *
 * Brief problem description:
 *    8 queens problemm, but each square has a value. You want
 *    the combination of squares that sums to the higest value.
 *
 * Solution Summary:
 *    Used backtracking, checked that each solution was valid before placing it.
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
#include <cstdlib>
#include <cstring>

using namespace std;
const int N = 8;
int rows[N], highest, solution;
int board[N][N];

// check previous placed positions
bool place(int row, int col) {
    for (int prev = 0; prev < col; prev++)
        if (rows[prev] == row || abs(rows[prev] - row) == abs(prev - col))
            return false;
    return true;
}
    
    
void backtrack(int col) {
    //base case
    if (col == N) {
        highest = highest > solution ? highest : solution;
    }
        
    // backtracking step
    for (int row = 0; row < N; row++)
        if(place(row, col)) {
            rows[col] = row;
            solution += board[row][col];
            backtrack(col + 1);
    
            rows[col] = -1;
            solution -= board[row][col];
        }
}

int main() {
    int testcases, solution, spaces, N = 8;

    
    scanf("%d", &testcases);
    
    while(testcases--) {
        
        for (int i = 0; i < N; i++)
        
        memset(board, 0, sizeof(int) * N * N);
        memset(rows, -1, sizeof(int) * N);
        highest = 0;
        solution = 0;
        
        // populate board
        for (int i = 0; i < N; ++i)
            for (int j =0; j < N; ++j)
                scanf("%d", &board[i][j]);
        
        backtrack(0);
        printf("%5d\n", highest);
    }
}

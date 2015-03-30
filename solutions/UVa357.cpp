/* UVa problem: 357 - LetMeCountTheWays
 *
 * Topic: Dynamic Programming
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *  Figure out how many possible ways there are to make change for a given value.
 *  With possible value from 0 .. 30000
 *
 * Solution Summary:
 *  Use bottom up dynamic programming. Table is filled out as number of ways with coin
 *  + number of ways without coin. We start by calculating the lowest coin and work
 *  up, while it would be possible to store everything in O(N) space, we want to cache
 *  combinations for all coins so we can continue to use our table on all future iterations.
 *  (Doable because the coinset doesn't change)
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   Referenced my solution for UVa674
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

const int types = 5;
int coins[types] = {1, 5, 10, 25, 50};
long long dp[30001][types];

long long max_ways(int highest_calc, int N) {

    // fill out our table by value
    for (int i = highest_calc+1; i <= N; ++i) {

        dp[i][0] = 1;
        // sum number of combinations with coin + number without coint
        for (int j = 1; j < types; ++j) {
            dp[i][j] = (coins[j] <= i) ? dp[i - coins[j]][j] : 0;
            dp[i][j] += dp[i][j-1];
        }
    }


    return dp[N][types - 1];
}

int main() {
    long long ways;
    int N, highest_calc;
    highest_calc = 0;

    // initial value for N = 0 is 1 (no coins)
    for (int j = 0; j < types; ++j)
        dp[0][j] = 1;

    // read test cases until end of file
    while(scanf("%d", &N) == 1) {

        // look up N from a table or calculate it
        if (N <= highest_calc) {
            ways = dp[N][types - 1];
        }
        else {
            ways = max_ways(highest_calc, N);
            highest_calc = N;
        }

        if (ways > 1)
            printf("There are %lld ways to produce %d cents change.\n", ways, N);
        else
            printf("There is only %lld way to produce %d cents change.\n", ways, N);
    }


}

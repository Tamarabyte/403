/* UVa problem: 674 - CoinChange
 *
 * Topic: Dynamic Programming
 *
 * Level: trivial
 *
 * Brief problem description:
 *   Given a value and the set of coin denominations determine the number of possible
 *   combinations of denominations that can make up the given value.
 *
 * Solution Summary:
 *   Use dynamic programming (I used the bottom up approach). For
 *   each step in 0 .. value, the number of possible ways to make
 *   change is the number of ways to make change with the coin +
 *   number of ways to make change without the coin. I could have further
 *   optimized and made the table smaller (we only need an array of N
 *   if we calculate coins one at a time).
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
using namespace std;

const int types = 5;
int coins[types] = {1, 5, 10, 25, 50};
int table[7490][types];

int max_ways(int highest_calc, int N) {

    // fill out our table by value
    for (int i = highest_calc+1; i < N + 1; ++i) {

        // number of combinatons for just pennies is always 1
        table[i][0] = 1;

        for (int j = 1; j < types; ++j) {

            // number of combinatons if we include the coin
            table[i][j] = (coins[j] <= i) ? table[i - coins[j]][j] : 0;

            // plus number of combinatons not containing the coin
            table[i][j] += table[i][j-1];
        }
    }


    return table[N][types - 1];
}

int main() {

    int ways, N, highest_calc;
    highest_calc = 0;

    // initial value for N = 0 is 1 (no coins)
    for (int j = 0; j < types; ++j)
        table[0][j] = 1;

    // read test cases until end of file
    while(scanf("%d", &N) == 1) {

        // if we've already looked up N, don't bother calculating again
        if (N <= highest_calc) {
            ways = table[N][types - 1];
        }
        // otherwise N becomes are new highest calc
        else {
            ways = max_ways(highest_calc, N);
            highest_calc = N;
        }

        printf("%d\n", ways);
    }
}

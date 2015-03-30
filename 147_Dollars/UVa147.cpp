/* UVa problem: 146 - dollars
 *
 * Topic: Dynamic Programming
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *  Given a set of bills and coins determine how many ways to make change
 *  from values of 5 cents ... 300 dollars, with all values multiples of 5 cents.
 *
 * Solution Summary:
 *  For simplicty start by converting all input to integers and dividing by 0.05 because
 *  all denominations be 0.05 multipes. Use dynamic programming from top up
 *  Keep cache table in between test cases.
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
#define UNSET -1

using namespace std;

const int types = 11;
int currency[types] = {1, 2, 4, 10, 20, 40, 100, 200, 400, 1000, 2000};
int memoize[6001][types];


// fill in table
int ways(int N, int c) {
    if (N < 0)
        return 0;

    if (N == 0 || c == 0)
        return 1;

    int &cached = memoize[N][c];
    if (cached != UNSET)
        return cached;

    // update cache with sum of choosing/not choosing currency
    cached = ways(N, c-1) + ways(N - currency[c], c);
    return cached;
}

int main() {
    int N, result;
    float input;
    memset(memoize, -1, sizeof(memoize));

    while(scanf("%f", &input), (input)) {
        // convert to integer representation for simplicty
        N = input / 0.05;
        result = ways(N, types-1);

        // output value and result
        printf("%6.2f%17d\n", input, result);
    }
}

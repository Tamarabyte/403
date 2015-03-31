/* UVa problem: 147 - dollars
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
 *  all denominations be 0.05 multipes (be careful with the roudning
 *  error converting to integer). Use dynamic programming from top up
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
long long memoize[6001][types];


// fill in table
long long ways(int N, int c) {
    if (N < 0)
        return 0;

    if (N == 0 || c == 0)
        return 1;

    long long &cached = memoize[N][c];
    // update cache with sum of choosing/not choosing currency
    if (cached == UNSET)
        cached = ways(N, c-1) + ways(N - currency[c], c);

    return cached;
}

int main() {
    int N;
    long long result;
    float input;
    memset(memoize, UNSET, sizeof(memoize));

    while(scanf("%f", &input), (input != 0.00)) {
        // convert to integer representation for simplicty
        // add 0.05 to prevent rounding error when converting to integer
        N = (input / 0.05) + 0.5;
        result = ways(N, types-1);

        // output value and result
        printf("%6.2f%17lld\n", input, result);
    }
}

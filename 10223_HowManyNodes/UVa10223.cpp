/* UVa problem: 10223 - HowManyNodes
 *
 * Topic: Combinatorics
 *
 * Level: trivial
 *
 * Brief problem description:
 *  This one of the Catalan number problems listed in Competive Programming 3.
 *  The twist is you are given a nth Catalan number and have to determine n.
 *
 * Solution Summary:
 *  Maximum input is 4294967295 which includes up to the 19th Catalan number.
 *  I compute 1 .. 19 Catalan numbers, store them in an array and then for each
 *  input provide the matching index to get n.
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   http://www.math.uiuc.edu/~llpku/qtCatalan/qCatalan.html
 *   http://www.cplusplus.com/reference/climits/
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
#include <algorithm>

using namespace std;
typedef unsigned long ul;

ul numbers[20];

// formula referenced from Competitive Programming 3
// we memoize all catalan numbers we encounter while computing
ul cat(int n) {
    if (numbers[n])
        return numbers[n];

    double m = (double)n;
    return numbers[n] = (2*m*(2*m-1))/((m+1)*m) * cat(m-1);
}

int main() {
    ul cat_num;

    // precompute catalan numbers for retrieval from stdin
    memset(numbers, 0, sizeof(numbers));
    numbers[1] = 1;
    cat(19);

    while(scanf("%lu", &cat_num) != EOF) {
        for (int i = 0; i < 20; ++i)
            // output the associated catalan number
            if (cat_num == numbers[i]) {
                printf("%d\n", i);
                break;
            }
    }
}

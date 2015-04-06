/* UVa problem: 11955 - BinomialTheorem
 *
 * Topic: Arithmetic
 *
 * Level: trivial
 *
 * Brief problem description:
 *      Given the sum of two string varaibles to the power
 *      of k (k <= 50) expand into a sum of powers.
 *      Ex. (a+b)^2 = a^2+2*a*b+b^2
 *
 * Solution Summary:
 *      Straight forward application of the binomial theorem. I used
 *      the recursive algorithm given in Competitive Programming 3
 *      and used a memo table to cache each step. Because the coefficients
 *      for a power of 50 can be quite large, I used long longs to store coefficients.
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
#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;
typedef long long ll;

ll memo[50][50];

// adapted from Competitive Programming 3
ll binomial_coefficient(int n, int k) {
    // base case C(n, 0) or C(n, n)
    if (k == 0 || n == k)
        return 1;

    ll &cached = memo[n][k];
    if (cached)
        return cached;

    cached = binomial_coefficient(n-1, k-1) + binomial_coefficient(n-1, k);
    return cached;
}

int main() {
    int T, test_case = 0, n;
    string token, a, b;
    stringstream stream;
    memset(memo, 0, sizeof(memo));
    scanf("%d", &T);

    while(T--) {
        ++test_case;

        // parse input lines for variable names and power
        getline(cin, token, '(');
        getline(cin, a, '+');
        getline(cin, b, ')');
        scanf("^%d", &n);
        getline(cin, token);

        // special case where n=1
        printf("Case %d: ", test_case);
        if (n == 1) {
            printf("%s+%s\n", a.c_str(), b.c_str());
            continue;
        }

        // otherwise print out each term calculating the
        // binomial coefficient as we go
        int powA = n, powB=0;
        printf("%s^%d+", a.c_str(), powA);
        for(int k = 1; k < n; ++k) {
            ++powB;
            --powA;

            printf("%lld*%s", binomial_coefficient(n, k), a.c_str());

            if (powA > 1)
                printf("^%d", powA);

            printf("*%s", b.c_str());

            if (powB > 1)
                printf("^%d", powB);

            printf("+");
        }

        ++powB;
        printf("%s^%d", b.c_str(), powB);

        printf("\n");
    }

}

/* UVa problem: 991 - SafeSalutations
 *
 * Topic: Combinatorics
 *
 * Level: trivial
 *
 * Brief problem description:
 *   Given a number of people generate the feasible number of sets of handshakes
 *   that do not have any person crossing hands.
 *
 * Solution Summary:
 *   This is flagged as a Catalan Numbers problem in Competitive Programming 3.
 *   The input is very small (<= 10) so I compute catalan numbers in a
 *   recursive fashion and memoize them in an integer array.
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

int numbers[11] = {1};

// formula referenced from Competitive Programming 3
// we memoize all catalan numbers we encounter while computing
int cat(int n) {
    if (numbers[n])
        return numbers[n];

    float m = (float)n;
    return numbers[n] = (2*m*(2*m-1))/((m+1)*m) * cat(m-1);
}

int main() {
    int pairs, after=0;
    memset(numbers, 0, sizeof(numbers));
    numbers[1] = 1;

    while(scanf("%d", &pairs) != EOF) {
        // print a new line between test input
        if (after)
            printf("\n");
        after = 1;

        // calculate catalan numbers
        printf("%d\n", cat(pairs));
    }
}

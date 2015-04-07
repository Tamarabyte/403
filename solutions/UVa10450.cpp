/* UVa problem: 10450 - WorldCupNoise
 *
 * Topic: Combinatorics
 *
 * Level: trivial
 *
 * Brief problem description:
 * You're given a set of rules for how sequences are generated and asked
 * to find the number of possible sequences for a given step n.
 * Howard Cheng's hint says to find a recurrence relationship for this sequence.
 *
 * Solution Summary:
 * For the first 5 sequences we have (starting with n > 0):
 *   n = 1: 2
 *   n = 2: 3
 *   n = 3: 5
 *   n = 4: 8
 *   n = 5: 13
 * This is fibonaci's just offset by 2. I implemented fibonaccis
 * recurrence relation with this offset. For extra speed (not
 * needed for n < 51 but hey why not) I cache the results.
 *
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   http://www.cs.uleth.ca/~cheng/contest/hints.html
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
long cache[51];


// recurrence relation
// technically n != 0, but it felt safer this way
long recurrence(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return 2;
    if (n == 2)
        return 3;

    // retrive from cache if possible
    if (cache[n])
        return cache[n];

    // this is just fibbonacci's
    return cache[n] = (recurrence(n-1) + recurrence(n-2));
}

int main() {
    int testcases, n, current = 1;
    memset(cache, 0, sizeof(cache));
    scanf("%d", &testcases);

    while (testcases--) {
        scanf("%d", &n);
        printf("Scenario #%d:\n", current);
        printf("%ld\n\n", recurrence(n));
        ++current;
    }

}

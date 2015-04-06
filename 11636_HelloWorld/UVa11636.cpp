/* UVa problem: 11636 - HelloWorld
 *
 * Topic: Arithmetic
 *
 * Level: trivial
 *
 * Brief problem description:
 *  Given an input file with a positive integer on each line. Each number
 *  represents the number of lines "Hello World" appears in a row.
 *  Assuming the user is copy and pasting "Hello Word" how many paste
 *  operations occured to end up with that many lines.
 *
 * Solution Summary:
 *  I solved this by bitshifting from 1 until I hit >= the number. The number
 *  of bitshifts == the number of paste operations.
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

int main() {
    int test_case = 1, n, lines, pastes;

    while(scanf("%d", &n)) {
        if (n < 0)
            break;

        // we start with 1 line and 0 pastes
        lines = 1;
        pastes = 0;

        // bitshift until we reach our number
        while(lines < n) {
            lines <<= 1;
            ++pastes;
        }

        printf("Case %d: %d\n", test_case, pastes);
        ++test_case;

    }
}

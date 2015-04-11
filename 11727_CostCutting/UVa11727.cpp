/* UVa problem: 11727 - CostCutting
 *
 * Topic: Other
 *
 * Level: trivial
 *
 * Brief problem description:
 *  You are given 3 input numbers and have to output the
 *  middle one. That's literally it.
 *
 * Solution Summary:
 *   It can't get much more straighforward the comparisons.
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
    int tests, s1, s2, s3, survivor, n = 0;
    scanf("%d", &tests);
    
    while(tests--) {
        ++n;
        scanf("%d %d %d", &s1, &s2, &s3);
        if ((s2 < s1 && s1 < s3) || (s3 < s1 && s1 < s2)) survivor = s1;
        else if ((s1 < s2 && s2 < s3) || (s3 < s2 && s2 < s1)) survivor = s2;
        else survivor = s3;
        printf("Case %d: %d\n", n, survivor);
        
    }
}
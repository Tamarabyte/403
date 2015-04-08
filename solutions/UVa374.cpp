/* UVa problem: 374 - BigMod
 *
 * Topic: Number Theory
 *
 * Level: trivial
 *
 * Brief problem description:
 *  Given B, P and M, where B and P are longs and M is an integer.
 *  Quickly calculate B^P mod M.
 *
 * Solution Summary:
 *  B^P will overflow even a long long, so we resort to a divide and
 *  conquer method using the principle:
 *  (base^exp) % m = ((base^(exp/2) % m) * (base^(exp/2) % m)) % m
 *  If exp is odd we include an extra term (base ^ 1 % m).
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

int modPow(long base, long exp, int m) {
    // base cases
    if (exp == 0)
        return 1;

    if (exp == 1)
        return base % m;

    // referenced from Competitive Programming 3
    //(base^exp) % m = ((base^(exp/2) % m) * (base^(exp/2) % m)) % m
    long answer = modPow(base, exp/2, m);
    answer *= answer;

    // if the exponent is odd we ave to add one more modPow
    if (exp % 2 == 1)
        answer *= modPow(base, 1, m);

    answer = answer % m;

    return (int)answer;
}

int main() {
    long B, P;
    int M, result;

    while(scanf("%ld\n%ld\n%d", &B, &P, &M) != EOF) {

        if (M == 1)
            result = 0;
        else
            result = modPow(B, P, M);

        printf("%d\n", result);
    }

}

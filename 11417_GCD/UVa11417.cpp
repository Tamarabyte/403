/* UVa problem: 11417 - GCD
 *
 * Topic: Arithmetic
 *
 * Level: trivial/non-trivial: T
 *
 * Brief problem description:
 *   Find the sum of all GCDs in an array.
 *
 * Solution Summary:
 *  Used the GCD algorithm.
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

int gcd(int i, int j) {
    return j == 0 ? i : gcd(j, i % j);
}

int main() {
    int n;
    long sum;
    
    while(scanf("%d",  &n), (n)) {
        // gcd of all numbers + 1 is one
        // so we don't have to do the first iteration
        sum = n-1;
        
        for (int i = 2; i < n; ++i)
            for (int j = i+1; j <= n; ++j) 
                sum += gcd(j, i); // faster to put the largest number first
        
        printf("%ld\n", sum);
    }
}


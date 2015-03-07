/* UVa problem: 729 - HammingDistanceProblem
 *
 * Topic: Backtracking
 *
 * Level: trivial/non-trivial: N
 *
 * Brief problem description:
 *   Given a hamming distance and a size, output in lexigraphical order all binary strings
 *   of that size that are that hamming distance from the all zero bit string.
 *
 * Solution Summary:
 *  Solved with bitsets and next_permutation (which conveniently permutates in lexical order)
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   Pointed to next_permutation:
 *   http://stackoverflow.com/questions/17396222/how-to-generate-all-permutations-of-an-array-in-sorted-order
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
#include <bitset>
#include <algorithm>

using namespace std;
int bits[16];
int N, dif, curdif, iteration;

int main() {
    int testcases;

    scanf("%d", &testcases);
    while(testcases--) {
        scanf("%d %d", &N, &dif);
        
        for(int i = 0; i < N-dif; ++i) 
            bits[i] = 0;
        
        for(int i = N-dif; i < N; ++i) 
            bits[i] = 1;
        
        do {
            for(int i = 0; i < N; ++i) 
                printf("%d", bits[i]);
            printf("\n");
        } while(next_permutation(bits, bits+N));
        
        if (testcases)
            printf("\n");
    }
}
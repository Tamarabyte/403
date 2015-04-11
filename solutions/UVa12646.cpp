/* UVa problem: 12646 - ZeroOrOne
 *
 * Topic: Other
 *
 * Level: trivial
 *
 * Brief problem description:
 *  You are given a list of 3 bits 
 *  and you have to decide which is the
 *  odd one out or if they're all the same.
 *
 * Solution Summary:
 *  Just did a simple xor & operation. I want to see how short
 *  and fast I could make my code. Still only 390 though, I will
 *  have to experiment for faster implementations.
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
    int a, b, c;
    while(scanf("%d %d %d", &a, &b, &c) != EOF) {
        if ((a ^ b)&(a ^ c)) printf("A\n");
        else if ((a ^ b)&(b ^ c)) printf("B\n");
        else if ((a ^ c)&(b ^ c)) printf("C\n");
        else printf("*\n");
    }
}
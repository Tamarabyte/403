/* UVa problem: 10931 - Parity
 *
 * Topic: Arithmetic
 *
 * Level: trivial/non-trivial: T
 *
 * Brief problem description:
 *  Count the number of 1's in a numbers binary representation.
 *
 * Solution Summary:
 *  Bitset made this problem trivial. I read in the number, saved
 *  it in a bitset, counted the 1s and output the binary number.
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
#include <bitset>

using namespace std;

int main() {
    unsigned long number;
    int parity, i;
    
    while (scanf("%lu", &number), number) {
        
        parity = 0;
        bitset<31> binary(number);
        string binary_string = binary.to_string();
        
        // Count the 1s
        for (i=0; i < 31; ++i) 
            parity += binary[i];

        printf("The parity of ");
        
        // Skip over all the leading 0's
        i = 0;
        while (binary_string[i] == '0' && i < 31)
            ++i;
        
        // Output the binary number
        for (; i < 31; ++i) 
            printf("%c", binary_string[i]);
        
        printf(" is %d (mod 2).\n", parity);
    }
}
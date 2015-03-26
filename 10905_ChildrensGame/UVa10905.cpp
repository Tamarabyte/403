/* UVa problem: 10905 - ChildrensGame
 *
 * Topic: Sorting
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *   You are given a list of numbers and you have to combine them to get the largest number.
 *
 * Solution Summary:
 *   Implemented a custom comparator. At first I tried comparing by digits
 *   and I ran into problems with enforcing strict ordering. Then I realized
 *   I could just compare the concatted numbers instead of the numbers to eachother.
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
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

bool comp(string a, string b) {
    string ab = a + b;
    string ba = b + a;
    
    if (ab > ba)
        return true;
        
    return false;
}

int main() {
    int N;
    string number;
    vector<string> numbers;
    
    while(scanf("%d", &N), N) {
        
        numbers.clear();
        
        // read in numbers into a vector
        for (int i = 0; i < N; ++i) {
            cin >> number;
            numbers.push_back(number);
        }
        
        // combine two strings and compare the combined value
        // the one that goes first in the greater combination goes first
        // in the ordering
        sort(numbers.begin(), numbers.end(), comp); 
        
        for (int i = 0; i < N; ++i) 
            printf("%s", numbers[i].c_str());
        
        printf("\n");
    }
}

/* UVa problem: 11491 - ErasingAndWinning
 *
 * Topic: Other
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *  Delete X numbers from a number to end up with the biggest possible number. 
 * Solution Summary:
 *  Greedy solution. Always delete a number if it's adjacent number is larger.
 *  The trick is shifting backwards afterwards. Initially I iterated through an array
 *  but that was too slow. With linked lists I can delete and move back one easily. 
 *  preventing iterations.
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
#include <string>
#include <iostream>
#include <list>
using namespace std;

int main() {
    int digits, erase;
    int N = 100002;
    char numstr[N];
    
    list<int> number;
    list<int>::iterator cur, next;
    
    // for each test case
    while(scanf("%d %d", &digits, &erase), (digits || erase)) {

        scanf("%s", numstr);
        //printf("number %s\n", numstr);
        
        // transform into a linked list to take advantage of fast deletes
        number.clear();
        for(int i = 0; i < digits; i ++)
            number.push_back(numstr[i]-'0');
        

        cur = next = number.begin();
        next++;
        while(erase) {

            // start with pointers to the current and next node
            // if the current is less than the next node then use
            // the next node to access the new previous node and
            // continue from there
            if  ((*cur) < (*next) || next == number.end()) {
                
                number.erase(cur);
                
                // special case to handle the beginning of the list
                if (next == number.begin())
                    cur = next;
                else
                    cur = --next;
                ++next;
                --erase;            
            }
            
            else {
                ++cur;
                ++next;
            }
        }
        
        for (auto& digit : number) 
            printf("%d", digit);
        
        printf("\n");
    }
}

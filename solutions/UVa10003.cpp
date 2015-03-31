/* UVa problem: 10003 - CuttingSticks
 *
 * Topic: Dynamic Programming
 *
 * Level: trivial
 *
 * Brief problem description:
 *   Given a stick of a particular lengths and a number of cuts
 *   to be made to the stick. Find the cutting sequence that is the cheapest.
 *   (Cutting costs are based on the size of the stick)
 *
 * Solution Summary:
 *   Use a top-down dynamic programming approach. As suggested in Competitive Programming 3 
 *   cuttings of a stick can be identified by their start/end points. By storing endpoints
 *   in an array in increasing order and adding 0 and stick initial length to this
 *   array we have a means of descriping each stick in the result. We can then memoize
 *   on startpoint/endpoint where startpoint and endpoint are indices in our sequence
 *   of start/cuts/endpoint. The min cost of each cut is the cost of making the cut
 *   plus the cost of making each required cut in its resultant halves.
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
#include <cstring>
#include <algorithm>

#define MAX_SEQ 52
#define INF 999999
#define UNSET -1

using namespace std;

int cuts, length;
int sequence[MAX_SEQ];
int memo[MAX_SEQ][MAX_SEQ];

int cut(int left, int right) {
    
    // base case, no more cuts to apply
    if (left + 1 == right) 
        return 0;
    
    // check the cache for a stick with the given startpoint/endpoint
    int &cached = memo[left][right];
    if (cached != UNSET)
        return cached;
    
    // otherwise the cost to cut = cost for cutting 
    // the current stick + the sticks that result from this cut
    int cost_for_current = sequence[right] - sequence[left];
    cached = cut(left, left+1) + cut(left+1, right) + cost_for_current;
    
    for(int i = left + 2; i < right; ++i)
        cached = min(cached, cut(left, i) + cut(i, right) + cost_for_current);
    
    return cached;
}

int main() {
    int result;
    
    while(scanf("%d", &length), length) {
        // wipe the memoization table
        memset(memo, UNSET, sizeof(memo));
        
        // read in cut sequence
        scanf("%d", &cuts);
        
        // start point of the stick
        sequence[0] = 0;
        
        // each cut point
        for(int i=1; i <= cuts; ++i) 
            scanf("%d", &(sequence[i]));
        
        // endpoint of the stick
        sequence[cuts+1] = length;
        result = cut(0, cuts+1);

        printf("The minimum cutting is %d.\n", result);
    }
}
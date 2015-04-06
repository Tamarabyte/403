/* UVa problem: 11330 - AndysShoes
 *
 * Topic: Combinatorics
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *  Find the minimum swaps neccesary to swap the shoes
 *  so that that pairs of shoes are beside eachother.
 *
 * Solution Summary:
 *  This reminded me of Erasing and Winning, and after
 *  trying a few implementations I am convinced that DP is overkill
 *  and tried for the AC by going through the vector of shoes 2 at a time and
 *  if the shoes don't match swapping the second shoe
 *  with it's match in the list (greedy strategy).
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
#include <vector>
#include <algorithm>

using namespace std;
vector<int> shoes;
typedef pair<int, int> ii;

int main() {
    int testcase, pairs, shoe, index, temp, swaps;
    scanf("%d", &testcase);

    while(testcase--) {
        scanf("%d", &pairs);
        shoes.clear();
        swaps = 0;

        // place shoes in vector
        for (int i = 0; i < 2*pairs; ++i) {
            scanf("%d", &shoe);
            shoes.emplace_back(shoe);
        }

        // if shoes are beside eachother we don't have to do anything
        for (int i = 0; i < 2*pairs - 1; i=i+2) {
            if (shoes[i] == shoes[i+1])
                continue;

            // otherwise swap with the next occurance of the shoe
            index = find(shoes.begin()+i+1, shoes.end(), shoes[i]) - shoes.begin();
            temp = shoes[i+1];
            shoes[i+1] = shoes[index];
            shoes[index] = temp;
            ++swaps;
        }

        printf("%d\n", swaps);
    }
}



/* UVa problem: 10026 - ShoemakersProblem
 *
 * Topic: Sorting
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *   For each job the number of days it takes to complete and a 
 *   penalty associated for each day spent in queue is given. Output
 *   the optimal order for the jobs. If there is a tie rely on lexiographical order
 *   to break it.
 *   
 * Solution Summary:
 *   I used the hint given on Howard Chengs website 'sort by ratio'.
 *   I saved each 'job' as a pair of fine/days, index and wrote a compartor
 *   to order the greatest ratios first followed by lexiographically on the index.
 *
 * Used Resources:
 *   http://www.cs.uleth.ca/~cheng/contest/hints.html
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
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

using namespace std;

// order jobs with a higher ratio of cost/time first
// followed by whatever job was received first
bool comp(const pair<float, int>& a, const pair<float, int>& b) {
  if (a.first != b.first)
      return a.first > b.first;
  return a.second < b.second;
}

int main() {
    int testcases, lines, days, fine;
    vector<pair<float, int>> ratio;
    
    scanf("%d", &testcases);
    
    while(testcases--) {
        
        scanf("%d", &lines);
        
        // add each job found to the vector
        // as a pair of ratio/index so that after we sort
        // we can output the required index
        for(int i = 0; i < lines; i ++) {
            scanf("%d %d", &days, &fine);
            ratio.push_back(make_pair(float(fine)/days, i+1));
        }
        
        sort(ratio.begin(), ratio.end(), comp);
        
        // output index of jobs
        for (int j = 0; j < lines; j++) {
            printf("%d", ratio[j].second);
            if (j != lines-1)
                printf(" ");
            else
                printf("\n");
        }
        
        if (testcases!=0)
            printf("\n");
        
        ratio.clear();
    }
}

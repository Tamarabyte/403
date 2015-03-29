/* UVa problem: 668 - Parliament
 *
 * Topic: Other
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *  Given a number find the distinct set of addends for that number
 *  that has the largest possible product.
 *
 * Solution Summary:
 *  Greedy solution. We can immediately see that we don't want 1
 *  in any of our sets of addents as 1 does not add anything to
 *  the total product and would be better redistributed on another addend.
 *  Secondly the largest possible product of addends will
 *  be the largest possible set of addents. (see proof in reources).
 *  Using this we can find a solution in O(N) time but iterating through
 *  0 .. N and for each element adding it to the current sum and storing it in array, stopping when
 *  adding the next element would overtake N. At this point we distribute the remainder
 *  of elements in the array starting at the end of the array and working backwards until
 *  the remainer is spent.
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   Proof: https://cs.uwaterloo.ca/journals/JIS/VOL8/Doslic/doslic15.pdf
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
    int testcases, N, sum, remainder, i, index, partition_size;
    int partition[1001];
    
    scanf("%d", &testcases);
    
    while(testcases--) {
        
        scanf("%d", &N);
        
        // start at 2 because 1 cannot increase the product
        sum = 0;
        for (i = 2 ; sum <= N; ++i) {
            
            // if we've exceeded our desired number then we need to 
            // take the remainer prior to adding i and distribute
            // it amongst our current partition
            if (sum + i > N) {
                --i;
                
                remainder = N - sum;
                index = i - 2;
                partition_size = index + 1;
                
                // divide remainder by partition starting at the
                // highest numbers and iterating backwards circularly
                while (remainder--) {
                    ++partition[index];
                    index = (partition_size+index-1) % partition_size;
                }
                
                break;
            }
            partition[i-2] = i;
            sum += i;
        }
        
        // print out partition
        partition_size = i - 2 + 1;
        for (int i = 0; i < partition_size; ++i) {
            printf("%d", partition[i]);
            
            if (i+1 != partition_size)
                printf(" ");
        }
        
        printf("\n");  
        if (testcases)
            printf("\n");
    }
}
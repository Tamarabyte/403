/* UVa problem: 307 - Sticks
 *
 * Topic: Backtracking
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *  Given a list of stick pieces by length reconstruct the size of the original stick(s)
 *  such that all original sticks are equal length and the original sticks are the
 *  smallest possible length.
 *
 * Solution Summary:
 *  This is a backtracking problem. We know our answer has to be at least the
 *  size of the largest stick piece and can be no larger than the sum of all the stick
 *  pieces. We can discard any potential answers that don't give us an integer number
 *  of sticks (sum of pieces % goal != 0).
 *
 *  We can then backtrack with this goal in mind and see if it is possible to
 *  generate from given stick pieces. Our state is the current stick we are looking at,
 *  the number of sticks we have yet to make, and the remaining length to go on the
 *  current stick we are making. Our base case occurs when we have made
 *  all our sticks.

    We need to apply a lot of pruning to get this within the correct time.
 *  The pruning I applied is as follows:
 *  1. Sort the array so that we only check edges for larger -> smaller sticks,
 *     this prevents us from exploring a symetrical path from smallest -> largest
 *  2. We have to include at least every stick once, so if it is ever not possible to
 *     include a stick we should stop.
 *
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   Marcus Karpoff
 *     - gave me the idea of thinking of the sticks as a adj. matric which
 *       led to me sorting the sticks
 *   http://online-judge.uva.es/board/viewtopic.php?f=4&t=2582&start=15
 *     - ended up referencing the forum for the maximum number of sticks in input,
 *       I misread the question and assumed this was 50 and was getting a Runtime Error,
 *       forum cleared up that it's < 100*
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
#define UNSET -1

using namespace std;

int lengths[100];
bool visited[100];
int N, stick_size;

bool backtrack(int i, int remaining_len, int remaining_sticks) {

    // base case: we've made all our sticks
    if (!remaining_sticks)
        return true;

    // we've gone to far
    if (remaining_len  < 0) {
        return false;
    }

    // backtracking
    // we want to combine each stick piece with smaller pieces only
    // (this is so we don't try combinations in both directions)
    // see whether it is possible to make a stick using the
    // pieces
    bool possible = false;
    for (int j = i; j < N; ++j) {

        if (visited[j])
            continue;

        int new_remaining_len = remaining_len - lengths[j];

        // if we've fully built a stick
        // then decremented the required sticks
        // and begin again with remaining_length = stick_size
        if (new_remaining_len == 0) {
            visited[j] = true;
            possible = backtrack(0, stick_size, remaining_sticks - 1);
        }
        // otherwise continue backtracking
        else {
            visited[j] = true;
            possible = backtrack(j, new_remaining_len, remaining_sticks);
        }

        // if it's possible to make the stick
        // the stop and return (keep the stick piece)
        // marked as visited so we don't use it again
        if (possible)
            break;

        // otherwise unmark the stick piece
        // so that backtracking can try without it
        visited[j] = false;

        if (new_remaining_len == 0)
            break;

        // backtracked fully and couldn't include the piece in a stick
        if ((!possible && remaining_len == stick_size))
            break;
    }

    return possible;
}


int main() {
    int sum, required_sticks;
    bool result;

    while(scanf("%d", &N), N) {
        sum = 0;

        for (int i = 0; i < N; ++i) {
            scanf("%d", &lengths[i]);
            visited[i] = false;
            sum += lengths[i];
        }

        sort(lengths, lengths+N, greater<int>());

        for(stick_size = lengths[0]; stick_size < sum; ++stick_size) {

            // start length for our sticks must be an integer
            // so skip this length if this is not possible
            if (sum % stick_size != 0)
                continue;

            // number of sticks we started with
            required_sticks = sum / stick_size;

            // clear the visited nodes
            for (int i = 0; i < N; ++i)
                visited[i] = false;

            result = backtrack(0, stick_size, required_sticks);

            if (result)
                break;
        }

        printf("%d\n", stick_size);

    }
}

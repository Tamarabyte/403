/* UVa problem: 202 - RepeatingDecimals
 *
 * Topic: Arithmetic
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *  Given a fraction find the position and length of the
 *  repeating cycle after the decimal point when the fraction
 *  is converted into a decimal.
 *
 * Solution Summary:
 *  I used floyd cycle detection as described in Competitive Programming
 *  3 to solve this problem. My catch was that I forgot to adjust
 *  for finding cycles after the decimal point. Had to generate a test script
 *  for input 0..3000 / 1..3000 to catch my bug.
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
#include <utility>
#include <vector>

using namespace std;
typedef pair<int, int> ii;
vector<int> digits;
int denom;


// expansion - take remainer and multiply by 10 for next digit
int f(int num) {
    int remainder = num % denom;
    num =  remainder * 10;
    return num;
}

// long divides and stores digits in an array
void divide(int num, int length) {
    digits.clear();
    while (length--) {
        digits.push_back(num/denom);
        num = f(num);
    }
}

// adapted from Competitive Programming 3
ii floyd_cycle_detection(int x) {
    int tortoise, hare, cycle_length = 1, cycle_start = 0;

    // find k * cycle start
    // hare moves at double speed until tortoise = hare
    tortoise = f(x);
    hare = f(f(x));

    while (tortoise != hare) {
        tortoise = f(tortoise);
        hare = f(f(hare));
    }

    // find cycle start
    // hare and tortoise move at same speed
    hare = x;
    while (tortoise != hare) {
        tortoise = f(tortoise);
        hare = f(hare);
        ++cycle_start;
    }

    //find cycle length
    //hare moves, tortoise waits
    hare = f(tortoise);
    while (tortoise != hare) {
        hare = f(hare);
        ++cycle_length;
    }

    return ii(cycle_start, cycle_length);
}

int main() {
    int num, start, length, extra = 0;
    ii result;

    // read in input
    while(scanf("%d", &num) != EOF) {
        extra = 0;

        // compute before the decimal place value here
        // we are only interested in cycles after the decimal place
        scanf("%d", &denom);
        printf("%d/%d = ", num, denom);
        printf("%d.", num/denom);
        num = f(num);

        result = floyd_cycle_detection(num);

        start = result.first;
        length = result.second;

        divide(num, start+length + extra);


        // print output
        if (digits.size() == 0)
            printf("(0");

        for (int i = 0; i < (int)digits.size(); ++i) {

            if (i == start)
                printf("(");

            if (i == 50) {
                printf("...");
                break;
            }

            printf("%d", digits[i]);
        }
        printf(")\n   %d = number of digits in repeating cycle\n\n", length);
    }
}

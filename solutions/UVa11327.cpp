/* UVa problem: 11327 - EnumeratingRationalNumbers
 *
 * Topic: Number Theory
 *
 * Level: trivial
 *
 * Brief problem description:
 *   Given a number return the corresponding
 *   rational number corresponding to that position (1 indexed)
 *   in a sequence of rational numbers between 0 and 1
 *   ex. 0/1, 1/1, 1/2, 1/3, 2/3, 1/4, 3/4, 1/5...
 *
 * Solution Summary:
 *   I used a modified sieve to calculate all phi values from 1..20001
 *   (we know 20000 is the max denominator so we don't need phi values higher).
 *   These phi values give us the number of rational numbers present for that
 *   denominator. I use this to construct ranges mapping a start and n index
 *   to a denominator. When reading an index from input, I binary search
 *   these precomputed ranges until I find the one that encompasses the index.
 *   Then, starting at the beginning of the range I iterate through all
 *    possible numerators from 0..denom until gcd(num, denom) is
 *   1. When it is 1 I increment the position in the range until my
 *   position equals the desired index. Then I return the numerator associated
 *   with that index.
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   http://www.cs.uleth.ca/~cheng/contest/hints.html
 *   http://mathworld.wolfram.com/TotientFunction.html
 *   https://www.topcoder.com/community/data-science/data-science-tutorials/binary-search/
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
#include <bitset>
#include <vector>
#include <cassert>
#include <algorithm>


using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

ll MAX = 12158598920;
const int PHI_MAX = 200001;
int phi[PHI_MAX];


// struct for holding our ranges
// built by iterating our phi array
// stores the range for a denominator
struct RationalRange {

    ll start;
    ll stop;
    int denom;

    // we're only concerned with positions up to MAX
    // so truncate any ranges that overflow this.
    RationalRange(ll start, int counts, int denom)
        : start(start), denom(denom) {

        this->stop = start + counts;
        if (stop > MAX)
            stop = MAX;
    }

    int gcd(int i, int j) {
        return j == 0 ? i : gcd(j, i % j);
    }

    // given an index iterate all possible numerators
    // from 1..denominator. If we find a numerator
    // where gcd(num, denom) is 1 then we have found
    // the rational number for that position
    // increment the positions in this manner until we reach our desired index
    int get_num(ll index) {
        ll position = start;

        for (int num = 1; num <= denom; ++num) {

            if (gcd(num, denom) != 1) continue;

            if (position >= index)
                return num;

            ++position;
        }

        return -1;
    }
};

// holds the ranges of rational numbers sorted
// by start positions
vector<RationalRange> ranges;


// binary search our vector of ranges until
// we reach one that encompasses our desired position
int b_search(ll pos) {
    int mid, low = 0, high = ranges.size()-1;

    while (low <= high) {
        mid = low + (high - low)/2;
        if (ranges[mid].start <= pos && ranges[mid].stop > pos)
            return mid;

        if (ranges[mid].start < pos)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}


void modified_sieve () {
    int counts;

    // sieve for Euler Phi referenced
    // from Competitive Programming 3
    for (int i = 1; i < PHI_MAX; i++)
        phi[i] = i;

    for (int i = 2; i < PHI_MAX; i++) {
        if (phi[i] == i) {
            for (int j = i; j < PHI_MAX; j += i)
            phi[j] = (phi[j] / i) * (i - 1);
        }
    }

    // create our list of ranges using phi values
    // each phi value phi[n] represents the number of denomonaters
    // present that are equal to n
    ll index = 2;
    for (int i = 2; i < PHI_MAX; ++i) {
        if (index >= MAX) {
            printf("%lld > MAX (%lld) breaking!\n", index, MAX);
            break;

        }

        counts = phi[i];
        ranges.emplace_back(RationalRange(index, counts, i));
        index += counts;
    }

    return;
}

int main() {
    ll pos;
    int index;
    modified_sieve();

    while(scanf("%lld", &pos), pos) {
        // numbers in input are offset by 1
        --pos;

        // base cases, these aren't included in our ranges
        // because phi[0] is not defined and pos 0 has the
        // same denominator as position 1
        if (pos == 0) { printf("0/1\n"); continue; }
        if (pos == 1) { printf("1/1\n"); continue; }

        index = b_search(pos);
        RationalRange range = ranges[index];
        printf("%d/%d\n", range.get_num(pos), range.denom);
    }
}

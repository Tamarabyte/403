/* UVa problem: 11858 - FroshWeek
 *
 * Topic: Sorting
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *   Find the minimum number of swaps performed when sorting a list. Restrictive
 *   time limit means bubble sort will be too slow.
 *
 * Solution Summary:
 *   Found this in Competitive Programming 3 under inversion sort.
 *   It suggests using a merge sort and couting the number of inversions
 *   by adding the number of elements you supass in the lhs of the merge list
 *   when you choose an element of the right list over an element of the left list.
 *   Ran into a hiccup initially using ints because numbers can be upwards of 1 million.
 *
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   http://www.sorting-algorithms.com/merge-sort
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
#include <string.h>

using namespace std;
long long inversions;
long long students[1000001];
long long temp[1000001];

void merge_sort(long long start, long long n) {
    
    // don't sort single element lists
    if (start + 1 == n)
        return;

    //printf("start: %d - end: %d\n", start, n);
    long long m = (start + n)/2;

    // recursive sorts
    merge_sort(start, m);
    merge_sort(m, n);
    
    long long i = start;
    long long k = start;
    long long j = m;
    
    // create temp array for merging
    for(long long l = start; l < m; ++l)
        temp[l] = students[l];
        
    // merge based on order
    while (i < m && j < n) {
        if (students[j] < temp[i]) {
            students[k++] = students[j++];
            // add to the inversion counter by the size of the left sublist
            inversions += m-i;
        }
        else {
            students[k++] = temp[i++];
        }
    }

    // include any remaining of the first half
    while (i < m) {
        students[k++] = temp[i++];
    }
}

int main() {
    long long n;

    while (scanf("%lld", &n) != EOF) {
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &students[i]);
        }
    
        inversions = 0;
        merge_sort(0, n);
        
        printf("%lld\n", inversions);
    }
}
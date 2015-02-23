/* UVa problem: 11512 - GATTACA
 *
 * Topic: Strings
 *
 * Level: trivial/non-trivial: trivial
 *
 * Brief problem description:
 * Find the longest repeated substring in a string and output
 * it plus the number of times it occurs.
 *
 * Solution Summary:
 * It was suggested on the course website that we use a suffix array for this problem.
 * I relied heavily on the implementation of the suffix array from competitive programming 3
 * and used the suffix array to fill out a longest common prefix table. The longest repeating substring
 * starts at the index in the suffix array corresponding to the index of the largest value in the lcp table.
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
#include <iostream>
#include <string>
#include <algorithm>
#define MAX_N 1001

using namespace std;

int n;
int rank_arr[MAX_N];
int temp_rank[MAX_N];
int suff_arr[MAX_N];
int temp_suff[MAX_N];
int freq_table[MAX_N];

// adapted from Competitive Programming 3
// build lcp table
void computeLCP(int *lcp, const char* sequence) {
    lcp[0] = 0;

    for (int i = 1; i < n; i++) {
        // default value // compute LCP by definition // always reset L to 0 // same L-th char, L++
        int L = 0;
        // compute LCP by definition
        while (sequence[suff_arr[i] + L] == sequence[suff_arr[i-1] + L]) {
            L++;
            lcp[i] = L;
        }
    }
}

// adapted from Competitive Programming 3
// counting sort of suffix array
void countingSort(int k) {
    int index, sum, maxi;
    maxi = max(300, n);

    // clear table
    memset(freq_table, 0, sizeof(freq_table));

    // count frequency of each rank
    for (int i = 0; i < n; i++) {
        index = i + k < n ? rank_arr[i+k] : 0;
        freq_table[index]++;
    }

    sum = 0;
    for (int i = 0; i < maxi; i++) {
        int temp = freq_table[i];
        freq_table[i] = sum;
        sum += temp;
    }

    // shuffle the suffix array if neccesary
    for (int i = 0; i < n; i++) {
        index = suff_arr[i]+k < n ? rank_arr[suff_arr[i]+k] : 0;
        temp_suff[freq_table[index]++] = suff_arr[i];
    }

    // update the suffix array
    for (int i = 0; i < n; ++i) {
        suff_arr[i] = temp_suff[i];
    }
}

// adapted from Competitive Programming 3
// constructing the suffix array
void constructSA(const char *sequence) {

    // initial rankings
    for (int i = 0; i < n; ++i)
        rank_arr[i] = sequence[i];

    // set suffix substrings in initial order
    for (int i = 0; i < n; ++i) {
        suff_arr[i] = i;
    }

    for (int k = 1; k < n; k <<= 1) {
        // radix sort based on the second item
        countingSort(k);
        // stable sort based on the first item
        countingSort(0);
        temp_rank[suff_arr[0]] = 0;
        int r = 0;
        // if our two suffixes are the same then their ranks are the same
        for (int i = 1; i < n; ++i) {

            if (rank_arr[suff_arr[i]] == rank_arr[suff_arr[i-1]] &&
                rank_arr[suff_arr[i]+k] == rank_arr[suff_arr[i-1]+k]) {
                temp_rank[suff_arr[i]] = r;
            }
            else {
                temp_rank[suff_arr[i]] = ++r;
            }
        }

        // update rank array
        for (int i = 0; i < n; ++i)
            rank_arr[i] = temp_rank[i];

        if (rank_arr[suff_arr[n-1]] == n-1)
            break;
    }
}

int main() {

    int testcases, num;
    string sequence;
    int *lcp;

    scanf("%d", &testcases);
    while(testcases--) {

        cin >> sequence;
        sequence = sequence + "$";
        n = sequence.length();

        lcp = new int[n]();

        constructSA(sequence.c_str());
        computeLCP(lcp, sequence.c_str());

        // find the index of the largest value in the lcp
        size_t max_index = 0;
        for (int i = 0; i < n; ++i) {
            if (lcp[i] > lcp[max_index])
                max_index = i;
        }

        if (lcp[max_index] == 0) {
            printf("No repetitions found!\n");
            continue;
        }

        // go through the table counting substrings
        num = 0;
        for (int i = 0; i < n; i ++) {
            if (suff_arr[i] + lcp[max_index] >= n)
                continue;

            if (sequence.substr(suff_arr[i], lcp[max_index]) == sequence.substr(suff_arr[max_index], lcp[max_index]).c_str()) {
                num++;
            }
        }
            printf("%s %d\n", sequence.substr(suff_arr[max_index], lcp[max_index]).c_str(), num);



        delete[] lcp;
    }

}
